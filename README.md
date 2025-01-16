
# ESP8266 LED Control Project

This project demonstrates how to control an LED using an ESP8266 microcontroller. The LED's state (ON/OFF) and brightness can be controlled via a web interface hosted by the ESP8266. The ESP8266 also creates its own Wi-Fi network for easy access.

## Features

- Turn the LED ON or OFF using web-based buttons.
- Adjust LED brightness with a slider.
- ESP8266 creates a self-hosted Wi-Fi network with a custom SSID and password.
- Accessible via any device with a browser (smartphone, laptop, etc.).


## Hardware Requirements
- ESP8266 microcontroller

- 1 x LED

- 1 x Resistor (220 ohms)

- Breadboard and jumper wires.

## Software requirement
- Arduino IDE with ESP8266 board support.
## Wiring digram
- ESP8266 Pin --> LED Pin

- D1 (GPIO5) -> Anode (+)

- GND -> Cathode (-)


## Installation and Usage
1. Clone or Download the Repository:

   git clone https://github.com/Satyamjha001/ESP8266-LED-Control.git

2. Open the Project in Arduino IDE:

   Open the Led_control.ino file in Arduino IDE.

3. Install Required Libraries:

   ESP8266WiFi

   ESP8266WebServer

   ArduinoJson

   These can be installed from the Arduino Library Manager.

4. Upload the Code:

   Connect your ESP8266 to your computer.

   Select the correct board and port in Arduino IDE.

   Click Upload to flash the code to the ESP8266.

5. Connect to the Wi-Fi Network:

   On your device, connect to the Wi-Fi network created by the ESP8266:

      SSID: ESP8266_AP

      Password: 12345678

6. Access the Web Interface:

   Open a browser and enter the IP address: 192.168.4.1

Use the buttons and slider to control the LED.

## Customization
Change Wi-Fi Credentials:
Modify the ssid and password variables in the code.

Adjust Pin Configuration:
Update the ledPin variable if you're using a different GPIO pin.
## License
This project is licensed under the [MIT](https://choosealicense.com/licenses/mit/) License. See the LICENSE file for details.



## Acknowledgments
- Arduino community for their excellent support and libraries.

- Inspiration from IoT projects and enthusiasts worldwide.
