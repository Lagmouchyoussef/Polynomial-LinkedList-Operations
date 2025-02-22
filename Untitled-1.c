#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct monomial_data {
    int degree;
    float coef;
};

struct monomial_node {
    struct monomial_data D;
    struct monomial_node *next;
};

typedef struct monomial_data MD;
typedef struct monomial_node* poly;

float evaluatePolynomial(poly L, float x) {
    float result = 0.0;
    while (L != NULL) {
        result += L->D.coef * pow(x, L->D.degree);
        L = L->next;
    }
    return result;
}

float composePolynomials(poly f, poly g, float x) {
    float g_x = evaluatePolynomial(g, x);
    return evaluatePolynomial(f, g_x);
}

void multiplyByScalar(poly L, float A) {
    while (L != NULL) {
        L->D.coef *= A;
        L = L->next;
    }
}

poly copyPolynomial(poly A) {
    poly new_poly = NULL, last = NULL;
    while (A != NULL) {
        poly temp = (poly)malloc(sizeof(struct monomial_node));
        temp->D = A->D;
        temp->next = NULL;
        if (new_poly == NULL) {
            new_poly = temp;
        } else {
            last->next = temp;
        }
        last = temp;
        A = A->next;
    }
    return new_poly;
}

poly simplifyPolynomial(poly A) {
    poly current = A;
    while (current != NULL && current->next != NULL) {
        if (current->D.degree == current->next->D.degree) {
            current->D.coef += current->next->D.coef;
            poly temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return A;
}

poly sortPolynomial(poly A) {
    if (A == NULL || A->next == NULL) return A;
    poly sorted = NULL;
    while (A != NULL) {
        poly current = A;
        A = A->next;
        if (sorted == NULL || current->D.degree < sorted->D.degree) {
            current->next = sorted;
            sorted = current;
        } else {
            poly temp = sorted;
            while (temp->next != NULL && temp->next->D.degree < current->D.degree) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    return sorted;
}

poly differentiatePolynomial(poly A) {
    poly current = A;
    poly prev = NULL;
    while (current != NULL) {
        if (current->D.degree == 0) {
            if (prev == NULL) {
                A = current->next;
                free(current);
                current = A;
            } else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            current->D.coef *= current->D.degree;
            current->D.degree--;
            prev = current;
            current = current->next;
        }
    }
    return A;
}

poly differentiatePolynomialOrderN(poly A, int n) {
    for (int i = 0; i < n; i++) {
        A = differentiatePolynomial(A);
    }
    return A;
}

poly addPolynomials(poly A, poly B) {
    poly result = NULL, last = NULL;
    while (A != NULL && B != NULL) {
        poly temp = (poly)malloc(sizeof(struct monomial_node));
        if (A->D.degree < B->D.degree) {
            temp->D = A->D;
            A = A->next;
        } else if (A->D.degree > B->D.degree) {
            temp->D = B->D;
            B = B->next;
        } else {
            temp->D.degree = A->D.degree;
            temp->D.coef = A->D.coef + B->D.coef;
            A = A->next;
            B = B->next;
        }
        temp->next = NULL;
        if (result == NULL) {
            result = temp;
        } else {
            last->next = temp;
        }
        last = temp;
    }
    while (A != NULL) {
        poly temp = (poly)malloc(sizeof(struct monomial_node));
        temp->D = A->D;
        temp->next = NULL;
        if (result == NULL) {
            result = temp;
        } else {
            last->next = temp;
        }
        last = temp;
        A = A->next;
    }
    while (B != NULL) {
        poly temp = (poly)malloc(sizeof(struct monomial_node));
        temp->D = B->D;
        temp->next = NULL;
        if (result == NULL) {
            result = temp;
        } else {
            last->next = temp;
        }
        last = temp;
        B = B->next;
    }
    return result;
}

poly multiplyPolynomials(poly A, poly B) {
    poly result = NULL;
    while (A != NULL) {
        poly tempB = B;
        while (tempB != NULL) {
            poly temp = (poly)malloc(sizeof(struct monomial_node));
            temp->D.degree = A->D.degree + tempB->D.degree;
            temp->D.coef = A->D.coef * tempB->D.coef;
            temp->next = NULL;
            result = addPolynomials(result, temp);
            tempB = tempB->next;
        }
        A = A->next;
    }
    return result;
}

int main() {
    
    poly A = (poly)malloc(sizeof(struct monomial_node));
    A->D.degree = 2;
    A->D.coef = 3.0;
    A->next = (poly)malloc(sizeof(struct monomial_node));
    A->next->D.degree = 0;
    A->next->D.coef = 4.0;
    A->next->next = NULL;

    poly B = (poly)malloc(sizeof(struct monomial_node));
    B->D.degree = 1;
    B->D.coef = 2.0;
    B->next = (poly)malloc(sizeof(struct monomial_node));
    B->next->D.degree = 0;
    B->next->D.coef = 1.0;
    B->next->next = NULL;

    printf("Polynomial A: ");
    poly temp = A;
    while (temp != NULL) {
        printf("%0.1fx^%d ", temp->D.coef, temp->D.degree);
        temp = temp->next;
    }
    printf("\n");

    printf("Polynomial B: ");
    temp = B;
    while (temp != NULL) {
        printf("%0.1fx^%d ", temp->D.coef, temp->D.degree);
        temp = temp->next;
    }
    printf("\n");

    poly result = multiplyPolynomials(A, B);

    printf("Result of A * B: ");
    temp = result;
    while (temp != NULL) {
        printf("%0.1fx^%d ", temp->D.coef, temp->D.degree);
        temp = temp->next;
    }
    printf("\n");

    while (A != NULL) {
        temp = A;
        A = A->next;
        free(temp);
    }
    while (B != NULL) {
        temp = B;
        B = B->next;
        free(temp);
    }
    while (result != NULL) {
        temp = result;
        result = result->next;
        free(temp);
    }

    return 0;
}