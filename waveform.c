# include "waveform.h"
#include "inputoutput.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

float computeRMSVoltage(CSVValues *structArray, int n) { // n = 1 -> phase A, N = 2 -> phase B, n = 3 -> phase C
    float sumOfSqVoltages = 0;
    float finalRMS = 0;
    switch (n) { //
        case 1:
            for (int i = 0; i < 1000; i++) {
                sumOfSqVoltages = sumOfSqVoltages + (structArray[i].phaseA * structArray[i].phaseA);
            }
            break;
        case 2:
            for (int i = 0; i < 1000; i++) {
                sumOfSqVoltages = sumOfSqVoltages + (structArray[i].phaseB * structArray[i].phaseB);
            }
            break;
        case 3:
            for (int i = 0; i < 1000; i++) {
                sumOfSqVoltages = sumOfSqVoltages + (structArray[i].phaseC * structArray[i].phaseC);
            }
            break;
        default:
            printf("Invalid value of n entered (only values 1, 2 and 3 are valid).\n");
            return 0;
    }
    finalRMS = sqrt(sumOfSqVoltages / 1000);
    return finalRMS;
}

int checkIfRMSTolerant(float finalRMS) { 
    if (finalRMS <= 253 && finalRMS >= 207) {
        return 1; // returned 1 = compliant
    } else {
        return 0; // returned 0 = noncompliant
    }
}

