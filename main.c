#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "inputoutput.h"

int main(void) {
    float *clippingArray = malloc(1000*sizeof(float));
    CSVValues *structArray = malloc(1000*sizeof(CSVValues));
    readCSVFile(structArray);

    printf("Phase A Offset:%f ", computeDCOffset(structArray, 1));
    printf("Phase B Offset:%f ", computeDCOffset(structArray, 2));
    printf("Phase C Offset:%f ", computeDCOffset(structArray, 3));
    printf("Phase D Offset:%f ", computeDCOffset(structArray, 4));

    void free(void *clippingArray);
    void free(void *structArray);
    return 0;
}
