#define LATCH 4
#define CLK 3
#define DATA 2

#define LATCH2 7
#define CLK2 6
#define DATA2 5

//pins
const int buttonpin1 = 10;     // the number of the pushbutton1 pin
const int buttonpin2 = 11;     // the number of the pushbutton2 pin
const int ledpin = 9;

//numbers
byte digits1[10]= {B10000000, B11110010, B01001000, B01100000, B00110011, B00100100, B00000101, B11110001, B00000000, B00100000};//0,1,2,3,4,5,6,8,9
byte digits2[10]= {B10000000, B11110010, B01001000, B01100000, B00110011, B00100100, B00000101, B11110001, B00000000, B00100000};//0,1,2,3,4,5,6,8,9
byte digits3[10]= {~B01000000, ~B11110010, ~B10001000, ~B10100000, ~B00110011, ~B00100100, ~B00000101, ~B11110001, ~B00000000, ~B00100000};//0,1,2,3,4,5,6,8,9
byte digits4[10]= {~B01000000, ~B11110010, ~B10001000, ~B10100000, ~B00110011, ~B00100100, ~B00000101, ~B11110001, ~B00000000, ~B00100000};//0,1,2,3,4,5,6,8,9

int i;
int buttonState1 = 0;         // variable for reading the pushbutton1 status
int buttonState2 = 0;         // variable for reading the pushbutton2 status

void setup()
{
 //Seven segment displays
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH2, OUTPUT);
  pinMode(CLK2, OUTPUT);
  pinMode(DATA2, OUTPUT);
  Serial.begin(9600);

  //Buttons
  pinMode(buttonpin1, OUTPUT);
  pinMode(buttonpin2, OUTPUT);
  pinMode(ledpin, OUTPUT);
 
}

void loop()
{
    buttonState1=digitalRead(buttonpin1);

    if(buttonState1==HIGH)
      Serial.println("pressed1");


    buttonState2=digitalRead(buttonpin2);

    if(buttonState2==HIGH)
      Serial.println("pressed2");

    
    /*
    for(int i=0; i<10; i++)
    {
      for(int j=0; j<10; j++)
      {
       digitalWrite(LATCH, LOW);
       shiftOut(DATA, CLK, MSBFIRST, digits1[i]); // digitTwo
       shiftOut(DATA, CLK, MSBFIRST, digits2[j]); // digitOne
       digitalWrite(LATCH, HIGH);
       
       digitalWrite(LATCH2, LOW);
       shiftOut(DATA2, CLK2, MSBFIRST, digits3[j]); // digitTwo
       shiftOut(DATA2, CLK2, MSBFIRST, digits4[i]); // digitTwo
       digitalWrite(LATCH2, HIGH);
       delay(1000);
      }
    }
    */
    
}

