
#include "main.h"

status save_database(hash arr[], char *filename)
{
    FILE *fp = fopen(filename, "w");

    if(fp == NULL)
    {
        return e_failure;
    }

    int found = 0;

    for(int i = 0; i < 27; i++)
    {
        if(arr[i].link != NULL)
        {
            main_node *temp_mainNode = arr[i].link;

            while(temp_mainNode != NULL)
            {
                found = 1;

                // Save main node contents
                fprintf(fp, "#%d;%s;%d;", i,
                        temp_mainNode->word,
                        temp_mainNode->file_count);

                sub *temp_subNode = temp_mainNode->sublink;

                while(temp_subNode != NULL)
                {
                    // Save sub node contents
                    fprintf(fp, "%s;%d;",
                            temp_subNode->filename,
                            temp_subNode->wordcount);

                    temp_subNode = temp_subNode->link;
                }

                fprintf(fp, "#\n");

                temp_mainNode = temp_mainNode->mainlink;
            }
        }
    }

    fclose(fp);

    if(!found)
    {
        return e_failure;
    }

    return e_success;
}
