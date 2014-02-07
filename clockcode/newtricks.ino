void newDoTricks(){
  //This will not exit until the trick is done!
  //choose a trick
  //int K = random(0,3);
   //k = 3;
  switch (random(4)){
  case 0:  //linear moves
    linearMoves();
    break;
  case 1:
    cosFunc();
    break;
  case 2:
    splashFade();
    break;
  case 3:
    newAccel();
    break;
  }
}

void newSetBG(int hue, int sat, int value, int twinkle){
  for(int i=0; i<12; i++){
    strip.setPixelColor(i,HSV(hue, sat, value));
  }
}
void newTime(int Csec, int Cmin, int Chour ){
  newSetBG(256, 100, 1, 0);
  newpos2LEDs(Csec, 10, 512, 0);
  newpos2LEDs(Cmin, 10, 0, 64);
  if(Chour>11)
    Chour = Chour-12;
  Chour = Chour*5;
  newpos2LEDs(Chour, 10, 640, 0);
  strip.show();
  delay(20);
}

void newpos2LEDs(int pos, int maxB, int hueA, int deltaHue){
  int sat = 100;
  float R1 = 0.9;
  float R2 = 0.7;
  float R3 = 1-R2;
  float R4 = 1-R1;
  pos = pos + 180;  //3 revs above 0
  int rStep = pos%5;
  float locHue = 0;
  float locBrightness;
  int LEDA = (pos%60)/5;
  int LEDB = LEDA + 1;
  if (LEDB>11)
    LEDB=0;

  switch (rStep){
  case 0:
    strip.setPixelColor(LEDA,HSV(hueA, sat, maxB));
    break;
  case 1:
    locBrightness = maxB*R1;
    locHue = hueA + deltaHue*R4;
    strip.setPixelColor(LEDA,HSV(locHue, sat, locBrightness));
    locBrightness = maxB*R4;
    locHue = hueA + deltaHue*R1;
    strip.setPixelColor(LEDB,HSV(locHue, sat, locBrightness));
    break;
  case 2:
    locBrightness = maxB*R2;
    locHue = hueA + deltaHue*R3;
    strip.setPixelColor(LEDA,HSV(locHue, sat, locBrightness));
    locBrightness = maxB*R3;
    locHue = hueA + deltaHue*R2;
    strip.setPixelColor(LEDB,HSV(locHue, sat, locBrightness));
    break;
  case 3:
    locBrightness = maxB*R3;
    locHue = hueA + deltaHue*R2;
    strip.setPixelColor(LEDA,HSV(locHue, sat, locBrightness));
    locBrightness = maxB*R2;
    locHue = hueA + deltaHue*R3;
    strip.setPixelColor(LEDB,HSV(locHue, sat, locBrightness));
    break;
  case 4:
    locBrightness = maxB*R4;
    locHue = hueA + deltaHue*R1;
    strip.setPixelColor(LEDA,HSV(locHue, sat, locBrightness));
    locBrightness = maxB*R1;
    locHue = hueA + deltaHue*R4;
    strip.setPixelColor(LEDB,HSV(locHue, sat, locBrightness));
    break;
  }
}

void linearMoves(){
  int hue = random(0,255);
  int sat = 100;
  int value = 10;
  int twinkle = 2;
  int time = 0;
  int endTime = 60*(1 + random(2));
  int locTime;
  int dir = random(2);

  while(time < endTime){
    newSetBG(hue, sat, 1, random(twinkle));
    time++;
    //Serial.println(time);
    if(dir==0)
      locTime = time;
    else
      locTime = endTime-time;
    newpos2LEDs(currentMinute+locTime,10,512,128);
    strip.show();
    delay(30); 
  }
  newTrickDone = true; 
}

void cosFunc(){ 
  int endTime=120;
  int time = 0;
  int locPos = 180;
  int dir = random(2);
  if(dir==0)
    dir = 1;
  else
    dir = -1;
  int locHue;
  int deltaHue = random(64,255);
  int centreHue = random(0,767);
  int locBrightness;
  float cosStep = (1 +random(4))*PI/60;
  float locCos = 0;
  while(time<endTime){
    for(int i=0; i<12; i++){
      locPos = i*5 + dir*time;
      locCos = cos(locPos*cosStep);
      locHue = centreHue + deltaHue*locCos;
      if(locHue>767)
        locHue = locHue -767;
      if(locHue<0)
        locHue = 767 + locHue;
      locBrightness = 34 + 30*locCos;
      locBrightness = locBrightness/5;
      strip.setPixelColor(i,HSV(locHue, 100, locBrightness));

    }
    time++;
    strip.show();
    delay(30);
  }
  newTrickDone = true;
}

void splashFade() {
  int endTime=120;
  int time = 0;
  int k = 0;
  int Hue[12];
  for (int i=0; i<12; i++) {
    Hue[i] = random(767);
  }
  int brightness = 30;
  while(time<endTime){

    for (int i=0; i<12; i++) {
      brightness = Hue[i]/6 - time;
      brightness = Hue[i]/6 - time;
      brightness = brightness + random(4);
      brightness = brightness/5;
      if(brightness == 1)
        brightness = 20;
      if(brightness<0)
        brightness = 0;
      strip.setPixelColor(i,HSV(Hue[i], 100, brightness));
    }
    time++;
    strip.show();
    delay(30);
  }
  newTrickDone = true;
}

void newAccel(){
  int time = 0;
  int hue1 = random(767);
  int hue2 = random(767);
  int hueBG = random(767);
  int endTime = 180;
  int displayPos = 0;
  float currentPos = 180 + currentMinute;
  float offsetPos = 0;
  float velocity = 0.0;
  float accel = 0.03 + float(random(-2,10)/100);
  //float friction = 0.99;
  int gravityPt =currentPos + 30 + random(-20,20);
  while(time<endTime){
    newSetBG(600, 100, 1, 0);
    if(offsetPos+currentPos<gravityPt)
      velocity += accel;
    else
      velocity -= accel;
    
    //velocity *= friction;
    offsetPos += velocity;
    //Serial.print(time);
    //Serial.print(" ; pos= ");
    //Serial.print(currentPos);
    //Serial.print(" ; vel= ");
    //Serial.println(velocity);
    displayPos  = int(currentPos + offsetPos)%60;
    newpos2LEDs(displayPos,10,hue1,64);
    displayPos  = int(currentPos - offsetPos)%60;
    newpos2LEDs(displayPos,10,hue2,64);
    time++;
    strip.show();
    delay(10);
  }
  newTrickDone = true;
}













