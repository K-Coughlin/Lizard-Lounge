#ifndef FEEDBACKLOOP_H
#define FEEDBACKLOOP_H

#include <Lizard_Lounge.h>

extern float temperature_hot;
extern int humidity_hot;
extern float temperature_cool;
extern int humidity_cool;
bool tempHot = false;
bool tempCold = false;
bool tempHotChange = false;

// Timer variables


// Timers
const unsigned long sensorDuration = 30000; // How often to read sensors (30 seconds)
elapsedMillis sensorTimer = sensorDuration;

const unsigned long pumpDuration = 10000; // 10 seconds
const unsigned long fanDuration = 120000; // 2 mins
const unsigned long tooHotDuration = 30000;  //half min
const unsigned long tooColdDuration = 30000;  //half min

// Action variables (Is certain peripheral active?)
bool fanActive = false;
bool pumpActive = false;
bool baskActive = false;
bool CHEActive = false;

// -- Thresholds --//
float hot_temp_threshold = 100.0;
float low_temp_threshold = 70.0;
float hi_humid_threshold = 50.0;
float lo_humid_threshold = 25.0;

long pumpStart;
long pumpTimer;

long fanStart;
long fanTimer;

long tooHotStart;
long tooHotTimer;

long tooColdStart;
long tooColdTimer;

long testUVWater;
long testUVWaterStart;

void pumpDemo();
void feedbackLoop();
void readAllSensors();
void decideNextMode();

#endif