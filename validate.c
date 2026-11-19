
#include "main.h"

status insert_at_last(char *str, sll **head)
{
    char *ptr = strrchr(str, '.');

    if(ptr == NULL || strcmp(ptr, ".txt") != 0)
    {
        printf("\nERROR: File %s is in wrong format\n", str);
        printf("INFO: Only .txt files are accepted\n");
        return e_failure;
    }

    if(strlen(str) >= sizeof(((sll *)0)->name))
    {
        printf("ERROR: Filename is too long\n");
        return e_failure;
    }

    FILE *fptr = fopen(str, "r");

    if(fptr == NULL)
    {
        printf("\nERROR: Reading %s file failed\n", str);
        return e_failure;
    }

    if(getc(fptr) == EOF)
    {
        printf("\nERROR: File %s is empty\n", str);
        fclose(fptr);
        return e_failure;
    }

    fclose(fptr);

    // Check for duplicate filename
    sll *temp = *head;

    while(temp != NULL)
    {
        if(strcmp(str, temp->name) == 0)
        {
            printf("\nINFO: File %s is a duplicate file\n", str);
            return e_duplicate;
        }

        temp = temp->link;
    }

    sll *newnode = malloc(sizeof(sll));

    if(newnode == NULL)
    {
        return e_failure;
    }

    strcpy(newnode->name, str);
    newnode->link = NULL;

    // Insert first node
    if(*head == NULL)
    {
        *head = newnode;
        return e_success;
    }

    // Traverse to last node
    temp = *head;

    while(temp->link != NULL)
    {
        temp = temp->link;
    }

    // Link new node
    temp->link = newnode;

    return e_success;
}
