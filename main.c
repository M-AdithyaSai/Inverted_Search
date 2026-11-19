/*
Description : 
Name            : M ADITHYA SAI
Roll No         : 26012_15
Project title   : Inverted Search
Start date      : 31/10/2026
End date        : 7/11/2026

========== Inverted Search Menu ==========
1. Create DataBase
2. Display DataBase
3. Update DataBase
4. Search a Word in DataBase
5. Save DataBase
6. Exit
==========================================
Enter your choice: 1 
Enter number of files you want to add into database: 5
Enter the file names:
f1.txt f2.txt f3.txt empty.txt f1.txt
f1.txt inserted successfully
f2.txt inserted successfully
f3.txt inserted successfully

ERROR: File empty.txt is empty
Unable to insert empty.txt

INFO: File f1.txt is a duplicate file
Unable to insert f1.txt

Database created successfully

*/


#include "main.h"

hash arr[27];

int main()
{
    sll *head = NULL;
    sll *tail = NULL;

    // Initialize hash table
    for(int i = 0; i < 27; i++)
    {
        arr[i].index = i;
        arr[i].link = NULL;
    }

    int choice = 0;

    do
    {
        printf("\n========== Inverted Search Menu ==========\n");
        printf("1. Create DataBase\n");
        printf("2. Display DataBase\n");
        printf("3. Update DataBase\n");
        printf("4. Search a Word in DataBase\n");
        printf("5. Save DataBase\n");
        printf("6. Exit\n");
        printf("==========================================\n");
        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1)
        {
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF);

            printf("\nPlease enter a valid input\n");
            continue;
        }

        switch(choice)
        {
            // Create Database
            case 1:
            {
                int n = 0;
                int exists = 0;

                for(int i = 0; i < 27; i++)
                {
                    if(arr[i].link != NULL)
                    {
                        exists = 1;
                        break;
                    }
                }

                if(exists)
                {
                    printf("Database already exists\n");
                    break;
                }

                printf("Enter number of files you want to add into database: ");
                if(scanf("%d", &n) != 1)
                {
                    printf("Invalid input\n");
                    break;
                }

                if(n <= 0 || n > 100)
                {
                    printf("Invalid number of files\n");
                    break;
                }

                char filenames[100][30];

                printf("Enter the file names:\n");

                for(int i = 0; i < n; i++)
                {
                    scanf("%29s", filenames[i]);
                }

                for(int i = 0; i < n; i++)
                {
                    if(insert_at_last(filenames[i], &head) == e_success)
                    {
                        printf("%s inserted successfully\n", filenames[i]);
                    }
                    else
                    {
                        printf("Unable to insert %s\n", filenames[i]);
                    }
                }

                // Find tail of filename list
                tail = head;

                while(tail != NULL && tail->link != NULL)
                {
                    tail = tail->link;
                }

                // Create database
                if(create_database(head, arr) == e_success)
                {
                    printf("\nDatabase created successfully\n");
                }
                else
                {
                    printf("\nDatabase creation failed\n");
                }

                break;
            }

            // Display Database
            case 2:
            {
                if(display_database(arr) == e_success)
                {
                    printf("\nDatabase displayed successfully\n");
                }
                else
                {
                    printf("\nDatabase is empty\n");
                }

                break;
            }

            // Update Database
            case 3:
            {
                if(update_database(arr, &head, &tail) == e_success)
                {
                    printf("Database updated successfully\n");
                }
                else
                {
                    printf("Database update failed\n");
                }

                break;
            }

            // Search a Word
            case 4:
            {
                char word[25];

                printf("Enter the word to search: ");
                scanf("%24s", word);

                if(search_database(arr, word) == e_success)
                {
                    printf("\nWord found successfully\n");
                }
                else
                {
                    printf("\nWord not found in database\n");
                }

                break;
            }

            // Save Database
            case 5:
            {
                char filename[100];

                printf("Enter the backup file name: ");
                scanf("%99s", filename);

                if(save_database(arr, filename) == e_success)
                {
                    printf("Database saved successfully\n");
                }
                else
                {
                    printf("Database saving failed\n");
                }

                break;
            }

            // Exit
            case 6:
            {
                printf("Exiting Successfully...\n");
                break;
            }

            default:
            {
                printf("\nInvalid choice. Please try again.\n");
                break;
            }
        }

    } while(choice != 6);

    return 0;
}
