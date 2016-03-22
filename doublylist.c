/* Doubly Linked List using C

    Functions included such as insert, delete, delete_entire, search
    
    Thanks to the folks at harvard for cs50 library
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <unistd.h>

typedef struct dllist
{
    int n;
    struct dllist* prev;
    struct dllist* next;
}dllist;

void lower(char* s);
dllist* insert(int n, dllist* head);
dllist* search(int n, dllist* head);
bool delete(int n, dllist* head);
bool delete_entire(dllist* head);


int main(void)
{
    char* s = NULL;
    dllist* head = malloc(sizeof(dllist)); 
    
    printf("Welcome to this program. Have fun\n");
    while(true)
    {
        
        sleep(2);
        printf("Please select any one of the following options\n a) Insert\n b)Search\n c)Delete\n d)Delete Entire (delete entire)\n ENTER 'quit' TO EXIT\n");
        do
        {
            s = GetString();
        }while(!strcmp(s, ""));
       
        lower(s); // convert the string to all lower case letters
       
        int x;
        // insert into the list here
        if(strncmp(s, "insert", sizeof(s) + 1) == 0)
        {
            printf("Please enter the number you want to insert in the list\n");
            scanf("%i", &x);
            head = insert(x, head);
            if(head != NULL)
                printf("The data was sucessfully added in the list: %p\n", head);
        }
        
        // search from the list here
        else if(strncmp(s, "search", sizeof(s) + 1) == 0)
        {
            printf("Please enter the number you want to search: \n");
            scanf("%i", &x);
            dllist* location = search(x, head);
            if(location != NULL)
                printf("The number found at location: %p\n", location);
            else
                printf("The number was not found in the list\n");
        }
        
        // delete form the list here
        else if(strncmp(s, "delete", sizeof(s) + 1) == 0)
        {
            printf("Please enter the value of the node you want to delete: \n");
            scanf("%i", &x);
            if(delete(x, head))
                printf("The node was sucessfully deleted\n");
            else
                printf("There seems to be a problem, Node could not be deleted\n");
        }
        
        // Delete entire list from here
        else if(strncmp(s, "delete entire", sizeof(s) + 1) == 0)
        {
            if(delete_entire(head) == true)
            {
                printf("The list was sucessfully deleted\n");
                return 0;
            }
        }
        
        // Handle quit here 
        else if(strncmp(s, "quit", sizeof(s) + 1) == 0)
            return 0;
            
        else
            printf("Something choose from one of the options\n");
    }
    
}

/*convert a string to lower case */
void lower(char* s)
{
    int i = 0;
    while(s[i])
    {
       s[i] = tolower(s[i]);
        i++;
    }
}

/* Function that inserts value inside an array */
dllist* insert(int n, dllist* head)
{
  
    // check if the first element is entered in the head    
    if(!head->n)
    {
        head->n = n;
        head->prev = NULL;
        head->next = NULL;
    }
    else
    {
        dllist* ptr = malloc(sizeof(dllist));
        ptr->n = n;
        ptr->prev = NULL;
        ptr->next = head;
        head->prev = ptr;
        head = ptr;
    }
    return head;
}

/* function searches for a given element */
dllist* search(int n, dllist* head)
{
    dllist* ptr = head;
    do
    {
        if(ptr->n == n)
            return ptr;
        ptr = ptr->next;
    }while(ptr != NULL);

    return NULL;
}

/* delete a particular element */
bool delete(int n, dllist* head)
{
    dllist* location = search(n, head);
    if(location != NULL)
    {
        dllist* prev = location->prev;
        dllist* next = location->next;
        if(location->next != NULL && location->prev != NULL)
        {
            prev->next = next;
            next->prev = prev;
        }
        else if (location->next == NULL && location-> prev != NULL)
            prev->next = NULL;
        else if (location->prev == NULL && location->next != NULL)
            next->prev = NULL;
        free(location);
        return true;
    }
    return false;
}

/* Delete the entire list */
bool delete_entire(dllist* head)
{
    if(head == NULL)
        return false;
        
    dllist* ptr = head;
    while(ptr != NULL)
    {
        ptr = ptr->next;
        free(head);
        delete_entire(ptr);
    }
    return true;
}