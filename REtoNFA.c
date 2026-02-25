#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ret[100];
int pos = 0;
int sc = 0;

void nfa(int st, int p, char* s)
{
    int sp, fs[15], fsc = 0;

    sp = st;
    pos = p;
    sc = st;

    while(*s != '\0')
    {
        if(isalpha(*s))
        {
            ret[pos++] = sp;
            ret[pos++] = *s;
            ret[pos++] = ++sc;
            sp = sc;
        }

        else if(*s == '.')
        {
            ret[pos++] = sc;
            ret[pos++] = 'e';   // epsilon
            ret[pos++] = ++sc;
            sp = sc;
        }

        else if(*s == '+')
        {
            sp = st;
            fs[fsc++] = sc;
        }

        else if(*s == '*')
        {
            ret[pos++] = sc;
            ret[pos++] = 'e';
            ret[pos++] = sp;

            ret[pos++] = sp;
            ret[pos++] = 'e';
            ret[pos++] = sc;
        }

        else if(*s == '(')
        {
            char ps[50];
            int i = 0, flag = 1;

            s++;
            while(flag != 0)
            {
                ps[i++] = *s;

                if(*s == '(')
                    flag++;

                if(*s == ')')
                    flag--;

                s++;
            }

            ps[--i] = '\0';
            nfa(sc, pos, ps);
            s--;
        }

        s++;
    }

    sc++;
}

int main()
{
    int i;
    char inp[100];

    printf("\nEnter the regular expression: ");
    fgets(inp, sizeof(inp), stdin);

    // Remove newline if present
    inp[strcspn(inp, "\n")] = '\0';

    nfa(1, 0, inp);

    printf("\nState   Input   State\n");

    for(i = 0; i < pos; i += 3)
    {
        printf("%d  -->  %c  -->  %d\n", ret[i], ret[i+1], ret[i+2]);
    }

    return 0;
}
