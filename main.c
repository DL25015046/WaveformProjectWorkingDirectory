#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "inputoutput.h"

int main(void) {

    CSVValues *structArray = malloc(1000*sizeof(CSVValues));
    readCSVFile(structArray);

    int i = 998; // THIS GOES UP TO 999
    printf("Timestamp: %fms\n", structArray[i].timestamp);
    printf("Frequency: %fHz\n", structArray[i].frequency);

    void free(void *structArray);
    return 0;
}
