#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
#define BLYNK_MAX_SENDBYTES 128 //antal data som får plats i mailet

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "6ea35185021c478cb26eeeb1b2c1914d"; //vår author key som är kopplad till blynkappen

char ssid[] = "Gokkee";
char pass[] = "123456789";

SoftwareSerial EspSerial(6, 7);//RX, TX
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

#define pirPin 5                
int pirValue;                   
int pinValue;            

BLYNK_WRITE(V0)
{
  pinValue = param.asInt();
}

void setup()
{
  Serial.begin(115200);

  EspSerial.begin(9600);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  //Är en blockerande kommando som 

  // Setting the button
  pinMode(pirPin, INPUT);
  // Attach pin 2 interrupt to our handler
  //attachInterrupt(digitalPinToInterrupt(2), emailOnButtonPress, CHANGE);
}

void loop()
{
  
    if (pinValue)
    {
      getPirValue();
    }
  
  Blynk.run();
}

void getPirValue(void)        //Get PIR Data
{
  pirValue = digitalRead(pirPin);
  if (!pirValue)
  {

    Serial.println("Motion detected");
    Blynk.notify("Varning rörelse på G!");
    Blynk.email("adonay_u@hotmail.com", "Varning", "Rörelse på G!.");
    delay(1500);
  }
}
