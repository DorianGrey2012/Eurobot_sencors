
#define encoder0pinA  2//A pin -> the interrupt pin 0
#define encoder0pinB  4//B pin -> the digital pin 4
#define encoder1pinA  3//A pin -> the interrupt pin 0
#define encoder1pinB  5//B pin -> the digital pin 4
#define cvetn 8
#define shnurok 9
byte encoder0PinALast;
byte encoder1PinALast;
int duration;//the number of the pulses
int duration1;//the number of the pulses
boolean Direction;//the rotation direction 
boolean Direction1;//the rotation direction 
//boolean cvetnost;//the rotation direction 
//boolean raz;//the rotation direction 
float distance,distance1=0.0;
int distpin[6] = {
  A0,A1,A2,A3,A4,A5};
int val[6]={
  0,0,0,0,0,0};
String sensor_data="";
String space=" ";
const float pi = 3.1415926;

void setup()
{
  for (int i=0;i<6;i++)
  {
    pinMode(distpin[i], INPUT);
    digitalWrite(distpin[i], HIGH);
  }
  pinMode(cvetn, INPUT);
  pinMode(shnurok, INPUT);
  Serial.begin(57600);
  EncoderInit();
  delay(50);
}

void loop()
{
  int cvet=digitalRead(cvetn);
  int shnur=digitalRead(shnurok);


  if(Serial.available())
  {
    char value = Serial.read();
    if(value != -1)
    {
      switch(value)
      {
      case 'f'://Move Forward fast
        //advance(255,255);
        for  (int i=0;i<6;i++)
        {
          val[i] = digitalRead(distpin[i]);
          sensor_data+=val[i]+space;
        }
        Serial.println(sensor_data);
        sensor_data="";
        break;
      case 'g'://Move Forward fast
        //advance(255,255);
        distance1=(pi/6)*duration1;
        distance=(pi/6)*duration;
        // Serial.print("Pulse1:");
        // Serial.print(duration1);
        //Serial.print("Pulse:");
        //Serial.println(duration);
        Serial.print(" Distance:");
        Serial.print(distance);
        Serial.print("  Distance1:");
        Serial.println(distance1);
        break;
      case 'e'://Move Forward fast
        duration=0;
        duration1=0;
        break;
       case 'h'://Move Forward fast
        Serial.println(shnur);
        break;
        case 'c'://Move Forward fast
        Serial.println(cvet);
        break;
      }
    }
  }

}
void EncoderInit()

{
  Direction = true;//default -> Forward  
  pinMode(encoder0pinB,INPUT); 
  pinMode(encoder1pinB,INPUT);  
  attachInterrupt(0, wheelSpeed, CHANGE);
  attachInterrupt(1, wheelSpeed1, CHANGE);
}

void wheelSpeed()
{
  int Lstate = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoder0pinB);
    if(val == LOW && Direction)
    {
      Direction = false; //Reverse
    }
    else if(val == HIGH && !Direction)
    {
      Direction = true;  //Forward
    }
  }
  encoder0PinALast = Lstate;

  if(!Direction)  duration++;
  else  duration--;
}
void wheelSpeed1()
{
  int Lstate1 = digitalRead(encoder1pinA);
  if((encoder1PinALast == LOW) && Lstate1==HIGH)
  {
    int val1 = digitalRead(encoder1pinB);
    if(val1 == LOW && Direction1)
    {
      Direction1 = false; //Reverse
    }
    else if(val1 == HIGH && !Direction1)
    {
      Direction1 = true;  //Forward
    }
  }
  encoder1PinALast = Lstate1;

  if(!Direction1)  duration1++;
  else  duration1--;
}
//void shnur ()
//{
//  int lenin=digitalRead(shnurok);
//  if(lenin == LOW)
//    raz = 0; //Reverse
//
//  else if (lenin == HIGH)
//    raz=1;
//}
//void cvet ()
//{
//  int svet=digitalRead(shnurok);
//  if(svet == LOW)
//    cvetnost = 0; //Reverse
//
//  else if (svet  == HIGH)
//    cvetnost=1;
//
//}


