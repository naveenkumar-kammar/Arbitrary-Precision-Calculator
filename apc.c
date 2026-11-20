#include "apc.h"

// Function definitions

/* Validate command-line arguments */
int cla_validation(int argc, char *argv[])
{
    /* Initialize the digit index */
    int i = 0;

    /* Check the number of arguments */
    if (argc != 4)
    {
        return INVALID_COUNT;
    }

    /* Check whether the operator contains exactly one character */
    if (argv[2][0] == '\0' || argv[2][1] != '\0')
    {
        return INVALID_OP;
    }

    /* Check whether the operator is supported */
    if (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != '*' && argv[2][0] != 'x' && argv[2][0] != 'X' && argv[2][0] != '/')
    {
        return INVALID_OP;
    }

    /* Check whether the first operand is empty */
    if (argv[1][0] == '\0')
    {
        return INVALID_OP1;
    }

    /* Reset the digit index */
    i = 0;

    /* Skip the optional sign */
    if (argv[1][0] == '+' || argv[1][0] == '-')
    {
        i = 1;
    }

    /* Check whether the first operand contains digits */
    if (argv[1][i] == '\0')
    {
        return INVALID_OP1;
    }

    /* Validate each digit of the first operand */
    for (; argv[1][i] != '\0'; i++)
    {
        /* Reject non-numeric characters */
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            return INVALID_OP1;
        }
    }

    /* Check whether the second operand is empty */
    if (argv[3][0] == '\0')
    {
        return INVALID_OP2;
    }

    /* Reset the digit index */
    i = 0;

    /* Skip the optional sign */
    if (argv[3][0] == '+' || argv[3][0] == '-')
    {
        i = 1;
    }

    /* Check whether the second operand contains digits */
    if (argv[3][i] == '\0')
    {
        return INVALID_OP2;
    }

    /* Validate each digit of the second operand */
    for (; argv[3][i] != '\0'; i++)
    {
        /* Reject non-numeric characters */
        if (argv[3][i] < '0' || argv[3][i] > '9')
        {
            return INVALID_OP2;
        }
    }

    return SUCCESS;
}

/* Create a linked list from the operand string */
int create_list(char *opr, node **head, node **tail)
{
    /* Declare digit and index variables */
    int i, data;

    /* Traverse each character of the operand */
    for (i = 0; opr[i] != '\0'; i++)
    {
        /* Convert the character into an integer digit */
        data = opr[i] - '0';

        /* Append the digit to the linked list */
        if (insert_last(head, tail, data) == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

/* Insert a node at the beginning of the list */
int insert_first(node **head, node **tail, int data)
{
    /* Allocate memory for a new node */
    node *new = malloc(sizeof(node));

    /* Check memory allocation */
    if (new == NULL)
    {
        return FAILURE;
    }

    /* Initialize the new node links and data */
    new->data = data;
    new->prev = NULL;
    new->next = *head;

    /* Check whether the list is empty */
    if (*head == NULL)
    {
        /* Set the new node as both head and tail */
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        /* Link the new node before the current head */
        (*head)->prev = new;

        /* Update the head pointer */
        *head = new;

        return SUCCESS;
    }
}

/* Insert a node at the end of the list */
int insert_last(node **head, node **tail, int data)
{
    /* Allocate memory for a new node */
    node *new = malloc(sizeof(node));

    /* Check memory allocation */
    if (new == NULL)
    {
        return FAILURE;
    }

    /* Initialize the new node links and data */
    new->data = data;
    new->prev = *tail;
    new->next = NULL;

    /* Check whether the list is empty */
    if (*head == NULL)
    {
        /* Set the new node as both head and tail */
        *head = new;
        *tail = new;

        return SUCCESS;
    }
    else
    {
        /* Link the new node after the current tail */
        (*tail)->next = new;

        /* Update the tail pointer */
        *tail = new;

        return SUCCESS;
    }
}

/* Delete all nodes from the linked list */
int delete_list(node **head, node **tail)
{
    /* Check whether the list is empty */
    if (*head == NULL)
    {
        return FAILURE;
    }

    /* Start deletion from the head node */
    node *temp = *head;

    /* Traverse the list until all nodes are freed */
    while (temp != NULL)
    {
        /* Move the head to the next node */
        *head = (*head)->next;

        /* Free the current node */
        free(temp);

        /* Update the temporary pointer */
        temp = *head;
    }

    /* Reset the tail pointer */
    *tail = NULL;

    return SUCCESS;
}

/* Display the linked list */
void print_list(node *head)
{
    /* Checking the list is empty or not */
    if (head == NULL)
    {
        printf(ORANGE "Info: The list is empty\n" RESET);
    }
    else
    {
        printf(WHITE "HEAD -> " RESET);
        while (head)
        {
            /* Printing the list */
            printf(WHITE "%d" RESET, head->data);

            /* Traversing in forward direction */
            head = head->next;
            if (head)
            {
                printf(WHITE " <-> " RESET);
            }
        }
        printf(WHITE " <- TAIL\n" RESET);
    }
}

/* Print the numerical result */
void print_result(node *head)
{
    /* Checking the list is empty or not */
    if (head == NULL)
    {
        printf(ORANGE "Info: The list is empty\n" RESET);
    }
    else
    {
        while (head)
        {
            /* Printing the list */
            printf(BRIGHT_GREEN "%d" RESET, head->data);

            /* Traversing in forward direction */
            head = head->next;
        }
    }
    printf("\n");
}

/* Compare two linked-list operands */
int compare_list(node *head1, node *head2)
{
    /* Create temporary pointers for comparison */
    node *temp1 = head1;
    node *temp2 = head2;

    /* Initialize operand length counters */
    int count1 = 0, count2 = 0;

    /* Calculate the first operand length */
    count1 = list_len(temp1);

    /* Calculate the second operand length */
    count2 = list_len(temp2);

    /* Compare operand lengths */
    if (count1 > count2)
    {
        return OPERAND1;
    }

    /* Check whether the second operand is longer */
    else if (count2 > count1)
    {
        return OPERAND2;
    }

    /* Compare digits when operand lengths are equal */
    else
    {
        /* Compare corresponding digits */
        while (temp1 != NULL && temp2 != NULL)
        {
            /* Check whether the first operand digit is larger */
            if (temp1->data > temp2->data)
            {
                return OPERAND1;
            }

            /* Check whether the second operand digit is larger */
            else if (temp2->data > temp1->data)
            {
                return OPERAND2;
            }

            /* Continue comparison when digits are equal */
            else
            {
                /* Move both pointers to the next nodes */
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
        }

        return SAME;
    }
}

/* Calculate the linked-list length */
int list_len(node *head)
{
    /* Initialize the node counter */
    int count = 0;

    /* Traverse the linked list */
    while (head != NULL)
    {
        /* Increment the node count */
        count++;

        /* Move to the next node */
        head = head->next;
    }

    return count;
}

/* Remove leading zeros from the linked list */
void remove_pre_zeros(node **head)
{
    /* Check whether list is empty */
    if (*head == NULL)
    {
        return;
    }

    /* Initialize the temporary pointer */
    node *temp = *head;

    /* Continue while leading zeros remain */
    while (temp->data == 0 && temp->next != NULL)
    {
        /* Update the head to the next node */
        *head = temp->next;

        /* Reset the previous link of the new head */
        (*head)->prev = NULL;

        /* Free the removed leading-zero node */
        free(temp);

        /* Update the temporary pointer */
        temp = *head;
    }
}