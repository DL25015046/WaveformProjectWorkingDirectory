#ifndef UNTITLED_INPUTOUTPUT_H
#define UNTITLED_INPUTOUTPUT_H

float readCSVFile();

typedef struct {
    float timestamp;
    float phaseA;
    float phaseB;
    float phaseC;
    float lineCurrent;
    float frequency;
    float powerFactor;
    float THD;
} CSVValues;

#endif //UNTITLED_WAVEFORM_H