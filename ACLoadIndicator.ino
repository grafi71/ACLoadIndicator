/*
  Power indicator, bar led is scaled for 20A sensor to show max load of 16A
*/

#define NO_ADC_READS 1700

const int analogInPin = A0;  // Analog input pin 
const int ledBarPins[]={2,3,4,10,11,5,6,7,8,9};

int sensorValue = 0;        // value read from the pot
int minValue = 0;
int maxValue = 0;
int difference = 0;
int scaled[] = {0, 80, 160, 240, 320, 400, 480, 560, 640, 720};

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
    digitalWrite(ledBarPins[i], (difference>=scaled[i])?LOW:HIGH);
  }
}
