
/*
File name is patient.h
 Purpose: file contains stuctures and functions related to patients
 


 */


#ifndef PATIENT_2401_HEADER
#define PATIENT_2401_HEADER 1

/************************************************************************/
// DEFINES


#define NAME_LENGTH 16
#define PROBLEM_LENGTH 24

/************************************************************************/

// STRUCTURES


typedef struct patientInfo {
	unsigned int id;			// patient id
	unsigned int arrivalTime;	// arrival order of patients
	unsigned char priorityLevel;	// priority level
	char medicalProblem[PROBLEM_LENGTH];	// a description of the medical problem
	char firstName[NAME_LENGTH];		// patients first name
	char familyName[NAME_LENGTH];	// patients family name
} PatientInfo;



/************************************************************************/
// FUNCTION PROTOTYPES

int patientAssessment(unsigned int id, unsigned char priorityLevel, char* medicalProblem);

#endif
