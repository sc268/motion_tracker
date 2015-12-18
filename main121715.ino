
/** Copy and paste data below----------------------------------------------------------------**/

float avgStart = -0.80;
float avgStop = 0.89;
float stdStart = 0.07;
float stdStop = 0.07;

//-------------------------------------------------------------------------------------------**/
int repsNeeded = 5;
int setsNeeded = 1;
int stdMultiplier = 1;



//Pitches______________________________________________________________________________________
/*************************************************
* Public Constants
*************************************************/

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#include <Wire.h> // Must include Wire library for I2C
#include <SFE_MMA8452Q.h> // Includes the SFE_MMA8452Q library*/
#include <Average.h>
#include <utility.h>
#include <StandardCplusplus.h>
#include <vector>
#include "data_processing.h"
#include <stdlib.h> 
using namespace std;

//_____________________________________________________________________________________________
MMA8452Q accel; // Default MMA8452Q object create. (Address = 0x1D)


int buzz_pin = 9;
int switch_pin = 2;
int calibration_button = 2;
float wantedValue[] = {avgStart,avgStop};
boolean index = true; //0 for start, 1 for stop
int set = 0;
float val;


//declare dat
int i = 0;
const int dat_records = 100;
double dat[10][10] = {0} ;






float threshold[] = {(stdMultiplier*stdStart),(stdMultiplier*stdStop)};
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(switch_pin, INPUT);
 pinMode(calibration_button, INPUT);
 accel.init(); // Default init: +/-2g and 800Hz ODR
 reset();
}

void loop() {
/*
    for (int i =0; i< dat_records; i++){
          Serial.println(dat[0][i]);
    }
*/  
  //Serial.println(set);
  if(set == setsNeeded){
    Serial.println("Congratulations! You did " + String(setsNeeded) + " sets of " + String(repsNeeded) + " reps!\n\n");
    reset();
  }
  else{
    
    for(float reps = 0; reps<repsNeeded; reps+=0.5){
      accel.read();
      float val = accel.cy; 
      //Serial.println(accel.cy);
      //Serial.println(abs(wantedValue[index]-val) > threshold[index]);
      while((fabs(wantedValue[index]-val) - threshold[index])>0){
        accel.read();
        val = accel.cy; 
        delay(5);
        //Serial.println(abs(wantedValue[index]-val)-threshold[index]);
        //Serial.println(threshold[index]);
      
      }
    if(index==true){
       Serial.println("Sets: " + String(set+1) + " Reps: " + String(reps+1));  
    }
    buzz();
      if(index == true){
        //Serial.println("change");
        index = false;  
      }
      else{
        index = true;
      }
    }
    set += 1;
    buzz1();
  }
}

void reset(){
    wantedValue[0] = avgStart;
    wantedValue[1] = avgStop;
    index = 1; //0 for start, 1 for stop
    Serial.println("Please complete " + String(setsNeeded) + " sets of " + String(repsNeeded) + " reps!\nPress the button to start\nGood Luck! \n");
    while(!switchOn()){delay(5);}
    buzz2();
    set = 0;
    
}

// notes in the melody:
int melody[] = {
NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3,
NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_C5, NOTE_C5, NOTE_C5,
NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_C4,
NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
8,4,4,8,4,2,2,
3,3,3,4,4,8,4,8,8,8,4,8,4,3,8,8,3,
3,3,3,4,4,8,4,8,8,8,4,8,4,3,8,8,2,
8,8,8,4,4,8,8,4,8,8,3,8,8,8,4,4,4,8,2,
8,8,8,4,4,8,8,4,8,8,3,3,3,1,
8,4,4,8,4,8,4,8,2,8,4,4,8,4,1,
8,4,4,8,4,8,4,8,2
};

void buzz(){
  tone(buzz_pin,NOTE_B5,100);
  delay(100);
  tone(buzz_pin,NOTE_E7,400);
  delay(500);
  noTone(8);
}
void buzz1(){
  tone(buzz_pin,NOTE_E6,125);
  delay(130);
  tone(buzz_pin,NOTE_G6,125);
  delay(130);
  tone(buzz_pin,NOTE_E7,125);
  delay(130);
  tone(buzz_pin,NOTE_C7,125);
  delay(130);
  tone(buzz_pin,NOTE_D7,125);
  delay(130);
  tone(buzz_pin,NOTE_G7,125);
  delay(125);
  noTone(8); 
}

void buzz2(){
  //***********************************************************

  double** data = create2DArray(50,10);
  
  //update data  
  //put your for loops here to save data
  data[0][0] = 1.5;
  data[0][1] = 2.5;

  //truncated data
  double** data_trunc = create2DArray(5,10); //new dimension: 5x10
  data_trunc = modify2DArray(data, 50, 10, 5, 10); 

  //***********************************************************
  
  for (int thisNote = 0; thisNote < 7; thisNote++) {
  
  // to calculate the note duration, take one second
  // divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int noteDuration = 1000/noteDurations[thisNote];
  tone(buzz_pin, melody[thisNote],noteDuration);
  
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  // stop the tone playing:
  noTone(buzz_pin);  
  }
}

boolean switchOn(){
  return(digitalRead(switch_pin));  
}