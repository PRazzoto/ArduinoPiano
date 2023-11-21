#include "math.h"
#include "TimerOne.h"
#include "Volume-mod.h"

#define TAMANHO_VETOR 100
#define C 1
#define Cs 2
#define D 3
#define Ds 4
#define E 5
#define F 6
#define Fs 7
#define G 8
#define Gs 9
#define A 10
#define As 11
#define B 12


const int buttonPinC = 1;
const int buttonPinCs = 2;
const int buttonPinD = 3;
const int buttonPinDs = 4;
const int buttonPinE = 6;
const int buttonPinF = 7;
const int buttonPinFs = 8;
const int buttonPinG = 9;
const int buttonPinGs = 10;
const int buttonPinA = 11;
const int buttonPinAs = 12;
const int buttonPinB = 13;
int speakerPin = 5;
float volume = 0.0;

float button = 0;
bool REC = true;
bool REC_passado = REC;
float recorded_button[TAMANHO_VETOR];
int pev_button;
int button_index = 0;
unsigned long start_time;
int note_time;

int octave = 0;

const int reverbPin = A2;
const float reverbDecay = 0.9;




// Tempered frequency of each note based on the Michigan State research
const int freqC = 130.81;
const int freqCs = 138.59;
const int freqD = 146.83;
const int freqDs = 155.56;
const int freqE = 164.81;
const int freqF = 174.61;
const int freqFs = 185.00;
const int freqG = 196.00;
const int freqGs = 207.65;
const int freqA = 220.00;
const int freqAs = 233.08;
const int freqB = 246.94;

void recorder(){

  if(!REC){
    tone(5, recorded_button[button_index]*pow(2,octave), 500);
    if(button_index < 99){
      button_index++;
    }else{
      button_index=0;
    }
    return;
  }

  if (digitalRead(buttonPinC) == HIGH) {
    button = freqC;
  }
  else if (digitalRead(buttonPinCs) == HIGH) {
   button = freqCs;
  }
  else if (digitalRead(buttonPinD) == HIGH) {
   button = freqD;
  }
  else if (digitalRead(buttonPinDs) == HIGH) {
    button = freqDs;
  }
  else if (digitalRead(buttonPinE) == HIGH) {
    button = freqE;
  }
  else if (digitalRead(buttonPinF) == HIGH) {
    button = freqF;
  }
  else if (digitalRead(buttonPinFs) == HIGH) {
    button = freqFs;
  }
  else if (digitalRead(buttonPinG) == HIGH) {
   button = freqG;
  }
  else if (digitalRead(buttonPinGs) == HIGH) {
    button = freqGs;
  }
  else if (digitalRead(buttonPinA) == HIGH) {
    button = freqA;
  }
  else if (digitalRead(buttonPinAs) == HIGH){
    button = freqAs;
  }
  else if (digitalRead(buttonPinB) == HIGH){
    button = freqB;
  }
  else{
    button = 0.00;
  }


  if(button_index < TAMANHO_VETOR)
  {
    recorded_button[button_index] = button;
    button_index++;
  }

}


void setup() {
  pinMode(0, INPUT);
  pinMode(buttonPinC, INPUT);
  pinMode(buttonPinCs, INPUT);
  pinMode(buttonPinD, INPUT);
  pinMode(buttonPinDs, INPUT);
  pinMode(buttonPinE, INPUT);
  pinMode(buttonPinF, INPUT);
  pinMode(buttonPinFs, INPUT);
  pinMode(buttonPinG, INPUT);
  pinMode(buttonPinGs, INPUT);
  pinMode(buttonPinA, INPUT);
  pinMode(buttonPinAs, INPUT);
  pinMode(buttonPinB, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(A5, INPUT); //SPDT switch
  pinMode(reverbPin, OUTPUT);

  Timer1.initialize(100000); //250ms
  Timer1.attachInterrupt(recorder);


}



void loop() {
  octave = analogRead(A1)/ 204.60;

  if(digitalRead(A5) == 1){
    REC = false;
  }
  else{
    REC = true;
  }
  

  if(REC_passado != REC){
    REC_passado = REC;
    button_index = 0;
  }

  if(REC){
    tone(5,button*pow(2,octave), 500);
  }

}



