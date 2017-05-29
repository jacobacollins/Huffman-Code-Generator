/************************/
/*    Jacob Collins     */
/*      CS-241          */
/*uses huffman encoding */
/*to compress/decompress*/
/*        data          */
/************************/
#include <stdio.h>
#include <string.h>
#include "huffman.h"
#include <stdlib.h>

unsigned char representSymbol;

unsigned long Count = 0;

unsigned char symbols[256] = {0};

unsigned long pool[256] = {0};

char Codes[256] = {0};





/*
  @function: insertSorted()
  @param: node, newNode
  @return: This sorts into the priority queue
*/

struct queueNode* insertSorted(struct queueNode* node, struct queueNode* newNode)
{

  struct queueNode* currentNode = node;

  if(currentNode == NULL || compare(newNode, currentNode))
  {
    newNode->next = currentNode;
    return newNode;
  }
  else
  {
    while(currentNode->next != NULL && compare(currentNode->next, newNode))
    {
      currentNode = currentNode->next;
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    return node;
  }
}
/*
  @function: compare
  @param: a, b
  @return: this compares our two nodes and sorts them, or breaks the tie
  had advice from David on this function
*/
int compare(struct queueNode* a, struct queueNode* b)
{
  if(b->freq < a->freq)
  {
    return 0;
  }
  if(a->freq == b->freq)
  {
    if(a->symbol > b->symbol)
      return 1;
    return 0;
  }
  if(b->freq > a->freq)
    return 1;
}

/*
  @function:pop()
  @param: head
  @return: pops the node of to compare
*/
struct queueNode* pop(struct queueNode** head)
{
  struct queueNode* node = *head;
  *head = (*head)->next;
  return node;
}

/*
  @function: queueLength()
  @param: node
  @return: returns length of our queue
*/
int queueLength(struct queueNode* node)
{
  struct queueNode* current = node;
  int length = 0;
  while(current != NULL)
  {
    length++;
    current = current->next;
  }
  return length;
}

/*
  @function: queueSort()
  @param:none
  @return: builds a sorted queue
*/
void queueSort()
{
  int i;
  for(i = 0; i < 256; i++)
  {
    if(!pool[i] == 0)
    {
      linkedList = insertSorted(linkedList, makeNode(i, pool[i]));
    }
  }
}
/*
  @function:isLeaf()
  @param:node
  @return:checks to see if node is a leaf
  had some advice from David on this one
*/
int isLeaf(struct queueNode* node)
{
  if((node->left == NULL) && (node->right == NULL))
  {
    return 1;
  }
  else
  {
    return 0;
  }

}


/*
  @function:createTree()
  @param:node
  @return: returns a built huffman tree
*/
struct queueNode* createTree(struct queueNode* node)
{
  int top = 0;
  struct queueNode *left, *right, *topNode, *wholeQueue;
  struct queueNode* head = node;
  struct queueNode *newNode;
  struct queueNode *first;
  struct queueNode *second;

  while(head->next != NULL)
  {
  /*pop our two nodes off, add em up, and then reinsert the new node*/
    first = pop(&head);
    second = pop(&head);
    
    newNode = makeNode(second->symbol, (first->freq +   second->freq));
    newNode->left = first;
    newNode->right = second;
    
    head = insertSorted(head, newNode);
  }

