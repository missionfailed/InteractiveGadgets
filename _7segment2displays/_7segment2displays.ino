#include <Time.h>

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

//button states
int buttonState1 = 0;         // variable for reading the pushbutton1 status (Change Digits DOWN or START TIMER)
int buttonState2 = 0;         // variable for reading the pushbutton2 status (Change Digits UP or START TIMER)
int buttonState3 = 0;         // variable for reading the pushbutton3 status (Set up alarm button)

//piezo variables and muric
int length = 15; // the number of notes
char notes[] = "EDEDEbDCaceabegbCeEDEDEbDCaceabeCbaEDEDEbDCaceabegbCeEDEDEbDCaceabeCbabCDEgFEDfEDCeDCbeEeEDEDEDEDEDEDEbDCaceabegbCeEDEDE"; 
//              E D E D E b D C a c e a b e g b C e E D|E D E b D C a c e a b e C b a E D E D E b D C|a c e a b e g b C e E D E D E b D C a c e a|b e C b a b C D E g F E D f E D C e D C|b e E e E D E D E D E D E D E D E b D C a c e a b e g b C e E D E D E b D C a c e a b e C b a
int beats[] = { 1,1,1,1,1,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,1,1,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,3,1,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,3,1,1,1,6};
int tempo = 175;
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
int counter =0;
int i;

//matrix display
byte matrix1[8]= {B11100111,B10101010,~B10101010,B10101010, B00001111,B11001100,B00110011,B10101010};

//time variables
time_t t;
int settingAlarm;
int timechanger;
int alarm[] = {100,100};//set alarm at an impossible time
int start;

void setup()
{
  settingAlarm=0;
  timechanger=0;
  start=0;
  
  //Led pin on indicates no alarm
  digitalWrite(ledpin,HIGH);
  
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

  //Start time in Zeros
  writeToSegments(0,0,0,0,0);
 
}

void loop()
{
    if(digitalRead(ledpin) == HIGH)
    {
          //Read from alarm button, see if user wants to set the alarm
          buttonState3=digitalRead(buttonpin3);

          if(buttonState3==HIGH)
          {//Press the button once to set minutes, twice to set seconds, thrice to finish
              if(settingAlarm==0)
                settingAlarm=1;
              else if(settingAlarm==1)
                settingAlarm=2;  
              else if(settingAlarm==2)
                settingAlarm=0;
          }

           if(settingAlarm!=0)
           {//If the user has pushed the button to set the alarm
                        
           buttonState1=digitalRead(buttonpin1);
           buttonState2=digitalRead(buttonpin2);
          
           int changeTime1, changeTime2;
    
           if(buttonState2==HIGH)
           {//Adds up minutes until 59 then loops around
              if (timechanger>=59)
                timechanger=0;
              else
               timechanger++;
           }
           if(buttonState1==HIGH)
           {//Subtracts minutes until 0 then loops around
              if (timechanger<=0)
                timechanger=59;
              else
               timechanger--;
                        
           }
    
            if(timechanger>=10)
            {//Get first and second digits if they are greater than 10
              changeTime1= timechanger/10;
              changeTime2= timechanger%10;
            }
            else
            {//Get second digit and set first as 0
              changeTime1=0;
              changeTime2=timechanger;
            }
    
           if(settingAlarm==1)
           {//Set alarm minutes
               writeToSegmentPair1(changeTime1,changeTime2,0);
               alarm[0]=timechanger;
           }   
           else if (settingAlarm==2)
           {//Set alarm seconds
              writeToSegmentPair2(changeTime1,changeTime2,0);   
              alarm[1]=timechanger;  
           }

        }

           if(alarm[0]!=100 && alarm[1]!=100 && settingAlarm==0)
           {//The alarm has been set, get out of here           
              setTime(0);
              digitalWrite(ledpin,LOW);             
           }   
    }
   
    else
    {//When not setting up the alarm
      
          //Save current time  
          int minutes,minutes1,minutes2;
          int seconds,seconds1,seconds2;

          minutes=minute();
          seconds=second();
        
          if(minutes>=10)
          {//Get minutes
            minutes1= minutes/10;
            minutes2= minutes%10;
          }
          else
          {
            minutes1=0;
            minutes2=minutes;
          }
          
          if(seconds>=10)
          {//Get seconds
            seconds1= seconds/10;
            seconds2= seconds%10;
          }
          else
          {
            seconds1=0;
            seconds2=seconds;
          }

          //Display current time
          writeToSegments(minutes1,minutes2,seconds1,seconds2,0);
    
          //TURN ON THE ALARM IF THE RIGHT TIME IS ON
          if(alarm[1]==seconds && alarm[0]==minutes)
          {
             alarmSounds(1);
             //Start over configuration
             digitalWrite(ledpin,HIGH);
             timechanger=0;
             settingAlarm=0;
             alarm[0]=alarm[1]=100;
             writeToSegments(0,0,0,0,0);
          }
    }
             
    delay(200);     
    
}

