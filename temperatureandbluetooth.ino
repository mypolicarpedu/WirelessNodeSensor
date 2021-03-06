/* Temperature Sensor Working With Bluetooth
 * Version: 1.0 BETA
 * Created: 3/1/2021
 * Modified: 3/1/2021
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
const float vout0 = 485; //sensor output voltage at 0C (*NOTE THIS IS DIFFERENT THAN THE DATA SHEET DUE TO IMPERFECTIONS IN COMPONENTS but calibrated using scope and physical thermometer.)
const float tc = 10.0; //mv/C of temperature coefficient for the MCP9700

// variables used in program:

int i, f;
float vout, vout_avg, ta, tempF;
String fString;


// MAIN PROGRAM

void setup() {
  Serial.begin(9600);            //begin device communication
  pinMode(in, INPUT);            // set pin IN as input to prepare to read A0
  analogReference(DEFAULT);


  //intialize bluetooth serial port
  hc06.begin(9600);
 
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

  

  
}
