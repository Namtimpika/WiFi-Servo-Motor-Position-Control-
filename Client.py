import socket
import struct

ESP_IP = "192.168.4.1"  
ESP_PORT = 33

Start_byte = 0xAA
Stop_byte = 0x55

def send_data(command, value=1):
    data = struct.pack("!BBHB", Start_byte, ord(command), value,Stop_byte)
    print(f"Data to send: {data.hex()}")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.settimeout(1)
        s.connect((ESP_IP, ESP_PORT))
        s.sendall(data)

        try:
            response = s.recv(5)  
            print(f"Raw Response: {response.hex()}")

            start, cmd, value_received, stop = struct.unpack("!BBHB", response)

            if start == Start_byte and stop == Stop_byte and cmd == ord('R'): 
               print(f"Received -> Command: {chr(cmd)}, Servo Position: {round((value_received - 93.612) / 5.144)} degrees")
            else:
                print("Error: Incomplete response received.")
        except Exception as e:
            print(f"Error: {e}")


while True:
    user_input = input("Enter command (P<angle> | G<gain> | R to Read): ").strip().upper()
    
    if user_input.startswith("P"):
        try:
            value = int(user_input[1:])  
            send_data('P', value)
        except ValueError:
            print("Invalid angle. Please enter a number (e.g., P150).")
    elif user_input.startswith("G"):
        try:
            #raw_value = float(user_input.split[1:].strip())
            raw_value = float(user_input[1:])
            value = int(raw_value * 1000)
            send_data('G', value)
        except ValueError:
            print("Invalid gain. Please enter a number (e.g., G2).")
    elif user_input == "R":
        send_data('R') 
    else:
        print("Invalid command. Use 'P<angle>', 'G<gain>', 'R' or to Read.")

    
