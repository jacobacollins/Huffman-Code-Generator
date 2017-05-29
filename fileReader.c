/************************/
/*    Jacob Collins     */
/*      CS-241          */
/*uses huffman encoding */
/*to compress/decompress*/
/*        data          */
/************************/
#include <stdio.h>
#include "huffman.h"

int main(int argc, char** argv)
{
  char* infile;
  char* outfile;
  FILE* in;
  FILE* out;

  if(argc != 3) 
  {
    printf("wrong number of args\n");
    return 1;
  }

  infile = argv[1];
  outfile = argv[2];

  in = fopen(infile, "rb");
  if(in == NULL)
  {
    printf("couldn't open %s for reading\n", infile);
    return 2;
  }

  
  operations(in, out);
  fclose(in);
 

  return 0;
}
