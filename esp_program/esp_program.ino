#include <ThingSpeak.h>               // add librery
#include <ESP8266WiFi.h>

#include <DHT.h>  // Including library for dht
#include <DHT_U.h>

//---------------------------------------------------------------------------

WiFiClient  client;
unsigned long counterChannelNumber = 2161862;                // Channel ID
const char * myCounterReadAPIKey = "FLJ0XIFDKB6YEYZQ";      // Read API Key
const char * myCounterWriteAPIKey = "AHTK578F67AEOQJW";     // Write API Key

const int FieldNumber1 = 1;     // Temperature
const int FieldNumber2 = 2;     // Humidity
const int FieldNumber3 = 3;     // Smoke Sensor
const int FieldNumber4 = 4;     // Flame Sensor
const int FieldNumber5 = 5;     // Rain Sensor

//------------------------------------------------------------------------------

#define DHTPIN D3                          //pin where the dht11 is connected
#define DHTTYPE DHT11                      // DHT 11 
DHT dht(DHTPIN, DHTTYPE);

//---------------------------------------------------------

#define smoke D4
int smokeValue = 0;                       // value read from the Gas  sensor

//---------------------------------------------------------
#define flame D1
int flameValue = 0;                       // value read from the Gas  sensor

//---------------------------------------------------------
#define rain D2
int rainValue = 0;                       // value read from the Gas  sensor

//---------------------------------------------------------

void setup()
{  
  Serial.begin(9600);
 
  Serial.println();
  
  WiFi.begin("Pranav", "pranav11");                 // write wifi name & password           

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
//---------------------------------------------------------
  delay(10);

  dht.begin();
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Serial.print("Temperature: "); 
  Serial.println(t);
  Serial.print("Humidity: "); 
  Serial.println(h);

  ThingSpeak.writeField(counterChannelNumber ,FieldNumber1 , t ,myCounterWriteAPIKey);    // write on channel
  ThingSpeak.writeField(counterChannelNumber ,FieldNumber2 , h ,myCounterWriteAPIKey);    // write on channel

//---------------------------------------------------------------------------------------------------------
  
    if(digitalRead(smoke)== 1){
      
      smokeValue = 0;
    }
    else {
        smokeValue = 1;  
    }
       
       ThingSpeak.writeField(counterChannelNumber , FieldNumber3 ,smokeValue  , myCounterWriteAPIKey);         //Send Smoke value to cloud      
     Serial.print("Smoke Detected = ");
     Serial.println(smokeValue);    
//------------------------------------------------------------------------------------------------------------
 
      if(digitalRead(flame)== 1){
      
         flameValue = 0;
      }
    else {
        flameValue = 1;  
    }       
       ThingSpeak.writeField(counterChannelNumber , FieldNumber4 ,flameValue  , myCounterWriteAPIKey);             //Send Flame value to cloud     
     Serial.print("Flame Detected = ");
     Serial.println(flameValue);    
//---------------------------------------------------------------------------------------------------------
 
      if(digitalRead(rain)== 1){
      
         rainValue = 0;
       }
       else {
          rainValue = 1;  
        }
           
       ThingSpeak.writeField(counterChannelNumber , FieldNumber5 ,rainValue  , myCounterWriteAPIKey);               //Send Rain value to cloud   
     Serial.print("Rain Detected = ");
     Serial.println(rainValue);    
     
 //--------------------------------------------------------------------------------------------------
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
