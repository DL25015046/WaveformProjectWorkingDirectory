# include "waveform.h"
#include "inputoutput.h"
#include <stdio.h>
#include <math.h>

// this file is dedicated to waveform functions
// note the codes (RMS, DCO, PTP) indicate the function where the message originates from in the command line
// this is purely for troubleshooting purposes on the developer's side

float computeRMSVoltage(CSVValues *structArray, int n) { // this function calculates the RMS value for a given phase (determined by n)
    float sumOfSqVoltages = 0; // holds all squared voltages as one sum during calculations
    float finalRMS = 0; // is the value that is returned (see calculation at bottom)
    switch (n) {
        case 1: // for phase A (n = 1)
            for (int i = 0; i < 1000; i++) { // loop ~1000 times
                sumOfSqVoltages = sumOfSqVoltages + (structArray[i].phaseA * structArray[i].phaseA); // squares the indexed structure's phase value and adds it to a sum
            }
            break;
        case 2: // for phase B (n = 2)
            for (int i = 0; i < 1000; i++) { // identical to loop above
                sumOfSqVoltages = sumOfSqVoltages + (structArray[i].phaseB * structArray[i].phaseB); // same as above
            }
            break;
        case 3: // for phase C (n = 3)
            for (int i = 0; i < 1000; i++) { // identical to loop above
                sumOfSqVoltages = sumOfSqVoltages + (structArray[i].phaseC * structArray[i].phaseC); // same as above
            }
            break;
        default: // for n != 1, n != 2, n != 3, should NOT occur in real runtime
            printf("RMS - Invalid value of n entered (only values 1, 2 and 3 are valid).\n"); // used mainly as a development failsafe for bad n-inputs
            return 0; // this function should never return 0 so this will show immediately that something is wrong
    }
    finalRMS = sqrt(sumOfSqVoltages / 1000); // could honestly just 'return sqrt(sumOfSqVoltages/1000)'
    return finalRMS;
}

int checkIfRMSTolerant(float finalRMS) { // this function returns a value to indicate whether a given RMS is tolerable
    if (finalRMS <= 253 && finalRMS >= 207) { // +- 10% of ~230V
        return 1; // returned 1 = RMS is within tolerable boundaries
    } else {
        return 0; // returned 0 = RMS is outside of tolerable boundaries
    }
}

void checkForClipping(float *clippingArray, CSVValues *structArray) { // this function counts all instances of clipping...
    int j = 0; // ...it does this by filling clipping array with 1s at indexes where clipping occurs for the CSVValues structures
    while (j < 1000) { // ...these can be counted later (see compileReport)
        clippingArray[j] = 0; // this while loop sets every value in the array to 0, since it is not initialised with values...
        j++; // ...this helps prevent garbage values that might interfere with the clipping count
    }
    for (int i = 0; i < 1000; i++) { // loop 1000 times
        if (structArray[i].phaseA == 325 || structArray[i].phaseA == -325) { // "if phase value is at sensor threshold..."
            clippingArray[i+2] = 1;; // "...append it to the array (index +2'd to be accurate to the position on the CSV file)"
        }
    }
    for (int i = 0; i < 1000; i++) { // loops are the same as above
        if (structArray[i].phaseB == 325 || structArray[i].phaseB == -325) {
            clippingArray[i+2] = 1;;
        }
    }
    for (int i = 0; i < 1000; i++) { // loops are the same as above
        if (structArray[i].phaseC == 325 || structArray[i].phaseC == -325) {
            clippingArray[i+2] = 1;;
        }
    }
}

int checkIfTHDCompliant(CSVValues *structArray) { // returns 2 on >8%, 1 for 5%-8%, 0 for <5%
    for (int i = 0; i < 1000; i++) { // loop 1000 times...
        if (structArray[i].THD > 8) {
            return 2; // if THD at ANY point >8%, it is heavily noncompliant/excessive, action required
        } else if (structArray[i].THD <= 8 && structArray[i].THD >= 5) {
            return 1; // if THD at ANY point >=5% AND <=8% (so 5%-8%), it is noncompliant, monitoring is suggested
        }
    }
    return 0; // otherwise, it's nominal! a 0 value is generally expected
}

float computeDCOffset(CSVValues *structArray, int n) { // this function calculates the DC offset for a given phase (given by n)
    float sumOfVoltages = 0; // holds the sum of voltages not unlike sumOfSqVoltage (except values aren't squared)
    switch (n) {
        case 1: // for phase A (n = 1)
            for (int i = 0; i < 1000; i++) { // loop 1000 times
                sumOfVoltages = sumOfVoltages + structArray[i].phaseA; // add a given phase value from the indexed structure to sumOfVoltages
            }
            break;
        case 2: // for phase B (n = 2)
            for (int i = 0; i < 1000; i++) { // loop same as above
                sumOfVoltages = sumOfVoltages + structArray[i].phaseB;
            }
            break;
        case 3: // for phase C (n = 3)
            for (int i = 0; i < 1000; i++) { // loop same as above
                sumOfVoltages = sumOfVoltages + structArray[i].phaseC;
            }
            break;
        default: // failsafe case, same as other defaults seen in this program
            printf("DCO - Invalid value of n entered (only values 1, 2 and 3 are valid).\n"); // dev-troubleshooting message, should not appear in real runs
            return 999999; // returns a ridiculous value so that you know it can't be realistic (if you somehow miss the message)
    }
    return (sumOfVoltages / 1000); // simply returns the mean/DC offset
}

float computePeakToPeakAmp(CSVValues *structArray, int n) { // calculates peak-to-peak voltage amplitude for a given phase (given by n)
    float largestVoltage = 0; // variable that stores the largest found voltage through the iteration of a phase's values
    float smallestVoltage = 0; // ditto, but for smallest voltage
    switch (n) {
        case 1: // phase A (n = 1)
            for (int i = 0; i < 1000; i++) { // loop 1000 times
                if (structArray[i].phaseA > largestVoltage) { // if the value in the indexed structure is larger than the current largest voltage...
                    largestVoltage = structArray[i].phaseA; // ...the largest voltage becomes this indexed structure's value
                }
                if (structArray[i].phaseA < smallestVoltage) { // same as above, but inverse (checks to see which is smaller)
                    smallestVoltage = structArray[i].phaseA;
                }
            }
            break;
        case 2: // phase B (n = 2)
            for (int i = 0; i < 1000; i++) { // loop same as above
                if (structArray[i].phaseB > largestVoltage) {
                    largestVoltage = structArray[i].phaseB;
                }
                if (structArray[i].phaseB < smallestVoltage) {
                    smallestVoltage = structArray[i].phaseB;
                }
            }
            break;
        case 3: // phase C (n = 3)
            for (int i = 0; i < 1000; i++) { // loop same as above
                if (structArray[i].phaseC > largestVoltage) {
                    largestVoltage = structArray[i].phaseC;
                }
                if (structArray[i].phaseC < smallestVoltage) {
                    smallestVoltage = structArray[i].phaseC;
                }
            }
            break;
        default: // failsafe case like the other defaults
            printf("PTP - Invalid value of n entered (only values 1 and 3 are valid).\n"); // again, should not appear in real runs
            return 0; // returns a number that is clearly suspicious for a peak-to-peak amp (in case you missed the message)
    }
    return (largestVoltage - smallestVoltage); // returns the peak-to-peak amplitude
}