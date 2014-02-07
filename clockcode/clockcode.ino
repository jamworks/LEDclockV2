#include <LPD8806.h>
//#include <Chronodot.h>
//Ver4 Jan 2014, version with photoimput gain
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
// Git repro LedClockV2
#include <Wire.h>
#include "SPI.h"
#include "RTClib.h"
RTC_DS1307 RTC;
// Number of RGB LEDs in strand:
int nLEDs = 12;
// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 4;  //green
int clockPin = 5;  //yellow
// First parameter is the number of LEDs in the strand.    
// Next two parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
int currentMinute;
int currentHour;
int lastSecond = 0;
int timeOffset = 0;
int ClkState =0;  //counter 0-3 states for clock
//mode a counter 0-2 for clock modes differnt ways to display time
//  0= normal,1=artclockA, 2=artclockB
int mode = 0;  
// artClockStartTime when first artclock trick is started!
long ArtClockStartTime = 20;
int deadmanCtr;
int PBAstate = 1;
int lastPBAstate =0;
int PBBstate = 1;
int lastPBCstate = 0;
int PBCstate = 1;
int lastPBBstate = 0;
const int PBApin = 8;
const int PBBpin = 9;
const int PBCpin = 7;
int photoIn = 0;
float Gain = 1.0;

boolean newTrickDone = true;
int k = 0;  //trick choice
int bkgHue = 256;
int bkgValue = 5;
int bkgSat = 100;

void setup () {
  Serial.begin(9600);
  Serial.println("Begin clock");
  pinMode(PBApin, INPUT_PULLUP);
  pinMode(PBBpin, INPUT_PULLUP);
  pinMode(PBCpin, INPUT_PULLUP);
  Wire.begin();
  RTC.begin();
  strip.begin();
  if (! RTC.isrunning()) //
    Serial.println("RTC is NOT running!");
  // following line sets the RTC to the date & time this sketch was compiled
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  //This is for show before the clock is running.
  deadmanCtr=0;
  //Blue fadedown
  for(int t=0; t<11; t++){
    for(int i=0; i<12; i++){
      strip.setPixelColor(i,HSV(512, 100, 10-t));
    }
    strip.show();
    delay(50);
  }
  
  delay(1000);
}

void loop () {
  DateTime now = RTC.now();
  currentMinute = now.minute();
  currentHour = now.hour();
  if(now.second() != lastSecond){  
    //test photoiput
    photoIn = analogRead(A0);  //Cds photoCell reading for backgrond light
    Gain = photoIn/150;  //Linear Eq for gain vs background light level
    if(Gain<1)
    Gain = 1.0;
    
    //Gain = 0.2;  //testing
    Serial.print("Gain= ");
    Serial.println(Gain);
   // if(Gain<0.35)  //clamp gain at .35
    //  Gain = 0.35;
    //Serial.println(now.second());
    lastSecond = now.second();
    if(ClkState==0 ){
      switch (mode){
      case 0:
        
          break;
      case 1:  //tick at fied time
        if(now.second()==0){
          //trick = true;
          newDoTricks();
          newDoTricks();
        }
        if(now.minute()==0 && now.second()<10){
          for(int i=0; i<4; i++){
          newDoTricks();
          }
          
        }
        break;
      case 2:  //trick at some random art time
        if(now.unixtime()>ArtClockStartTime){  //&& trickInit
          newDoTricks();
          ArtClockStartTime = now.unixtime() + random(3,50);
        }
        break;
      }
    }

    if(deadmanCtr>0)
      deadmanCtr--;
    else{
      ClkState = 0;  //return clock to normal time mode
      deadmanCtr=0;
    }

  }  //end of onesecond loop
  timeOffset = 0;
  switch (ClkState){
  case 0:   //normal show the current time
    newTime(now.second(), now.minute(), now.hour());
    break;
  case 1:  //set minutes
    setMinute();
    break;
  case 2:  //set hour
    setHour();
    break;
  case 3:  //special clock modes
    setMode();
    break; 
  }
  readPBA();
  readPBB();
  readPBC();
  if (timeOffset!=0){
    DateTime now = RTC.now();  // get current time
    DateTime PlusOne (now.unixtime() + timeOffset); // add offset
    RTC.adjust(PlusOne); // set to new time
  }
  timeOffset = 0;

}  //end of loop














































