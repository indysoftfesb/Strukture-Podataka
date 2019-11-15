#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

#ifndef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

struct Person;
typedef struct Person* person;
typedef struct Person* list;

typedef struct Person
{
	char* name;
	char* last_name;
	int year;

	person next;
}Person;

person CreatePerson(char*, char*, int);	//
list CreateList();						//


int AddToList_Front(person, list);		//
int AddToList_Last(person, list);		//

person FindByLastName(char*, list);		//
person FindLast(list);					//
int Delete(person, list);				//

int AddAfter(person, person,list);		//
int AddBefore(person, person,list);		//

void SortListByLastName(list);			//
void PrintList(list);					//

int PrintListToFile(list,char*);
int ReadListFromFile(list, FILE*);

/////////////////////////////////////////////////////////
int main()
{
	list l = CreateList();
	person a = CreatePerson("dome", "dome", 1995);
	person b = CreatePerson("jozo", "antic", 1950);
	person  c = CreatePerson("jure", "jure", 1999);


	AddToList_Front(a, l);
	AddAfter(b, a, l);
	AddAfter(c, b, l);

	SortListByLastName(l);

	PrintListToFile(l,"Text.txt");
	
}


person CreatePerson(char* n, char* ln, int y)
{
	person p = (person)malloc(sizeof(struct Person));
	if (p != NULL)
	{
		p->name = n;
		p->last_name = ln;
		p->year = y;
		p->next = NULL;

		return p;
	}
	else
		return NULL;
}
list CreateList()
{
	list l = (person)malloc(sizeof(struct Person));
	l->name = "List";
	l->next = NULL;
	return l;
}
person FindLast(list l)
{
	person temp = l->next;

	if (temp == NULL)
	{
		printf("Empty list");
		return NULL;
	}

	else
	{
		while (temp->next != NULL)
			temp = temp->next;

		return temp;
	}
}
int Delete(person p, list l)
{
	person temp = l;
	if (p != NULL && l != NULL)
	{
		
		while (temp->next != p)
			temp = temp->next;

		temp->next = p->next;


		free(p);
		return 0;

	}
	else
	{
		printf("Something is missing");
		return -1;
	}
}

int AddAfter(person p, person a,list l)
{
	person temp = a->next;
	if (p != NULL && a != NULL && l != NULL)
	{
		p->next = temp;
		a->next = p;
		return 0;
	}
	else
	{
		printf("Something is missing in function AddAfter");
		return -1;
	}
}
int AddBefore(person p,person b,list l)
{
	person temp;

	if (p != NULL && b != NULL && l != NULL)
	{
		temp = l;
		while (temp->next != b)
			temp = temp->next;

		temp->next = p;
		p->next = b;

		return 0;
	}


	else
	{
		printf("Something is missing in function AddBefore");
		return -1;
	}
}

int AddToList_Front(person p, list l)
{
	if (p != NULL && l != NULL)
	{
		p->next = l->next;
		l->next = p;

	
		return 0;
	}
	else
	{
		printf("Something is missing in function AddToList_Front");
		return -1;
	}




}
int AddToList_Last(person p, list l)
{
	person temp = FindLast(l);
	if (temp == NULL)
	{
		l->next = p;
		p->next = NULL;
		return 0;
	}
	else
	{
		temp->next = p;
		p->next = NULL;
		return 0;
	}
}

person FindByLastName(char* ln, list l)
{
	person p = l->next;
	if (p != NULL)
	{
		while (p->last_name != ln)
		{
			if (p == NULL)
				return NULL;
			else
				p = p->next;
		}
		return p;
	}
	else
	{
		printf("Empty list");
		return NULL;
	}
}

void SortListByLastName(list l)
{
	person i, j, prev_j, temp, end;

	end = NULL;

	i = l;

	while (i->next != end)
	{
		prev_j = i;
		j = i->next;
		while (j->next != end)
		{
			if (strcmp(j->last_name, j->next->last_name) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}
		end = j;
	}

}

void PrintList(list l)
{
	person temp = l->next;

	if (temp == NULL)
		printf("Empty list");
	else
	{
		while (temp != NULL)
		{
			printf("%s %s %d \n", temp->name, temp->last_name, temp->year);
			temp = temp->next;
		}
	}
}


int PrintListToFile(list l,char* fileName)
{
	person temp;

	FILE* fp = fopen(fileName, "w");
	if (fp == NULL && l!=NULL)
	{
		printf("Cannot find the file.");
		return -1;
	}
	else
	{
		if (l->next != NULL)
		{
			temp = l->next;

			while (temp != NULL)
			{
				fprintf(fp, "%s %s %d \n", temp->name, temp->last_name, temp->year);
				temp = temp->next;
			}
			return 0;
		}
		else
		{
			printf("Cannot find the list.");
			return -2;

		}
	}


}
int ReadListFromFile(list l, FILE* fp)
{
	char* name_tmp;
	char* last_name_tmp;
	int year_temp;
	person p;
	if (fp != NULL)
	{
		while (feof(fp) == 0)
		{
			fscanf(fp, "%s %s %d", name_tmp, last_name_tmp, year_temp);
			p = CreatePerson(name_tmp, last_name_tmp, year_temp);
			AddToList_Front(p, l);
		}

		fclose(fp);
	}
}