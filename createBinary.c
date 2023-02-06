#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "patient.h"
#include "string.h"

int populatePatient(int arrivalTime, PatientInfo* patient);

int main(int argc, char *argv[])

{
	int i;
	char *fname = NULL;
    FILE *fdBin = NULL;
    FILE *fdTxt = NULL;
    PatientInfo p;
    unsigned int numPatients;
    int rc = 0;

	unsigned int number;

	if (argc < 3) {
        printf(" Usage: %s outputFileName numberOfPatients \n",argv[0]);
        return(1);
    }

    fdBin = fopen(argv[1],"wb");
    if (fdBin == NULL) {
        printf("error when openning file %s\n",argv[1]);
       return(1);
    }

    fname = malloc(strlen(argv[1])+4+1);
    strncpy(fname,argv[1],strlen(argv[1]));
    strcat(fname,".txt");
    printf("fname = %s",fname);
    fdTxt = fopen(fname,"w");
    if (fdTxt == NULL) {
        printf("error when openning file %s\n",fname);
       return(1);
    }

	rc = sscanf(argv[2], "%du", &numPatients);
	if (rc != 1) return(1);
	printf("num patients = %d\n", numPatients);
    for (i = 0; i < numPatients; i++) {
		populatePatient(i, &p);
 		fprintf(fdTxt,"%-20s %-20s %7d %5d %3d  %s \n",
			p.firstName, p.familyName, p.id, p.arrivalTime, 
			p.priorityLevel, p.medicalProblem);
        rc = fwrite(&p, sizeof(PatientInfo), 1, fdBin);
        if (rc != 1) {
            printf("error when writing to file %s \n",argv[1]);
            if (fdBin != NULL) fclose(fdBin);
            return(1);
        }
    }


    if (fname != NULL) {free(fname);fname = NULL;}
    if (fdBin != NULL) fclose(fdBin);
    if (fdTxt != NULL) fclose(fdTxt);

	exit(0);
}




/***************************************************************************/
/* purpose: the function populate the patient info for testing

output
patient - allocated memory to the struct pointer which the function assigns values.




*/

int populatePatient(int arrivalTime, PatientInfo* patient)
{
	int j;
	char* first[10] = { "John", "Don", "Edna", "Bev", "Miya", "Jennifer", "Mark","Leslie","Ian","Fraser" };
	char* family[10] = { "Broker", "Smith", "Tower", "Little", "Bronson" , "Guy","Parrot","Klein", "Snow","Dual" };
	char* highPriorMedicalProblem[5] = { "High Fever", "COVID", "Drug Overdose", "Concussion", "Car Accident" };
	char* lowPriorMedicalProblem[5] = { "Low Fever", "Earaches", "Broken Bone", "Nosebleed", "Mild concussion" };


	// populate the first  name using a random i ndex to the first name array 
	j = rand() % 10;
	// copy the first name to the structure pointed by p using strcpy
	strncpy(patient->firstName, first[j], NAME_LENGTH);

	// populate the family  name using a random i ndex to the first name array 
	j = rand() % 10;
	// copy the family name to the structure pointed by p using strcpy
	strncpy(patient->familyName, family[j], NAME_LENGTH);

	// populate the patient id using the random numnber in the range of 0-4096  
	patient->id = rand() % 15000;

	// populate arrival time 
	patient->arrivalTime = arrivalTime;

	// populate the priorty level and the medical condition 
	patient->priorityLevel = rand() % 10;
	switch (patient->priorityLevel) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		strncpy(patient->medicalProblem, lowPriorMedicalProblem[patient->priorityLevel], sizeof(patient->medicalProblem) - 1);
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		strncpy(patient->medicalProblem, highPriorMedicalProblem[patient->priorityLevel - 5], sizeof(patient->medicalProblem) - 1);
		break;
	default:
		printf("should not be here priorityLevel = %d \n", patient->priorityLevel);
		return(1);
		break;
	}

	return(0);
}
