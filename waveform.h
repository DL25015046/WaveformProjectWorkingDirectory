#ifndef UNTITLED_WAVEFORM_H
#define UNTITLED_WAVEFORM_H

float computeRMSVoltage(); // calculates RMS values for a given phase
int checkIfRMSTolerant(float); // calculates whether a given RMS value is tolerable
void checkForClipping(); // tallies how many clipping samples there are
int checkIfTHDCompliant(); // checks if there are any noncompliant THD values in the samples
float computeDCOffset(); // calculates DC offset for a given phase
float computePeakToPeakAmp(); // calculates peak-to-peak voltage amplitude for a given phase

#endif //UNTITLED_WAVEFORM_H