# Polynomial-LinkedList-Operations
Advanced C implementations of linked lists for polynomial operations, sorted sets, and large number representation
Module: Data Structures
Series No. 3: Linked Lists (continued)

Exercise 1:

For this exercise, we will use the linked list developed in the course.
Let L be a polynomial in a single variable, which can be represented by a linked list whose nodes are monomials (as shown below: P(X)=10+14*X^2+6∗x^9+4∗x^11)

First

mono1
degree=0;
coef=10;

mono2
degree=3;
coef=14;

mono3
degree=9;
coef=6;

mono4
Degree=11;
coef=4;

NULL

Given the following declarations:
struct monomial_data {
    int degree;
    float coef;
};

struct monomial_node {
    struct monomial_data D;
    struct monomial_node *next;
};

typedef struct monomial_data DM;
typedef struct monomial_node* mon;

Write a function to evaluate a polynomial at a point x, for example P(0)=10;

Write a function to compute fog(x)=f(g(x)), where f and g are two polynomials, and x is a given real number.

Write a function to multiply a polynomial by a scalar λ (multiplication of the list by λ).

Write a function to copy a polynomial A. It should return a copy of A.

Write a function to simplify a polynomial A by replacing all monomials with the same degree by a single monomial that is their sum.

Write a function to sort a polynomial A in ascending order of the degrees of the monomials (assuming A is simplified).

Write a function to return a list DeriveDuPoly, which is the derivative of the polynomial A.
Write a function to return a list DeriveDuPolyOrderN, which is the nth-order derivative of the polynomial A.

Write a function to add two polynomials A and B.

Write a function to multiply a polynomial A by another polynomial B.

Exercise 2:

In this exercise, we propose to represent finite sets of strictly positive integers sorted in ascending order by linked lists defined in C as follows:
typedef struct set {
    int number; // a strictly positive integer element of the set
    struct set *next; // the address of the next element
} setList;
Terminology: We will call "Set List at address p" a linked list of elements of type setList (defined above) with the following properties:

The first element is at address p.

The last element has NULL in its next field.

For any element at address el in the linked list, such that (el->next != NULL), we have (0 < el->number < ((el->next)->number)) (list sorted in ascending order of numbers).

Example: The set {3,7,10,36} will be represented by the Set List at address p as follows:
p
|
number: 3
next
|
number: 7
next
|
number: 10
next
|
number: 36
NULL
Given the following global declaration:
setList *p;
We assume that elements have been defined and inserted into the "Set List at address p" (p is declared above).

Task:

Write a function with the header:
void insert(int val)
that inserts an element of type setList into the "Set List at address p" in its correct position so that the list remains sorted in ascending order. This element has the value val (function parameter) in its number field. Additionally, we assume that: (val > p->number) (see remark and example).

Remark:

If the parameter val is the value of the number field of an element that already exists in the list, no element will be inserted.

Example: Let the "Set List at address p" be as follows:
p -> 2 -> 3 -> 5 -> 7 -> 9 -> 12 -> 98 -> NULL
After calling the function insert(8), the "Set List at address p" becomes:
p -> 2 -> 3 -> 5 -> 7 -> 8 -> 9 -> 12 -> 98 -> NULL
Exercise 3:

Representation of Large Numbers by Linked Lists

In this exercise, we will use linked lists to represent large positive integers or zero.

To optimize the representation of a number, we propose to decompose it into several parts. Each part can contain 4 digits
Let N be a positive integer or zero with NC digits N=Cnc−1Cnc−2...C1C0  where C0 is the units digit, C1 is the tens digit, etc. Then N will be decomposed as follows:
N = C_{NC-1}C_{NC-2}C_{NC-3}C_{NC-4} C_{NC-5}C_{NC-6}C_{NC-7}C_{NC-8} ... ...C_1C_0
1st part        2nd part        ...        last part
Example: The number 
N=8002590300407896420003 can be decomposed as follows:
N = 8002    5903      0040      7896     4200       03
1st part  2nd part  3rd part  4th part  5th part  6th part
To represent a number by decomposing it in this way, we will use a linked list of type NumberList defined in C as follows:
typedef struct List {
    short int part;
    struct List *next; // address of the next element
} NumberList;
Each part of the number is an element of the linked list containing the value of the part and the address of the next part. The number N=Cnc−1Cnc−2...C1C0
will be represented by a list of type NumberList as follows:
p -> C_{NC-1}C_{NC-2}C_{NC-3}C_{NC-4} -> C_{NC-5}C_{NC-6}C_{NC-7}C_{NC-8} -> ... -> C_1C_0 -> NULL
Where p is the address of the first element of the list.

Since the part field is declared as type short int, non-significant zeros (on the left) will not appear in the value of the part (see example).
Example: The number 8002590300407896420003 can be decomposed as follows:
N =    802       903       40       7896      4200       3
    1st part  2nd part  3rd part  4th part  5th part  6th part
and will be represented by a list of type NumberList as follows:
p -> 802 -> 903 -> 40 -> 7896 -> 4200 -> 3 -> NULL
Creating a Linked List of Parts of a Number

Let a positive integer or zero be defined by a DigitString S (containing only digit characters: '0','1','2',...,'9'). We propose to represent it by a linked list of type NumberList. To do this:

Write a function with the prototype:
NumberList *groupDigits(char *S);
that creates a new linked list of type NumberList to represent the number defined by the DigitString S (as a parameter). This function returns the address of the first element of the created list.

Example: Let the number 330104660000027 be represented by the DigitString S="330104660000027".

The call to the function groupDigits(S) will return the address of the first element p of the created list as follows:

p -> 3301 -> 466 -> 0 -> 27 -> NULL
Plan

EX1: Representation of a polynomial in a single variable by a linked list whose nodes are monomials.

EX2: Representation of finite sets of strictly positive integers sorted in ascending order by linked lists.

EX3: Representation of large numbers by linked lists
