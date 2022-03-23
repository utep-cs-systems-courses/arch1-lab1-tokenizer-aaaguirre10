#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"


/* Initialize the linked list to keep the history. */
List* init_history()
{
  List* init_list = (List*) malloc(sizeof(List)); //allocates memory for the list
  return init_list;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str)
{
  Item *n_data = (Item*) malloc(sizeof(Item)); //allocates memory for the history
  Item *curr_node = list -> root; //creates a node to traverse the list

  //find the len of str
  int item_Id = 0; 
  int str_len = 0;
  while(str[str_len] != '\0')
    str_len++;

  //set item to the a copy string
  n_data -> str = copy_str(str, str_len); //command
  n_data -> next = NULL; //next pointer

  if(curr_node == NULL)
    {
      n_data -> id = item_Id; //id number
      list -> root = n_data; //sets root with new information
      return;
    }

  while(curr_node -> next != NULL)
    {
      item_Id++; //increments id number
      curr_node = curr_node -> next;//traverses the list
    }

  item_Id++;
  n_data -> id = item_Id;
  curr_node -> next = n_data; //stores the command
}


/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id)
{
  if(id < 0)
    {
      printf("Invalid ID. Please try again.");
      return "Error! Wrong ID";
    }

  Item *curr_node = list -> root; //sets node to traverse list 

  while(curr_node != NULL)
    {
      if(curr_node -> id == id) //searches for match id number and returns it
	{
	  return curr_node -> str;
	}
      curr_node = curr_node -> next; //traverse list
    }
  return "Error! Wrong ID"; //not found ID
}


/*Print the entire contents of the list. */
void print_history(List *list)
{
  Item *curr_node = list -> root; //sets node to traverse list
  for(int i = 0; curr_node != NULL; i++)
    {
      printf("%s", curr_node ->str); //prints current node
      curr_node = curr_node -> next; //traverse node
    }
  printf("Printing history done.");
}

/*Free the history list and the strings it references. */
void free_history(List *list)
{
  Item *curr_node = list -> root; //sets node to traverse list
  while(list -> root != NULL)
    {
      list -> root = list -> root -> next;
      free(curr_node -> str);
      free(curr_node);
      curr_node = list -> root; //traverse list
    }
  free(list); //frees the entire list
}
