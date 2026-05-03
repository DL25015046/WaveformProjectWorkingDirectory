# include "waveform.h"
#include "inputoutput.h"
#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include <math.h>

float computeRMSVoltage(CSVValues *structArray, int n) { // n = 1 -> phase A, N = 2 -> phase B, n = 3 -> phase C
    float sumOfSqVoltages = 0;
    float finalRMS = 0;
    switch (n) {
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

void checkForClipping(float *clippingArray, CSVValues *structArray) {
    int j = 0;
    while (j < 1000) {
        clippingArray[j] = 0;
        j++;
    }
    for (int i = 0; i < 1000; i++) {
        if (structArray[i].phaseA == 325 || structArray[i].phaseA == -325) {
            clippingArray[i+2] = 1;;
        }
    }
    for (int i = 0; i < 1000; i++) {
        if (structArray[i].phaseB == 325 || structArray[i].phaseB == -325) {
            clippingArray[i+2] = 1;;
        }
    }
    for (int i = 0; i < 1000; i++) {
        if (structArray[i].phaseC == 325 || structArray[i].phaseC == -325) {
            clippingArray[i+2] = 1;;
        }
    }
}

int checkIfTHDCompliant(CSVValues *structArray) { // returns 2 on >8%, 1 for 5%-8%, 0 for <5%
    for (int i = 0; i < 1000; i++) {
        if (structArray[i].THD > 8) {
            return 2;
        } else if (structArray[i].THD <= 8 && structArray[i].THD >= 5) {
            return 1;
        }
    }
    return 0;
}

float computeDCOffset(CSVValues *structArray, int n) { // n = 1 -> phase A, N = 2 -> phase B, n = 3 -> phase C
    float sumOfVoltages = 0;
    switch (n) {
        case 1:
            for (int i = 0; i < 1000; i++) {
                sumOfVoltages = sumOfVoltages + structArray[i].phaseA;
            }
            break;
        case 2:
            for (int i = 0; i < 1000; i++) {
                sumOfVoltages = sumOfVoltages + structArray[i].phaseB;
            }
            break;
        case 3:
            for (int i = 0; i < 1000; i++) {
                sumOfVoltages = sumOfVoltages + structArray[i].phaseC;
            }
            break;
        default:
            printf("Invalid value of n entered (only values 1, 2 and 3 are valid).\n");
            return 999999;
    }
    return (sumOfVoltages / 1000);
}

float computePeakToPeakAmp(CSVValues *structArray, int n) { // n = 1 -> phase A, N = 2 -> phase B, n = 3 -> phase C
    float largestVoltage = 0;
    float smallestVoltage = 0;
    switch (n) {
        case 1:
            for (int i = 0; i < 1000; i++) {
                if (structArray[i].phaseA > largestVoltage) {
                    largestVoltage = structArray[i].phaseA;
                }
                if (structArray[i].phaseA < smallestVoltage) {
                    smallestVoltage = structArray[i].phaseA;
                }
            }
            break;
        case 2:
            for (int i = 0; i < 1000; i++) {
                if (structArray[i].phaseB > largestVoltage) {
                    largestVoltage = structArray[i].phaseB;
                }
                if (structArray[i].phaseB < smallestVoltage) {
                    smallestVoltage = structArray[i].phaseB;
                }
            }
            break;
        case 3:
            for (int i = 0; i < 1000; i++) {
                if (structArray[i].phaseC > largestVoltage) {
                    largestVoltage = structArray[i].phaseC;
                }
                if (structArray[i].phaseC < smallestVoltage) {
                    smallestVoltage = structArray[i].phaseC;
                }
            }
            break;
        default:
            printf("Invalid value of n entered (only values 1 and 3 are valid).\n");
            return 0;
    }
    return (largestVoltage - smallestVoltage);
}