#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "inputoutput.h"

int main(void) {
    float *CSVArray = malloc(7999*sizeof(float));
    readCSVFile(CSVArray);

    printf("\n%f", CSVArray[533+1000]);

    void free(void *CSVArray);
    return 0;
}
