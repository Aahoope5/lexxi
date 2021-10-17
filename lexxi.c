#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int isKeyword(char buffy[])
{
    int i;
    int f = 0;
    const char keywords[15][9] = {{"program"}, {":"}, {"end"}, {"bool"}, {"int"}, {";"}, {":="}, {"if"}, {"then"}, {"else"}, {"fi"}, {"while"}, {"do"}, {"od"}, {"print"}};
    for (i = 0; i < 15; ++i)
    {
        if (strcmp(keywords[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}
int is_relops(char buffy[])
{
    const char relops[5][3] = {"<", "=<", "=", "!=", ">"};
    int i;
    int f = 0;
    for (i = 0; i < 5; ++i)

    {
        if (strcmp(relops[i], buffy) == 0)
        {
            f = 1;

            break;
        }
    }
    return f;
}
int is_addops(char buffy[])
{
    const char addops[3][3] = {"+", "-", "or"};
    int i;
    int f = 0;
    for (i = 0; i < 3; ++i)
    {
        if (strcmp(addops[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}
int is_mult(char buffy[])
{
    const char mult[3][4] = {"*", "/", "and"};
    int i;
    int f = 0;
    for (i = 0; i < 3; ++i)
    {
        if (strcmp(mult[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}
int is_factor(char buffy[])
{
    const char factor[2][2] = {"(", ")"};
    int i;
    int f = 0;
    for (i = 0; i < 2; ++i)
    {
        if (strcmp(factor[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}
int is_unops(char buffy[])
{
    const char unops[2][4] = {"-", "not"};
    int i;
    int f = 0;
    for (i = 0; i < 2; ++i)
    {
        if (strcmp(unops[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}
int is_boolit(char buffy[])
{
    const char boolit[2][6] = {"fasle", "true"};
    int i;
    int f = 0;
    for (i = 0; i < 2; ++i)
    {
        if (strcmp(boolit[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}

char check_next(FILE *const fp, char *next, char *ch)
{
    char innext;
    char inch;
   
    
    fseek(fp, -1L, SEEK_CUR);
    fseek(fp, -0L, SEEK_CUR);
   *next = getc(fp);
    innext= *next;
  
    //  printf("next Char is %c  \n", innext);
    fseek(fp, -2L, SEEK_CUR);
    fseek(fp, -0L, SEEK_CUR);
    // printf("%d current position \n", ftell(fp)) ;
    *ch= getc(fp);
    inch=*ch;
    // printf("current Char is %c  \n", inch);
    return innext;
}

int main()
{

    FILE *fpI;
    FILE *fpO;

    char c,n;
 
    char buffy[10];

    int i, j = 0;
    int line = 1;
    int position = 1;
    char kind[2][4] = {{"ID"}, {"NUM"}};

    char *in = "ab.txt";
    char *out = "lexemeTable.txt";

    fpI = fopen(in, "rb+");
    fpO = fopen(out, "a+");
    c = fgetc(fpI);

    const char ws[4] = {0x09, 0x0A, 0x0D, 0x0F};

    while (c != EOF)
    {

       

        if (isalnum(c))
        {
            buffy[j++] = c;
        }
        else if (c == ' ' || c == '\n'|| ispunct(c) && (j != 0))
        {
            buffy[j] = '\0';
            j = 0;

            if (isKeyword(buffy) == 1)
            {
                printf("line %d position %d:  %s is keyword\n", line, position - strlen(buffy), buffy);
                check_next(fpI,&n,&c);
                printf("%c\n ",n);
                
                memset(buffy, 0, strlen(buffy));
            }
            else if (isdigit(buffy[0]))
            {
                printf("line %d position %d:  kind: %s Value: %s \n", line, position - strlen(buffy), kind[1], buffy);
                printf("%c\n ",check_next(fpI,&n,&c));
                memset(buffy, 0, strlen(buffy));
            }
            else if (isalpha(buffy[0]))
            {
                printf("line %d position %d:  kind: %s Value: %s \n", line, position - strlen(buffy), kind[0], buffy);
               printf("%c\n ",check_next(fpI,&n,&c));
                memset(buffy, 0, strlen(buffy));
            }
        }

        //  if (ispunct(c))
        // {
        //     buffy[j++] = c;
        // }
        // else if ((c == ' ' || c == '\n') && (j != 0))
        // {
        //     buffy[j] = '\0';
        //     j = 0;

        //     if (is_relops(buffy) == 1)
        //     {
        //         printf("line %d position %d:  kind: %s \n", line, position, buffy);

        //     } else if (is_addops(buffy))
        //     {
        //           printf("line %d position %d:  kind: %s \n", line, position,buffy);
        //     } else if (is_mult(buffy))
        //     {
        //           printf("line %d position %d:  kind: %s  \n", line, position, buffy);
        //     } else if (is_factor(buffy))
        //     {
        //           printf("line %d position %d:  kind: %s  \n", line, position,buffy);
        //     } else if (is_unops(buffy))
        //     {
        //           printf("line %d position %d:  kind: %s \n", line, position,buffy);
        //     }
        //     else
        //         printf(" kind: %s is not recognized  \n", line, position, buffy);
        // }

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

    // printf("%s\n", buffy);
    fclose(fpI);
    fclose(fpO);

    return 0;
}
