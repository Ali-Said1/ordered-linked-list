#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

void printvalues(node *list);
void freememory(node *list);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Usage: /orderedlist [values]\n");
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        if (!atoi(argv[i]) && argv[i][0] != '0')
        {
            printf("The arguments shall only be numbers\n");
            return 2;
        }
    }
    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Can't add more values\n");
            if (list != NULL)
            {
                printf("Maintained valuse: ");
                printvalues(list);
                freememory(list);
            }
            else
            {
                printf("No values added to the list\n");
            }
            return 3;
        }
        n->number = atoi(argv[i]);
        n->next = NULL;
        // Check if the list is empty
        if (list == NULL)
        {
            list = n;
        }
        // Check if the number is less than the first element in the list
        else if (n->number < list->number)
        {
            node *tmp = list;
            list = n;
            n->next = tmp;
        }
        else
        {
            // loop inside of the list
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // if the current pointer isn't pointing to NULL and the number is less than the next number in the list
                if (ptr->next != NULL && n->number < ptr->next->number)
                {
                    node *tmp = ptr->next; // Create a temp pointer
                    ptr->next = n; // set the current pointer to point to the current node
                    n->next = tmp;  // set the current node to point to the next node in list
                    break;
                }
                // if the current pointer is the last pointer
                else if (ptr->next == NULL)
                {
                    ptr->next = n; // add the current node to the end of the list
                    break;
                }
            }
        }
    }
    printvalues(list);
    freememory(list);
    return 0;
}

void printvalues(node *list)
{
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i ", ptr->number);
    }
    printf("\n");
}

void freememory(node *list)
{
    node *ptr = list;
    while (ptr != NULL)
    {
        node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}