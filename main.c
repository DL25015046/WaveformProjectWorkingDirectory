#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "inputoutput.h"

int main(void) {
    //float *CSVArray = malloc(7999*sizeof(float));
    CSVValues structArray[1000];
    readCSVFile(*structArray); // can put CSVArray

    int i = 30;
    printf("Timestamp: %fms\n", structArray[i].timestamp);
    printf("Frequency: %fHz\n", structArray[i].frequency);

    //printf("\n%f", CSVArray[533+1000]);
    void free(void *CSVArray);
    return 0;
}
