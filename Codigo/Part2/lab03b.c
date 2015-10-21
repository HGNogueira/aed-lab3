/*
 *  File name: lab03b.c
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *
 *  Description: See the handout for Lab 03.
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */



/* Header Inclusions                                              */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LinkedList.h"
#include"Entry.h"



/*
 *  Function:
 *    readEntryFile2LinkedList
 *
 *  Description:
 *    Reads the entries from a file and creates a linked list with
 *   these entries in the inverse order.
 *
 *  Arguments:
 *    Pointer to the file stream:
 *        FILE * fp
 *
 *  Return value:
 *    Pointer to the first node of the linked list.
 */
LinkedList * readEntryFile2LinkedList(FILE * fp, int (* getAttribute)(Entry *))
{
  int id;
  int age;
  int height;
  int weight;

  LinkedList * lp;
  Entry * entry;

  /* Initialize linked list                                       */
  lp = initLinkedList();

  /* Cycle through file rows                                      */
  while(fscanf(fp, "%d %d %d %d", &id, &age, &height, &weight) == 4)
  {
    /* Create new entry                                           */
    entry = newEntry(id, age, height, weight);

    /* Store entry in the linked list                             */
    lp = insertSortedLinkedList(lp,(Item) entry, less(Item, Item, getAttribute(Entry *)), getAttribute(Entry *));
  }

  return lp;
}



/*
 *  Function:
 *    writeEntryFile
 *
 *  Description:
 *    Writes the entries from a linked list to a file.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *      LinkedList * lp
 *    Pointer to the file stream:
 *      FILE * fp
 *
 *  Return value:
 *    None.
 */
void writeEntryFile(LinkedList * lp, FILE *fp)
{
  LinkedList * aux;

  aux = lp;
  while(aux != NULL)
  {
    printEntry((Entry *) getItemLinkedList(aux), fp);
    aux = getNextNodeLinkedList(aux);
  }
}



/*
 *  Function:
 *    freeEntryItem
 *
 *  Description:
 *    Frees the memory allocated to an Item of the type Entry
 *
 *  Arguments:
 *    Pointer to the item
 *      Item item
 *
 *  Return value:
 *    None.
 */
void freeEntryItem(Item item)
{
  freeEntry((Entry *) item);
}





/*
 * Function:
 *   main
 */


int main(int argc, char *argv[])
{
  FILE * fp;
  LinkedList * lp;

  char extOut[] = ".sort";
  char * fileNameIn;
  char * fileNameOut;

  int attribute = 1;
  int ascending = 1;


  /* Check number of arguments                                    */
  if(argc < 2)
  {
    printf("Usage: lab03b [filename] [arguments opcions]\n");
    exit(1);
  }


  /* Open input file                                              */
  fileNameIn = argv[1];

  fp  = fopen(fileNameIn, "r");
  if(fp == NULL)
  {
    printf("Open error of input file.\n");
    exit(2);
  }

  if(argc >= 4) {
    if(strcasecmp(argv[3], "-d")
      ascending = 0;
  }

  /* Read input file and construct linked list with entries       */
  if(argc >= 3) {
      if(strcasecmp(argv[2],"-id") == 1)
        lp = readEntryFile2LinkedList(fp, getIdEntry);
      else if(strcasecmp(argv[2],"-age") == 1)
        lp = readEntryFile2LinkedList(fp, getAgeEntry);
      else if(strcasecmp(argv[2],"-height") == 1)
        lp = readEntryFile2LinkedList(fp, getHeightEntry);
      else if(strcasecmp(argv[2],"-weight") == 1)
        lp = readEntryFile2LinkedList(fp, getWeightEntry);
  }


  /* Close input file                                             */
  fclose(fp);


  /* Determine output filename                                    */
  fileNameOut = (char *) malloc(sizeof(char) * 
                                 (strlen(fileNameIn) + 
                                  strlen(extOut) + 1));
  if(fileNameOut == NULL)
  {
    printf("Memory allocation error for fileNameOut.\n");
    exit(1);
  }

  strcpy(fileNameOut, fileNameIn);
  strcat(fileNameOut, extOut);


  /* Open output file                                             */
  fp  = fopen(fileNameOut, "w");

  if(fp == NULL)
  {
    printf("Open error of input file.\n");
    exit(2);
  }


  /* Write entries to output file                                 */
  writeEntryFile(lp, fp);


  /* Free space allocated to fileNameOut                          */
  free(fileNameOut);


  /* Close output file                                            */
  fclose(fp);


  /* Free linked list with entries                                */
  freeLinkedList(lp, freeEntryItem);


  return 0;
}
