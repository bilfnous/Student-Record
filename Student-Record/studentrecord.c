#include "studentrecord.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void StudentInformation(void)
{
	int status;
	char operation;

	// Creating the first record pointer;
	struct studentdata* srecord;

	srecord = (struct studentdata*)calloc(1, sizeof(struct studentdata));
	if (srecord == NULL)
	{
		printf("\nCannot allocate memory\n");
		return;
	}

	RetrieveStudentInformation("studentdata.txt", srecord);

	printf("\n\nStudent Information\n\n");
	while (1)
	{
		printf("\n\nEnter 'R' to Register a Student\n");
		printf("Enter 'D' to De-Register a Student\n");
		printf("Enter 'M' to Enter Student Marks\n");
		printf("Enter 'S' to Display Student Information\n");
		printf("Enter 'C' to Display Class Information\n");
		printf("Enter 'Q' to Quit\n\n");
		printf(">> ");
		scanf(" %c", &operation);
		switch (operation)
		{
		case 'R':
		case 'r':
			status = RegisterStudent(GetStudentID(), srecord);
			if (status == 2)
			{
				printf("\nStudent already registered\n");
			}
			else if (status == 1)
			{
				printf("\nRecord Added\n");
			}
			else
			{
				printf("\nOut of Record Space\n");
			}
			break;
		case 'D':
		case 'd':
			if (DeregisterStudent(GetStudentID(), srecord))
			{
				printf("\nRecord Deleted\n");
			}
			else
			{
				printf("\nRecord Not Found\n");
			}
			break;
		case 'M':
		case 'm':
			if (!EnterMarks(GetStudentID(), srecord))
			{
				printf("\nStudent Record Not Found\n");
			}
			break;
		case 'S':
		case 's':
			if (!DisplayStudentInformation(GetStudentID(), srecord))
			{
				printf("\nStudent Record Not Found\n");
			}
			break;
		case 'C':
		case 'c':
			DisplayClassInformation(srecord);
			break;
		case 'Q':
		case 'q':
			if (SaveStudentInformation("studentdata.txt", srecord))
			{
				printf("\nStudent data saved\n");
			}
			DeleteList(srecord);
			return;
		default:
			printf("\nInvalid Selection ..Try Again\n");

		}
		operation = '\0';
	}

}


int RegisterStudent(int SID, struct studentdata* head)
{
	struct studentdata* add = NULL;
	struct studentdata* cur = NULL;

	if (FindStudent(SID, head) != NULL)
	{
		return 2;
	}
	cur = head;
	if (cur->sid == 0)
	{
		EnterStudentInformation(cur);
		cur->sid = SID;
		return 1;
	}

	while (cur->next != NULL)
	{
		cur = cur->next;
	}

	add = (struct studentdata*)calloc(1, sizeof(struct studentdata));
	if (add != NULL)
	{
		EnterStudentInformation(add);
		add->sid = SID;
		add->prev = cur;
		add->next = NULL;
		cur->next = add;
		return 1;
	}
	return 0;
}

int DeregisterStudent(int SID, struct studentdata* cr)
{
	struct studentdata* del = NULL;
	struct studentdata* cur = NULL;

	del = FindStudent(SID, cr);
	if (del != NULL)
	{
		if (del->next == NULL)
		{
			cur = del->prev;
			cur->next = NULL;
		}
		else
		{
			cur = del->prev;
			cur->next = del->next;
			cur = del->next;
			cur->prev = del->prev;
		}
		free(del);
		return 1;
	}
	return 0;
}

void DisplayClassInformation(struct studentdata* cr)
{
	struct studentdata* cur = NULL;
	double sum = 0;
	double total = 0;
	int i, count = 0;

	cur = cr;
	printf("\nClass Information\n\n");
	while (cur != NULL)
	{
		total = 0;
		count++;
		printf("\n%5d - %s, %s\n", cur->sid, cur->lastname, cur->firstname);
		for (i = 0; i < MAXTESTS; i++)
		{
			printf("Test%d: %3.0d\t", i + 1, cur->test[i]);
			total += cur->test[i];
		}
		printf("Average: %5.2f%%\n", total / MAXTESTS);
		sum += total;
		cur = cur->next;
	}
	printf("\n\nClass Average: %4.2lf%%\n", sum / count / MAXTESTS);
}

