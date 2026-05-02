#include "inputoutput.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float readCSVFile(CSVValues *structArray) { //can have float *CSVArray

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

        //CSVArray[i] = timestamp; CSVArray[i+1000] = phaseA; CSVArray[i+2000] = phaseB; CSVArray[i+3000] = phaseC;
        //CSVArray[i+4000] = lineCurrent; CSVArray[i+5000] = frequency; CSVArray[i+6000] = powerFactor; CSVArray[i+7000] = THD;

        //printf("Time = %fms\n Phase A Voltage = %fV\n Phase B Voltage = %fV\n Phase C Voltage = %fV\n", CSVArray[i], CSVArray[i+1000], CSVArray[i+2000], CSVArray[i+3000]);
        //printf("Line Current = %fA\n Frequency = %fHz\n PowerFactor = %fV\n THD = %fV\n", CSVArray[i+4000], CSVArray[i+5000], CSVArray[i+6000], CSVArray[i+7000]);

        structArray[i].timestamp = timestamp; structArray[i].phaseA = phaseA; structArray[i].phaseB = phaseB; structArray[i].phaseC = phaseC;
        structArray[i].lineCurrent = lineCurrent; structArray[i].frequency = frequency; structArray[i].powerFactor = powerFactor; structArray[i].THD = THD;
        //printf("Timestamp: %fms\n", structArray[i].timestamp); printf("Phase A Voltage: %fV\n", structArray[i].phaseA); printf("Phase B Voltage: %fV\n", structArray[i].phaseB);
        //printf("Phase C Voltage: %fV\n", structArray[i].phaseC); printf("Line Current: %fA\n", structArray[i].lineCurrent); printf("Frequency: %fHz\n", structArray[i].frequency);
        //printf("Power Factor: %fV\n", structArray[i].powerFactor); printf("THD: %f\n", structArray[i].THD);

        i++;

    }

    //printf("%f", CSVArray[533+1000]);

    fclose(filepntr);
    return 0;
}