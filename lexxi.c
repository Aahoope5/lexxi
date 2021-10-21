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

// check comments
int iscommie(char buffy[])
{
    int i;
    int f = 0;

    for (i = 0; i < 2; ++i)
    {
        if (buffy[i] == '/' && buffy[i + 1] == '/')
        {
            f = 1;
        }
    }
    return f;
}

void lex_on_em(FILE *fp)
{

    const char ws[4] = {0x09, 0x0A, 0x0D, 0x0F};

    char c, n, buffy[9];
    char out_buffy[11];
    int i, j = 0, line = 1, position = 1;

    char kind[2][4] = {{"ID"}, {"NUM"}};
    FILE *fpO;
    char *out = "lexemeTable.txt";

    fpO = fopen(out, "a+");
    c = fgetc(fp);

    while (c != EOF)
    {
        // check comments
        if (c == '/' && check_next(fp, &n, &c) == '/')
        {
            while (c != '\n')
            {
                c = fgetc(fp);
            }
        }

        if (c == ':' && check_next(fp, &n, &c) == '=')
        {
            buffy[0] = c;
            buffy[1] = fgetc(fp);
            buffy[2] = '\0';
            j = 0;
            position++;
            if (isKeyword(buffy) == 1)
            {

                printf("%d:%d:%s\n", line, position - strlen(buffy), buffy);

                c = fgetc(fp);
                position++;
            }
        }
        // check speciall combo
        if (c == '!' && (check_next(fp, &n, &c) == '='))
        {
            buffy[0] = c;
            buffy[1] = fgetc(fp);
            buffy[2] = '\0';
            j = 0;
            position++;
            if (isKeyword(buffy) == 1)
            {
                printf("%d:%d:%s\n", line, position - strlen(buffy), buffy);
                c = fgetc(fp);
                position++;
            }
        }
        // check speciall combo
        if (c == '>' && (check_next(fp, &n, &c) == '='))
        {
            buffy[0] = c;
            buffy[1] = fgetc(fp);
            buffy[2] = '\0';
            j = 0;
            position++;
            if (isKeyword(buffy) == 1)
            {
                printf("%d:%d:%s\n", line, position - strlen(buffy), buffy);
                c = fgetc(fp);
                position++;
            }
        }
        // check speciall combo
        if (c == '<' && (check_next(fp, &n, &c) == '='))
        {
            buffy[0] = c;
            buffy[1] = fgetc(fp);
            buffy[2] = '\0';
            j = 0;
            position++;

            if (isKeyword(buffy) == 1)
            {
                printf("%d:%d:%s\n", line, position - strlen(buffy), buffy);
                c = fgetc(fp);
                position++;
            }
        }
        // start with letters add punctiuaton and starting digits later
        if (isalpha(c))
        {
            buffy[j++] = c;
        }
        else if ((isblank(c) || c == '\n' || c == ':' || c == '(' || c == ';' || c == ')' || c == '*' || c == '=' || c == '+' || c == '_' || c == '-' || c == '/' || c == '_' || ispunct(c)) && (j != 0))
        {
            buffy[j] = '\0';
            j = 0;

            if (isKeyword(buffy) == 1)
            {
                printf("%d:%d:%s\n", line, position - strlen(buffy), buffy);
                memset(buffy, 0, strlen(buffy));
            }
            else if (isdigit(buffy[0]))
            {
                printf("%d:%d:%s:%s\n", line, position - strlen(buffy), kind[1], buffy);
                memset(buffy, 0, strlen(buffy));
            }
            else if (isalpha(buffy[0]))
            {
                printf("%d:%d:%s:%s\n", line, position - strlen(buffy), kind[0], buffy);
                memset(buffy, 0, strlen(buffy));
            }
            // not recognized
            else if (!isblank(c) && !isalnum(c) && !isdigit(c) && !isalpha(c))
            {
                if (isKeyword(buffy) == 0)
                {
                    printf("Not recognized! line %d: position %d:   %s \n", line, position, buffy);
                    memset(buffy, 0, strlen(buffy));
                }
            }
        }
        // start taking punctuation
        if (ispunct(c))
        {
            buffy[j++] = c;
        }
        // start taking digits
        if (isdigit(c))
        {
            buffy[j++] = c;
        }

        // start tracking white space and new lines
        if (c == ws[1])
        {
            line++;
            position = 1;
        }

        if (c != ws[1])
        {
            position++;
        }

        // progress pointer
        c = fgetc(fp);
    }

    printf("EOF");

    fclose(fpO);

    return;
}

int main()
{

    // char *in = "ex/nonsense.txt";
    char *in = "ex/euclid.txt";

    FILE *fpI;
    fpI = fopen(in, "rb+");

    lex_on_em(fpI);

    fclose(fpI);

    return 0;
}
