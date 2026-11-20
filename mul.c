#include "apc.h"

/* Perform multiplication of two linked-list operands */
int multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    /* Preserve the original tail of the first operand */
    node *original_tail1 = tail1;

    /* Declare multiplication calculation variables */
    int carry, pro, digit;

    /* Initialize the positional zero counter */
    int zero_count = 0;

    /* Process each digit of the second operand */
    while (tail2 != NULL)
    {

        /* Initialize partial product and temporary result lists */
        node *headP = NULL, *tailP = NULL;
        node *headTemp = NULL, *tailTemp = NULL;

        /* Reset carry for the current partial product */
        carry = 0;

        /* Reset the first operand pointer */
        tail1 = original_tail1;

        /* Multiply corresponding digits of both operands */
        while (tail1 != NULL)
        {
            /* Calculate the product including carry */
            pro = (tail1->data * tail2->data) + carry;

            /* Extract the current product digit */
            digit = pro % 10;

            /* Calculate carry for the next position */
            carry = pro / 10;

            /*Insert the product digit into the partial result */
            if (insert_first(&headP, &tailP, digit) == FAILURE)
            {
                /* Free the partial product if insertion fails */
                delete_list(&headP, &tailP);
                return FAILURE;
            }

            /* Move to the previous digit of the first operand */
            tail1 = tail1->prev;
        }

        /* Check whether a final carry remains */
        if (carry)
        {
            /* Insert the remaining carry into the partial product */
            if (insert_first(&headP, &tailP, carry) == FAILURE)
            {
                /* Free the partial product if carry insertion fails */
                delete_list(&headP, &tailP);
                return FAILURE;
            }
        }

        /* Append zeros according to the digit position */
        for (int i = 0; i < zero_count; i++)
        {
            /* Insert a positional zero into the partial product */
            if (insert_last(&headP, &tailP, 0) == FAILURE)
            {
                /* Free the partial product if zero insertion fails */
                delete_list(&headP, &tailP);
                return FAILURE;
            }
        }

        /* Check whether this is the first partial product */
        if (*headR == NULL)
        {
            /* Assign the first partial product as the result */
            *headR = headP;
            *tailR = tailP;
        }

        /* Add the current partial product to the result */
        else
        {
            /* Handle failure during partial product addition */
            if (addition(*tailR, tailP, &headTemp, &tailTemp) == FAILURE)
            {
                /* Free the previous result and partial product */
                delete_list(headR, tailR);
                delete_list(&headP, &tailP);
                delete_list(&headTemp, &tailTemp);
                return FAILURE;
            }

            /* Free the previous result and partial product */
            delete_list(headR, tailR);
            delete_list(&headP, &tailP);

            /* Store the newly calculated result */
            *headR = headTemp;
            *tailR = tailTemp;

            /* Reset temporary result pointers */
            headTemp = NULL;
            tailTemp = NULL;
        }

        /* Increase the positional zero count */
        zero_count++;

        /* Move to the previous digit of the second operand */
        tail2 = tail2->prev;
    }

    return SUCCESS;
}
