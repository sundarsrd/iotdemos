# iotdemos
IoT Demos for SmartCities (Arduino, ESP8266)

* Place the ESP8266 in the BreadBoard, and connect it to an USB port

1. Install Arduino IDE
2. Get USB to UART driver https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
3. Add ESP1266 Board Manager - 
    https://github.com/esp8266/Arduino
    http://arduino.esp8266.com/stable/package_esp8266com_index.json --> Add to preferences
4. Select the "Tools -> "Board Generic ESP8666 Module -> Generic ESP8666 Module"
5. Open "File -> Examples -> ESP8266 -> Blink"
6. Compile & Upload (hold the flash button)
7. Get the code for a HTTP server from "https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html" & run it
8. Change the SSID, Pwd in the code to your wifi SSID & password
9. Compile & Upload --> Open the serial monitor from "Tools -> Serial Monitor" to see the diagnostics msgs (Ensure the baudrate of the serial monitor is set to what's given in the program - ex: 115200)
10. The HTTP Server starts in ESP8266, connects using DNS and sends out it's IP address to the serial console
11. Connect to the IP address from the web-browser & check if the LED can be toggled using the button
12. The readings from the LED (# of times switched on,off) would be sent back to the Readings Service


## Other Links:
ESP8266 User guide - https://tttapa.github.io/ESP8266/Chap01%20-%20ESP8266.html
https://www.instructables.com/id/A-Beginners-Guide-to-Arduino/
https://arduino-esp8266.readthedocs.io/en/latest/
https://electrosome.com/esp8266-arduino-programming-led-blink/