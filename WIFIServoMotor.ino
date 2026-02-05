#include <ESP8266WiFi.h>
#include <Servo.h>

// ตั้งค่า WiFi Access Point
const char *ssid = "ESP_servo";
const char *password = "987654321";
WiFiServer server(33);  

WiFiClient client;

Servo myservo;

float gain = 1.0; 
int setpoint = 90;
float feedback = 0.0;
float error = 0.0;
float output = 0.0;
float Normalize_feedback = 0.0;
float Normalize_setpoint = 0.0;

void setup() {
  Serial.begin(115200);
  myservo.attach(D3,500,2500);  

  // เริ่มต้น WiFi AP Mode
  WiFi.softAP(ssid, password);
  server.begin();
  delay(100);

}

void loop() {
  int raw_feedback = analogRead(A0);
  feedback = constrain(((raw_feedback - 93.612) / 5.144),0,180);
  Serial.print(feedback);
  Serial.print(" ");

  if (!client || !client.connected()) {
    client = server.available();  // wait for new Client 
  } 
  
  if (client) {
    if (client.available() >= 5) {  // received 5 byte data
      byte data[5];
      client.read(data, 5);
      client.flush();  // ล้างข้อมูลที่ค้าง
      Serial.print("Received: ");

      if (data[0] == 0xAA && data[4] == 0x55){
        for (int i = 1; i < 4; i++) {
                Serial.print(data[i], HEX);  // show in  hexadecimal
                Serial.print(" ");  
        }
        Serial.println(); 

        char command = data[1];  // Byte 2
        int new_value = (data[2] << 8) | data[3];  // Byte 3-4
        Serial.printf("Received Command: %c, Value: %d\n", command, new_value);

        if (command == 'P') {  // Controlled servo motor position
          setpoint = constrain(((new_value + 4.8571)/1.0095), 0, 180);
  
        } else if (command == 'G') { 
          gain = (new_value/1000.0);

        } else if (command == 'R') { 
          byte response[5];

          response[0] = 0xAA; //startbyte
          response[1] = 'R';  // confirmed that recieved R
          response[2] = raw_feedback >> 8;  // High byte
          response[3] = raw_feedback & 0xFF;  // Low byte
          response[4] = 0x55;  // stopbyte

          client.write(response, 5);  // Send 5 byte data

          Serial.print("Response Sent: ");
            for (int i = 0; i < 5; i++) {
            Serial.print(response[i], HEX);  // show in  hexadecimal
            Serial.print(" ");  // 
            }
            Serial.println();  // 
        } 
      }
      }
  }
          Normalize_feedback = feedback/180.0;
          Normalize_setpoint = setpoint/180.0;
          error = Normalize_setpoint - Normalize_feedback;

          output = constrain((Normalize_feedback + (gain * error))*180, 0, 180);
          myservo.write(output);
          
      Serial.print(output);
      Serial.print(" ");
      Serial.print(setpoint);
      Serial.print("\n"); 

      delay(10);

}

  

