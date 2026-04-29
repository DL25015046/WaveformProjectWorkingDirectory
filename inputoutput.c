#include "inputoutput.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    float timestamp;
    float phaseA;
    float phaseB;
    float phaseC;
    float lineCurrent;
    float frequency;
    float powerFactor;
    float THD;
} CSVValues;

float readCSVFile() {

    float *CSVArray = malloc(1900*sizeof(float));

    FILE *filepntr = fopen("C:/Users/me/CLionProjects/untitled/power_quality_log.csv", "r");
    if (filepntr == NULL) {
        printf("Could not open CSV file!\n");
        return 1;
    }
    char line[256];
    fgets(line, sizeof(line), filepntr);
    int i = 0;
    while (fgets(line, sizeof(line), filepntr) != NULL) {
        char *TOKEN = strtok(line, ",");
        float timestamp = atof(TOKEN);
        TOKEN = strtok(NULL, ",");
        float phaseA = atof(TOKEN);
        TOKEN = strtok(NULL, ",");
        float phaseB = atof(TOKEN);
        TOKEN = strtok(NULL, ",");
        float phaseC = atof(TOKEN);
        TOKEN = strtok(NULL, ",");
        float lineCurrent = atof(TOKEN);
        TOKEN = strtok(NULL, ",");
        float frequency = atof(TOKEN);
        TOKEN = strtok(NULL, ",");
        float powerFactor = atof(TOKEN);
        TOKEN = strtok(NULL, ",");
        float THD = atof(TOKEN);

        //printf("Time = %fms\n Phase A Voltage = %fV\n Phase B Voltage = %fV\n Phase C Voltage = %fV\n", timestamp, phaseA, phaseB, phaseC);
        //printf("Line Current = %fA\n Frequency = %fHz\n PowerFactor = %fV\n THD = %fV\n", lineCurrent, frequency, powerFactor, THD);
        CSVArray[i] = timestamp; CSVArray[i+124] = phaseA; CSVArray[i+249] = phaseB; CSVArray[i+374] = phaseC;
        CSVArray[i+499] = lineCurrent; CSVArray[i+624] = frequency; CSVArray[i+749] = powerFactor; CSVArray[i+874] = THD;

        printf("Time = %fms\n Phase A Voltage = %fV\n Phase B Voltage = %fV\n Phase C Voltage = %fV\n", CSVArray[i], CSVArray[i+124], CSVArray[i+249], CSVArray[i+374]);
        printf("Line Current = %fA\n Frequency = %fHz\n PowerFactor = %fV\n THD = %fV\n", CSVArray[i+499], CSVArray[i+624], CSVArray[i+749], CSVArray[i+874]);

        //printf("%d ", i);
        i++;
    }

    fclose(filepntr);
    return 0;
}

void free(void *CSVArray);