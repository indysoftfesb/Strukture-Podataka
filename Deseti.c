#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Element
{
	char value;
	
	struct Element* right;
	struct Element* left;

};

struct Stack
{

	struct Element* next;

};

typedef struct Element Element;
typedef struct Element* element;
typedef struct Stack* stack;

element Create(char);

stack CreateStack();
element Push(element,stack);
element Pop(stack);
int PrintStack(stack);

int Inorder(element,FILE*);





int main()
{
	stack s = CreateStack();
	char c;
	char text[128];
	int i  = 0;
	
	

	element temp = NULL;
	element tempL = NULL;
	element tempR = NULL;
	
	
	FILE* fp = fopen("Text.txt","r");
	FILE *fpw = fopen("Text2.txt","a");

	
	
	while((c=fgetc(fp)) != EOF)
	{	
		if( c == '+' || c == '-' || c=='*' || c == '/')
		{
			tempR = Pop(s);
			tempL = Pop(s);
			Push(Create(c),s);
			
			temp = s->next;
			while(temp->right != NULL)
				temp = temp ->right;	
			temp->right = tempR;
			temp->left = tempL;
		}	

		else
			Push(Create(c),s);
		
	}	
	

	Inorder(s->next,fpw);

	
	
	
	
}


element Create(char value)
{
	element e = (element) malloc (sizeof(Element));
	
	if(e!=NULL)
	{
		e->value = value;
		e-> right = e->left = NULL;
	}
	return e;
}

stack CreateStack()
{
	return (stack) malloc (sizeof(struct Stack));
}

element Push(element e, stack s)
{
	element temp = s->next;
	
	if(temp == NULL)
		s->next = e;
	else
	{
		while(temp->right != NULL)
			temp = temp -> right;
			
		temp->right = e;
	}
	
	return e;

}



element Pop(stack s)
{
	element temp = s->next;
	element prev = s->next;
	
	if(temp==NULL)
	{
		printf("Stack is empty! \n");
		return NULL;
	}
	else
	{
			
		while(temp->right != NULL)
			temp = temp->right;

		if(temp == prev)
			s->next = NULL;
		else
		{
			while(prev->right != temp)
				prev = prev->right;
			prev->right = NULL;
		
		
		}
		
		return temp;
		
	}

}

int PrintStack(stack s)
{
	element temp = s->next;
	
	if(temp == NULL)
		printf("Stack is empty \n");
	else
	{
		while(temp != NULL)
		{
			printf("%c \n",temp->value);
			temp = temp->right;
		}	
	
	}


}

int Inorder(element e,FILE* fp)
{



	if(e!=NULL)
	{
		Inorder(e->left,fp);
		fputc(e->value,fp);
		Inorder(e->right,fp);
	
	
	}


}















