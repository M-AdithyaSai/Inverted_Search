
#include "main.h"

status create_database(sll *head, hash arr[])
{
    while(head != NULL)
    {
        char fname[20];
        strcpy(fname, head->name);

        FILE *fptr = fopen(fname, "r");

        if(fptr == NULL)
        {
            return e_failure;
        }

        char word[25];

        // Read every word from the file
        while(fscanf(fptr, "%24s", word) == 1)
        {
            int i;

            // Find the hash index
            if(word[0] >= 'a' && word[0] <= 'z')
            {
                i = word[0] - 'a';
            }
            else if(word[0] >= 'A' && word[0] <= 'Z')
            {
                i = word[0] - 'A';
            }
            else
            {
                i = 26;
            }

            main_node *main = arr[i].link;
            main_node *prev = NULL;

            // Search for existing word
            while(main != NULL)
            {
                if(strcmp(main->word, word) == 0)
                {
                    break;
                }

                prev = main;
                main = main->mainlink;
            }

            // Word already exists
            if(main != NULL)
            {
                sub *subnode = main->sublink;
                sub *sub_prev = NULL;

                // Search for existing filename
                while(subnode != NULL)
                {
                    if(strcmp(subnode->filename, fname) == 0)
                    {
                        break;
                    }

                    sub_prev = subnode;
                    subnode = subnode->link;
                }

                // Same word in same file
                if(subnode != NULL)
                {
                    subnode->wordcount++;
                }
                // Same word in different file
                else
                {
                    sub *newSub = malloc(sizeof(sub));

                    if(newSub == NULL)
                    {
                        fclose(fptr);
                        return e_failure;
                    }

                    strcpy(newSub->filename, fname);
                    newSub->wordcount = 1;
                    newSub->link = NULL;

                    if(sub_prev == NULL)
                    {
                        main->sublink = newSub;
                    }
                    else
                    {
                        sub_prev->link = newSub;
                    }

                    main->file_count++;
                }
            }

            // Word does not exist
            else
            {
                // Create main node
                main_node *newMain = malloc(sizeof(main_node));

                if(newMain == NULL)
                {
                    fclose(fptr);
                    return e_failure;
                }

                strcpy(newMain->word, word);
                newMain->file_count = 1;
                newMain->mainlink = NULL;
                newMain->sublink = NULL;

                // Create sub node
                sub *newSub = malloc(sizeof(sub));

                if(newSub == NULL)
                {
                    free(newMain);
                    fclose(fptr);
                    return e_failure;
                }

                strcpy(newSub->filename, fname);
                newSub->wordcount = 1;
                newSub->link = NULL;

                newMain->sublink = newSub;

                // Link main node
                if(prev == NULL)
                {
                    arr[i].link = newMain;
                }
                else
                {
                    prev->mainlink = newMain;
                }
            }
        }

        fclose(fptr);

        head = head->link;
    }

    return e_success;
}
