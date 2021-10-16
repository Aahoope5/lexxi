#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    FILE* fpI;
    FILE* fpO;

    char  c;
    
    char* in = "grammar.txt";
    char* out = "keywords.txt";

    fpI =fopen(in,"r");
    fpO =fopen(out,"a+");
printf("Thumbs up good buddy!\n");

c = fgetc(fpI);

while (c>=0)
{
    if(c != ' ')
    {
  printf ("%c",c);
    }
  c =fgetc(fpI);
}




fclose(fpI);
fclose(fpO);

    
    return 0;
}

// void skip_white_space(File* fpw)
// {



// }