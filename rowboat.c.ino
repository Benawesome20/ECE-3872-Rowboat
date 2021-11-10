//-----------------------------------------------------
// Engineer: Benjamin Ventimiglia
// Edited from Tim Brother's conductor.c
// Overview
//    When this device is turned on it plays the song Row
//    Row Row Your Boat.
// Design Name:   The Singing Rowboat
// File Name:     rowboat.c
//
// Inputs: 
//    Octave: controls the octave of the song
//    Tempo: controls the tempo of the song
// Outputs: 
//    Servos: Spins the oars of the rowboat
//
// History:       29 October 2021 File created
//                3 November 2021 Edited motors to add timing
//                4 November 2021 Debugged motors
//
//-----------------------------------------------------

#include <Servo.h>
#include <stdio.h>
#include <math.h>

/*
#define TempoCal 512
#define TempoPotMax 1023
#define PwmMax 255 */

// Define the two octave settings for the octave input switch
#define OCTAVE_0 6 // TODO: hand tune values
#define OCTAVE_1 8

// Define the two tempo settings for the tempo input switch
#define TEMPO_0 250 // TODO: hand tune values
#define TEMPO_1 300

#define OCTAVE_PIN 2
#define TEMPO_PIN 3

// Music Notes based on Octave
#define C 16.3516
#define D 18.35405
#define E 20.60172
#define F 21.82676
#define G 24.49971
#define A 27.5
#define B 30.86771
#define HIGH_C 32.70320
#define REST 0

#define SPEAKER_PIN 7


// Row Row Row Your Boat
int songLength = 54;    
int notes[] = {C, REST, C, REST, C, REST, D, REST, E, REST, E, REST, D, REST, E, 
               REST, F, REST, G, REST, HIGH_C, REST, HIGH_C, REST, HIGH_C, REST, 
               G, REST, G, REST, G, REST, E, REST, E, REST, E, REST, C, REST, C, 
               REST, C, REST, G, REST, F, REST, E, REST, D, REST, C, REST};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};

// setup the servo output
Servo oar_1;
Servo oar_2;

// Timing variables
unsigned long start = millis();
unsigned long elapsed, finished;

void setup()
{
  // set up inputs
  pinMode(OCTAVE_PIN, INPUT); // octave switch
  pinMode(TEMPO_PIN, INPUT); // tempo switch
  
  // set up outputs
  pinMode(SPEAKER_PIN, OUTPUT);
 
  // Set up servos for the spinning oars
  // TODO: make sure that these pins are available/correct
  oar_1.attach(10);
  oar_2.attach(11);
  
  //set the servos to zero initial condition
  oar_1.write(-180);
  oar_2.write(-180);
  
  //debug only
  Serial.begin(9600);
  Serial.print("Setup Complete\n");
}

void loop()
{
  int duration;
  int tempo;
  int tempo_switch;
  int octave;
  int octave_switch;
  int note;
  int i_note_index = 0;
  
  // when the box is turned on, spin the motors
  // motion is back and forth between (-180, 180), every 2 seconds

  finished = millis();
  elapsed = finished - start;
  Serial.print("elapsed: ");
  Serial.println(elapsed);
  if (elapsed > 2000) { // If 2 or more seconds have passed since start
    start = millis(); // reset start time
    Serial.println("Swapping");
    Serial.println(oar_1.read());
    Serial.println(oar_2.read());
    
    if (oar_1.read() = -180) // Swap directions on all motors
      oar_1.write(180);
    else //if (oar_1.read() > -180)
      oar_1.write(-180);
    if (oar_2.read() = -180)
      oar_1.write(180);
    else //if (oar_2.read() > -180)
      oar_2.write(-180);  
  }
  
  // Set the tempo based on the switch
  tempo_switch = digitalRead(TEMPO_PIN);
  tempo = 250;//(tempo_switch) ? TEMPO_1 : TEMPO_0;

  // Set the octave based on the switch
  octave_switch = digitalRead(OCTAVE_PIN);
  octave = 6;//(octave_switch) ? OCTAVE_1 : OCTAVE_0;
 
  //play the song
  duration = beats[i_note_index] * tempo;
  note = notes[i_note_index] * pow(2, octave);
  //tone(SPEAKER_PIN, note, duration);
  delay(duration);
        
  //increment the note counter
  ++i_note_index;
  if(i_note_index >= songLength) 
  {
    i_note_index = 0;
  }
}
