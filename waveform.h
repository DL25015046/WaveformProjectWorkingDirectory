#ifndef UNTITLED_WAVEFORM_H
#define UNTITLED_WAVEFORM_H
#include "inputoutput.h"

float computeRMSVoltage();
int checkIfRMSTolerant(float);
void checkForClipping();
int checkIfTHDCompliant();
float computeDCOffset();

#endif //UNTITLED_WAVEFORM_H