
#include "main.h"

status search_database(hash arr[], char word[])
{
    int index;

    if(word[0] >= 'a' && word[0] <= 'z')
    {
        index = word[0] - 'a';
    }
    else if(word[0] >= 'A' && word[0] <= 'Z')
    {
        index = word[0] - 'A';
    }
    else
    {
        index = 26;
    }

    main_node *temp = arr[index].link;

    if(temp != NULL)
    {
        while(temp != NULL)
        {
            if(strcmp(temp->word, word) == 0)
            {
                printf("Word %s is present in %d files\n",
                       word, temp->file_count);

                sub *temp1 = temp->sublink;

                while(temp1 != NULL)
                {
                    printf("In %s : %d times\n",
                           temp1->filename, temp1->wordcount);

                    temp1 = temp1->link;
                }

                return e_success;
            }

            temp = temp->mainlink;
        }
    }

    return e_datanotfound;
}
