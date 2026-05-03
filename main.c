#include <stdlib.h>
#include "inputoutput.h"

// this file is used mainly to call the inputoutput.c file functions (performing input and output)
// waveform functions are used primarily by the inputoutput.c functions

int main(void) {
    float *clippingArray = malloc(1000*sizeof(float)); // used to count instances of clipping later. holds 1000 float files
    CSVValues *structArray = malloc(1000*sizeof(CSVValues)); // holds all the information from the CSV file. holds 1000*8 float files
    readCSVFile(structArray); // simply calls CSVFile with the defined array of structures to capture the CSV file's information for use
    compileReport(structArray, clippingArray); // calls compileReport to file and export the text document report
    void free(void *clippingArray); // frees memory for the clipping array before the program closes
    void free(void *structArray); // ditto, but for the array of CSVValues structures
    return 0;
}
