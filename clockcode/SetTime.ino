void setMinute(){
  //Blue Bg
  newSetBG(512,100,1,0);
  newpos2LEDs(currentMinute, 10, 0, 64);
  strip.show();
}

void setHour(){
  //yellow Bg
  newSetBG(128,100,1,0);
  int hourLED = currentHour;
  if (hourLED>11)
    hourLED = hourLED -12;
   
  newpos2LEDs(hourLED*5, 10, 640, 0);
  strip.show();

}

void setMode(){
  //yellow Bg
  for(int i=0; i<12; i++){
    if(mode==0)  //green
      strip.setPixelColor(i,HSV(256, 100, 1));
    if(mode==1)  //red & green
      strip.setPixelColor(i, HSV(255*(i%2 +1), 100, 1));
    if(mode==2)
      strip.setPixelColor(i, HSV(255*(i%3 +1), 100, 1));
  }
  strip.show();
}

