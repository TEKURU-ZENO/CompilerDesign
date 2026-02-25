#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int iskeyword(char buf[])
{
    char keyword[11][10] = {
        "int", "float", "for", "while", "if",
        "else", "do", "double", "return",
        "void", "main"
    };

    for(int i = 0; i < 11; i++)
    {
        if(strcmp(keyword[i], buf) == 0)
            return 1;
    }
    return 0;
}

int main()
{
    char op[] = {'+', '-', '=', '*', '/', '%', '&'};
    char pun[] = {',', ';', '!'};
    char ch, buf[50], name[100];
    FILE *fp;
    int i, j = 0;

    printf("Enter file name: ");
    scanf("%s", name);

    fp = fopen(name, "r");

    if(fp == NULL)
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    while((ch = fgetc(fp)) != EOF)
    {
        /* Check operators */
        for(i = 0; i < 7; i++)
        {
            if(ch == op[i])
                printf("\n%c : Operator", ch);
        }

        /* Check punctuation */
        for(i = 0; i < 3; i++)
        {
            if(ch == pun[i])
                printf("\n%c : Punctuation", ch);
        }

        /* Build word */
        if(isalnum(ch))
        {
            if(j < 49)   // prevent overflow
                buf[j++] = ch;
        }
        else
        {
            if(j != 0)
            {
                buf[j] = '\0';
                j = 0;

                if(iskeyword(buf))
                    printf("\n%s : Keyword", buf);
                else if(isdigit(buf[0]))
                    printf("\n%s : Digit", buf);
                else
                    printf("\n%s : Identifier", buf);
            }
        }
    }

    /* Check if last word exists */
    if(j != 0)
    {
        buf[j] = '\0';

        if(iskeyword(buf))
            printf("\n%s : Keyword", buf);
        else if(isdigit(buf[0]))
            printf("\n%s : Digit", buf);
        else
            printf("\n%s : Identifier", buf);
    }

    fclose(fp);
    return 0;
}
