/*
 * LED Matrix Display Program
 * This program displays two numbers [0-9] on a 7-segment LED matrix display.
 * 
 * By: Graciela Garcia, but arrays of bytes at the bottom were taken from 
 * user @elexhack at http://www.instructables.com/id/Room-Temperature-in-Dot-Matrix-Display-with-Arduin/
 */
 
#include "LedControl.h" //include library for interfacing MAX7219
LedControl lc=LedControl(12,11,10,1);
int reading; //for reading a number in the future, not useful now
const int number= 24; //number to display

void setup() 
{
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

int ones(int t)
{//get first number of t
  return ((int)t/10);
}

int tenths(int t)
{//get second number of t
  return t%10;
}

void upperglow()
{//display left number on display
  int i=tenths(number);
  switch (i)
  {
    case 0:
      lzero();
      break;        
    case 1:
      lone();
      break;
    case 2:
      ltwo();
      break;
    case 3:
      lthree();
      break;
    case 4:
      lfour();
      break;
    case 5:
      lfive();
      break;
    case 6:
      lsix();
      break;
    case 7:
      lseven();
      break;
    case 8:
      leight();
      break;
    case 9:
      lnine();
      break;
    default:
      break;
  }

  
}

void lowerglow()
{//display second number on display
  
  int i=ones(number);
  switch (i)
  {
    case 0:
      rzero();
      break;        
    case 1:
      rone();
      break;
    case 2:
      rtwo();
      break;
    case 3:
      rthree();
      break;
    case 4:
      rfour();
      break;
    case 5:
      rfive();
      break;
    case 6:
      rsix();
      break;
    case 7:
      rseven();
      break;
    case 8:
      reight();
      break;
    case 9:
      rnine();
      break;
    default:
      break;
  }
  
}

void loop() 
{
  upperglow();
  lowerglow();
}

//The following functions are the ones user elexhack made, thank you! The names of the functions stand for (left or right number) and then the number to display (zero-nine)
void rzero()
{
  byte zero[8]={B00000000, B00000000, B00000110, B00001001, B00001001, B00001001, B00000110, B00000000};
  lc.setRow(0,0, zero[0]);
  lc.setRow(0,1, zero[1]);
  lc.setRow(0,2, zero[2]);
  lc.setRow(0,3, zero[3]);
  lc.setRow(0,4, zero[4]);
  lc.setRow(0,5, zero[5]);
  lc.setRow(0,6, zero[6]);
  lc.setRow(0,7, zero[7]);
}

void rone()
{
  byte one[8]={B00000000, B00000000, B00000010, B00000110, B00000010, B00000010, B00000111, B00000000};
  lc.setRow(0,0, one[0]);
  lc.setRow(0,1, one[1]);
  lc.setRow(0,2, one[2]);
  lc.setRow(0,3, one[3]);
  lc.setRow(0,4, one[4]);
  lc.setRow(0,5, one[5]);
  lc.setRow(0,6, one[6]);
  lc.setRow(0,7, one[7]);
}

void rtwo()
{
  byte two[8]={B00000000, B00000000, B00000010, B00000101, B00000010, B00000100, B00000111, B00000000};
  lc.setRow(0,0, two[0]);
  lc.setRow(0,1, two[1]);
  lc.setRow(0,2, two[2]);
  lc.setRow(0,3, two[3]);
  lc.setRow(0,4, two[4]);
  lc.setRow(0,5, two[5]);
  lc.setRow(0,6, two[6]);
  lc.setRow(0,7, two[7]);
}

void rthree()
{
  byte three[8]={B00000000, B00000000, B00000110, B00000001, B00000010, B00000001, B00000110, B00000000};
  lc.setRow(0,0, three[0]);
  lc.setRow(0,1, three[1]);
  lc.setRow(0,2, three[2]);
  lc.setRow(0,3, three[3]);
  lc.setRow(0,4, three[4]);
  lc.setRow(0,5, three[5]);
  lc.setRow(0,6, three[6]);
  lc.setRow(0,7, three[7]);
}

void rfour()
{
  byte four[8]={B00000000, B00000000, B00000101, B00000101, B00000111, B00000001, B00000001, B00000000};
  lc.setRow(0,0, four[0]);
  lc.setRow(0,1, four[1]);
  lc.setRow(0,2, four[2]);
  lc.setRow(0,3, four[3]);
  lc.setRow(0,4, four[4]);
  lc.setRow(0,5, four[5]);
  lc.setRow(0,6, four[6]);
  lc.setRow(0,7, four[7]);
}

void rfive()
{
  byte five[8]={B00000000, B00000000, B00000111, B00000100, B00000111, B00000001, B00000111, B00000000};
  lc.setRow(0,0, five[0]);
  lc.setRow(0,1, five[1]);
  lc.setRow(0,2, five[2]);
  lc.setRow(0,3, five[3]);
  lc.setRow(0,4, five[4]);
  lc.setRow(0,5, five[5]);
  lc.setRow(0,6, five[6]);
  lc.setRow(0,7, five[7]);
}

void rsix()
{
  byte six[8]={B00000000, B00000000, B00000100, B00001000, B00001110, B0001010, B00000100, B00000000};
  lc.setRow(0,0, six[0]);
  lc.setRow(0,1, six[1]);
  lc.setRow(0,2, six[2]);
  lc.setRow(0,3, six[3]);
  lc.setRow(0,4, six[4]);
  lc.setRow(0,5, six[5]);
  lc.setRow(0,6, six[6]);
  lc.setRow(0,7, six[7]);
}

void rseven()
{
  byte seven[8]={B00000000, B00000000, B00001111, B00000001, B00000010, B00000100, B00001000, B00000000};
  lc.setRow(0,0, seven[0]);
  lc.setRow(0,1, seven[1]);
  lc.setRow(0,2, seven[2]);
  lc.setRow(0,3, seven[3]);
  lc.setRow(0,4, seven[4]);
  lc.setRow(0,5, seven[5]);
  lc.setRow(0,6, seven[6]);
  lc.setRow(0,7, seven[7]);
}

void reight()
{
  byte eight[8]={B00000000, B00000000, B00000110, B00001001, B00000110, B00001001, B00000110, B00000000};
  lc.setRow(0,0, eight[0]);
  lc.setRow(0,1, eight[1]);
  lc.setRow(0,2, eight[2]);
  lc.setRow(0,3, eight[3]);
  lc.setRow(0,4, eight[4]);
  lc.setRow(0,5, eight[5]);
  lc.setRow(0,6, eight[6]);
  lc.setRow(0,7, eight[7]);
}

void rnine()
{
  byte nine[8]={B00000000, B00000000, B00000100, B00001010, B00001110, B00000010, B00000100, B00000000};
  lc.setRow(0,0, nine[0]);
  lc.setRow(0,1, nine[1]);
  lc.setRow(0,2, nine[2]);
  lc.setRow(0,3, nine[3]);
  lc.setRow(0,4, nine[4]);
  lc.setRow(0,5, nine[5]);
  lc.setRow(0,6, nine[6]);
  lc.setRow(0,7, nine[7]);
}

void lzero()
{
  byte zero[8]={B00000000, B00000000, B01100000, B10010000, B10010000, B10010000, B01100000, B00000000};
  lc.setRow(0,0, zero[0]);
  lc.setRow(0,1, zero[1]);
  lc.setRow(0,2, zero[2]);
  lc.setRow(0,3, zero[3]);
  lc.setRow(0,4, zero[4]);
  lc.setRow(0,5, zero[5]);
  lc.setRow(0,6, zero[6]);
  lc.setRow(0,7, zero[7]);
}

void lone()
{
  byte one[8]={B00000000, B00000000, B00100000, B01100000, B00100000, B00100000, B01110000, B00000000};
  lc.setRow(0,0, one[0]);
  lc.setRow(0,1, one[1]);
  lc.setRow(0,2, one[2]);
  lc.setRow(0,3, one[3]);
  lc.setRow(0,4, one[4]);
  lc.setRow(0,5, one[5]);
  lc.setRow(0,6, one[6]);
  lc.setRow(0,7, one[7]);
}

void ltwo()
{
  byte two[8]={B00000000, B00000000, B00100000, B01010000, B00100000, B01000000, B01110000, B00000000};
  lc.setRow(0,0, two[0]);
  lc.setRow(0,1, two[1]);
  lc.setRow(0,2, two[2]);
  lc.setRow(0,3, two[3]);
  lc.setRow(0,4, two[4]);
  lc.setRow(0,5, two[5]);
  lc.setRow(0,6, two[6]);
  lc.setRow(0,7, two[7]);
}

void lthree()
{
  byte three[8]={B00000000, B00000000, B01100000, B00010000, B00100000, B00010000, B01100000, B00000000};
  lc.setRow(0,0, three[0]);
  lc.setRow(0,1, three[1]);
  lc.setRow(0,2, three[2]);
  lc.setRow(0,3, three[3]);
  lc.setRow(0,4, three[4]);
  lc.setRow(0,5, three[5]);
  lc.setRow(0,6, three[6]);
  lc.setRow(0,7, three[7]);
}

void lfour()
{
  byte four[8]={B00000000, B00000000, B01010000, B01010000, B01110000, B00010000, B00010000, B00000000};
  lc.setRow(0,0, four[0]);
  lc.setRow(0,1, four[1]);
  lc.setRow(0,2, four[2]);
  lc.setRow(0,3, four[3]);
  lc.setRow(0,4, four[4]);
  lc.setRow(0,5, four[5]);
  lc.setRow(0,6, four[6]);
  lc.setRow(0,7, four[7]);
}

void lfive()
{
  byte five[8]={B00000000, B00000000, B01110000, B01000000, B01110000, B00010000, B01110000, B00000000};
  lc.setRow(0,0, five[0]);
  lc.setRow(0,1, five[1]);
  lc.setRow(0,2, five[2]);
  lc.setRow(0,3, five[3]);
  lc.setRow(0,4, five[4]);
  lc.setRow(0,5, five[5]);
  lc.setRow(0,6, five[6]);
  lc.setRow(0,7, five[7]);
}

void lsix()
{
  byte six[8]={B00000000, B00000000, B01000000, B10000000, B11100000, B10100000, B01000000, B00000000};
  lc.setRow(0,0, six[0]);
  lc.setRow(0,1, six[1]);
  lc.setRow(0,2, six[2]);
  lc.setRow(0,3, six[3]);
  lc.setRow(0,4, six[4]);
  lc.setRow(0,5, six[5]);
  lc.setRow(0,6, six[6]);
  lc.setRow(0,7, six[7]);
}

void lseven()
{
  byte seven[8]={B00000000, B00000000, B11110000, B00010000, B00100000, B01000000, B10000000, B00000000};
  lc.setRow(0,0, seven[0]);
  lc.setRow(0,1, seven[1]);
  lc.setRow(0,2, seven[2]);
  lc.setRow(0,3, seven[3]);
  lc.setRow(0,4, seven[4]);
  lc.setRow(0,5, seven[5]);
  lc.setRow(0,6, seven[6]);
  lc.setRow(0,7, seven[7]);
}

void leight()
{
  byte eight[8]={B00000000, B00000000, B01100000, B10010000, B01100000, B10010000, B01100000, B00000000};
  lc.setRow(0,0, eight[0]);
  lc.setRow(0,1, eight[1]);
  lc.setRow(0,2, eight[2]);
  lc.setRow(0,3, eight[3]);
  lc.setRow(0,4, eight[4]);
  lc.setRow(0,5, eight[5]);
  lc.setRow(0,6, eight[6]);
  lc.setRow(0,7, eight[7]);
}

void lnine()
{
  byte nine[8]={B00000000, B00000000, B01000000, B10100000, B11100000, B00100000, B01000000, B00000000};
  lc.setRow(0,0, nine[0]);
  lc.setRow(0,1, nine[1]);
  lc.setRow(0,2, nine[2]);
  lc.setRow(0,3, nine[3]);
  lc.setRow(0,4, nine[4]);
  lc.setRow(0,5, nine[5]);
  lc.setRow(0,6, nine[6]);
  lc.setRow(0,7, nine[7]);
}

