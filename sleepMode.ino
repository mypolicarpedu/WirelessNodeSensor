//Test arduino sleep code
//Wireless Sensor Node Project
//Created 4/19/2021
//By: Michael and Shef

#include <avr/sleep.h>
void setup() {
  Serial.begin(9600); //start communication with port

}

void loop() {
  enterSleep();         //enter sleep
  exitSleep();          //exit sleep and wait 30 seconds before waking up again
}

void enterSleep() {
  sleep_enable();            //go to sleep
  set_sleep_mode(SLEEP_MODE_IDLE);       //set sleep mode
  digitalWrite(LED_BUILTIN, LOW);         //turn off light to show sleep
  sleep_cpu();              //CPU is asleep
}

void exitSleep() {
  sleep_disable();          //wake up CPU
  digitalWrite(LED_BUILTIN, HIGH);       //turn on LED to show it's awake
  delay(30000);  //may have to change to account for 
}
