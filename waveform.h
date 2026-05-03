#ifndef UNTITLED_WAVEFORM_H
#define UNTITLED_WAVEFORM_H

float computeRMSVoltage();
int checkIfRMSTolerant(float);
void checkForClipping();
int checkIfTHDCompliant();
float computeDCOffset();
float computePeakToPeakAmp();

#endif //UNTITLED_WAVEFORM_H