void writeToSegments(int min1, int min2, int sec1, int sec2, int delayy)
{//Write to displays
       writeToSegmentPair1(min1,min2,delayy);
       writeToSegmentPair2(sec1,sec2,delayy);
}

void writeToSegmentPair1(int min1, int min2, int delayy)
{//Write to minutes
       digitalWrite(LATCH, LOW);
       shiftOut(DATA, CLK, MSBFIRST, digits1[min1]); // digit1
       shiftOut(DATA, CLK, MSBFIRST, digits2[min2]); // digit2
       digitalWrite(LATCH, HIGH);
}

void writeToSegmentPair2(int sec1, int sec2, int delayy)
{//Write to seconds
       digitalWrite(LATCH2, LOW);
       shiftOut(DATA2, CLK2, MSBFIRST, digits3[sec2]); // digit4
       shiftOut(DATA2, CLK2, MSBFIRST, digits4[sec1]); // digit3
       digitalWrite(LATCH2, HIGH); 
}

void displayMatrix(int on, int delayy)
{//Turn matrix on/off (for debbugging matrix)
       if(on)
       {
        for(int i=0; i<8 ; i++)
        {
                 digitalWrite(LATCH3, LOW);
                 shiftOut(DATA3, CLK3, MSBFIRST, matrix1[i]); // digit4
                 digitalWrite(LATCH3, HIGH); 
                 delay(delayy);
        }
       }
       else
       {//off
                 digitalWrite(LATCH3, LOW);
                 shiftOut(DATA3, CLK3, MSBFIRST, B00000000); // digit4
                 digitalWrite(LATCH3, HIGH); 
       }
}

//FOR IMPERIAL MARCH obtained from: http://forum.arduino.cc/index.php?topic=259450.0
void alarmSounds(int one)
{

  //Play first section
  firstSection();

  //Play second section
  secondSection();

  //Variant 1
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);

  delay(500);

  //Repeat second section
  secondSection();

  //Variant 2
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  

  //turn off the matrix
  digitalWrite(LATCH3, LOW);
  shiftOut(DATA3, CLK3, MSBFIRST, B00000000);
  digitalWrite(LATCH3, HIGH); 
}

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(piezopin, note, duration);

  //Play with the matrix depending on value of 'counter'
  if(counter % 2 == 0)
  {
    digitalWrite(LATCH3, LOW);
    shiftOut(DATA3, CLK3, MSBFIRST, matrix1[counter%8]);
    digitalWrite(LATCH3, HIGH); 
    delay(duration);
    Serial.println("low");
  }else
  {
    digitalWrite(LATCH3, LOW);
    shiftOut(DATA3, CLK3, MSBFIRST, matrix1[counter%8]);
    digitalWrite(LATCH3, HIGH); 
    delay(duration);
     Serial.println("low");
  }

  //Stop tone on buzzerPin
  noTone(piezopin);

  delay(50);

  //Increment counter
  counter++;
}

void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);
}

void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);

  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  

  delay(350);
}


/* COMMENTED CODE, PLAYS TWINKLE TWINKLE OR FUR ELISE, but must change on loop to use function alarmSounds2
void alarmSounds2(int high)
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
  //char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' }; Twinkle Twinkle
 // int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 char names[] = {'c','d','e','f','g','a','b','C', 'D', 'E', 'F', 'G', 'A', 'B', 'U'}; Fur Elise
  int tones[] = {3822,3424,3033,2864,2551,2272,2024, 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};


  // play the tone corresponding to the note name
  for (int i = 0; i < sizeof(tones); i++) 
  {             
    //AND PLAY TONE
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
    //LIGHT UP AS THE SOUND PLAYS
    digitalWrite(LATCH3, LOW);
    shiftOut(DATA3, CLK3, MSBFIRST, matrix1[i%8]);
    digitalWrite(LATCH3, HIGH); 
  }
}*/



