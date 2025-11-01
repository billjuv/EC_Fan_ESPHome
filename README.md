# EC Fan Control using ESP32, ESPHome and MQTT

This project allows for ESP32/WiFi control of 10V EC Fans which use USB-C type cables (i.e. AC Infinity or Vivosun). The PWM signal (duty cycle) is sent to the fan to control the fan speed and, if available on the fan, the tach speed (RPM) is returned. The ESP32 microcontroller is powered directly from the 10 volts supplied by the fan through the USB cable and communicates to an MQTT broker (local or cloud) through WiFi. No other cabling is needed.

It was designed for use in a mushroom grow operation in shipping containers where WiFi communication to the controller was desired over long cable runs. 

### Parts Used:
- Custom PCB board with logic level shift circuitry for safe GPIO voltages
- ESP32 DevKit v1 board (chosen for stronger WiFi than C3)
- Power Buck converter - 10v in, 5v out to power ESP32 (mounted on bottom of board)
- USB-C header cable (box mounted)
- 


### Included in this project:

- ESPHome YAML code
- Gerber files for PCB board
- 3D print files for the box
- Links to parts
- Example NodeRed flow information
  

  
Body  
  
~~Body Strikethrough ~~  

https://github.com/billjuv/EC_Fan_ESPHome/blob/main/README.md
