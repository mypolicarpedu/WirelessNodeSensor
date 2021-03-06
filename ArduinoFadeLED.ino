//Figure 2: LED Fading with PWM duty cycle
int led = 3;
int analog = 2;
int val = 0;

int fade = 255;

void setup() {  // initialize digital pin 2 as an output. This can be changed to any arduino port
   pinMode(led, OUTPUT);   //LED pin

   pinMode(analog, OUTPUT);  //analog pin
}
void loop() {
   
   if (fade == 0){

    fade = 255;
    
   } 
   val = analogRead(3); //how to read PWM
   analogWrite(led, fade);
   delay(1);

   fade--;
}
