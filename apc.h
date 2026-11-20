#ifndef APC_H
#define APC_H

/* Include required standard library headers */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Define operation status and validation codes */
#define SUCCESS 0
#define FAILURE -1
#define INVALID_OP1 -2
#define INVALID_OP2 -3
#define INVALID_OP -4
#define INVALID_COUNT -5

/* Define operand comparison results */
#define SAME 0
#define OPERAND1 1
#define OPERAND2 2

/* Define terminal text colors */
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[1;92m"
#define YELLOW "\033[0;33m"
#define GRAY "\033[0;90m"
#define MAGENTA "\033[0;35m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[1;37m"
#define ORANGE "\033[38;5;202m"
#define BRIGHT_GREEN "\033[0;32m"

/* Define the doubly linked list node structure */
typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} node;

/* Declare addition operation function */
int addition(node *tail1, node *tail2, node **headR, node **tailR);

/* Declare subtraction function */
int subtraction(node *tail1, node *tail2, node **headR, node **tailR);

/* Declare multiplication function */
int multiplication(node *tail1, node *tail2, node **headR, node **tailR);

/* Declare division function */
int division(node *head1, node *head2, node *tail2, node **headR, node **tailR, node **headRem, node **tailRem);

/* Declare command-line argument validation function */
int cla_validation(int argc, char *argv[]);

/* Declare operand-to-list conversion function */
int create_list(char *opr, node **head, node **tail);

/* Declare insertion at the beginning of the list */
int insert_first(node **head, node **tail, int data);

/* Declare insertion at the end of the list */
int insert_last(node **head, node **tail, int data);

/* Declare linked-list deletion function */
int delete_list(node **head, node **tail);

/* Declare linked-list display function */
void print_list(node *head);

/* Declare numerical result display function */
void print_result(node *head);

/* Declare operand comparison function */
int compare_list(node *head1, node *head2);

/* Declare linked-list length function */
int list_len(node *head);

/* Declare leading-zero removal function */
void remove_pre_zeros(node **head);

#endif