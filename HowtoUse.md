##﻿#Jerry's LED Trick O'Clock

A colourful LED clock that not only shows the time but can put on a light show too! The clock has timekeeping battery that will last for many years. After you first set the time, the clock will display the correct time, even if the power goes off or you unplug it, as soon as power is restored to the clock.  This version has a photo light sensor that adjusts the clock light levels with a ambient light level. In a dark room the clock will not be as bright as in a sunny room.

The clock can create numerous light effects,  I call these effects “tricks.” Each trick lasts about 2 seconds.  The clock works in three modes: 
* 1-Keeps time 
* 2-Keeps time plus performs a trick on the minute and on the hour 
* 3-Keeps time plus performs a trick at random times.

###POWER:
Power is supplied via the USB connector which needs to be connected to the included USB power point.  Supplied with standard 240 VAC Aus power connector. Any other USB power point should work. It is just the standard USB 5 vdc supply. The USB connector also connects to the Arduino Micro that runs the clock. 

Use the Arduino IDE  http://arduino.cc/en/Main/Software with your computer, plug in the USB connector and reprogram the clock. 

###SETTING TIME & TRICKS
The clock has three push buttons on the face of the clock.  The centre button is used to change modes. 
 
**First push of Centre Button:**  
Set Minutes - the minute time is shown in yellow/red; the remaining LEDs are green. Increase or decrease the minute by pressing the outer push buttons. Clock returns to timekeeping mode (with your setting) 10 sec after last push. 

**Second Push of Centre Button:**  
Set Hour - the hour time is shown in magenta and the remaining LEDs are yellow. Increase or decrease the hour by pressing the outer push buttons. Clock returns to timekeeping mode (with your setting) 10 sec after last push.

**Third Push of Centre Button:**  
Select working mode for tricks - Pressing the outer buttons will cycle through the following choices which are indicated by the colour of the clock LEDs.
1. No tricks = All LEDs green
2. Tricks occur on the minute and the hour =  LEDs alternate green and blue
3. Tricks occur at random times = LEDs alternate red, green, and blue

**NOTE:** A fourth push of centre button will return clock to time display with your current settings. This will always happen in about 10 seconds even if you do nothing!

If you think the clock is not behaving, just unplug it and plug it back in to reset everything.

We hope Jerry's LED Trick O'Clock gives you years of trouble free operation.


