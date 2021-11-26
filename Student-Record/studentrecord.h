#ifndef STUDENTRECORD_H
#define STUDENTRECORD_H

// Constants
#define MAXTESTS 3
#define MAXLNAME 20
#define MAXFNAME 10
#define MAXMARK 100

// Structures
struct studentdata
{
	char lastname[MAXLNAME];
	char firstname[MAXFNAME];
	int sid;
	int test[MAXTESTS];
	struct studentdata* prev;
	struct studentdata* next;
};


// Function Prototypes
void StudentInformation(void);
int RegisterStudent(int SID, struct studentdata* head);
int DeregisterStudent(int SID, struct studentdata* cr);
int DisplayStudentInformation(int SID, struct studentdata* cr);
void DisplayClassInformation(struct studentdata* cr);
int GetStudentID(void);
struct studentdata* FindStudent(int SID, struct studentdata* head);
void DeleteList(struct studentdata* head);
void EnterStudentInformation(struct studentdata* sd);
int EnterMarks(int SID, struct studentdata* sd);
int SaveStudentInformation(char* fname, struct studentdata* head);
int RetrieveStudentInformation(char* fname, struct studentdata* head);


#endif
