/* Basic USB Joystick Example
   Teensy becomes a USB joystick

   You must select Joystick from the "Tools > USB Type" menu

   Pushbuttons should be connected to digital pins 0 and 1.
   Wire each button between the digital pin and ground.
   Potentiometers should be connected to analog inputs 0 to 1.

   This example code is in the public domain.
*/
#define DCSBIOS_DEFAULT_SERIAL
#include <Bounce.h>
#include "DcsBios.h" 



DcsBios::LED handleGearWarning(0x1026, 0x4000, 24);
int x = 1;
int flaps3 = 1;
int gearDown = 1;
// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.

Bounce hat_bttn = Bounce(5, 5);
Bounce trigger1 = Bounce(6, 5);
Bounce weapon_rls = Bounce(7, 5);
Bounce buttonGear = Bounce(8, 5); //gear
Bounce buttonFlaps1 = Bounce(9, 5); //flaps1
Bounce buttonFlaps2 = Bounce(10, 5); //flaps2
//Bounce button7 = Bounce(11, 5);
Bounce button8 = Bounce(12, 5);


void setup() {
  DcsBios::setup();
  pinMode(0, INPUT_PULLUP); //hat_l 
  pinMode(1, INPUT_PULLUP); //hat_up 
  pinMode(2, INPUT_PULLUP); //hat_r 
  //pinMode(3, INPUT);//pin 3 tundub persses olevat, ei funka ehk ta on ss hat=-1 - reset hat position
  pinMode(4, INPUT_PULLUP); //hat_down 
  pinMode(5, INPUT_PULLUP); //hat_bttn 
  pinMode(6, INPUT_PULLUP); //trigger1
  pinMode(7, INPUT_PULLUP); //weapon_rls done
  pinMode(8, INPUT_PULLUP); //gear
  pinMode(9, INPUT_PULLUP); //flaps1
  pinMode(10, INPUT_PULLUP); //flaps2
  //pinMode(24, OUTPUT); //gear_switch_LED
  //pin 11 flaps 3
  //pin 12 geardown
  Serial.begin(9600);
}

void loop() {
  DcsBios::loop();
  
  /* ----(gear_switch_LED blinker)----
  digitalWrite(24, HIGH);
  delay(100);
  digitalWrite(24, LOW);
  delay(100);*/
  //määrab ära, millal resettida hat pos.i
  if ((digitalRead(0) == HIGH) && (digitalRead(1) == HIGH) && (digitalRead(2) == HIGH) && (digitalRead(4) == HIGH)) {
    x = 0;
  }
  else {
    x = 1;
  };
  
  //joycon
  //A6-Throttle
  
  Joystick.X(analogRead(5));
  Joystick.Y(analogRead(4));
  Joystick.Z(analogRead(2));
  Joystick.Zrotate(analogRead(3));
  Joystick.sliderLeft(analogRead(6)); //throttle
  
  //hat
  
  if (digitalRead(2)== LOW) Joystick.hat(0);
  if (digitalRead(4)== LOW) Joystick.hat(90);
  if (digitalRead(0)== LOW) Joystick.hat(180);
  if (digitalRead(1)== LOW) Joystick.hat(270);
 /* if (digitalRead(1)== LOW) Joystick.button(20, 1);
  if (digitalRead(1)== HIGH) Joystick.button(20, 0);
  if (digitalRead(2)== LOW) Joystick.button(21, 1);
  if (digitalRead(2)== HIGH) Joystick.button(21, 0);
  if (digitalRead(4)== LOW) Joystick.button(22, 1);
  if (digitalRead(4)== HIGH) Joystick.button(22, 0);
  if (digitalRead(0)== LOW) Joystick.button(23, 1);
  if (digitalRead(0)== HIGH) Joystick.button(23, 0);*/
  if (x==0)Joystick.hat(-1);
  
  //buttons
  
  if(digitalRead(8)== HIGH){
    //gearDown = 0;
    Joystick.button(7, 1);
  }
  else{
    //gearDown = 1;
    Joystick.button(7, 0);
  };

  if(digitalRead(9)== HIGH && digitalRead(10) == HIGH){
    //flaps3 = 0;
    Joystick.button(8, 1);
  }
  else{
    //flaps3 = 1;
    Joystick.button(8, 0);
  };


//-------------------------------------

  hat_bttn.update();
  trigger1.update();
  weapon_rls.update();
  buttonGear.update();
  buttonFlaps1.update();
  buttonFlaps2.update();
  
//-------------------------------------

  if (hat_bttn.fallingEdge()) {
    Joystick.button(1, 1);
  }
  if (trigger1.fallingEdge()) {
    Joystick.button(2, 1);
  }
  if (weapon_rls.fallingEdge()) {
    Joystick.button(3, 1);
  }
  if (buttonGear.fallingEdge()) {
    Joystick.button(4, 1);
  }
  if (buttonFlaps1.fallingEdge()) {
    Joystick.button(5, 1);
  }
  if (buttonFlaps2.fallingEdge()) {
    Joystick.button(6, 1);
  }
  
//------------------------------------

  if (hat_bttn.risingEdge()) {
    Joystick.button(1, 0);
  }
  if (trigger1.risingEdge()) {
    Joystick.button(2, 0);
  }
  if (weapon_rls.risingEdge()) {
    Joystick.button(3, 0);
  }
  if (buttonGear.risingEdge()) {
    Joystick.button(4, 0);
  }
  if (buttonFlaps1.risingEdge()) {
    Joystick.button(5, 0);
  }
  if (buttonFlaps2.risingEdge()) {
    Joystick.button(6, 0);
  }
    
/*---------------------(SERIAL PRINT)----------------------*/
/*---------------------(VVVVVVVVVVVV)----------------------*/

  
  Serial.print(analogRead(5)); //stick parem-vasak
  Serial.print("  ");
  Serial.print(analogRead(4)); //stick edasi-tagasi
  Serial.print("  ");
  Serial.print(analogRead(2)); //parem nupp parem-vasak
  Serial.print("  ");
  Serial.print(analogRead(3)); //parem nupp ülesse-alla
  Serial.print("  ");
  Serial.print(analogRead(0)); //vasak nupp parem-vasak
  Serial.print("  ");
  Serial.print(analogRead(1)); //vasak nupp ülesse-alla
  Serial.print("  ");
  Serial.print(analogRead(6)); //varakThrottle
  Serial.print("  / ");
  Serial.print(digitalRead(0));
  Serial.print("/");
  Serial.print(digitalRead(1));
  Serial.print("/");
  Serial.print(digitalRead(2));
  Serial.print("/");
  Serial.print(digitalRead(4));
  Serial.print("/");
  Serial.print(digitalRead(5));
  Serial.print("::");
  Serial.println(x);

  // a brief delay, so this runs 'only' 50 times per second
  delay(20);
}
