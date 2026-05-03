#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "inputoutput.h"

int main(void) {
    float *clippingArray = malloc(1000*sizeof(float));
    CSVValues *structArray = malloc(1000*sizeof(CSVValues));
    readCSVFile(structArray);

    //int x = checkIfRMSTolerant(computeRMSVoltage(structArray, 1));
    //printf("%d", x);

    checkForClipping(clippingArray, structArray);

    void free(void *clippingArray);
    void free(void *structArray);
    return 0;
}
