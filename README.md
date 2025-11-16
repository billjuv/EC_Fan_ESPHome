# EC Fan Control using ESP32, ESPHome and MQTT

This project allows for ESP32/WiFi control of 10V EC Fans which use USB-C type cables (i.e. AC Infinity ('AIS') or Vivosun ('SGS')). The PWM signal (duty cycle) is sent to the fan to control the fan speed and, if available on the fan, the tach speed (RPM) is returned. The ESP32 microcontroller is powered directly from the 10 volts supplied by the fan through the USB cable and communicates to an MQTT broker (local or cloud) through WiFi. No other cabling is needed.

This was designed for use in a mushroom grow operation in shipping containers where WiFi communication to the controller was desired instead of long cable runs. The controller is a Raspberry Pi 4 running Mycodo, Mosquitto for MQTT, and NodeRed. Fan control is done through a NodeRed Dashboard (2.0) though could also be done through Mycodo.

### Parts Used:
- Custom PCB board with logic level shift circuitry for safe GPIO voltages
- ESP32 DevKit v1 board (chosen for stronger WiFi than C3)
- MP1584EN DC-DC buck converter - 10v in, set to 5v out - to power ESP32 (mounted on bottom of board)
- USB-C header cable (box mounted)
- Custom 3d printed enclosure

### Included in this project:
- Example ESPHome YAML code
- Gerber files for PCB board
- 3d print files for the box
- Links to parts
- Example NodeRed flow information
  
<img src=Attachments/IMG_1472.jpg width="50%"/>

<img src=Attachments/IMG_1470.jpg width="50%"/>

<img src=Attachments/IMG_1486.jpg width="50%"/>

<img src=Attachments/IMG_1493.jpg width="50%"/>

<img src=Attachments/IMG_1494.jpg width="50%"/>

<img src=Attachments/IMG_4527.jpg width="50%"/>

[Amazon link to cables below][def]
<img src=Attachments/cable.jpg width="50%"/>

<img src=Attachments/IMG_4349.jpg width="50%"/> 
Hole sizes for above cable mount


### As of 11/25 still need ESPHome 12-2024 or older and the 'arduino' framework to work
  

https://github.com/billjuv/EC_Fan_ESPHome/blob/main/README.md

[def]: https://www.amazon.com/Female-Waterproof-Terminal-Pigtail-Extension/dp/B0D7CN4BTV/ref=sr_1_1?crid=22DIPVZJ6NLNA&dib=eyJ2IjoiMSJ9.5A5gh8wlE1dA5xzyWRfnF6wJ0fd9cFGKaGoMoL32RONrxG9_nN8LmJ9rJli3ujotLw90tzZNpYxllE3eMCpda7KoQPOh_-vPp3rROVUxTw11IfYGYRkTlLA7TaCoP3jR.uXNtln_9dJgcMFb5AaFasS38uiNJQxI2SMAjDUyGoKk&dib_tag=se&keywords=xiwai%2B5pcs%2FSet&qid=1761968034&sprefix=xiwai%2B5pcs%2Fset%2Caps%2C101&sr=8-1&th=1