# Temperature and Humidity Montitor

This project is used to measure the air temperature and relative humidity values and transmit that to a local network dashboard using MQTT. The measurements are also logged and added to a spreadsheet at regular intervals.

## Software / hardware requirements

The project uses an ESP32 development board connected to a SHT30 temperature and humidity sensor. It also uses Node-RED for the dashboard. 

## Usage

After powering on the ESP, start the Node-RED client. The UI is available at http://localhost:1880/ui/
