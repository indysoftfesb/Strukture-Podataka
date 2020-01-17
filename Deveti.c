#include <stdio.h>
#include <stdlib.h>


struct Element
{
	int value;
	
	struct Element* right;
	struct Element* left;

};


typedef struct Element Element;
typedef struct Element* element;


element Create(int);
element Insert(int,element);
void Inorder(element);
element Find(int,element);

int main()
{
	element root = NULL;
	int i;
	
	root = Insert(3,root);
	
	Insert(5,root);
	Insert(2,root);
	Insert(4,root);
	Insert(6,root);
	Insert(1,root);
	Insert(0,root);

	Inorder(root);

	for(i=0;i<10;i++)
		Find(i,root);
	
	return 0;
	

}


element Create(int value)
{
	element e = (element) malloc (sizeof(Element));
	
	if(e!=NULL)
	{
		e->value = value;
		e-> right = e->left = NULL;
	}
	return e;
}

element Insert(int value, element root)
{
	if(root == NULL)
		return Create(value);
	if(value > root->value)
		root->right = Insert(value,root->right);
	else
		if(value < root->value)
			root->left = Insert(value,root->left);
			
	return root;
}


void Inorder(element root)
{
	if(root!=NULL)
	{
		Inorder(root->left);
		printf("%d\n",root->value);
		Inorder(root->right);
	
	}

}

element Find(int value, element root)
{
	if(root == NULL)
		return root;	
	if(value > root->value)
		Find(value,root->right);
	else
		if(value < root->value)
			Find(value,root->left);
	
	else
	{
		printf("Element found! \n");
		return root;
	
	}
}













