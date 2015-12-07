#include <Time.h>
#include <TimeAlarms.h>

#define LATCH 4
#define CLK 3
#define DATA 2

#define LATCH2 7
#define CLK2 6
#define DATA2 5

#define LATCH3 A2
#define CLK3 A1
#define DATA3 A0

//pins
const int buttonpin1 = 10;     // the number of the pushbutton1 pin set time
const int buttonpin2 = 11;     // the number of the pushbutton2 pin set time
const int buttonpin3 = 12;     //set alarm
const int ledpin = 13;
const int piezopin = 8;

//numbers
byte digits1[10]= {B10000000, B11110010, B01001000, B01100000, B00110011, B00100100, B00000101, B11110001, B00000000, B00100000};//0,1,2,3,4,5,6,8,9
byte digits2[10]= {B10000000, B11110010, B01001000, B01100000, B00110011, B00100100, B00000101, B11110001, B00000000, B00100000};//0,1,2,3,4,5,6,8,9
byte digits3[10]= {~B01000000, ~B11110010, ~B10001000, ~B10100000, ~B00110011, ~B00100100, ~B00000101, ~B11110001, ~B00000000, ~B00100000};//0,1,2,3,4,5,6,8,9
byte digits4[10]= {~B01000000, ~B11110010, ~B10001000, ~B10100000, ~B00110011, ~B00100100, ~B00000101, ~B11110001, ~B00000000, ~B00100000};//0,1,2,3,4,5,6,8,9

int i;
int buttonState1 = 0;         // variable for reading the pushbutton1 status
int buttonState2 = 0;         // variable for reading the pushbutton2 status
int buttonState3 = 0;

//piezo variables
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

//matrix display
byte matrix1[8]= {B11111111,B10101010,~B10101010,B10101010, B00001111,B11001100,B00110011,B10101010};

//time variables
time_t t;
int settingAlarm;
int timechanger;
int alarm[] = {100,100};//set alarm at an impossible time

void setup()
{
  t = now();
  settingAlarm=0;
  timechanger=0;
 //Seven segment displays
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH2, OUTPUT);
  pinMode(CLK2, OUTPUT);
  pinMode(DATA2, OUTPUT);

  //matrix
  pinMode(LATCH3, OUTPUT);
  pinMode(CLK3, OUTPUT);
  pinMode(DATA3, OUTPUT);
  Serial.begin(9600);

  //Buttons
  pinMode(buttonpin1, OUTPUT);
  pinMode(buttonpin2, OUTPUT);
  pinMode(buttonpin3, OUTPUT);

  //LED and Piezo
  pinMode(ledpin, OUTPUT);
  pinMode(piezopin, OUTPUT);
 
}

