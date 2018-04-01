#include <Arduino.h>


/*----------MPS430 G2553外设使用说明------------*/
/********************串口*******************************
*    实现语句：Serial.begin(115200);   //初始化串口，入参为波特率，可变。(引脚已封装好)
*             Serial.println("button is pushed.\n" );   //发送button is pushed。字符串
*    pin：    TX:P1_1  RX:P1_2
********************************************************/

/********************pin脚操作*******************************
*     实现语句：  pinMode(P1_0, OUTPUT);  //初始化P1_0为输出模式
*                pinMode(P1_1, INPUT_PULLUP);    //初始化P1_1为上拉输入
*                digitalWrite(P1_0, LOW)   //P1_0复位
*                digitalWrite(P1_0, HIGH)  //P1_0置位
*                state = digitalRead(P1_1)  //获取P1_1引脚电平
********************************************************/

/********************ADC*******************************
*    实现语句(样例)： Serial.print("adc intput value =");
*                    float voltage=analogRead(a_in)*(5.0/1023.0);
*                    Serial.print(voltage);
*                    Serial.print("\n");
*     说明：此example实现a_in引脚的电压获取并用串口打回，其中，
*          a_in引脚可选A0~A7，analogRead返回值为0~1023，要转换为实际voltage。
********************************************************/

/*************TIMER说明********************************
*         DAC使用方法（PWM+外部LPF脉宽调制法）
*    实现语句：analogWrite(pwm_out, fadeValue)；
*             pwm_out为以下列出pin脚，fadeValue为脉宽值（0~255）.
*             其中OUT0不能用。
*             若要输出两路PWM，则不能选同一通道下的两个pin，如P1_2和P1_5。
*     pin:  TIMER0:OUT0:P1_1 P1_5 P3_4
*                  OUT1:P1_2 P1_6 P2_6 P3_5
*                  OUT2:P3_0 P3_6
*          TIMER1:OUT0:P2_0 P2_3 P3_1
*                 OUT1:P2_1 P2_2 P3_2
*                 OUT2:P2_4 P2_5 P3_3
********************************************************/

int test = P1_4;      //P1_4
int button = PUSH2;  //P1_3
int a_in = A5;    //adc P1_5
int pwm_out = GREEN_LED;

// setup initializes serial and the button pin
void setup()
{
  Serial.begin(115200);               //uart
  pinMode(test, INPUT_PULLUP);        //digital input.
  pinMode(RED_LED, OUTPUT);           //red output
  pinMode(GREEN_LED, OUTPUT);         //gled output.
  pinMode(button, INPUT_PULLUP);      //button input.
  pinMode(a_in, INPUT_PULLUP);
}

// loop checks the button pin each time,
// and will send serial if it is pressed
void loop()
{
  /*****blink*****/
  // if(digitalRead(RED_LED))  {digitalWrite(RED_LED, LOW);}
  // else {digitalWrite(RED_LED,HIGH);}
digitalWrite(RED_LED, LOW);
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
  float voltage=analogRead(a_in)*(5.0/1023.0);
  Serial.print(voltage);
  Serial.print("\n");


  /********DAC**********/
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) {
  // 输出PWM
  analogWrite(pwm_out, fadeValue);
  // 等待30ms，以便观察到渐变效果
  delay(15);
  }
  for(int fadeValue = 255 ; fadeValue >= 5; fadeValue -=5) {
  // 输出PWM
  analogWrite(pwm_out, fadeValue);
  delay(15);
  }

  //delay(1000);

}
