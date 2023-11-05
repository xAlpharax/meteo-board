
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

// #include "WiFi.h" // working with wifi, might interfere with pins (or so it seemed)

// #include "Arduino.h"
// #include "HTTPClient.h" // HTTP Handling
// #include "ArduinoJson.h" // JSON Handling

// CONFIGURATION

// DHT PINS

#define DHTPIN 4  // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14

// Uncomment whatever type you're using
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// DSM PINS

#define DSM501 18  // Just leave it as is

// END PIN CONFIGURATION SECTION


// SOME VARS

unsigned long duration;
unsigned long starttime;
unsigned long endtime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
uint32_t delayMS = 2000; // in loop delay() explicited

// WiFI stuff

const char* ssid = "Stefan's Galaxy A52s 5G";
const char* password = "12345678";
const char* apiEndpoint = "";


// Initialize DHT Sensor. The current DHT reading algorithm adjusts itself to work on faster procs. (rtfm --> docs)
DHT dht(DHTPIN, DHTTYPE);


void setup() { // Setup code that gets run regardless
  Serial.begin(9600);

  // WiFi.begin(ssid, password); // WiFi configuration at startup
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");

  Serial.println(F("----- DHT + MQ + DSM Interface -----"));

  dht.begin(); // Begin DHT System at startup
  
  pinMode(DSM501,INPUT); // Initialize DSM501A Sensor
  
  starttime = millis(); 
}

void loop() { // Main code
  // Wait a few seconds between measurements.
  delay(delayMS);

  // vvv DHT MEASUREMENTS SECTION vvv //

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  // vvv MQ135 MEASUREMENTS SECTION vvv //

  Serial.println(analogRead(15)); // MQ135 Sensor - ppm metrics (raw)
  Serial.println(F("^ppm^"));
 // vvv DSM501A MEASUREMENTS SECTION vvv //

  duration = pulseIn(DSM501, LOW);
  lowpulseoccupancy += duration;
  starttime = millis();
  endtime = starttime + sampletime_ms;

  while ( starttime < endtime) {
    ratio = (lowpulseoccupancy-endtime+starttime + sampletime_ms)/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // idk what s going on in here anymore.. it used to work, it doesn t now..
    // concentration = 0.001915 * pow(low_ratio, 2) + 0.09522 * low_ratio - 0.04884;
    Serial.print("lowpulseoccupancy: ");
    Serial.print(lowpulseoccupancy);
    Serial.print("    ratio: ");
    Serial.print(ratio);
    Serial.print("    DSM501A: ");
    Serial.println(concentration);

    lowpulseoccupancy = 0;
    starttime = millis();
    delay(2000);
  }
}
