#include <Arduino.h>
#include <ESP8266WiFi.h> nvbh bbbbbbbbbbbbbb                                                                                                                                                              
#include <Wire.h>
#include <incub.h>


bool Heater, SprdFan, ExtFan, Motor;
float HumidValue { }, TempValue { }; 

// Replace with your network credentials
const char* ssid     = "Norahlinks";
const char* password = "Norahlinks";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "https://192.168.242.32/dashboardss/server.php";

//API Key for syncing with database
String apiKeyValue = "NL_incub_2024_AD";


byte buffer { };


void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {

    Serial.println("ERROR!!!");                                                                                                                                                                                                                           
    delay(500);
  }

  Serial.println("Success");
  delay(1000);
  Serial.flush();

}


void loop()
{
  buffer = Serial.read();
   
   switch (buffer)
   {
   case STMtemperature:
   {
    getTemperature();
    break;
   }
   case STMhumidity:
   {
    getHumidity();
    break;
   }
   case STMheater:
   {
    getHeaterState();
    break;
   }
   case STMspreadfan:
   {
    getSprdFanState();
    break;
   }
   case STMExtFan:
   {
    getExtFanState();
    break;
   }
   case STMmotor:
   {
    getMotorState();
    break;
   }
    case STM_SEND:
    {
      if(sendPAYLOAD() == true)
        Serial.println(SendSuccess); 

      else 
        Serial.println('p');
      break;
    }
  
   default:
    break;
   }
  
 
}


bool sendPAYLOAD()
{
  int r = 0;
    if(WiFi.status()== WL_CONNECTED)

        {
            std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

            // Ignore SSL certificate validation
            client->setInsecure();

            HTTPClient https;

            // Your Domain name with URL path or IP address with path
            https.begin(*client, serverName);


            // Specify content-type header
            https.addHeader("Content-Type", "application/x-www-form-urlencoded");


             String httpRequestData = "&APIKEY=" + String(apiKeyValue) + "&temperature=" + String(TempValue) +  "&humidity=" + String(HumidValue)
                            + "&HeaterState=" + String(Heater ? "ON"
                            :"OFF") + "&SpreadFan="+ String(SprdFan?"ON":"OFF")  + "&ExtFan=" + String(ExtFan ?"ON" :"OFF") + "&MotorState=" + String(Motor ? "ON":"OFF")  + "";


            Serial.print("httpRequestData: ");


            Serial.println(httpRequestData);

            // Send HTTP POST request
            int httpResponseCode = https.POST(httpRequestData);

            if (httpResponseCode>0)
            {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode) ;
            }

            else
            {
                Serial.print("Error code: ");
                Serial.println(httpResponseCode);
                r = httpResponseCode;
            }


            // Free resources
            https.end();
        }
      else
      Serial.print("Not connected!!");
      WiFi.begin(ssid, password);
  
  

  if(r == 200)
    return true;
  
  else 
    return false;

}



