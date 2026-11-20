#include "apc.h"

/* Perform division of two linked-list operands */
int division(node *head1, node *head2, node *tail2, node **headR, node **tailR, node **headRem, node **tailRem)
{
    /* Declare quotient digit and comparison variables */
    int count, cmp;

    /* Check whether the divisor is zero */
    if (head2 == NULL || (head2->data == 0 && head2->next == NULL))
    {
        printf(RED "Error: Division by zero is not allowed\n" RESET);
        return FAILURE;
    }

    /* Initialize pointer to the dividend */
    node *temp1 = head1;

    /* To store quotient */
    node *headq = NULL, *tailq = NULL;

    /* To store remainder */
    node *headr = NULL, *tailr = NULL;

    /* To store remainder  temp*/
    node *temphead = NULL, *temptail = NULL;

    /* Process each digit of the dividend */
    while (temp1 != NULL)
    {
        /* Reset the quotient digit count */
        count = 0;

        /* Append the next dividend digit to the remainder */
        if (insert_last(&headr, &tailr, temp1->data) == FAILURE)
        {
            /* Handle memory allocation failure */
            delete_list(&headq, &tailq);
            delete_list(&headr, &tailr);
            return FAILURE;
        }

        /* Remove leading zeros from the remainder */
        remove_pre_zeros(&headr);

        /* Compare the remainder with the divisor */
        cmp = compare_list(headr, head2);

        /* Subtract while the remainder is at least the divisor */
        while (cmp == OPERAND1 || cmp == SAME)
        {
            /* Calculate the next remainder */
            if (subtraction(tailr, tail2, &temphead, &temptail) == FAILURE)
            {
                /* Free all allocated lists before returning */
                delete_list(&headq, &tailq);
                delete_list(&headr, &tailr);
                delete_list(&temphead, &temptail);
                return FAILURE;
            }

            /*  Free remainder */
            delete_list(&headr, &tailr);

            /* Replace the old remainder with the new remainder */
            headr = temphead;
            tailr = temptail;

            /* Reset temporary list pointers */
            temphead = NULL;
            temptail = NULL;

            /* Remove leading zeros from the updated remainder */
            remove_pre_zeros(&headr);

            /* Increment the quotient digit count */
            count++;

            /* Compare the updated remainder with the divisor */
            cmp = compare_list(headr, head2);
        }

        /* Append the quotient digit */
        if (insert_last(&headq, &tailq, count) == FAILURE)
        {
            /*  Free quotient and remainder lists before returning */
            delete_list(&headq, &tailq);
            delete_list(&headr, &tailr);
            return FAILURE;
        }

        /* Move to the next dividend digit */
        temp1 = temp1->next;
    }

    /* Remove leading zeros from quotient and remainder */
    remove_pre_zeros(&headq);
    remove_pre_zeros(&headr);

    /* update headR and tailR with headq and tailq */
    *headR = headq;
    *tailR = tailq;

    /* updating reminder */
    *headRem = headr;
    *tailRem = tailr;

    return SUCCESS;
}
