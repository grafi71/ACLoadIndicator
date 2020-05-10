/*
  Arduino AC Power indicator using LED bar with 10 LEDs
  Configured for 20A sensor SC-013 type
*/

/* Number of test blinks */
#define NO_BLINK 3
/* Delay ms for blink */
#define DELAY_BLINK 100
/* Number of AC reads to be performed to get min and max values */
#define NO_ADC_READS 500
/* Number of LEDs in a bar */
#define NO_LEDS 10
/* Loop time in ms */
#define TIME_LOOP 1000
/* How many ms wait in a loop */
#define LOOP_DELAY 50

/* Analog input pin to connect directly to sensor */
const int analogInPin = A3;  
/* Arduino outputs to be connected with LEDs */
const int ledBarPins[NO_LEDS] = {2,3,4,5,6,7,8,9,11,10};
/* Store value red from sensor */
int sensorValue = 0;  
/* Store min value */
int minValue = 0;
/* Store max value */
int maxValue = 0;
/* Calculate difference (maxValue-minValue) */
int difference = 0;
/* Linear values to be compared with calculated difference value to light appropriate number of LEDs */
int scale = 50;
long timeStart;

// Test internal LED
void blinkBuiltInLed() {
  for(int n=0; n<NO_BLINK; n++) {
    for(int i=0;i <2; i++) {
      digitalWrite(LED_BUILTIN, (i)?LOW:HIGH);
      delay(DELAY_BLINK);
    }
  }
}

void blinkLedBar() {
  // Test LED bar
  for(int n=0; n<NO_BLINK; n++) {
    for(int i=0; i<NO_LEDS; i++) {
      for(int j=0; j<NO_LEDS; j++) {
        digitalWrite(ledBarPins[j], (j==i)?HIGH:LOW);
      }
      delay(DELAY_BLINK);
    }
  }
}

void initIndicatorLeds() {
  blinkBuiltInLed();
  blinkLedBar();
}

void setup() {
  //Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i=0; i<NO_LEDS; i++) {
    pinMode(ledBarPins[i], OUTPUT);
    digitalWrite(ledBarPins[i], LOW);
  }
  initIndicatorLeds();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  timeStart = millis();
  sensorValue = maxValue = minValue = analogRead(analogInPin);
  
  for(int i=0; i<NO_ADC_READS; i++) {
    sensorValue = analogRead(analogInPin);
    if(sensorValue>maxValue) { maxValue = sensorValue; }
    if(sensorValue<minValue) { minValue = sensorValue; }
  }
  difference = maxValue - minValue;

  for(int i=0; i<NO_LEDS; i++) {
    digitalWrite(ledBarPins[i], (difference>=scale*i)?HIGH:LOW);
  }  
  
//  Serial.print(minValue);
//  Serial.print("\t");
//  Serial.print(maxValue);
//  Serial.print("\t");
//  Serial.print(timeStart);
//  Serial.print("\t");
//  Serial.println(difference);
  
  digitalWrite(LED_BUILTIN, LOW);

  while((millis() - timeStart)<TIME_LOOP) {
    delay(LOOP_DELAY);
  }
  
}
