#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "inputoutput.h"

int main(void) {

    CSVValues *structArray = malloc(1000*sizeof(CSVValues));
    readCSVFile(structArray);

    //int i = 999; // THIS GOES UP TO 999
    //printf("Timestamp: %fms\n", structArray[i].timestamp);
    //printf("Frequency: %fHz\n", structArray[i].frequency);
    //printf("%f\n", computeRMSVoltage(structArray, 1));
    //printf("%f\n", computeRMSVoltage(structArray, 2));
    //printf("%f\n", computeRMSVoltage(structArray, 3));

    int x = checkIfRMSTolerant(computeRMSVoltage(structArray, 1));

    void free(void *structArray);
    return 0;
}
