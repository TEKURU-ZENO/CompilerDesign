#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m = 0;
char a[10][20], f[20];

void first(char c);
void follow(char c);

/* Compute FIRST */
void first(char c)
{
    if(!isupper(c))
    {
        f[m++] = c;
        return;
    }

    for(int k = 0; k < n; k++)
    {
        if(a[k][0] == c)
        {
            if(a[k][2] == '$')     // epsilon
                f[m++] = '$';
            else if(!isupper(a[k][2]))
                f[m++] = a[k][2];
            else
                first(a[k][2]);
        }
    }
}

/* Compute FOLLOW */
void follow(char c)
{
    if(a[0][0] == c)   // Start symbol
        f[m++] = '$';

    for(int i = 0; i < n; i++)
    {
        for(int j = 2; j < strlen(a[i]); j++)
        {
            if(a[i][j] == c)
            {
                if(a[i][j+1] != '\0')
                    first(a[i][j+1]);

                if(a[i][j+1] == '\0' && c != a[i][0])
                    follow(a[i][0]);
            }
        }
    }
}

int main()
{
    int z;
    char c;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (Example: E=TR):\n");
    for(int i = 0; i < n; i++)
        scanf("%s", a[i]);

    do {
        m = 0;
        printf("\nEnter symbol to find FIRST & FOLLOW: ");
        scanf(" %c", &c);

        /* FIRST */
        first(c);
        printf("FIRST(%c) = { ", c);
        for(int i = 0; i < m; i++)
            printf("%c ", f[i]);
        printf("}\n");

        /* FOLLOW */
        m = 0;
        follow(c);
        printf("FOLLOW(%c) = { ", c);
        for(int i = 0; i < m; i++)
            printf("%c ", f[i]);
        printf("}\n");

        printf("\nContinue? (1/0): ");
        scanf("%d", &z);

    } while(z == 1);

    return 0;
}
