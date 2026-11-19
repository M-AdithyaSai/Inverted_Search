#ifndef main_h
#define main_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef enum status{
    e_success,
    e_failure,
    e_emptylist,
    e_datanotfound,
    e_duplicate
}status;

typedef struct sll{
    char name[20];
    struct sll *link;
}sll;

typedef struct subnode
{
    int wordcount;
    char filename[20];
    struct subnode *link;
    
}sub;

typedef struct main_node
{
    char word[25];
    int file_count;
    sub *sublink;
    struct main_node *mainlink;
}main_node;

typedef struct node{
    int index;
    main_node *link;
}hash;

status insert_at_last(char *, sll **);
status create_database(sll *head, hash arr[]);
status display_database(hash arr[]);
status search_database(hash arr[], char word[]);
status save_database(hash arr[], char *filename);
status update_database(hash arr[], sll **indexed_head, sll **indexed_tail);
int is_file_indexed(sll *head, char *filename);
status add_indexed_file(sll **head, sll **tail, char *filename);
status validate_database_file(FILE *fp);

#endif