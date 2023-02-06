#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

int isPrime(unsigned long number);

int main(int argc, char *argv[]) {
    int i;

    unsigned int id;
    unsigned char priority;
    char* medicalProblem = NULL;
    int rc = 1;

    if (argc < 4) {
        return(-2);
    }

    sscanf(argv[1], "%u",&id);	// get the id
    sscanf(argv[2], "%hhu", &priority);  // get the priority
    medicalProblem = argv[3];

    if (priority < 0 || priority > 9) {
        rc = -1;
    }

    else {
        rc = patientAssessment(id, priority, medicalProblem);
    }

    return(rc);
}

