#include <DHT.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <dht11.h>
#include <ESP8266WiFi.h>

const char* ssid     = "khutj"; // Your ssid
const char* password = "hasan 27"; // Your Password


WiFiServer server(80);
#define DHTPIN 2     // what digital pin we're connected to


#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);




void setup() {
Serial.begin(9600);
delay(10);
Serial.println();

// Connect to WiFi network
WiFi.mode(WIFI_STA);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
server.begin();
Serial.println("Server started");

// Print the IP address
Serial.println(WiFi.localIP());
}

void loop() {
delay(2000);


  float h = dht.readHumidity();
  
  float t = dht.readTemperature();
  
  float f = dht.readTemperature(true);

  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  float hif = dht.computeHeatIndex(f, h);
 
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");



WiFiClient client = server.available();
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");  // the connection will be closed after completion of the response
client.println("Refresh: 5");  // refresh the page automatically every 5 sec
client.println();
client.println("<!DOCTYPE html>");
client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
client.println("<head>\n<meta charset='UTF-8'>");
client.println("<title>ESP8266 Temperature & Humidity DHT11 Sensor</title>");
client.println("</head>\n<body>");
client.println("<H2>ESP8266 & DHT11 Sensor</H2>");
client.println("<H3>Humidity / Temperature</H3>");
client.println("<pre>");
client.print("Humidity (%)         : ");
client.println((float)h, 2);
client.print("Temperature (°C)  : ");


client.println("</pre>");
client.println("<H3>www.elec-cafe.com</H3>");
client.print("</body>\n</html>");
delay(1000); //delay for reread
}
