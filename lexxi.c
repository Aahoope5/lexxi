#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int isKeyword(char buffy[])
{
    int i;
    int f = 0;
    const char keywords[32][9] = {{"program"}, {"end"}, {"bool"}, {"int"}, {"if"}, {"then"}, {"else"}, {"fi"}, {"while"}, {"do"}, {"od"}, {"print"}, {":"}, {";"}, {":="}, {"<"}, {"=<"}, {"="}, {"!="}, {">"}, {"+"}, {"-"}, {"or"}, {"*"}, {"/"}, {"and"}, {"("}, {")"}, {"-"}, {"not"}, {"fasle"}, {"true"}};

    for (i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffy) == 0)
        {
            f = 1;
        }
    }
    return f;
}

char check_next(FILE *const fp, char *next, char *ch)
{
    char innext;
    char inch;

    fseek(fp, -0L, SEEK_CUR);
    *next = getc(fp);
    innext = *next;
    fseek(fp, -1L, SEEK_CUR);
    fseek(fp, -0L, SEEK_CUR);

    return innext;
}

void lex_on_em(FILE *fpI)
{
    return;
}

int main()
{

    FILE *fpI;
    FILE *fpO;

    char c, n;

    char buffy[10];

    int i, j = 0;
    int line = 1;
    int position = 1;
    char kind[2][4] = {{"ID"}, {"NUM"}};

    char *in = "ex/nonsense.txt";
    // char *in = "ex/euclid.txt";
    char *out = "lexemeTable.txt";

    fpI = fopen(in, "rb+");

    fpO = fopen(out, "a+");
    c = fgetc(fpI);

    const char ws[4] = {0x09, 0x0A, 0x0D, 0x0F};

    while (c != EOF)

    {

        if (c == '/' && check_next(fpI, &n, &c) == '/')
        {
            while (c != '\n')
            {
                c = fgetc(fpI);
            }
        }

         if (c == ':' && check_next(fpI, &n, &c) == '=')
        {
            buffy[0] = c;
            buffy[1] = fgetc(fpI);
            buffy[2] = '\0';
            j = 0;

            if (isKeyword(buffy) == 1)
            {
                printf("line %d position %d:  kind: %s Value: %s \n", line, position - strlen(buffy), kind[1], buffy);
            c = fgetc(fpI);
            }

        }

        if (c == '!' && (check_next(fpI, &n, &c) == '='))
        {
            buffy[0] = c;
            buffy[1] = fgetc(fpI);
            buffy[2] = '\0';
            j = 0;

            if (isKeyword(buffy) == 1)
            {
                printf("line %d position %d:  kind: %s Value: %s \n", line, position - strlen(buffy), kind[1], buffy);
             
            }
        }













        if (isalpha(c))
        {
            buffy[j++] = c;
        }
        else if ((isblank(c) || c == '\n' || c == ':' || c == '(' || c == ';' || c == ')' || c == '=' || c == '+' || c == '_') && (j != 0))
        {
            buffy[j] = '\0';
            j = 0;

            if (isKeyword(buffy) == 1)
            {
                printf("line %d position %d: kind: %s \n", line, position - strlen(buffy), buffy);
                memset(buffy, 0, strlen(buffy));
            }
            else if (isdigit(buffy[0]))
            {
                printf("line %d position %d:  kind: %s Value: %s \n", line, position - strlen(buffy), kind[1], buffy);
                memset(buffy, 0, strlen(buffy));
            }
            else if (isalpha(buffy[0]))
            {
                printf("line %d position %d:  kind: %s Value: %s \n", line, position - strlen(buffy), kind[0], buffy);

                memset(buffy, 0, strlen(buffy));
            }
            else if (!isblank(c) && !isalnum(c) && !isdigit(c) && !isalpha(c))
            {
                if (isKeyword(buffy) == 0)
                {
                    printf("Not recognized! line %d: position %d:   %s \n", buffy);

                    memset(buffy, 0, strlen(buffy));
                }
            }
        }

        if (ispunct(c))
        {
            buffy[j++] = c;
        }

        if (isdigit(c))
        {
            buffy[j++] = c;
        }

        // lines and position

        if (c == ws[1])

        {
            line++;
            position = 1;
        }

        if (c != ws[1])

        {

            position++;
        }

        c = fgetc(fpI);
    }

    printf("EOF");
    fclose(fpI);
    fclose(fpO);

    return 0;
}
