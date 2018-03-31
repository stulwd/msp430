#include <Arduino.h>


int test = P1_4;
int button = PUSH2;
int a_in = A5;    //adc P1_5

// setup initializes serial and the button pin
void setup()
{
  Serial.begin(115200);               //uart
  pinMode(test, INPUT_PULLUP);        //digital input.
  pinMode(RED_LED, OUTPUT);           //red output
  pinMode(GREEN_LED, OUTPUT);         //gled output.
  pinMode(button, INPUT_PULLUP);      //button input.
}

// loop checks the button pin each time,
// and will send serial if it is pressed
void loop()
{
  /*****blink*****/
  if(digitalRead(GREEN_LED))  {digitalWrite(GREEN_LED,LOW);digitalWrite(RED_LED,HIGH);}
  else {digitalWrite(GREEN_LED, HIGH);digitalWrite(RED_LED,LOW);}

  /****test******/
  if (digitalRead(test) == HIGH)
  {
    Serial.write('H');
  }
  else
  {
    Serial.write('L');
  }

  /******button********/
  Serial.println("just a test!\n");
  if (0 == digitalRead(button))         //low-level when button pressed.
  {
    Serial.println("button is pushed.\n" );
  }

  /*********ADC*********/
  Serial.print("adc intput value =");
  Serial.print(analogRead(a_in));
  Serial.print("\n");



  delay(1000);

}
