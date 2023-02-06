/*

File singleAssesment.c


Purpose: read binary file and assess the number of days a person need to be hospitalized
- reads a binaryfile then morphs into drAssessment.c to get the number of days

Revision:
a. Initial code - Jason Huynh

*/

/************************************************************************/

// INCLUDE FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "patient.h"

/************************************************************************/
//MACROS  / DEFINES
#define PROBLEM_LENGTH 24

/************************************************************************/
// FUNCTION PROTOTYPES

int morph(char *id, char *priorityLevel, char *medicalProblem);


/***********************************************************************************/
/* Morph program into drAssessment

input
id - id of patient
priorityLevel - priority level of patient
medicalProblem - medical problem of patient

output
none

assumption - all inputs are valid
*/

int morph(char *id, char *priorityLevel, char *medicalProblem){

    char *in[] = { id, " ", priorityLevel, " ", medicalProblem, NULL };
    execv("drAssessment", in);
}

/***********************************************************************************/
/* main method, Correctly opens files, morph into drAssesment with correct inputs

input
id - id of patient
priorityLevel - priority level of patient
medicalProblem - medical problem of patient

output
none

assumption - all inputs are valid
*/

int main(int argc, char* argv[]) {
	//make sure enough arguments
    if (argc < 2) {
        printf("Usage: single assessment filename\n");
    }
	//open file and check if it exists
    else {
        FILE *file = fopen(argv[1], "r");

        if (file == NULL){
            printf("File %s does not exist, where %s is the provided file name", argv[1],argv[1]);
        }
        
        else {
			//define variables
            FILE *ptr = NULL;
            struct patientInfo patient;

            char priorityLevel[2];
            char medicalProblem[PROBLEM_LENGTH];
            char id[10];
			
			//open binary file and read first record
            ptr = fopen(argv[1],"rb");
            fread(&patient,sizeof(struct patientInfo), 1,ptr);
			
			//convert data to strings
            sprintf(priorityLevel, "%d", patient.priorityLevel);
            sprintf(medicalProblem, "%s", patient.medicalProblem);
            sprintf(id, "%i", patient.id);

			//execute the morphing
            morph(id, priorityLevel, medicalProblem);
        }

        fclose(file);
    }
}














