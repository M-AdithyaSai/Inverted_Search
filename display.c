
#include "main.h"

status display_database(hash arr[])
{
    int found = 0;

    for(int i = 0; i < 27; i++)
    {
        if(arr[i].link != NULL)
        {
            main_node *temp_mainNode = arr[i].link;

            while(temp_mainNode != NULL)
            {
                found = 1;

                // Print main node contents
                printf("[%d] ", i);
                printf("%s %d", temp_mainNode->word,
                       temp_mainNode->file_count);

                sub *temp_subNode = temp_mainNode->sublink;

                while(temp_subNode != NULL)
                {
                    // Print sub node contents
                    printf(" %s %d", temp_subNode->filename,
                           temp_subNode->wordcount);

                    temp_subNode = temp_subNode->link;
                }

                printf("\n");

                temp_mainNode = temp_mainNode->mainlink;
            }
        }
    }

    if(!found)
    {
        return e_emptylist;
    }

    return e_success;
}
