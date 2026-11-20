#include "apc.h"

/* Perform addition of two linked-list operands */
int addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    /* Initialize sum and carry variables */
    int sum, carry = 0;

    /* Process digits until both operands and carry are exhausted */
    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        /* Start the current sum with the carry */
        sum = carry;

        /* Check whether digits remain in the first operand */
        if (tail1 != NULL)
        {
            /* Add the current digit of the first operand */
            sum = sum + tail1->data;

            /* Move to the previous digit of the first operand */
            tail1 = tail1->prev;
        }

        /* Check whether digits remain in the second operand */
        if (tail2 != NULL)
        {
            /* Add the current digit of the second operand */
            sum = sum + tail2->data;

            /* Move to the previous digit of the second operand */
            tail2 = tail2->prev;
        }

        /* Calculate the carry for the next position */
        carry = sum / 10;

        /* Extract the current result digit */
        sum = sum % 10;

        /* Insert the result digit at the beginning of the result list */
        if (insert_first(headR, tailR, sum) == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}
