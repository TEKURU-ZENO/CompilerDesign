#include <stdio.h>
#include <string.h>

int main()
{
    char prod[100];
    char a1[100], a2[100];
    char common[100] = "";
    char rem1[100] = "";
    char rem2[100] = "";
    char start;

    printf("Enter production (Example: A->ab|ac): ");
    scanf("%s", prod);

    start = prod[0];

    int i, j = 0;

    /* Extract first production */
    for(i = 3; prod[i] != '|'; i++)
        a1[j++] = prod[i];
    a1[j] = '\0';

    /* Extract second production */
    i++;  // skip '|'
    j = 0;
    while(prod[i] != '\0')
        a2[j++] = prod[i++];
    a2[j] = '\0';

    /* Find common prefix */
    i = 0;
    while(a1[i] == a2[i] && a1[i] != '\0')
    {
        common[i] = a1[i];
        i++;
    }
    common[i] = '\0';

    /* Remaining parts */
    strcpy(rem1, a1 + i);
    strcpy(rem2, a2 + i);

    if(strlen(common) > 0)
    {
        printf("\nAfter Left Factoring:\n");
        printf("%c->%s%c'\n", start, common, start);
        printf("%c'->%s|%s\n", start, rem1, rem2);
    }
    else
    {
        printf("\nNo Left Factoring Required.\n");
    }

    return 0;
}
