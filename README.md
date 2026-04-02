# Fan-Powered EC Fan Control using ESP32, ESPHome and MQTT

This project enables ESP32/WiFi control of 10V EC fans that use USB-C type cables, such as those made by AC Infinity (AIS) or Vivosun (SGS). A PWM signal (duty cycle) is sent to the fan to control speed, and if supported by the fan, the tach signal (RPM) is returned. 

The ESP32 is powered directly from the 10V supplied by the fan through the USB-C cable and communicates with an MQTT broker via WiFi — no additional wiring is needed. The logic level shift circuitry used on this board are from [Kyle Gabriel's](https://github.com/kizniche) (Mycodo) fan control boards, modified for stand-alone use.

This was designed for a mushroom grow operation in shipping containers where WiFi control was preferred over long cable runs. The controller is a Raspberry Pi 4 running Mycodo, Mosquitto (MQTT broker), and Node-RED. Fan control is handled through a Node-RED Dashboard 2.0, though Mycodo could also be used.

---
## Overview

You can safely control the PWM speed of EC fans supplied with 10VDC via USB-C cable — such as AC Infinity ("UIS") or Vivosun ("SGS") fans, and possibly others — without the need for proprietary controllers.

### Tested and Verified

| Fan | PWM Control | Tach (RPM) |
|-----|-------------|------------|
| AC Infinity Airlift S Series Shutter Fan | ✅ | ✅ |
| AC Infinity Cloudray S6 6" Clip Fan | ✅ | ❌ |
| Vivosun AeroWave E6 Gen2 6" Clip Fan | ✅ | ❌ (larger models unknown) |

Testing was done using a Raspberry Pi 4 with Mycodo, and ESP32 boards with ESPHome and MQTT.

---

## What's Included

- ESPHome YAML configuration (example)
- Schematic
- Gerber files for the custom PCB
- 3D print files for the enclosure
- Links to parts
- Node-RED flow (EC_Fan.json in the NodeRed folder)

---

## Parts Used

| Part | Notes |
|------|-------|
| Custom PCB | Includes logic level shift circuitry for safe GPIO voltages |
| ESP32 DevKit v1 | Chosen for stronger WiFi than the C3 variant |
| MP1584EN DC-DC buck converter | Steps 10V down to 5V to power the ESP32 (mounted on PCB underside) |
| USB-C header cable | Box mounted |
| JST-PH 4-pin header | Through-hole for above cable |
| Transisters 2N3904(2)  | Resistors - 1k(2),10k(2), 3.3k(1)
| Custom 3D printed enclosure | Print files included |

---

## Hardware Photos

<img src=Attachments/IMG_1707.jpg width="50%"/>

<img src=Attachments/IMG_1472.jpg width="50%"/>

<img src=Attachments/IMG_1470.jpg width="50%"/>

<img src=Attachments/IMG_1493.jpg width="50%"/>

<img src=Attachments/IMG_1494.jpg width="50%"/>

<img src=Attachments/IMG_4527.jpeg width="50%"/>

<img src=Attachments/schematic.jpg width="80%"/>

---

## Cable

These fans use a USB-C style cable but carry PWM and tach signals — not USB data. The link below is for the correct cable type used in this project.

[Amazon — USB-C Pigtail Extension Cable][cable]

<img src=Attachments/cable.jpg width="50%"/>

<img src=Attachments/IMG_4349.jpg width="50%"/>

*Hole sizes for the above cable mount*

---

## Getting Started

1. Order the PCB using the included Gerber files (or build your own circuit)
2. Print the enclosure using the included 3D files
3. Flash the ESP32 using the example ESPHome YAML — edit `secrets.yaml` with your WiFi and MQTT credentials
4. Connect the fan via USB-C cable
5. Import the Node-RED flow (EC_Fan.json) into your Node-RED instance
6. The fan will appear as an MQTT device and can be controlled from the Node-RED dashboard

---

## Node-RED Dashboard

The included Node-RED flow provides a simple dashboard for controlling fan speed and monitoring RPM. Import `EC_Fan.json` from the NodeRed folder into your Node-RED instance.

<img src=Attachments/IMG_4529.jpeg width="50%"/>
<img src=Attachments/IMG_4531.jpeg width="50%"/>

---

[cable]: https://www.amazon.com/Female-Waterproof-Terminal-Pigtail-Extension/dp/B0D7CN4BTV/ref=sr_1_1?crid=22DIPVZJ6NLNA&dib=eyJ2IjoiMSJ9.5A5gh8wlE1dA5xzyWRfnF6wJ0fd9cFGKaGoMoL32RONrxG9_nN8LmJ9rJli3ujotLw90tzZNpYxllE3eMCpda7KoQPOh_-vPp3rROVUxTw11IfYGYRkTlLA7TaCoP3jR.uXNtln_9dJgcMFb5AaFasS38uiNJQxI2SMAjDUyGoKk&dib_tag=se&keywords=xiwai%2B5pcs%2FSet&qid=1761968034&sprefix=xiwai%2B5pcs%2Fset%2Caps%2C101&sr=8-1&th=1

## Related Project

For boards designed for controlling EC fans that use USB-C connectors for PWM speed control, see [EC_PWM_FanControlBoards](https://github.com/billjuv/EC_PWM_FanControlBoards) 
They are modifications of [Kyle Gabriel's](https://github.com/kizniche) (Mycodo) fan control boards for TerraBloom EC fans, adapted to use USB-C connectors instead of audio connectors. The boards provide voltage level shifting for safe use with Raspberry Pi GPIO pins or ESP32 pins, and support monitoring of tach signals (RPM) from compatible fans. 

---
