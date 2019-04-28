# iotdemos
IoT Demos for SmartCities (Arduino, ESP8266)

* Place the ESP8266 in the BreadBoard, and connect it to an USB port

1. [Install Arduino IDE](https://www.arduino.cc/en/Main/Software)
2. [Get USB to UART driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
3. Add ESP1266 Board Manager -   
    https://github.com/esp8266/Arduino    
    https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/   
    http://arduino.esp8266.com/stable/package_esp8266com_index.json -> Add to preferences
4. Select the "Tools -> "Board Generic ESP8666 Module -> Generic ESP8666 Module"
5. Test ESP8266 connectivity with [Blink OnChip LED](blink), [Blink OnBoard LED](blink-led) . 
   - Open "File -> Examples -> ESP8266 -> Blink" . 
   - Compile & Upload (hold the flash button) . 
6. [Test Control/Command via Wifi](http) - Get the code for a HTTP server from https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html & run it . 
   - Change the SSID, Pwd in the code to your wifi SSID & password .  
   - Compile & Upload --> Open the serial monitor from "Tools -> Serial Monitor" to see the diagnostics msgs (Ensure the baudrate of the serial monitor is set to what's given in the program - ex: 115200) . 
   - The HTTP Server starts in ESP8266, connects using DHCP and sends out it's IP address to the serial console . 
   - Connect to the IP address from the web-browser & check if the LED can be toggled using the button . 
   - The readings from the LED (# of times switched on,off) would be displayed in the webpage (and optionally sent back to the Readings Service) . 

----

## ESP8266 Pin Diagram
![ESP8266 PIN Diagram](docs/images/esp8266_nodemcu_pins.png)    

[ESP8266 Usage Instructions](docs/Usage.Instructions.ESP8266.docx)    

----

## Ref. Links:
[Documentation and help with the ESP8266 chip/boards/modules](https://github.com/tttapa/ESP8266)    
[ESP8266 User guide](https://tttapa.github.io/ESP8266/Chap01%20-%20ESP8266.html)   
[Beginners Guide to Arduino](https://www.instructables.com/id/A-Beginners-Guide-to-Arduino/)    
[Arduino ESP8266 Documentation](https://arduino-esp8266.readthedocs.io/en/latest/)    
[ESP8266 Example](https://electrosome.com/esp8266-arduino-programming-led-blink/)    
[Arduino Shell](https://github.com/nuket/ArduinoShell)    
