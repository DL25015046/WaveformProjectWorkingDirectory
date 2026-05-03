# USING THIS PROGRAM

## User Operation

**[LINK TO GITHUB](https://github.com/DL25015046/WaveformProjectWorkingDirectory)**

**1.** Find and download the CSV file, of which **must be** 1 to 1000 rows along and 8 columns across
(this program was designed with 1000 rows and 8 columns in mind, but the rows can vary from 1 to 1000)

**2.** Ensure the columns of your CSV files match with the columns listed in order in the source code, or
in this order (from left to right): **timestamp, phase A, phase B, phase C, line current, frequency,
power factor and THD.**

**3.** Locate the direct filepath to the CSV file on your computer

**4.** Run the program and, when prompted, enter the exact filepath (if you are not sure how to
structure the filepath and directly copying the filepath does not work, use the given developer
filepath in the source code's comments as a baseline for how to structure the filepath manually)

**5.** When prompted, enter the filepath you wish to save the report (please see the source code if you
need an example for how to manually structure a filepath)

**6.** Your report should be ready!

## Building and Running

The project can be run if the files are together in a dedicated project on any capable IDE i.e. CLion.
In CLion, once your files are placed into the same project (typically through navigating your own file explorer),
navigate to the top-left four-line-stack menu.

Click it, move to the "Build" section, and build the project. From there, your project is built. You will see
the output filepath of the built project in the command line interface of the IDE (CLion): check there for an
executable of the project.

You can easily run your project from within the IDE (for example, on CLion, the project can be run immediately
with Shift+F10 or by navigating to the green "run" button at the top-right of the corner.)