  return head;
}
/*
  @function: printCodes()
  @param: codes
  @return: returns our Symbol Codes
*/
void printCodes(char *codes[])
{
  int j;
  printf("Symbol\tFreq\tCode\n");
  for(j = 0; j < 256; j++)
  {
    
    if(pool[j] != 0)
    
    {
     
     
      if(j <= 33 || j > 126)
      {
        printf("=%d\t%lu\t%s\n", j, pool[j], codes[j]);
      }
     
     
      else
      {
        printf("%c\t%lu\t%s\n", j, pool[j], codes[j]);
      }
    }
  }
  printf("Total chars = %lu\n", Count);
}
/*
  @function: buildCodes()
  @param: node, code, CodesforSymbols, depth
  @return: returns built Huffman codes
  had help from David on this one, I couldn't figure out how
  to use memcpy
*/
void buildCodes(struct queueNode *node,char *code,char *CodesforSymbols[256],int depth)        
{
    char *codeCopy;
    int i = 0;

    if(isLeaf(node))
    {
        code[depth] = '\0';
        CodesforSymbols[node->symbol] = code;
        return;
    }

    codeCopy = malloc(255*sizeof(char));
    memcpy(codeCopy, code, 255*sizeof(char));

    code[depth] = '0';
    codeCopy[depth] = '1';
    buildCodes(node->left, code, CodesforSymbols, depth+1);
    buildCodes(node->right, codeCopy, CodesforSymbols, depth+1);
}

/*
  @function: freqOfFileSymbols()
  @param: FILE* in, FILE* out,
  @return: void
*/
void freqOfFileSymbols(FILE* in, FILE* out)
{  
    unsigned long freqs[256] = {0};
    int i, t, fileCh;

    while((fileCh = fgetc(in)) != EOF)
    {
        freqs[fileCh]++;
        Count++;
    }
    for(i = 0; i < 256; i++)
    {
        if(freqs[i] != 0)
        {
            symbols[i] = i;
            pool[i] = freqs[i];
            if(i <= 33 || i > 126)
            {
                representSymbol++;
            }
            else
            {
                representSymbol++;
            }
        }
    }
    
}

/*
  @function: encodeFile
  @param: in, out
  @return: void- encodes our file
*/
void operations(FILE* in, FILE* out)
{
    int top = 0;
    int i;
    char *code;
    char *CodesforSymbols[256] = {0};
    int depth = 0;

    code = malloc(255*sizeof(char));
    freqOfFileSymbols(in, out);
    queueSort();

    buildCodes(createTree(linkedList), code, CodesforSymbols, depth);
    printCodes(CodesforSymbols);
     

}


/*
@function makeNode()
@parameters symbol, freq
@return makes a new node and returns that
*/

struct queueNode* makeNode(char symbol, int freq)
{
  struct queueNode* makeNode = malloc(sizeof(struct queueNode));
  makeNode->symbol = symbol;
  makeNode->freq = freq;
  makeNode->left = makeNode->right = NULL;
  return makeNode;
}

/*
  @function: amountOfChars()
  @param: pool[]
  @return:unsigned long- returns the amount of Chars in a file
*/
unsigned long amountOfChars(unsigned long pool[])
{
  int i;
  unsigned long totalChars=0;
  for(i = 0; i<260;i++)
  {
    if(pool[i] != 0)
    {
      totalChars += pool[i];
    }
  }
  return totalChars;
}

/

/*
  @function: makeBinary()
  @param:code
  @return: puts our code into binary
*/
unsigned long makeBinary(char* code)
{
  unsigned long convertedCode = 0;
  while(*code != '\0')
  {
    if(*code == '1')
    {
      convertedCode = (convertedCode<<1) | 1;
    }
  return convertedCode;
}
}
/*
  @function: lengthOfCode()
  @param:code
  @return: returns our lengthOfCode
*/
unsigned char lengthOfCode(char* code)
{
  unsigned char codeLength = 0;
  while((*code) != '\0')
  {
    codeLength++;
    code++;
  }
  return  codeLength;
}
/*
  @function: anyDoubles()
  @param:code, codeLength, out, symbolCodes, pool
  @return:int- makes sure we don't have duplicate codes, 
  becuase then we have a problem
*/
int anyDoubles(unsigned long code, unsigned char codeLength,FILE* out,char* CodesforSymbols[],unsigned long pool[])
{
  int i;
  for(i=0;i<260;i++)
  {
    if(pool[i] != 0)
    {
      if((code == makeBinary(CodesforSymbols[i]))&&
      (codeLength == lengthOfCode(CodesforSymbols[i])))
      {
        putc(i,out);
        return 1;
      }
    }
  }
  return 0;
}
