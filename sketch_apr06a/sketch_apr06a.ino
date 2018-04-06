#include <ESP8266WiFi.h>

//IP or name of address root: ie: google.com
//NOT google.com/nothing/after/the/dotcom.html
const char* hostGet = "mydatasite.com"; 


void postData() {

   WiFiClient clientGet;
   const int httpGetPort = 80;

   //the path and file to send the data to:
   String urlGet = "/data/collector.php";

 
  // We now create and add parameters:
  String src = "ESP";
  String typ = "flt";
  String nam = "temp";
  String vint = "92"; 

  urlGet += "?src=" + src + "&typ=" + typ + "&nam=" + nam + "&int=" + vint;
   
      Serial.print(">>> Connecting to host: ");
      Serial.println(hostGet);
      
       if (!clientGet.connect(hostGet, httpGetPort)) {
        Serial.print("Connection failed: ");
        Serial.print(hostGet);
      } else {
          clientGet.println("GET " + urlGet + " HTTP/1.1");
          clientGet.print("Host: ");
          clientGet.println(hostGet);
          clientGet.println("User-Agent: ESP8266/1.0");
          clientGet.println("Connection: close\r\n\r\n");
          
          unsigned long timeoutP = millis();
          while (clientGet.available() == 0) {
            
            if (millis() - timeoutP > 10000) {
              Serial.print(">>> Client Timeout: ");
              Serial.println(hostGet);
              clientGet.stop();
              return;
            }
          }

          //just checks the 1st line of the server response. Could be expanded if needed.
          while(clientGet.available()){
            String retLine = clientGet.readStringUntil('\r');
            Serial.println(retLine);
            break; 
          }

      } //end client connection if else
                        
      Serial.print(">>> Closing host: ");
      Serial.println(hostGet);
          
      clientGet.stop();

}

void setup() {
    Serial.begin(115200);
    WiFiCon();
}

void loop() {

  postData();

  delay(10000);
  if (WiFiCon() > 0)
  {
    Serial.println("Connection is establised !!");
  }else{
    Serial.println(WiFiCon());
  }

  delay(1000);


}
