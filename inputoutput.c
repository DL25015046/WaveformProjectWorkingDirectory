#include "inputoutput.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float readCSVFile(CSVValues *structArray) {
    char CLIfilepath[128];
    printf("Please enter a valid filepath for your CSV file:\n");
    scanf("%s", CLIfilepath);
    FILE *filepntr = fopen(CLIfilepath, "r"); // test with C:/Users/me/CLionProjects/untitled/power_quality_log.csv
    while (filepntr == NULL) {
        printf("Could not open CSV file!\n");
        printf("Please re-enter a valid filepath for your CSV file:\n");
        scanf("%s", CLIfilepath);
        filepntr = fopen(CLIfilepath, "r");
    }
    printf("File successfully opened!\n");
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