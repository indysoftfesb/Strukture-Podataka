#define _CRT_SECURE_NO_WARNINGS
#define MAX_FILENAME 50
#include<stdio.h>
#include<stdlib.h>
 
struct node;
typedef struct node* Pnode;
struct node
{
    int broj;
    Pnode Next;
};
//Funkcije
 
//citanje listi
int read(Pnode);
int print(Pnode);
int intersection(Pnode, Pnode, Pnode);
int Union(Pnode, Pnode, Pnode);
 
 
int main()
{
    struct node L1, L2, U, I;
    int x;
    L1.Next = NULL;
    L2.Next = NULL;
    U.Next = NULL;
    I.Next = NULL;
 
    x = read(&L1);
    if (x != 1)
    {
        printf("Greska prilikom citanja prve liste\n");
        return 0;
    }
    x = read(&L2);
    if (x != 1)
    {
        printf("Greska prilikom citanja druge liste\n");
        return 0;
    }
 
    x = print(L1.Next);
    if (x != 1)
    {
        printf("Greska prilikom ispisa prve liste\n");
        return 0;
    }
 
    x = print(L2.Next);
    if (x != 1)
    {
        printf("Greska prilikom ispisa druge liste\n");
        return 0;
    }
 
    x = Union(L1.Next, L2.Next, &U);
    if (x != 1)
    {
        printf("Greska prilikom izrade unije\n");
        return 0;
    }
    printf("\nUnija:\n");
    x = print(U.Next);
    if (x != 1)
    {
        printf("Greska prilikom ispisa unije\n");
        return 0;
    }
 
    x = intersection(L1.Next, L2.Next, &I);
    if (x != 1)
    {
        printf("Greska prilikom izarde presjeka\n");
        return 0;
    }
    printf("\nPresjek:\n");
    x = print(I.Next);
    if (x != 1)
    {
        printf("Greska prilikom ispisa presjeka\n");
        return 0;
    }
 
    getchar();
    getchar();
    return 0;
}
 
 
int read(Pnode List)
{
    char ime_dat[MAX_FILENAME];
    FILE *fp = NULL;
    Pnode q, temp;
    printf("\nUpisi ime datoteke:\n");
    scanf(" %s", ime_dat);
    fp = fopen(ime_dat, "r");
    if (NULL == fp)
    {
        printf("\nGreska prilikom otvaranja datoteke.\n");
        return -1;
    }
 
    while (!feof(fp))
    {
        q = (Pnode)malloc(sizeof(struct node));
        if (NULL == q)
        {
            printf("Greska tokom alokacije memorije\n");
            return -1;
        }
        else
        {
            fscanf(fp, " %d", &q->broj);
            temp = List;
            while (temp->Next != NULL && temp->Next->broj >= q->broj)
                temp = temp->Next;
 
            q->Next = temp->Next;
            temp->Next = q;
        }
    }
    fclose(fp);
    return 1;
}
 
 
int print(Pnode List)
{
    printf("\nIspis liste:\n ");
    while (List != NULL)
    {
        printf(" %d", List->broj);
        List = List->Next;
    }
    return 1;
}
 
 
int Union(Pnode L1, Pnode L2, Pnode U)
{
    Pnode temp, q;
 
    while (L1 != NULL && L2 != NULL)
    {
        q = (Pnode)malloc(sizeof(struct node));
        if (NULL == q)
        {
            printf("Greska prilikom alokacije memorije.\n");
            return -1;
        }
        else
        {
            if (L1->broj > L2->broj)
            {
                q->broj = L1->broj;
                L1 = L1->Next;
            }
            else if (L1->broj < L2->broj)
            {
                q->broj = L2->broj;
                L2 = L2->Next;
            }
            else
            {
                q->broj = L1->broj;
                L1 = L1->Next;
                L2 = L2->Next;
            }
            if (U->broj == q->broj)
                free(q);
            else
            {
                q->Next = U->Next;
                U->Next = q;
                U = q;
            }
        }
    }
 
 
    if (L1)
        temp = L1;
    else
        temp = L2;
    while (temp)
    {
        q = (Pnode)malloc(sizeof(struct node));
        if (!q)
        {
            printf("Greska prilikom alokacije memorije");
            return -1;
        }
        else
        {
            q->broj = temp->broj;
            if (U->broj == q->broj)
                free(q);
            else
            {
                q->Next = U->Next;
                U->Next = q;
                U = q;
            }
            temp = temp->Next;
        }
    }
 
    return 1;
}
 
int intersection(Pnode L1, Pnode L2, Pnode I)
{
    Pnode q;
 
    while (L1!=NULL && L2!=NULL)
    {
        if (L1->broj > L2->broj)
            L1 = L1->Next;
        else if (L1->broj < L2->broj)
            L2 = L2->Next;
        else
        {
            q = (Pnode)malloc(sizeof(struct node));
            if (!q)
            {
                printf("Greska prilikom alokacije memorije");
                return -1;
            }
            else
            {
                q->broj = L1->broj;
                q->Next = I->Next;
                I->Next = q;
                I = q;
            }
            L1 = L1->Next;
            L2 = L2->Next;
        }
    }
 
    return 1;
}