# WiFi-Servo-Motor-Position-Control-
  This project is a wireless servo motor control system that integrates embedded programming, feedback control, and Python-based communication. The system uses a 10-bit ADC to measure potentiometer voltage from the servo motor and provide real-time angle feedback. A closed-loop Proportional (P) controller is implemented to regulate servo position, with controller gain tuned experimentally to improve system stability and response.
  The system communicates wirelessly using an ESP8266 operating in WiFi Access Point (AP) mode with a custom communication protocol. A Python-based client is used to send control commands, adjust controller parameters, and receive feedback, enabling flexible wireless control and automated testing. System performance is evaluated using linear regression analysis to analyze errors caused by ADC nonlinearity and noise.

->Key Knowledge & Skills Applied
  - Embedded programming using Arduino / ESP8266
  - Closed-loop P control with real-time feedback
  - ADC signal analysis and potentiometer-based angle measurement
  - Controller gain tuning for stability and response improvement
  - Custom WiFi (AP mode) communication protocol
  - Python-based client development for system control
  - Linear regression analysis for error evaluation
