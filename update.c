
#include "main.h"

int is_file_indexed(sll *head, char *filename)
{
    while(head != NULL)
    {
        if(strcmp(head->name, filename) == 0)
            return 1;

        head = head->link;
    }

    return 0;
}

status add_indexed_file(sll **head, sll **tail, char *filename)
{
    if(strlen(filename) >= sizeof(((sll *)0)->name))
        return e_failure;

    if(is_file_indexed(*head, filename))
        return e_success;

    sll *newNode = malloc(sizeof(sll));

    if(newNode == NULL)
        return e_failure;

    strcpy(newNode->name, filename);
    newNode->link = NULL;

    if(*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        (*tail)->link = newNode;
        *tail = newNode;
    }

    return e_success;
}

status validate_database_file(FILE *fp)
{
    char line[1000];
    int found = 0;

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        found = 1;

        if(line[0] != '#')
            return e_failure;

        line[strcspn(line, "\n")] = '\0';

        int len = strlen(line);

        if(len < 2 || line[len - 1] != '#')
            return e_failure;
    }

    if(!found)
        return e_failure;

    rewind(fp);

    return e_success;
}

status update_database(hash arr[], sll **indexed_head, sll **indexed_tail)
{
    char filename[100];

    printf("Enter the backup file name: \n");
    scanf("%99s", filename);

    char *ptr = strrchr(filename, '.');

    if(ptr == NULL || strcmp(ptr, ".txt") != 0)
    {
        printf("ERROR : Backup file must have .txt extension\n");
        return e_failure;
    }

    // Open backup file
    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("ERROR : Unable to open the file\n");
        return e_failure;
    }

    if(validate_database_file(fp) == e_failure)
    {
        printf("ERROR : Invalid Database file\n");
        fclose(fp);
        return e_failure;
    }

    // Check whether database is already loaded
    for(int i = 0; i < 27; i++)
    {
        if(arr[i].link != NULL)
        {
            printf("ERROR : Database already contains data\n");
            fclose(fp);
            return e_failure;
        }
    }

    if(*indexed_head != NULL || *indexed_tail != NULL)
    {
        printf("ERROR : Indexed file list is not empty\n");
        fclose(fp);
        return e_failure;
    }

    char line[1000];

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        int len = strlen(line);

        if(len < 2 || line[0] != '#' || line[len - 1] != '#')
        {
            fclose(fp);
            return e_failure;
        }

        // Remove first and last '#'
        memmove(line, line + 1, len);
        line[len - 2] = '\0';

        // Extract bucket index
        char *token = strtok(line, ";");

        if(token == NULL)
        {
            fclose(fp);
            return e_failure;
        }

        int index = 0;
        int i = 0;

        while(token[i] != '\0')
        {
            if(token[i] < '0' || token[i] > '9')
            {
                fclose(fp);
                return e_failure;
            }

            index = index * 10 + (token[i] - '0');
            i++;
        }

        if(index < 0 || index >= 27)
        {
            fclose(fp);
            return e_failure;
        }

        // Extract word
        token = strtok(NULL, ";");

        if(token == NULL || *token == '\0')
        {
            fclose(fp);
            return e_failure;
        }

        if(strlen(token) >= sizeof(((main_node *)0)->word))
        {
            fclose(fp);
            return e_failure;
        }

        main_node *newMain = malloc(sizeof(main_node));

        if(newMain == NULL)
        {
            fclose(fp);
            return e_failure;
        }

        strcpy(newMain->word, token);

        // Extract file count
        token = strtok(NULL, ";");

        if(token == NULL || *token == '\0')
        {
            free(newMain);
            fclose(fp);
            return e_failure;
        }

        int file_count = 0;
        i = 0;

        while(token[i] != '\0')
        {
            if(token[i] < '0' || token[i] > '9')
            {
                free(newMain);
                fclose(fp);
                return e_failure;
            }

            file_count = file_count * 10 + (token[i] - '0');
            i++;
        }

        if(file_count <= 0 || file_count > 100000)
        {
            free(newMain);
            fclose(fp);
            return e_failure;
        }

        newMain->file_count = file_count;
        newMain->sublink = NULL;
        newMain->mainlink = NULL;

        sub *subTail = NULL;

        // Restore subnodes
        for(int i = 0; i < file_count; i++)
        {
            char *file = strtok(NULL, ";");
            char *count = strtok(NULL, ";");

            if(file == NULL || count == NULL || *file == '\0')
            {
                fclose(fp);
                return e_failure;
            }

            if(strlen(file) >= sizeof(((sub *)0)->filename))
            {
                fclose(fp);
                return e_failure;
            }

            int word_count = 0;
            int j = 0;

            while(count[j] != '\0')
            {
                if(count[j] < '0' || count[j] > '9')
                {
                    fclose(fp);
                    return e_failure;
                }

                word_count = word_count * 10 + (count[j] - '0');
                j++;
            }

            if(word_count <= 0)
            {
                fclose(fp);
                return e_failure;
            }

            sub *newSub = malloc(sizeof(sub));

            if(newSub == NULL)
            {
                fclose(fp);
                return e_failure;
            }

            strcpy(newSub->filename, file);
            newSub->wordcount = word_count;
            newSub->link = NULL;

            // Link subnode
            if(newMain->sublink == NULL)
            {
                newMain->sublink = newSub;
                subTail = newSub;
            }
            else
            {
                subTail->link = newSub;
                subTail = newSub;
            }

            // Rebuild indexed filename list
            if(add_indexed_file(indexed_head, indexed_tail, file) == e_failure)
            {
                fclose(fp);
                return e_failure;
            }
        }

        // Check for extra fields
        if(strtok(NULL, ";") != NULL)
        {
            fclose(fp);
            return e_failure;
        }

        // Insert main node into hash table
        if(arr[index].link == NULL)
        {
            arr[index].link = newMain;
        }
        else
        {
            main_node *temp = arr[index].link;

            while(temp->mainlink != NULL)
            {
                temp = temp->mainlink;
            }

            temp->mainlink = newMain;
        }
    }

    fclose(fp);

    printf("INFO : Database Restored Successfully\n");

    return e_success;
}
