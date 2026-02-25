#include <stdio.h>
#include <string.h>

int main()
{
    char prod[100];
    char alpha[100] = "";
    char beta[100] = "";
    char newprod1[100] = "";
    char newprod2[100] = "";
    char start;

    printf("Enter production (Example: E->E+T|T): ");
    scanf("%s", prod);

    start = prod[0];   // Start symbol

    int size = strlen(prod);
    int pipePos = -1;

    /* Find position of '|' */
    for(int i = 0; i < size; i++)
    {
        if(prod[i] == '|')
        {
            pipePos = i;
            break;
        }
    }

    /* Check for immediate left recursion */
    if(prod[3] == start)
    {
        int c = 0;

        /* Extract alpha (after E->E) */
        for(int i = 4; i < pipePos; i++)
            alpha[c++] = prod[i];
        alpha[c] = '\0';

        c = 0;

        /* Extract beta (after |) */
        for(int i = pipePos + 1; i < size; i++)
            beta[c++] = prod[i];
        beta[c] = '\0';

        /* Construct new productions */

        sprintf(newprod1, "%c->%s%c'", start, beta, start);
        sprintf(newprod2, "%c'->%s%c'|e", start, alpha, start);

        printf("\nAfter Removing Left Recursion:\n");
        printf("%s\n", newprod1);
        printf("%s\n", newprod2);
    }
    else
    {
        printf("\nNo Immediate Left Recursion Found.\n");
    }

    return 0;
}
