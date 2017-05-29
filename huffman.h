/************************/
/*    Jacob Collins     */
/*      CS-241          */
/*uses huffman encoding */
/*to compress/decompress*/
/*        data          */
/************************/
#ifndef HUFFMAN_H
#define HUFFMAN_H
struct queueNode* linkedList;


struct queueNode
{
	struct queueNode *left
	struct queueNode *right;
	struct queueNode* next;
	char symbol;
	unsigned long freq;
	char *code;
};

/**************************************************************/
/* Huffman encode a file.                                     */
/* in -- File to encode.                                      */
/*       May be binary, so don't assume printable characters. */
/* out -- File where encoded data will be written.            */
/* printTable -- If not zero, print table of bytes,           */
/*               frequencies, and codes to standard output.   */
/**************************************************************/
void operations(FILE* in, FILE* out);
void freqOfFileSymbols(FILE* in, FILE* out);
void buildCodes(struct queueNode *node,char *code,char *symCodes[256],int depth);
void printCodes(char *codesArray[]);
struct queueNode* createTree(struct queueNode* node);
int isLeaf(struct queueNode* node);
void queueSort();
void printList(struct queueNode* node);
int listLength(struct queueNode* node);
struct queueNode* pop(struct queueNode** head);
int compare(struct queueNode* a, struct queueNode* b);
struct queueNode* insertSorted(struct queueNode* node, struct queueNode* htnNew);
struct queueNode* makeNode(char symbol, int freq);
unsigned char lengthOfCode(char* code);
unsigned long amountOfChars(unsigned long globalFreqs[]);
unsigned long makeBinary(char* code);
int anyDoubles(unsigned long code, unsigned char codeLength,FILE* out,char* symCodes[],unsigned long globalFreqs[]);
void maybeDecodes(FILE* in, FILE* out,char* symCodes[],unsigned long globalFreqs[]);
void decodeSymbolAmount(unsigned char totalSymbols,FILE* in,unsigned long globalFreqs[]);
#endif