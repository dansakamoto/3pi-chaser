#include <OrangutanLCD.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>
#include <OrangutanBuzzer.h>

#define MELODY_LENGTH 20

// These arrays take up a total of 285 bytes of RAM (out of a 1k limit)
unsigned char note[MELODY_LENGTH] = 
{
  NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), NOTE_A(5), NOTE_F(4), 
};

unsigned int duration[MELODY_LENGTH] =
{
  800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 
};

OrangutanLCD lcd;
OrangutanBuzzer buzzer;
unsigned char currentIdx;

  const int stopSpeed = 0;
  const int midSpeed = 15;
  const int goSpeed = 60;
  const int threshold = 650;
  const int maxFear = 350;
  
  int rightSpeed = 0;
  int leftSpeed = 0;

  int fear = 0;
  int dir = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  currentIdx = 0;
}

void loop() {

  if (currentIdx < MELODY_LENGTH && !buzzer.isPlaying())
  {
    // play note at max volume
    //buzzer.playNote(note[currentIdx], duration[currentIdx], 15);
    //currentIdx++;
  }
  
  // put your main code here, to run repeatedly:
  int rightValue = analogRead(A5);
  int leftValue = analogRead(A6);

  //lcd.print((unsigned int)rightValue);
  //delay(50);
  //lcd.clear();

  if(rightValue > threshold && leftValue > threshold){  // Both sensors detect light - go backwards

    dir = -1; // 0 = backwards
    fear = maxFear;
    rightSpeed = -1 * goSpeed;
    leftSpeed = -1 * goSpeed;

  } else if(rightValue <= threshold && leftValue <= threshold){ // no imminent threat

    if(fear > 0){
      leftSpeed = dir * goSpeed;
      rightSpeed = dir * goSpeed;face
      fear--;
    } else {
      leftSpeed = stopSpeed;
      rightSpeed = stopSpeed;
      dir = -1;
    }

  } else if(rightValue > threshold){ // Only right sensor detects light - steer away from it

      fear = maxFear;
      rightSpeed = dir * goSpeed;
      leftSpeed = dir * midSpeed;

  } else if(leftValue > threshold) { // Only left sensor detects light - steer away from it

     fear = maxFear;
     leftSpeed = dir * goSpeed;
     rightSpeed = dir * midSpeed;   
  }
  
    OrangutanMotors::setSpeeds(leftSpeed,rightSpeed);
    delay(5);
}




