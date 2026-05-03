#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "inputoutput.h"

int main(void) {
    float *clippingArray = malloc(1000*sizeof(float));
    CSVValues *structArray = malloc(1000*sizeof(CSVValues));
    readCSVFile(structArray);

    void free(void *clippingArray);
    void free(void *structArray);
    return 0;
}
