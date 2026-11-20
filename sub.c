#include "apc.h"

/* Perform subtraction of two linked-list operands */
int subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    /* Initialize difference and borrow variables */
    int diff, borrow = 0;

    /* Process digits until both operands are exhausted */
    while (tail1 != NULL || tail2 != NULL)
    {
        /* Start the current difference with the borrow */
        diff = borrow;

        /* Check whether digits remain in the first operand */
        if (tail1 != NULL)
        {
            /* Subtract the borrow from the first operand digit */
            diff = tail1->data - diff;

            /* Move to the previous digit of the first operand */
            tail1 = tail1->prev;
        }

        /* Check whether digits remain in the second operand */
        if (tail2 != NULL)
        {
            /* Subtract the second operand digit */
            diff = diff - tail2->data;

            /* Move to the previous digit of the second operand */
            tail2 = tail2->prev;
        }

        /* Check whether borrowing is required */
        if (diff < 0)
        {
            /* Adjust the difference by adding 10 */
            diff = diff + 10;

            /* Set borrow for the next digit position */
            borrow = 1;
        }

        /* Handle subtraction without a borrow */
        else
        {
            /* Reset the borrow value */
            borrow = 0;
        }

        /* Insert the difference digit into the result list */
        if (insert_first(headR, tailR, diff) == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}
