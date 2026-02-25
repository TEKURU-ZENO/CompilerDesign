#include <stdio.h>
#include <string.h>

char nfa[20][20];
char input[20];
char dstates[20][20];
char eclos[20];
char stack[20];
char dstack[20][20];

int ns, in = 0;
int top = 0, topd = 0;
int e = 0, nos = 0;

/* Convert char digit to int */
int ctoi(char a) {
    return a - '0';
}

/* Convert int to char digit */
char itoc(int a) {
    return a + '0';
}

/* Push to stack */
void push(char a) {
    stack[top++] = a;
}

/* Pop from stack */
char pop() {
    return stack[--top];
}

/* Push DFA state */
void pushd(char *a) {
    strcpy(dstack[topd++], a);
}

/* Pop DFA state */
char* popd() {
    return dstack[--topd];
}

/* Check if input symbol already exists */
int check(char a) {
    for(int i = 0; i < in; i++)
        if(input[i] == a)
            return i;
    return -1;
}

/* Check if state already in eclosure */
int checke(char a) {
    for(int i = 0; i < e; i++)
        if(eclos[i] == a)
            return 1;
    return 0;
}

/* Epsilon Closure */
char* eclosure(char *a) {
    int i, j;
    char c;

    e = 0;
    top = 0;
    strcpy(eclos, a);
    e = strlen(a);

    for(i = 0; i < strlen(a); i++)
        push(a[i]);

    while(top != 0) {
        c = pop();

        for(j = 0; j < ns; j++) {
            if(nfa[ctoi(c)][j] == 'e') {
                if(!checke(itoc(j))) {
                    eclos[e++] = itoc(j);
                    push(itoc(j));
                }
            }
        }
    }

    eclos[e] = '\0';
    return eclos;
}

int main() {
    int i, j, k, count;
    char a[20], b[20], ec[20], start[2];

    printf("Enter number of states: ");
    scanf("%d", &ns);

    printf("\nEnter NFA Transition Table (use '-' for no move, 'e' for epsilon)\n");

    for(i = 0; i < ns; i++) {
        for(j = 0; j < ns; j++) {
            printf("Move [%d][%d]: ", i, j);
            scanf(" %c", &nfa[i][j]);

            if(nfa[i][j] != '-' && nfa[i][j] != 'e') {
                if(check(nfa[i][j]) == -1)
                    input[in++] = nfa[i][j];
            }
        }
    }

    /* Initial state */
    start[0] = itoc(0);
    start[1] = '\0';

    pushd(eclosure(start));
    strcpy(dstates[nos++], eclosure(start));

    printf("\nDFA Transition Table:\n");

    printf("State");
    for(i = 0; i < in; i++)
        printf("\t%c", input[i]);
    printf("\n");

    while(topd > 0) {
        strcpy(a, popd());
        printf("%s", a);

        for(i = 0; i < in; i++) {
            int len = 0;

            for(j = 0; j < strlen(a); j++) {
                int x = ctoi(a[j]);

                for(k = 0; k < ns; k++) {
                    if(nfa[x][k] == input[i])
                        ec[len++] = itoc(k);
                }
            }

            ec[len] = '\0';
            strcpy(b, eclosure(ec));

            count = 0;
            for(j = 0; j < nos; j++) {
                if(strcmp(dstates[j], b) == 0)
                    count++;
            }

            if(count == 0 && b[0] != '\0') {
                pushd(b);
                strcpy(dstates[nos++], b);
            }

            printf("\t%s", b);
        }
        printf("\n");
    }

    return 0;
}
