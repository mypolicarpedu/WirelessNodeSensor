/*Seperate PWM Generator From Input Voltage
 * Version 1.0
 * 
 * 3/8/2021
 * By: Mike and Shef
 * Desc: Takes an Input Voltage in Pin A5 and returns an Output PWM from Pin 3
 */


int pwmPin = 3;

void setup() {
   // initialize serial communication at 9600 bits per second:
   Serial.begin(9600);

   //initialize pin three as PWM output pin
   pinMode(pwmPin, OUTPUT);
}

// the loop routine runs over and over again forever:

void loop() {
   // read the input on analog pin 5:
   int sensorValue = analogRead(A5);
   
   // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
   float voltage = sensorValue * (5.0 / 1023.0);
   
   // print out the value you read:
   //Serial.println(voltage);
   

  //When battery empty
   if (voltage > 0 && voltage <= 1.5){

   Serial.println("1V");

   //write no duty cycle
   analogWrite(pwmPin, 0);
    
   }

  //When battery is 50% 
   else if (voltage > 1.5 && voltage <= 2.5){

    Serial.println("50%");

    //write 50% duty cycle
    analogWrite(pwmPin, 122);
    
   }

  //When battery is full
   else if (voltage > 2.5 && voltage <= 3.5){

    Serial.println("60/70%");

    //write 70% duty cycle
    analogWrite(pwmPin, 150);
    
   }


   
}
