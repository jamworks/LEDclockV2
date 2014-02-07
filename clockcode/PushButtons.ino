void readPBA(){
  PBAstate = digitalRead(PBApin);
  if (PBAstate != lastPBAstate){
    delay(50);
    if (PBAstate == LOW){    //ButtonA down index Clkstate counter
      ClkState++;    //new ClkState 1-4
      deadmanCtr = 10;
      //Serial.println(ClkState);
      if (ClkState>3){
        ClkState = 0;
        deadmanCtr = 0;
      }
    }
  }
  lastPBAstate = PBAstate; 
}


void readPBB(){
  PBBstate = digitalRead(PBBpin);
  if (PBBstate != lastPBBstate){
    delay(50);
    if (PBBstate == LOW){
      if(ClkState == 1 )  //increment minute 
        timeOffset = 60;
      if(ClkState == 2 )  //increment hour
        timeOffset = 3600;
      if(ClkState == 3 ){
        //special mode  normal/hourtricks
        mode = mode++;
        if(mode>2)
          mode = 0;
      }
    }
  }
  lastPBBstate = PBBstate;
}

void readPBC(){
  PBCstate = digitalRead(PBCpin);
  if (PBCstate != lastPBCstate){
    delay(50);
    if (PBCstate == LOW){
      //Serial.println("buttonB down");
      if(ClkState == 1 )  //decrement minute 
        timeOffset = -60;
      if(ClkState == 2 )  //decrement hour
        timeOffset = -3600;
      if(ClkState == 3 ){//special mode  normalclock or hourtricks
        mode = mode--;
        if(mode<0)
          mode = 2;
      }
    }
  }
  lastPBCstate = PBCstate;
}






