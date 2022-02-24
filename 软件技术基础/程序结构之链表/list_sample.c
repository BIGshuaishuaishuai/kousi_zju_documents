#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define MaxLength 10

typedef struct LIST
{
	char name[MaxLength];
	int length;
	struct LIST *next;
}LIST;


void print_list(LIST *p) /* Print all the node of the list. */
{
	struct LIST *ptr = p;
	int i;
	
	while(ptr != NULL)
	{
		for(i = 0;i < ptr->length; i++)
			printf("%c", ptr->name[i]);
		printf("\n");
		ptr = ptr->next;
	} 
}


LIST * insert_node(LIST *head, char x[MaxLength], int k)
{
	LIST *NewNode;
	LIST *ptr = head;
	int i, length = 0;
	
	NewNode = (LIST*)malloc (sizeof(struct LIST));
	for(i = 0;i < MaxLength;i++) NewNode->name[i] = 0;
	strcpy(NewNode->name, x);
	NewNode->length = strlen(x);
	
	if(k == 1) {
		NewNode->next = head;
		return NewNode;
	}
	else {
		i = 2;
		while(i < k)
		{
			ptr = ptr->next;
			i++;
		}
		NewNode->next = ptr->next;
		ptr->next = NewNode;
	}
	
	return(head);
}

delete_node(LIST *head, int i)
{
	if(i == 1)
	{
		LIST *ptr = head->next;
		for(i = 0;i < MaxLength;i++) head->name[i] = 0;
		strcpy(head->name, head->next->name);
		head->length = head->next->length;
		head->next = head->next->next;
		free(ptr);
		return;
	}
	
	int j = 2;
	LIST *ptr = head, *ptr2;
	while(j < i && ptr->next != NULL)
	{
		ptr = ptr->next;
		j++;
	}
	if(ptr->next == NULL){
		printf("Error: there is no such a node at that position.\n");
		return;
	} 
	ptr2 = ptr->next;
	ptr->next = ptr2->next;
	free(ptr2);
}

main()
{
	int i, choice;
	char x[MaxLength], element, listname;
	LIST a, b, c, l, *p, *head; 
	
	strcpy(a.name, "Zhou");  a.length = 4;
	strcpy(b.name, "Xing");  b.length = 4;
	strcpy(c.name, "Chi");   c.length = 3;
	
	head = &a;
	a.next = &b;
	b.next = &c;
	c.next = NULL;
	p = head;
	
	/*
	LIST *a, *b, *c, *p, *head; 
	
	a = (LIST *)malloc(sizeof(LIST));
	strcpy(a->name, "Zhou");

	b = (LIST *)malloc(sizeof(LIST));
	strcpy(b->name, "Xing");

	c = (LIST *)malloc(sizeof(LIST));
	strcpy(c->name, "Chi"); 
	
	head = a;
	a->next = b;
	b->next = c;
	c->next = NULL;
	p = head;
	*/

	printf("Welcome to use this programe!\nNow the exist list is:\n");
	print_list(p);

	printf("Please chose the function:\n1.Insert a node in the linklist.\n2.Delete a node in the link list.\n3.Print link list.\n4.Quit the programe.\n");
	
	scanf("%d", &choice);
	switch(choice)
	{
		case 4:{
					printf("Thanks to use!Good bye!");
					break;
			   }
		case 1:{
					printf("Input where the node you want to Insert:");
					scanf("%d", &i);

					printf("Input the node you want to Insert:");
					scanf(" %s", &x);
					
					head = insert_node(head, x, i);
					print_list(head);
					
					break;
				}
		case 2:{
					printf("Input where the node you want to Delete:");
					scanf("%d", &i);

					delete_node(head, i);
					print_list(head);
					break;
				}
		case 3:{
					print_list(head);
					
					break;

			   }
	}
} 
