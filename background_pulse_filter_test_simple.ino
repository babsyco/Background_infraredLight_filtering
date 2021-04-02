 ///////////////////////////
// USER-DEFINABLE VALUES //
///////////////////////////
#define PULSE_VCC               7 // digital pin, pulse IR LED
#define READ_PIN                A1 // analog pin, read phototransistor
#define IR_TEST_LED_VCC         8 // digital pin, power IR LED for background light simulation
#define ADC_PRESCALER_VAL       128 // sets the value of the ADC prescaler
#define BAUD_RATE               9600
#define SAMPLE_DELAY   500 // us delay between samples. There is a min sample time of ~16us. 380 works well.
#define PRINT_BG_MAX            false
#define PRINT_UNFILTERED        false
bool PRINT_BG_LIGHT =           true;
bool PROC_SIGNAL_FIT =          false;
////////////////////////////////
// END USER-DEFINABLE VALUESS //
////////////////////////////////

float bg_light = 0;
float bg_max = 0;
float pulse_sampled = 0;
float pulse_sampled_adjusted = 0;
float output = 0;
String user_input;
float signal_out = 0;

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

float process_data(float bg_light, float pulse_sampled) {
  return -0.024551 + -0.986701*bg_light + -0.257718*sq(bg_light) + 1.038322*pulse_sampled + -0.012698*sq(pulse_sampled) + 
                                                    0.283598*bg_light*pulse_sampled + -0.001620*sq(pulse_sampled)*sq(bg_light);
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(PULSE_VCC, OUTPUT);
  pinMode(IR_TEST_LED_VCC, OUTPUT);
  digitalWrite(IR_TEST_LED_VCC, HIGH); // turn on test IR LED
  digitalWrite(PULSE_VCC, LOW); // turn off IR LED for 1 second
  delay(1000);
}

void loop() {
  // check for/process user input
  while (Serial.available()) {
      user_input = Serial.readString();
      if (user_input == "bg_on") {
        PRINT_BG_LIGHT = true;
      }
      else if (user_input == "bg_off") {
        PRINT_BG_LIGHT = false;
      }
      if (user_input == "fit_on") {
        PROC_SIGNAL_FIT = true;
      }
      if (user_input == "fit_off") {
        PROC_SIGNAL_FIT = false;
      }
  
  }
  // acquire data
  bg_light = analogRead(READ_PIN);
  digitalWrite(PULSE_VCC, HIGH);
  delayMicroseconds(SAMPLE_DELAY);
  pulse_sampled = analogRead(READ_PIN);
  digitalWrite(PULSE_VCC, LOW);
  delayMicroseconds(SAMPLE_DELAY);

  // get max bg light values
  if (bg_light > bg_max) {
    bg_max = bg_light;
  }
  // convert to voltages
  bg_light = bg_light*5/1023;
  pulse_sampled = pulse_sampled*5/1023;
  
  // adjust with fit
  if (PROC_SIGNAL_FIT) {
    signal_out = process_data(bg_light, pulse_sampled);
  }
  else {
    signal_out = pulse_sampled - bg_light;
  }
  
  
  if (PRINT_BG_LIGHT) {
    Serial.print(bg_light);
    Serial.print(" ");
    if (PRINT_BG_MAX) {
      Serial.print(bg_max);
      Serial.print(" ");
    }
  }
  
  Serial.print(signal_out);
  
  if (PRINT_UNFILTERED) {
    Serial.print(" ");
    Serial.print(pulse_sampled);
    Serial.print(" ");
  }
  Serial.print("\n");
}
