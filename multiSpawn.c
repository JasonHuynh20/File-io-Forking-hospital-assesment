/*

File multiSpawn.c


Purpose: to print the number of days oh hospitalization for the first 10 people in a binary file  
opens file, reads data from binary file, converts data, morph into drAssessment

Revision:
a. Initial code - Jason

*/

/************************************************************************/

// INCLUDE FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include "patient.h"

/************************************************************************/
//MACROS  / DEFINES
#define PROBLEM_LENGTH 24

/************************************************************************/
// FUNCTION PROTOTYPES
int morph(char *id, char *priorityLevel, char *medicalProblem);
int child(PatientInfo patient);
void parent(int argc, char* argv[]);


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
    char priorityLevel[2];
    char medicalProblem[PROBLEM_LENGTH];
    char id[10];
    sprintf(priorityLevel, "%d", patient.priorityLevel);
    sprintf(medicalProblem, "%s", patient.medicalProblem);
    sprintf(id, "%i", patient.id);
    return morph(id, priorityLevel, medicalProblem);
}
/***********************************************************************************/
/* Opens files and reads the binary data and calls child function

input
argc - the number of arguments
argv - a list of the arguments

output
prints the number of hospitalization for the first 10 patients in binary file

assumption - input is a valid patient
*/
//-------------------------------------------------------------------------------------------------
void parent(int argc, char* argv[]){
	//declare variables
    struct patientInfo patient[10];
    pid_t child_pid[10];
    pid_t childPid = { 0 };
    pid_t wpid;
    int status = 0;
    int result;

    unsigned int count = 0;

	//check if there are enough arguments
    if (argc < 2) {
        printf("Usage: single assessment filename\n");
    }
    
    else {
		//open file and make sure it exists
        FILE *file = fopen(argv[1], "r");

        if (file == NULL) {
            printf("File %s does not exist, where %s is the provided file name\n", argv[1],argv[1]);
        }
        
        else {
			//open binary file and record 10 records
            FILE *ptr = NULL;
            
            ptr = fopen(argv[1],"rb");
            fread(&patient, sizeof(patient), 1, ptr);

            fclose(ptr);
        }

        fclose(file);
    }

    //start child process for 10 patients
    for (int i = 0; i < 10; i++) {
        if ((child_pid[i] = fork()) == 0) {
            child(patient[i]);
            exit(0);
        }
    }
    
    //wait for all child processes
    for (int i = 0; i < 10; i++) {
		status = 0;
        childPid = waitpid(-1, &status, 0);
		//if more than 10 patients stop
        count++;
        if (count == 10) {
            exit(0);
        }
		//if wait fails, stop program
        if (childPid == -1) {
            exit(0);
        }

		//check the id for each child process and seach list
        for (int j = 0; j < 10; j++) {
			//if a match is found, record the data 
            if (childPid == child_pid[j]) {
				result = WEXITSTATUS(status);
				//print the data/number of days
                if (result > 0) { // BREAKS HERE CUZ DAYS HOSPITALIZED IS ZERO
                    printf("Patient %s %s id (%d) requires %i hospitalization\n", patient[j].firstName, patient[j].familyName, patient[j].id, result);
                }
            }
        }
    } 
}
/***********************************************************************************/
/* Main function

input
Same as parent

output
same as parent

assumption - input is a valid patient
*/
//--------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    parent(argc, argv);
}