int GetStudentID(void)
{
	int ID;

	while (1)
	{
		printf("\nEnter a 5 digit Student Number: ");
		scanf(" %d", &ID);
		if ((ID >= 10000) && (ID <= 99999))
		{
			return ID;
		}
		printf("\nInvalid ID..Try Again\n");
	}
}

void DeleteList(struct studentdata* head)
{
	struct studentdata* cur = NULL;

	cur = head;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	while (cur->prev != NULL)
	{
		cur = cur->prev;
		free(cur->next);
	}
	free(cur);
}

void EnterStudentInformation(struct studentdata* sd)
{
	while (getchar() != '\n');	// Clear Input buffer
	printf("\nStudent Data Input");
	printf("\nLast Name: ");
	scanf(" %S", sd->lastname);
	printf("\nFirst Name: ");
	scanf(" %S", sd->firstname);
}

int EnterMarks(int SID, struct studentdata* sd)
{
	struct studentdata* cur = NULL;
	int i;

	cur = FindStudent(SID, sd);
	if (cur != NULL)
	{
		printf("\nEnter %5d marks\n", cur->sid);
		for (i = 0; i < MAXTESTS; i++)
		{
			printf("Test%2d: ", i + 1);
			scanf("%3d", &cur->test[i]);
		}
		return 1;
	}
	return 0;
}

struct studentdata* FindStudent(int SID, struct studentdata* head)
{
	struct studentdata* cur;

	cur = head;
	while (cur != NULL)
	{
		if (cur->sid == SID)
		{
			return cur;
		}

		cur = cur->next;
	}
	return NULL;


}

// Displays Student Record and Returns 1 if record found Else returns 0
int DisplayStudentInformation(int SID, struct studentdata* cr)
{
	struct studentdata* cur = NULL;

	double total;
	int i;
	cur = FindStudent(SID, cr);
	printf("\nStudent Data Report\n\n");
	printf("\n%5d - %s, %s\n", cur->sid, cur->lastname, cur->firstname);
	for (i = 0; i < MAXTESTS; i++)
	{
		printf("Test%d: %3.0d\t", i + 1, cur->test[i]);
		total = +cur->test[i];
	}
	printf("Average: %5.2f%%\n", total / MAXTESTS);
	return 1;


}



int SaveStudentInformation(char* fname, struct studentdata* head)
{
	struct studentdata* cur;

	FILE* fp;
	fp = fopen(fname, "w");
	if (fp == NULL)
	{
		printf("\nCan't open file, data not saved\n");
		return 0;
	}
	cur = head;
	if (cur->sid == 0 || cur == NULL)
	{
		fclose(fp);
		return 0;
	}
	while (cur != NULL)
	{

		fwrite(cur, sizeof(struct studentdata), 1, fp);
		cur = cur->next;

	}
	fclose(fp);
	return 1;
}



int RetrieveStudentInformation(char* fname, struct studentdata* head)
{
	struct studentdata* cur = NULL;
	struct studentdata* add = NULL;
	FILE* fp;

	fp = fopen(fname, "r");
	if (fp == NULL)
	{
		printf("\nCan't open file, data not retrieved!\n");
		return 0;
	}
	cur = head;
	while (1)
	{
		if (cur->sid == 0)
		{
			fread(cur, sizeof(struct studentdata), 1, fp);
			cur->prev = NULL;
			cur->next = NULL;
		}
		else
		{
			add = (struct studentdata*)calloc(1, sizeof(struct studentdata));
			if (add == NULL)
			{
				printf("\nCannot allocate memory\n");
				return 0;
			}
			fread(add, sizeof(struct studentdata), 1, fp);
			if (feof(fp))
			{
				free(add);
				fclose(fp);
				return 1;
			}
			cur->next = add;
			add->prev = cur;
			add->next = NULL;
			cur = add;
		}
	}
}


