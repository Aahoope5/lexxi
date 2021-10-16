#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
int is_dgit(char buffy[])
{
    const char dgit[10][2] = {{"0"}, {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}};
    int i;
    int f = 0;
    for (i = 0; i < 10; ++i)
    {
        if (strcmp(dgit[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}
int is_letter(char buffy[])
{
    const char letter[52][2] = {{"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}, {"h"}, {"i"}, {"j"}, {"k"}, {"l"}, {"m"}, {"n"}, {"o"}, {"p"}, {"q"}, {"r"}, {"s"}, {"t"}, {"u"}, {"v"}, {"w"}, {"x"}, {"y"}, {"z"}, {"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"}, {"H"}, {"I"}, {"J"}, {"K"}, {"L"}, {"M"}, {"N"}, {"O"}, {"P"}, {"Q"}, {"R"}, {"S"}, {"T"}, {"U"}, {"V"}, {"W"}, {"X"}, {"Y"}, {"Z"}};
    int i;
    int f = 0;
    for (i = 0; i < 52; ++i)
    {
        if (strcmp(letter[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}
int is_ws(char buffy[])
{
    const char ws[4][15] = {{0x09}, {0x0A}, {0x0D}, {0x0F}};
    int i;
    int f = 0;
    for (i = 0; i < 4; ++i)
    {
        if (strcmp(ws[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}
int new_line(char buffy[])
{
    const char ws[4][15] = {{0x09}, {0x0A}, {0x0D}, {0x0F}};
    int i;
    int f = 0;
    for (i = 0; i < 4; ++i)
    {
        if (strcmp(ws[i], buffy) == 0)
        {
            f = 1;
            break;
        }
    }
    return f;
}

int main()
{
    const char ws[7] = {'\t', '\n', ' ', '\f', '\r', '\t'};

    FILE *fpI;
    FILE *fpO;

    char c,operators[] = "+-*/%=";
    char buffy[15];
    int i, j = 0;
    int line = 1;
    int position = 1;
    char *in = "grammar.txt";
    char *out = "lexemeTable.txt";

    fpI = fopen(in, "r");
    fpO = fopen(out, "a+");
    c = fgetc(fpI);

    while (c != EOF)
    {
        c = fgetc(fpI);

        for (i = 0; i < 6; ++i)
        {
            if (c == operators[i])
                printf("Line: %d Character: %d %c is operator\n",__LINE__, c);
        }
    }


      if(isalnum(c)){
   buffy[j++] = c;
   }
   else if((c == ' ' || c == '\n') && (j != 0)){
   buffy[j] = '\0';
   j = 0;
     


   if(isKeyword(buffy) == 1)
   printf("%s is keyword\n", buffy);
   else
   printf("%s is indentifier\n", buffy);
   }

    fclose(fpI);
    fclose(fpO);

    return 0;
}
