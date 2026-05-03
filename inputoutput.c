#include "inputoutput.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "waveform.h"

// this file is used for input/output; the functions here make use of the waveform functions (mainly compileReport)
// DEV: test file input with C:/Users/me/CLionProjects/untitled/power_quality_log.csv
// DEV: test file output with C:/Users/me/CLionProjects/untitled/report.txt

float readCSVFile(CSVValues *structArray) { // this function opens a CSV file and transfers its contents to an array of structures...
    char CLIfilepath[128]; // ...please note it was designed for a FIXED and INVARIABLE CSV file size (1000 rows and 8 columns)
    printf("Please enter a valid filepath for your CSV file:\n"); // prompts user to enter a filepath on command line interface
    scanf("%s", CLIfilepath);
    FILE *filepntr = fopen(CLIfilepath, "r"); // uses a file pointer to open the CSV file with, specified by the filepath
    while (filepntr == NULL) { // if the filepath is invalid, no file will open and this loop will open
        printf("Could not open CSV file!\n");
        printf("Please re-enter a valid filepath for your CSV file:\n");
        scanf("%s", CLIfilepath);
        filepntr = fopen(CLIfilepath, "r"); // if the new filepath does not work, the while loop does not break
    }
    printf("File successfully opened!\n"); // command-line interface assurance that the program is working so far
    char line[256]; //stores the information in a single line of the CSV file (one eighth of a given row)
    fgets(line, sizeof(line), filepntr);
    int i = 0; // serves as an index to identify specific structures in the array of structures, structArray
    while (fgets(line, sizeof(line), filepntr) != NULL) { // stores inputs into the line variable as long as it does not encounter a NULL value...
        char *TOKEN = strtok(line, ","); // ...if it encounters a NULL value (or empty space), it will terminate...
        float timestamp = atof(TOKEN); // ...for the program to function, it assumes the data is not damaged or missing in any place
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
        float powerFactor = atof(TOKEN); // this code block essentially just assigns values to each of these variables...
        TOKEN = strtok(NULL, ","); // ...these variables are then assigned to the various parts of the indexed structure
        float THD = atof(TOKEN); // in this way, all 8000 values in the CSV file are transferred to 1000 structures holding 8 pieces of information

        structArray[i].timestamp = timestamp; structArray[i].phaseA = phaseA; structArray[i].phaseB = phaseB; structArray[i].phaseC = phaseC;
        structArray[i].lineCurrent = lineCurrent; structArray[i].frequency = frequency; structArray[i].powerFactor = powerFactor; structArray[i].THD = THD;
        i++; // the above do what I explained - assigning read values in the row to the correct part of the indexed structure. also i is incremented
    } // after assignment, the loop iterates, which translates to the lines read shifting down one row
    fclose(filepntr); // closes the CSV file since we are done with it
    return 0; // this function should actually be a void, this return value is never used once
}
float compileReport(CSVValues *structArray, float *clippingArray) { // this uses waveform functions and the CSV file's values to create/write a .txt report
    int z = 0; // solely useful to "collect" clipped instances into a single integer (more on that during that part)
    char filepath[128]; // stores the filepath that the user will enter in the scanf
    printf("Please enter a valid filepath where you wish to create your report file (including the text file and extension):\n");
    scanf("%s", filepath); // there isn't really a fixed filepath that the report must be created in, since this creates a file instead of reading it...
    FILE *filepointer = fopen(filepath, "w"); // ...however it's still possible to have invalid filepaths here
    fprintf(filepointer, "WAVEFORM SAMPLES REPORT\n\n"); //prints the title of the report. most fprintf statements here are self-explanatory
    fprintf(filepointer,"PHASE A RMS: "); fprintf(filepointer, "%f", computeRMSVoltage(structArray, 1)); fprintf(filepointer,"V\n");
    fprintf(filepointer,"PHASE B RMS: "); fprintf(filepointer, "%f", computeRMSVoltage(structArray, 2)); fprintf(filepointer,"V\n");
    fprintf(filepointer,"PHASE B RMS: "); fprintf(filepointer, "%f", computeRMSVoltage(structArray, 3)); fprintf(filepointer,"V\n");
    int PhaseATolerant = checkIfRMSTolerant(computeRMSVoltage(structArray,1)); int PhaseBTolerant = checkIfRMSTolerant(computeRMSVoltage(structArray,2));
    int PhaseCTolerant = checkIfRMSTolerant(computeRMSVoltage(structArray,3)); // these assign a variable to hold the RMS tolerance function results for each phase...
    if (PhaseATolerant == 1) { // ...which are checked in these if loops, see the function itself in waveform.c for more details
        fprintf(filepointer,"Phase A RMS is tolerable!\n"); // just remember that 1 = tolerable, 0 = nontolerable
    } else {
        fprintf(filepointer,"Phase A RMS is not tolerable!\n");
    }
    if (PhaseBTolerant == 1) { // these two are the same as the one above
        fprintf(filepointer,"Phase B RMS is tolerable!\n");
    } else {
        fprintf(filepointer,"Phase B RMS is not tolerable!\n");
    }
    if (PhaseCTolerant == 1) { // ditto
        fprintf(filepointer,"Phase C RMS is tolerable!\n\n");
    } else {
        fprintf(filepointer,"Phase C RMS is not tolerable!\n\n");
    }
    float PhaseADCOffset = computeDCOffset(structArray, 1); float PhaseBDCOffset = computeDCOffset(structArray, 1); float PhaseCDCOffset = computeDCOffset(structArray, 3);
    if (PhaseADCOffset > 1 || PhaseADCOffset < -1) { // these fprintf statements show both the DC offset and whether they are within tolerable bounds
        fprintf(filepointer, "PHASE A DC OFFSET: %fV - Outside of tolerable range!\n", PhaseADCOffset);
    } else { // essentially, if DC offset is between -1V and 1V, it's tolerable, otherwise it's not tolerable
        fprintf(filepointer, "PHASE A DC OFFSET: %fV - Within tolerable range!\n", PhaseADCOffset);
    }
    if (PhaseBDCOffset > 1 || PhaseBDCOffset < -1) { // these two if-elses are the same as the one above
        fprintf(filepointer, "PHASE B DC OFFSET: %fV - Outside of tolerable range!\n", PhaseBDCOffset);
    } else {
        fprintf(filepointer, "PHASE B DC OFFSET: %fV - Within tolerable range!\n", PhaseBDCOffset);
    }
    if (PhaseCDCOffset > 1 || PhaseCDCOffset < -1) { // ditto
        fprintf(filepointer, "PHASE C DC OFFSET: %fV - Outside of tolerable range!\n\n", PhaseCDCOffset);
    } else {
        fprintf(filepointer, "PHASE C DC OFFSET: %fV - Within tolerable range!\n\n", PhaseCDCOffset);
    }
    fprintf(filepointer, "PHASE A PEAK-TO-PEAK VOLTAGE: %fV\n", computePeakToPeakAmp(structArray, 1));
    fprintf(filepointer, "PHASE B PEAK-TO-PEAK VOLTAGE: %fV\n", computePeakToPeakAmp(structArray, 2));
    fprintf(filepointer, "PHASE C PEAK-TO-PEAK VOLTAGE: %fV\n\n", computePeakToPeakAmp(structArray, 3));
    // these fprintf statements simply print the peak-to-peak voltage for all given phases, in order of A -> B -> C
    checkForClipping(clippingArray, structArray); // calls the checkForClipping function - it's a void, but it assigns values to clippingArray
    for (int i = 0; i < 1000; i++) { // loops 1000 times
        if (clippingArray[i] == 1) { // see checkForClipping in waveform.c to see why this works, but essentially tallies all clipping instances...
            z = z + 1; // ...and keeps them in one integer variable, z...
        }
    }
    fprintf(filepointer, "Total Sample Clipping Count: %d instances!\n\n", z); // ...which is then printed in the report as a number

    int THDCompliancy = checkIfTHDCompliant(structArray); // runs the THDCompliancy function to check, see waveform.c for more detail
    if (THDCompliancy == 2) { // if any value is >8%, THDCompliancy returns 2...
        fprintf(filepointer,"Warning! Maximum THD measured at >0.08 during the sample!");
    } else if (THDCompliancy == 1) { // if any value is between 5% and 8% or equal to either, THDCompliancy returns 1...
        fprintf(filepointer,"Warning! Maximum THD measured between 0.05-0.08 during the sample! Monitor closely!");
    } else { // ...otherwise, returns 0, which means it must be nominal
        fprintf(filepointer, "Maximum THD measured at nominal levels (<0.05) during the sample!");
    }
    return 0; // this function should also be a void, this return doesn't do anything
}