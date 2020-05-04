/*
  Arduino AC Power indicator using LED bar with 10 LEDs
  Configured for 20A sensor SC-013 type
*/

/* Number of AC reads to be performed to get min and max values */
#define NO_ADC_READS 1700

/* Analog input pin to connect directly to sensor */
const int analogInPin = A0;  
/* Arduino outputs to be connected with LEDs */
const int ledBarPins[] = {2,3,4,10,11,5,6,7,8,9};
/* Store value red from sensor */
int sensorValue = 0;  
/* Store min value */
int minValue = 0;
/* Store max value */
int maxValue = 0;
/* Calculate difference (maxValue-minValue) */
int difference = 0;
/* Linear values to be compared with calculated difference value to light appropriate number of LEDs */
int scale = 80;

void setup() {
  for(int i=0; i<10; i++) {
    pinMode(ledBarPins[i], OUTPUT);
    digitalWrite(ledBarPins[i], HIGH);
  }
}

void loop() {
  sensorValue = maxValue = minValue = analogRead(analogInPin);
  for(int i=0; i<NO_ADC_READS; i++) {
    sensorValue = analogRead(analogInPin);
    if(sensorValue>maxValue) { maxValue = sensorValue; }
    if(sensorValue<minValue) { minValue = sensorValue; }
  }
  difference = maxValue - minValue;
  for(int i=0; i<10; i++) {
    digitalWrite(ledBarPins[i], (difference>=scale*i)?LOW:HIGH);
  }
}
