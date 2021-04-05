///////////////////////////
// USER-DEFINABLE VALUES //
///////////////////////////
#define PULSE_VCC_1             7 // digital pin, pulse IR LED 1
#define PULSE_VCC_2             8 // digital pin, pulse IR LED 2
#define READ_PIN                A1 // analog pin, read phototransistor
#define ADC_PRESCALER_VAL       32 // sets the value of the ADC prescaler
#define BAUD_RATE               1000000
#define SAMPLE_DELAY            1000 // us delay between samples. There is a min sample time of ~16us.
#define PRINT_BG_LIGHT          true
#define PRINT_BG_MAX            false
#define PRINT_UNFILTERED        false
#define PRINT_ADJUSTED          true
////////////////////////////////
// END USER-DEFINABLE VALUESS //
////////////////////////////////

float pulse1_reading = 0;
float pulse2_reading = 2;
float bothOn_reading = 0;

// valid arg values are 2, 4, 8, 16, 32, 64, 128
void set_ADC_prescaler(int val) {
  if (val == 2) {
    bitSet(ADCSRA,ADPS0);
    bitClear(ADCSRA,ADPS1);
    bitClear(ADCSRA,ADPS2);
  } else if (val == 4) {
    bitClear(ADCSRA,ADPS0);
    bitSet(ADCSRA,ADPS1);
    bitClear(ADCSRA,ADPS2);
  } else if (val == 8) {
    bitSet(ADCSRA,ADPS0);
    bitSet(ADCSRA,ADPS1);
    bitClear(ADCSRA,ADPS2);
  } else if (val == 16) {
    bitClear(ADCSRA,ADPS0);
    bitClear(ADCSRA,ADPS1);
    bitSet(ADCSRA,ADPS2);
  } else if (val == 32) {
    bitSet(ADCSRA,ADPS0);
    bitClear(ADCSRA,ADPS1);
    bitSet(ADCSRA,ADPS2);
  } else if (val == 64) {
    bitClear(ADCSRA,ADPS0);
    bitSet(ADCSRA,ADPS1);
    bitSet(ADCSRA,ADPS2);
  } else if (val == 128) {
    bitSet(ADCSRA,ADPS0);
    bitSet(ADCSRA,ADPS1);
    bitSet(ADCSRA,ADPS2);
  } else {
    return;
  }
}

void setup() {
Serial.begin(BAUD_RATE);
  pinMode(PULSE_VCC_1, OUTPUT);
  pinMode(PULSE_VCC_2, OUTPUT);
  digitalWrite(PULSE_VCC_1, HIGH); // start with LED 1 on
  digitalWrite(PULSE_VCC_2, LOW); // start with LED 2 off
  delay(1000);}

void loop() {
  // 1) read LED 1, switch to LED 2
  pulse1_reading = analogRead(READ_PIN);
  digitalWrite(PULSE_VCC_1, LOW);
  digitalWrite(PULSE_VCC_2, HIGH);
  delayMicroseconds(SAMPLE_DELAY);
  // 2) read LED 2, switch both on
  pulse2_reading = analogRead(READ_PIN);
  digitalWrite(PULSE_VCC_1, HIGH);
  delayMicroseconds(SAMPLE_DELAY);
  // 3) read both, switch LED 2 off for next loop
  bothOn_reading = analogRead(READ_PIN);
  digitalWrite(PULSE_VCC_2, LOW);
  delayMicroseconds(SAMPLE_DELAY);

  // 4) OUTPUT
  Serial.print(pulse1_reading*5/1023);
  Serial.print(",");
  Serial.print(pulse2_reading*5/1023);
  Serial.print(",");
  Serial.println(bothOn_reading*5/1023);
}
