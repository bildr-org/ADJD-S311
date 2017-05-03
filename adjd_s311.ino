#include <ADJDS311.h>
#include <Wire.h>

int sensorLed_pin = 2; //LED on the ADJDS-311
ADJDS311 colorSensor(sensorLed_pin);

//if using an RGB LED (Needs PWM Pins)
int redPin = 3;
int greenPin = 5;
int bluePin = 6;

void setup(){
  Serial.begin(9600);
  
  colorSensor.init();
  colorSensor.ledOn(); //turn LED on
  
  //Calibrate white 
  //Need to hold white card in front (1-3mm) of it to calibrate from
  colorSensor.calibrate(); 
}

void loop(){
  RGBC color = colorSensor.read(); //read the color
  
  Serial.print(color.red);
  Serial.print(" | ");
  Serial.print(color.green);
  Serial.print(" | ");
  Serial.print(color.blue);
  Serial.print(" | ");
  Serial.println(color.clear);
  
  lightLED(color); //send color to the LED
  
  delay(200); //just here to slow down the serial output
  
}

void lightLED(RGBC color){
  //RGBC is an array of red/green/blue/clear readings 
  //Take a RGBC, and try to reproduce it on an RGB LED
  //This does not work very well as is because of how colors/our eyes work
  
  analogWrite(redPin, map(color.red, 0, 1024, 0, 255));
  analogWrite(greenPin, map(color.green, 0, 1024, 0, 255));
  analogWrite(bluePin, map(color.blue, 0, 1024, 0, 255));
}
