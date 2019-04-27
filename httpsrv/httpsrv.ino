#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int led = 2;
int readingCounterOn = 0;
int readingCounterOff = 0;

void handleRoot();              // function prototypes for HTTP handlers
void handleLED();
void handleNotFound();

void setup(void) {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  pinMode(led, OUTPUT);

  wifiMulti.addAP("RRHomen", "rrhome123");   // add Wi-Fi networks you want to connect to
  //wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  //wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form><br>"+getReadingData());
}

void handleLED() {                          // If a POST request is made to URI /LED
  digitalWrite(led, !digitalRead(led));     // Change the state of the LED
  // Keep a counter & report readings
  recordReading();
  //
  server.sendHeader("Location", "/");       // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void recordReading() {  
  // if LED is on
  if (digitalRead(led))
    readingCounterOn++;
  else
    readingCounterOff++;
  // Send the count to http service (on cloud...)
  // HTTPClient httpClient;
  // string readingsServiceUrl = "http://192.168.1.34/readings/";  
  // Serial.print("[HTTP] begin...\n");
  // if (httpClient.begin(client, readingsServiceUrl)) {
  //   Serial.print("[HTTP] POST...\n");
  //   // start connection and send HTTP header
  //   int httpCode = http.POST("on="+readingCounterOn+"&off="+readingCounterOff);

  //   // httpCode will be negative on error
  //   if (httpCode > 0) {
  //     // HTTP header has been send and Server response header has been handled
  //     Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  //   } else {
  //     Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  //   }
  // httpClient.end();
}

String getReadingData() {
  String result = "";
  result += "on=";
  result += readingCounterOn;
  result += "&off=";
  result += readingCounterOff;
  return result;
}
