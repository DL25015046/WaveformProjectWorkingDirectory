#include "inputoutput.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float readCSVFile() {
    FILE *filepntr = fopen("C:/Users/me/CLionProjects/untitled/power_quality_log.csv", "r");
    if (filepntr == NULL) {
        printf("Could not open CSV file!\n");
        return 1;
    }
    char line[256];
    fgets(line, sizeof(line), filepntr);
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

        printf("Time = %fms\n Phase A Voltage = %fV\n Phase B Voltage = %fV\n Phase C Voltage = %fV\n", timestamp, phaseA, phaseB, phaseC);
        printf("Line Current = %fA\n Frequency = %fHz\n PowerFactor = %fV\n THD = %fV\n", lineCurrent, frequency, powerFactor, THD);
    }

    fclose(filepntr);
    return 0;
}