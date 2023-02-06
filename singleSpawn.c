/*

File singleSpawn.c


Purpose: create a child process to compute days of hospitalization

It reads the first record of a binary file, translates the data and morphs into drAssesment.c to compute data and returns the number of days of hospitalization

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
#include <sys/wait.h>

/************************************************************************/
//MACROS  / DEFINES
#define PROBLEM_LENGTH 24

/************************************************************************/
// FUNCTION PROTOTYPES
int morph(char *id, char *priorityLevel, char *medicalProblem);
int child(PatientInfo patient);
void parent(int argc, char* argv[]);


/***********************************************************************************/
/* Morph program into drAssessent

input
id - id of patient
priorityLevel - priority level of patient
medicalProblem - medical problem of patient

output
none


assumption - all inputs are valid
*/

int morph(char *id, char *priorityLevel, char *medicalProblem){
	//define input paraeters for drAssesment
    char *in[] = { id, " ", priorityLevel, " ", medicalProblem, NULL };
	//morph
    return execv("drAssessment", in);

}
/***********************************************************************************/
/* executes the morphing with correct data

input
Patient - the patient struct that contains patient information

output
none

assumption - input is a valid patient
*/
//--------------------------------------------------------------------------------------------------
int child(PatientInfo patient){
	//declare variables
    char priorityLevel[2];
    char medicalProblem[PROBLEM_LENGTH];
    char id[10];
	//convert data to strings
    sprintf(priorityLevel, "%d", patient.priorityLevel);
    sprintf(medicalProblem, "%s", patient.medicalProblem);
    sprintf(id, "%i", patient.id);
	//call the morph
    return morph(id, priorityLevel, medicalProblem);
}
/***********************************************************************************/
/* open files properly and calls child and print out the number of days of hospitalization

input
argc - number of arguments
argv - list of arguments

output
print number of days of hospitalization

assumption - parameters are valid
*/
//-------------------------------------------------------------------------------------------------
void parent(int argc, char* argv[]){
	//declare variables
    struct patientInfo patient;
    pid_t child_pid, wpid;
    int status = 0;
    int result = 0;

	//check if you have enough arguments
    if (argc < 2){
        printf("Usage: single assessment filename\n");
    }else{
	//open file and check if it exists
        FILE *file = fopen(argv[1], "r");
        if (file == NULL){
            printf("File %s does not exist, where %s is the provided file name\n", argv[1],argv[1]);
        }else{
			//read the file's first record
            FILE *ptr = NULL;
            ptr = fopen(argv[1],"rb");
            fread(&patient,sizeof(struct patientInfo), 1,ptr);
            fclose(ptr);
        }
    fclose(file);
    }

    //start child process
    if((child_pid = fork()) == 0){
        result = child(patient);
        exit(0);
    }

    //wait for all child processes and record numer of days for hospitalization
    if(child_pid != 0){
        wait(&status);
        result = WEXITSTATUS(status);
    }

	//print out the result
   	if(result <= 0){
        printf("Patient %s %s id (%d) does not need hospitalization\n", patient.firstName, patient.familyName, patient.id);
    }else{
        printf("Patient %s %s id (%d) requires %i hospitalization\n", patient.firstName, patient.familyName, patient.id, result);
    }
}
/***********************************************************************************/
/* main function

input
same as parent function

output
same asd parent function

assumption - inputs are valid
*/
//--------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	//call parent function
    parent(argc, argv);
}
