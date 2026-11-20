/*
Documentation

Name        : Naveenkumar Kammar
Student id  : 26018_039
Batch id    : 26018D
Start Date  : 12/11/2026
End date    : 22/11/2026

Description: The following main functions are implemented in the Arbitrary Precision Calculator(APC) project to perform arithmetic operations on large numbers beyond the standard data type limits.

main()              :-> Handles command line arguments and selects the required arithmetic operation such as addition, subtraction, multiplication or division.
                     -> Validates the input operands and operator, identifies the signs of operands and calls the appropriate arithmetic function.
                     -> Displays the final result and handles the operation status.

addition()          :-> Performs addition of two large numbers using linked lists.
                     -> Adds corresponding digits from right to left while handling carry values.

subtraction()       :-> Performs subtraction of two large numbers using linked lists.
                     -> Subtracts corresponding digits while handling borrow values and maintains the correct sign of the result.

multiplication()    :-> Performs multiplication of two large numbers using linked lists.
                     -> Multiplies individual digits and handles carry values to generate the final product.

division()          :-> Performs division of two large numbers using the long division method.
                     -> Calculates the quotient and remainder while handling division by zero.

insert_first()      :-> Inserts a new digit at the beginning of the linked list.
                     -> Used to construct the result by storing digits in the required order.

insert_last()       :-> Inserts a new digit at the end of the linked list.
                     -> Used to build linked lists containing input numbers and intermediate results.

delete_list()       :-> Deletes all nodes from the linked list.
                     -> Frees the dynamically allocated memory used by the linked list.

print_list()        :-> Traverses and displays the digits stored in the linked list.

compare_lists()     :-> Compares two linked lists representing numbers.
                     -> Determines whether the first number is greater than, smaller than or equal to the second number.

remove_pre_zeros()  :-> Removes unnecessary leading zeros from a linked list.
                     -> Maintains the correct representation of the number.

cla_validation()    :-> Validates the command line arguments.
                     -> Checks the number of arguments and verifies whether the given arithmetic operator is valid.

*/

/*
Sample input:
$ ./a.out 12345678901234567890 + 98765432109876543210

Sample output:
+==================================================+
|          ARBITRARY PRECISION CALCULATOR          |
+==================================================+

+----------------- Input Details -------------------
| Operand 1 : 12345678901234567890
| Operator  : +
| Operand 2 : 98765432109876543210
+---------------------------------------------------

+--------------------------------------------------+
| Command-line arguments validated successfully    |
+--------------------------------------------------+

| HEAD -> 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6 <-> 7 <-> 8 <-> 9 <-> 0 <-> 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6 <-> 7 <-> 8 <-> 9 <-> 0 <- TAIL
| HEAD -> 9 <-> 8 <-> 7 <-> 6 <-> 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> 0 <-> 9 <-> 8 <-> 7 <-> 6 <-> 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> 0 <- TAIL

+=============== CALCULATION RESULT ================
| Sum of Two Operands : 111111111011111111100
+===================================================

Calculation completed successfully

✨✨✨   THANK YOU!   ✨✨✨

*/





#include "apc.h"

