//new color tables for 8806 chips
//input Hue, Sat, Val output 8806 color
// Jan 2014 Jerry Jeffress
// Value Hue 0 - 767
// Sat,0 - 100
// value 0 - 127
uint32_t HSV(uint16_t Hue, byte Sat, byte Value){
  byte r,g,b;
  r,g,b = 0;
  //Hue = Hue%768;
  switch(Hue/128){
  case 0:  //red  hue 0-127
    r=127;
    g=Hue;  //green up
    b=0;
    break;
  case 1:  //yellow hue 128-255
    r=127 - Hue%128;  //red down
    g=127;
    b=0;
    break;
  case 2:  //green hue 256-383
    r=0;  
    g=127;
    b=Hue%128;  //blue up
    break;
  case 3:  //blue hue 384-511
    r=0;  
    g=127-Hue%128;  //green down
    b=127;  
    break;
  case 4:  //blue hue 512-639
    r=Hue%128;  //red up
    g=0;      //green down
    b=127;  
    break;  
  case 5:  //blue hue 640-767
    r=127;  
    g=0;      
    b=127-Hue%128;  //blue down

    break;    
  }

  // r = CalcV(Value,r);
  // Set output Value with Gain
  Value = Value * Gain;
  int red = r + (127-r)*(100-Sat)/100;
  red = red*Value/127;
  int green = g + (127-g)*(100-Sat)/100;
  green = green*Value/127;
  int blue = b + (127-b)*(100-Sat)/100;
  blue = blue*Value/127;
  r = byte(red);
  g = byte(green);
  b = byte(blue);

  return(strip.Color(r,g,b));
}



