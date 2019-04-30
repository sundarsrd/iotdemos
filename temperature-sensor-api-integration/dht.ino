#include "DHT.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include "WiFiMulti.h"

WiFiMulti wifiMulti;

int LED_BUILTIN = 2; //Built-in Blue LED

#define DHTPIN 4        // Digital pin we're connected to on ESP32
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
char payload[512];

int status = WL_IDLE_STATUS;

String hstring;
String tstring;
HTTPClient http;      
String apiUrl;
String randomUid;

void apistatus(int blinks) {

  for (int i=1; i <= blinks; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

}

// Code here runs only once
void setup() {

  Serial.begin(115200);
  pinMode (LED_BUILTIN, OUTPUT);
  delay(5000);


  //Multiple wifi access points can be added
  wifiMulti.addAP("dummy access point", "dummy password");

  Serial.print("Attempting to connect to Wifi");
  if(wifiMulti.run() == WL_CONNECTED) {
  //while (status != WL_CONNECTED) {
     Serial.println("");
     Serial.println("WiFi connected");
     Serial.print("IP address: ");
     Serial.println(WiFi.localIP());
  }

  Serial.println("Connected to wifi");

  //generate random number
  randomUid = String(random(0, 100000));
  
  //Initialize the DHT11 sensor    
  dht.begin(); 

}

// Main code here runs repeatedly
void loop() {

  delay(5000);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 5 seconds 'old'
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT temperature and humidity sensor!");
  }
  else {
      Serial.println("Successfully read DHT sensor data");
      Serial.print("Humidity is ");
      hstring = "";
      hstring += h;
      Serial.println(hstring);
      Serial.print("Temperature is ");
      tstring = "";
      tstring += t;
      Serial.println(tstring);

      delay(5000);
      apiUrl = "";

      //static ip from home wifi
      //api url
      apiUrl += "http://dummy api url:8081/api/ambience/"; 


      apiUrl += "esp32-wroom-" + randomUid + "/";
      apiUrl += "20000"; 
      apiUrl += "/" + tstring;
      apiUrl += "/C/"; 
      apiUrl += hstring; 
      apiUrl += "/room";

      Serial.println(apiUrl);
      delay(5000);

      //set http timeout to 30 seconds
      http.setTimeout(30000);
      http.begin(apiUrl); 

      int httpCode = http.GET();
      if(httpCode == 200) {
        Serial.println("Successfully sent data to Ambient API");
        apistatus(5);
      
      } else {
        Serial.println("Failed to send data to Ambient API");
        Serial.println(httpCode);
        apistatus(1);
      }

      http.end();

      //yield control to background utility tasks of esp8266
      yield();
      
      //sprintf(payload,"Humidity:%f  Temperature:%f'C",h,t); // Create the payload for publishing
  }    

}