/* Main function */
int main(int argc, char *argv[])
{
    /* Initialize operand and result signs */
    int sign1 = 1;
    int sign2 = 1, sub_sign2;
    int result_sign = 1;
    int status, cmp;

    /* Declare operand string pointers */
    char *op1;
    char *op2;

    /* Print project title */
    printf(CYAN "\n+==================================================+\n" RESET);
    printf(BLUE "|          ARBITRARY PRECISION CALCULATOR          |\n" RESET);
    printf(CYAN "+==================================================+\n" RESET);

    /* Initialize all linked-list pointers */
    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;
    node *headR = NULL, *tailR = NULL;
    node *headRem = NULL, *tailRem = NULL;

    /* Display command-line inputs */
    if (argc == 4)
    {
        printf(MAGENTA "\n+----------------- Input Details -------------------\n" RESET);
        printf(GRAY "| Operand 1 : %s\n" RESET, argv[1]);
        printf(YELLOW "| Operator  : %s\n" RESET, argv[2]);
        printf(GRAY "| Operand 2 : %s\n" RESET, argv[3]);
        printf(MAGENTA "+---------------------------------------------------\n" RESET);
    }

    printf(MAGENTA "\n+--------------------------------------------------+\n" RESET);

    /* Validate command line arguments */
    status = cla_validation(argc, argv);

    /* Handle invalid argument count */
    if (status == INVALID_COUNT)
    {
        printf(RED "| Error: Invalid command-line arguments            |\n" RESET);
        printf(ORANGE "| Usage: ./a.out <operand1> <operator> <operand2>  |\n" RESET);
        printf(MAGENTA "+--------------------------------------------------+\n\n" RESET);
        return FAILURE;
    }

    /* Handle invalid operator */
    else if (status == INVALID_OP)
    {
        printf(RED "| Error: Invalid command-line arguments            |\n" RESET);
        printf(ORANGE "| Invalid operator                                 |\n" RESET);
        printf(ORANGE "| Supported operators are +, -, *, x, X, and /     |\n" RESET);
        printf(MAGENTA "+--------------------------------------------------+\n\n" RESET);
        return FAILURE;
    }

    /* Handle invalid first operand */
    else if (status == INVALID_OP1)
    {
        printf(RED "| Error: Invalid command-line arguments            |\n" RESET);
        printf(ORANGE "| The first operand must be a valid integer        |\n" RESET);
        printf(MAGENTA "+--------------------------------------------------+\n\n" RESET);
        return FAILURE;
    }

    /* Handle invalid second operand */
    else if (status == INVALID_OP2)
    {
        printf(RED "| Error: Invalid command-line arguments            |\n" RESET);
        printf(ORANGE "| The second operand must be a valid integer       |\n" RESET);
        printf(MAGENTA "+--------------------------------------------------+\n\n" RESET);
        return FAILURE;
    }

    /* Continue with valid arguments */
    else
    {
        printf(GREEN "| Command-line arguments validated successfully    |\n" RESET);
        printf(MAGENTA "+--------------------------------------------------+\n\n" RESET);

        /* Store operand strings */
        op1 = argv[1];
        op2 = argv[3];

        /* Read the selected operator */
        char oper = argv[2][0];

        /* Identify the sign of the first operand */
        if (op1[0] == '-')
        {
            sign1 = -1;
        }

        /* Remove the sign from the first operand */
        if (op1[0] == '+' || op1[0] == '-')
        {
            op1++;
        }

        /* Identify the sign of the second operand */
        if (op2[0] == '-')
        {
            sign2 = -1;
        }

        /* Remove the sign from the second operand */
        if (op2[0] == '+' || op2[0] == '-')
        {
            op2++;
        }

        /* Create list of operand1 */
        if (create_list(op1, &head1, &tail1) == FAILURE)
        {
            printf(RED "Error: Memory allocation failed\n" RESET);

            /* Free allocated memory */
            delete_list(&head1, &tail1);
            return FAILURE;
        }

        /* Create list of operand2 */
        if (create_list(op2, &head2, &tail2) == FAILURE)
        {
            printf(RED "Error: Memory allocation failed\n" RESET);

            /* Free allocated memory */
            delete_list(&head1, &tail1);
            delete_list(&head2, &tail2);
            return FAILURE;
        }

        /* Print list of operand1 */
        printf(WHITE "| " RESET);
        print_list(head1);

        /* Print list of operand2 */
        printf(WHITE "| " RESET);
        print_list(head2);

        /* Remove pre zeros of operand1*/
        remove_pre_zeros(&head1);

        /* Remove pre zeros of operand2*/
        remove_pre_zeros(&head2);

        printf(PURPLE "\n+=============== CALCULATION RESULT ================\n" RESET);
        switch (oper)
        {
            /* Handle addition operation */
            case '+':

                /* Check whether both operands have the same sign */
                if (sign1 == sign2)
                {
                    /* Add operands with the same sign */
                    if (addition(tail1, tail2, &headR, &tailR) == FAILURE)
                    {
                        printf(RED "Error: Addition operation failed\n" RESET);
                        status = FAILURE;
                        break;
                    }

                    /* Assign the common operand sign to the result */
                    result_sign = sign1;
                }

                /* Handle operands with different signs */
                else
                {
                    /* Compare the absolute values of operands */
                    cmp = compare_list(head1, head2);

                    /* Handle equal operands */
                    if (cmp == SAME)
                    {
                        /* Create zero result node */
                        if (insert_first(&headR, &tailR, 0) == FAILURE)
                        {
                            printf(RED "Error: Memory allocation failed\n" RESET);
                            status = FAILURE;
                            break;
                        }

                        /* Set result sign to positive */
                        result_sign = 1;
                    }

                    /* Handle the case where the first operand is larger */
                    else if (cmp == OPERAND1)
                    {
                        /* Subtract the second operand from the first */
                        if (subtraction(tail1, tail2, &headR, &tailR) == FAILURE)
                        {
                            printf(RED "Error: Subtraction operation failed\n" RESET);
                            status = FAILURE;
                            break;
                        }

                        /* Assign the first operand sign to the result */
                        result_sign = sign1;
                    }

                    /* Handle the case where the second operand is larger */
                    else if (cmp == OPERAND2)
                    {
                        /* Subtract the first operand from the second */
                        if (subtraction(tail2, tail1, &headR, &tailR) == FAILURE)
                        {
                            printf(RED "Error: Subtraction operation failed\n" RESET);
                            status = FAILURE;
                            break;
                        }

                        /* Assign the second operand sign to the result */
                        result_sign = sign2;
                    }
                }

                /* Check whether result creation failed */
                if (headR == NULL)
                {
                    printf(RED "Error: Memory allocation failed\n" RESET);
                    status = FAILURE;
                    break;
                }

                printf(BRIGHT_GREEN "| Sum of Two Operands : " RESET);

                /* Remove pre zeros of Result */
                remove_pre_zeros(&headR);

                /* Check whether the result is zero */
                if (headR != NULL && headR->data == 0 && headR->next == NULL)
                {
                    /* Keep zero result positive */
                    result_sign = 1;
                }

                /* Print the negative sign when required */
                if (result_sign == -1)
                {
                    printf(BRIGHT_GREEN "-" RESET);
                }

                /* Display the calculated result */
                print_result(headR);

                break;

            /* Handle subtraction operation */
            case '-':

                /* Reverse the second operand sign for subtraction */
                sub_sign2 = -sign2;

                /* Check whether effective operand signs match */
                if (sign1 == sub_sign2)
                {
                    /* Add operands when their effective signs match */
                    if (addition(tail1, tail2, &headR, &tailR) == FAILURE)
                    {
                        printf(RED "Error: Addition operation failed\n" RESET);
                        status = FAILURE;
                        break;
                    }

                    /* Assign the first operand sign to the result */
                    result_sign = sign1;
                }

                /* Handle operands with different effective signs */
                else
                {
                    /* Compare the absolute values of operands */
                    cmp = compare_list(head1, head2);

                    /* Handle equal operands */
                    if (cmp == SAME)
                    {
                        /* Create zero result node */
                        if (insert_first(&headR, &tailR, 0) == FAILURE)
                        {
                            printf(RED "Error: Memory allocation failed\n" RESET);
                            status = FAILURE;
                            break;
                        }

                        /* Set result sign to positive */
                        result_sign = 1;
                    }

                    /* Handle the case where the first operand is larger */
                    else if (cmp == OPERAND1)
                    {
                        /* Subtract the second operand from the first */
                        if (subtraction(tail1, tail2, &headR, &tailR) == FAILURE)
                        {
                            printf(RED "Error: Subtraction operation failed\n" RESET);
                            status = FAILURE;
                            break;
                        }

                        /* Assign the first operand sign to the result */
                        result_sign = sign1;
                    }

                    /* Handle the case where the second operand is larger */
                    else if (cmp == OPERAND2)
                    {
                        /* Subtract the first operand from the second */
                        if (subtraction(tail2, tail1, &headR, &tailR) == FAILURE)
                        {
                            printf(RED "Error: Subtraction operation failed\n" RESET);
                            status = FAILURE;
                            break;
                        }

                        /* Assign the effective second operand sign to the result */
                        result_sign = sub_sign2;
                    }
                }

                /* Check whether result creation failed */
                if (headR == NULL)
                {
                    printf(RED "Error: Memory allocation failed\n" RESET);
                    status = FAILURE;
                    break;
                }

                printf(BRIGHT_GREEN "| Difference of Two Operands : " RESET);

                /* Remove pre zeros of Result */
                remove_pre_zeros(&headR);

                /* Check whether the result is zero */
                if (headR != NULL && headR->data == 0 && headR->next == NULL)
                {
                    /* Keep zero result positive */
                    result_sign = 1;
                }

                /* Print the negative sign when required */
                if (result_sign == -1)
                {
                    printf(BRIGHT_GREEN "-" RESET);
                }

                /* Display the calculated result */
                print_result(headR);

                break;

            /* Handle multiplication operation */
            case 'x':
            case 'X':
            case '*':

                /* Calculate the multiplication result sign */
                result_sign = sign1 * sign2;

                /* Multiply the two operands */
                if (multiplication(tail1, tail2, &headR, &tailR) == FAILURE)
                {
                    printf(RED "Error: Multiplication operation failed\n" RESET);
                    status = FAILURE;
                    break;
                }

                /* Check whether result creation failed */
                if (headR == NULL)
                {
                    printf(RED "Error: Memory allocation failed\n" RESET);
                    status = FAILURE;
                    break;
                }

                printf(BRIGHT_GREEN "| Product of Two Operands : " RESET);

                /* Remove pre zeros of Result */
                remove_pre_zeros(&headR);

                /* Check whether the result is zero */
                if (headR != NULL && headR->data == 0 && headR->next == NULL)
                {
                    /* Keep zero result positive */
                    result_sign = 1;
                }

                /* Print the negative sign when required */
                if (result_sign == -1)
                {
                    printf(BRIGHT_GREEN "-" RESET);
                }

                /* Display the calculated result */
                print_result(headR);

                break;

            /* Handle division operation */
            case '/':

                /* Calculate the quotient sign */
                result_sign = sign1 * sign2;

                /* Perform division and calculate the remainder */
                if (division(head1, head2, tail2, &headR, &tailR, &headRem, &tailRem) == FAILURE)
                {
                    status = FAILURE;
                    break;
                }

                printf(BRIGHT_GREEN "| Quotient : " RESET);

                /* Print the negative quotient sign when required */
                if (result_sign == -1 && !(headR->data == 0 && headR->next == NULL))
                {
                    printf(BRIGHT_GREEN "-" RESET);
                }

                /* Display the quotient */
                print_result(headR);

                printf(BRIGHT_GREEN "| Remainder : " RESET);

                /* Remainder sign follows first operand */
                if (sign1 == -1 && !(headRem->data == 0 && headRem->next == NULL))
                {
                    printf(BRIGHT_GREEN "-" RESET);
                }
                print_result(headRem);

                break;

            /* Handle unsupported operators */
            default:
                printf(RED "Error: Unsupported operator\n" RESET);
                status = FAILURE;
                break;
        }
    }
    printf(PURPLE "+===================================================\n\n" RESET);
    if (status == SUCCESS)
    {
        printf(GREEN "\rCalculation completed successfully\n\n" RESET);
    }
    else
    {
        printf(RED "\rCalculation failed\n\n" RESET);
    }
    printf(BLUE "\r✨✨✨   THANK YOU!   ✨✨✨\n\n" RESET);

    /* Release all allocated linked lists */
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);
    delete_list(&headRem, &tailRem);

    return status;
}