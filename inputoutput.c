#include "inputoutput.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "waveform.h"

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

    fclose(filepntr);
    return 0;
}

float compileReport(CSVValues *structArray, float *clippingArray) {
    int z = 0;
    char filepath[128];
    printf("Please enter a valid filepath where you wish to create your report file (including the text file and extension):\n");
    scanf("%s", filepath);
    FILE *filepointer = fopen(filepath, "w"); // test with C:/Users/me/CLionProjects/untitled/report.txt
    fprintf(filepointer, "WAVEFORM SAMPLES REPORT\n\n");
    fprintf(filepointer,"PHASE A RMS: "); fprintf(filepointer, "%f", computeRMSVoltage(structArray, 1)); fprintf(filepointer,"V\n");
    fprintf(filepointer,"PHASE B RMS: "); fprintf(filepointer, "%f", computeRMSVoltage(structArray, 2)); fprintf(filepointer,"V\n");
    fprintf(filepointer,"PHASE B RMS: "); fprintf(filepointer, "%f", computeRMSVoltage(structArray, 3)); fprintf(filepointer,"V\n");
    int PhaseATolerant = checkIfRMSTolerant(computeRMSVoltage(structArray,1)); int PhaseBTolerant = checkIfRMSTolerant(computeRMSVoltage(structArray,2));
    int PhaseCTolerant = checkIfRMSTolerant(computeRMSVoltage(structArray,3));
    if (PhaseATolerant == 1) {
        fprintf(filepointer,"Phase A RMS is tolerable!\n");
    } else {
        fprintf(filepointer,"Phase A RMS is not tolerable!\n");
    }
    if (PhaseBTolerant == 1) {
        fprintf(filepointer,"Phase B RMS is tolerable!\n");
    } else {
        fprintf(filepointer,"Phase B RMS is not tolerable!\n");
    }
    if (PhaseCTolerant == 1) {
        fprintf(filepointer,"Phase C RMS is tolerable!\n\n");
    } else {
        fprintf(filepointer,"Phase C RMS is not tolerable!\n\n");
    }
    float PhaseADCOffset = computeDCOffset(structArray, 1); float PhaseBDCOffset = computeDCOffset(structArray, 1); float PhaseCDCOffset = computeDCOffset(structArray, 3);
    if (PhaseADCOffset > 1 || PhaseADCOffset < -1) {
        fprintf(filepointer, "PHASE A DC OFFSET: %fV - Outside of tolerable range!\n", PhaseADCOffset);
    } else {
        fprintf(filepointer, "PHASE A DC OFFSET: %fV - Within tolerable range!\n", PhaseADCOffset);
    }
    if (PhaseBDCOffset > 1 || PhaseBDCOffset < -1) {
        fprintf(filepointer, "PHASE B DC OFFSET: %fV - Outside of tolerable range!\n", PhaseBDCOffset);
    } else {
        fprintf(filepointer, "PHASE B DC OFFSET: %fV - Within tolerable range!\n", PhaseBDCOffset);
    }
    if (PhaseCDCOffset > 1 || PhaseCDCOffset < -1) {
        fprintf(filepointer, "PHASE C DC OFFSET: %fV - Outside of tolerable range!\n\n", PhaseCDCOffset);
    } else {
        fprintf(filepointer, "PHASE C DC OFFSET: %fV - Within tolerable range!\n\n", PhaseCDCOffset);
    }
    fprintf(filepointer, "PHASE A PEAK-TO-PEAK VOLTAGE: %fV\n", computePeakToPeakAmp(structArray, 1));
    fprintf(filepointer, "PHASE B PEAK-TO-PEAK VOLTAGE: %fV\n", computePeakToPeakAmp(structArray, 2));
    fprintf(filepointer, "PHASE C PEAK-TO-PEAK VOLTAGE: %fV\n\n", computePeakToPeakAmp(structArray, 3));

    checkForClipping(clippingArray, structArray);

    for (int i = 0; i < 1000; i++) {
        if (clippingArray[i] == 1) {
            z = z + 1;
        }
    }
    fprintf(filepointer, "Total Sample Clipping Count: %d instances!\n\n", z);

    int THDCompliancy = checkIfTHDCompliant(structArray);
    if (THDCompliancy == 2) {
        fprintf(filepointer,"Warning! THD measured at >0.08 during the sample!");
    } else if (THDCompliancy == 1) {
        fprintf(filepointer,"Warning! THD measured between 0.05-0.08 during the sample! Monitor closely!");
    } else {
        fprintf(filepointer, "THD measured at nominal levels (<0.05) during the sample!");
    }
}