void loop()
{
     
    int minutes,minutes1,minutes2;
    int seconds,seconds1,seconds2;

    minutes=minute();
    seconds=second();
        
    if(minutes>=10)
    {//Get minute
      minutes1= minutes/10;
      minutes2= minutes%10;
    }
    else
    {
      minutes1=0;
      minutes2=minutes;
    }
    
    if(seconds>=10)
    {//Get second
      seconds1= seconds/10;
      seconds2= seconds%10;
    }
    else
    {
      seconds1=0;
      seconds2=seconds;
    }
    
    //Read from alarm button, see if user wants to set the alarm
    buttonState3=digitalRead(buttonpin3);

    if(buttonState3==HIGH)
    {//Press the button once to set the alarm, press the button again to let the clock continue
        if(settingAlarm==0)
          settingAlarm=1;
        else if(settingAlarm==1)
          settingAlarm=2;  
        else if(settingAlarm==2)
          settingAlarm=0;
    }
    
    if(settingAlarm==0)
    {//if no alarm is being set continue displaying current time   
      writeToSegments(minutes1,minutes2,seconds1,seconds2,0);

      //ALLOW DISPLAY TO SHOW TIME BEFORE SETTING OFF THE ALARM
      if(alarm[1]==seconds && alarm[0]==minutes)
      {
         alarmSounds(1);
         digitalWrite(ledpin,LOW);
      }
      
      
      timechanger=0;
    }
    else
    {//if alarm is being set read from the buttons to set the alarm
        
       buttonState1=digitalRead(buttonpin1);
       buttonState2=digitalRead(buttonpin2);
       int changeTime1, changeTime2;

       if(buttonState2==HIGH)
       {
          if (timechanger>=59)
            timechanger=0;
          else
           timechanger++;
       }
       if(buttonState1==HIGH)
       {
          if (timechanger<=0)
            timechanger=59;
          else
           timechanger--;
                    
       }

        if(timechanger>=10)
        {//Get second
          changeTime1= timechanger/10;
          changeTime2= timechanger%10;
        }
        else
        {
          changeTime1=0;
          changeTime2=timechanger;
        }

       if(settingAlarm==1)
       {
           writeToSegmentPair1(changeTime1,changeTime2,0);
           alarm[0]=timechanger;
       }   
       else if (settingAlarm==2)
       {
          writeToSegmentPair2(changeTime1,changeTime2,0);   
          alarm[1]=timechanger;  
       }

       if(alarm[0]!=100 && alarm[1]!=100)
          digitalWrite(ledpin,HIGH);   
   
    }
             
    delay(200); 
    
    
}

void writeToSegments(int min1, int min2, int sec1, int sec2, int delayy)
{
       writeToSegmentPair1(min1,min2,delayy);
       writeToSegmentPair2(sec1,sec2,delayy);
}

void writeToSegmentPair1(int min1, int min2, int delayy)
{
       digitalWrite(LATCH, LOW);
       shiftOut(DATA, CLK, MSBFIRST, digits1[min1]); // digit1
       shiftOut(DATA, CLK, MSBFIRST, digits2[min2]); // digit2
       digitalWrite(LATCH, HIGH);
}

void writeToSegmentPair2(int sec1, int sec2, int delayy)
{
       digitalWrite(LATCH2, LOW);
       shiftOut(DATA2, CLK2, MSBFIRST, digits3[sec2]); // digit4
       shiftOut(DATA2, CLK2, MSBFIRST, digits4[sec1]); // digit3
       digitalWrite(LATCH2, HIGH); 
}

void displayMatrix(int on, int delayy)
{
       if(on)
       {
        for(int i=0; i<4 ; i++)
        {
                 digitalWrite(LATCH3, LOW);
                 shiftOut(DATA3, CLK3, MSBFIRST, matrix1[i]); // digit4
                 digitalWrite(LATCH3, HIGH); 
                 delay(delayy);
        }
       }
       else
       {
                 digitalWrite(LATCH3, LOW);
                 shiftOut(DATA3, CLK3, MSBFIRST, B00000000); // digit4
                 digitalWrite(LATCH3, HIGH); 
       }
}

void alarmSounds(int high)
{
    if(high==1)
    {
      for (int i = 0; i < length; i++)
      {
      if (notes[i] == ' ') 
      {
        delay(beats[i] * tempo); // rest
      } else 
      {
        playNote(notes[i], beats[i] * tempo);
      }
  
      // pause between notes
      delay(tempo / 2); 
    }    
    }

    //Turn off the lights
     digitalWrite(LATCH3, LOW);
     shiftOut(DATA3, CLK3, MSBFIRST, B00000000);
     digitalWrite(LATCH3, HIGH); 

}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) 
  {
    digitalWrite(piezopin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(piezopin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) 
  {              
    //LIGHT UP AS THE SOUND PLAYS
    digitalWrite(LATCH3, LOW);
    shiftOut(DATA3, CLK3, MSBFIRST, matrix1[i]);
    digitalWrite(LATCH3, HIGH); 

    //AND PLAY TONE
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}


