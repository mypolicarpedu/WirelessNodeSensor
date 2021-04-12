/* Combined Full Temperature Sensor Code
 * Version: 1.0 BETA
 * Created: 4/12/2021
 * Modified: 4/12/2021
 * 
 * By: Michael Policarpio
 */
 
//bluetooth module necessary to include import 
#include <SoftwareSerial.h>

//software serial name(rx/tx) to setup port
SoftwareSerial hc06(0,1);

// set pin numbers:
const int in = A0;           // our input A0 for reading the sensor output

//declare constants from datasheet:
const float vout0 = 470; //sensor output voltage at 0C (*NOTE THIS IS DIFFERENT THAN THE DATA SHEET DUE TO IMPERFECTIONS IN COMPONENTS but calibrated using scope and physical thermometer.)
const float tc = 10.0; //mv/C of temperature coefficient for the MCP9700

// variables used in program:

int i, f;
float vout, vout_avg, ta, tempF;
String fString;

//set PWM output PIN
int pwmPin = 5;


// MAIN PROGRAM

void setup() {
  Serial.begin(9600);            //begin device communication
  pinMode(in, INPUT);            // set pin IN as input to prepare to read A0
  analogReference(DEFAULT);


  //intialize bluetooth serial port
  hc06.begin(9600);



   // for PWM frequency of 7812.50 Hz
   TCCR0B = TCCR0B & B11111000 | B00000010;
  
   // initialize serial communication at 9600 bits per second:
   Serial.begin(9600);

   //initialize pin three as PWM output pin
   pinMode(pwmPin, OUTPUT);
 
}

void loop() {
  
  vout_avg = 0;                 //initialize the average at zero
  for (i = 0; i < 1024; i++) {
    vout = analogRead(A0) * (4976.30 / 1023);        //averages out 1024 values on pin A0.     
    //Serial.println(vout); TEST LINE
    
    vout_avg = vout_avg + vout;                      //this is connected to sensor input
  }
  vout = vout_avg / 1024;        //to get voltage out 
  //Serial.println(vout); TEST LINE
  
  ta = (vout - vout0) / tc;         //derived formula to get ambient temperature 

  tempF = (ta * 1.8) + 32;          //calculate temp in farenheit

//One option for reading out the temperature to user but not used in this version:
  /*
  Serial.print("Temperature (in C) = " );
  Serial.println(ta);
  Serial.print("Temperature (in F) = ");
  Serial.println(tempF);
  
  Serial.println("-----------------------------------");
  */

 //print temperature to serial so that it can be read by HC06
  Serial.print(tempF);
  Serial.println("");
 
  delay (30000);      //wait 30 seconds between readings


  //PWM STUFF
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
