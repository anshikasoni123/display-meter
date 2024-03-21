// ESP32 will make post requests to server on local network
// ESP32 has to be on same network

//  including wifi library
#include<WiFi.h>

//  including httpclient library
#include<HTTPClient.h>

//  wifi credentials
const char ssid[] = "your ssid";
const char password[] = "your password";

//  API url
String api = "write your API URL for POST request";

//  creating http client
HTTPClient http;

//  potpin
const int potpin = 34;

void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to : ");
  Serial.println(ssid);
  WiFi.begin(ssid , password);
  while (WiFi.status()  !=  WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with Wifi !");
}

void loop()
{

  //  reading potentiometer
  int pot = analogRead(potpin);
  Serial.println(pot);

  //  check if wifi is still connected
  if (WiFi.status()  ==  WL_CONNECTED)
  {
        
    WiFiClient client;

    HTTPClient http;

    http.begin(server_name);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST({",\"temperature\" : " + String(bmp.readTemperature()) });
    Serial.println(httpResponseCode);
    Serial.print("http response code");
    http.end();

    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
  }
  
  else
  {
    Serial.print("Not connected with : ");
    Serial.println(ssid);
  }
  //  wait for 1 seconds before hittng a POST request again
  delay(1000);

}
