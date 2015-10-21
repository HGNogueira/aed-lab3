/******************************************************************************
 *
 * File Name: word.h
 *	      (c) 2012 AED
 * Authors:    AED Team
 * Revision:  v2.3
 *
 *****************************************************************************/

#ifndef _WORD_H_
#define _WORD_H_

#include "defs.h"

typedef struct t_palavra t_palavra;
typedef struct t_palavra **t_tabela;


char *LePalavra(FILE * f);
FILE *AbreFicheiro(char *nome, char *mode);

void ExitErroMemoria(int k);
int  AllocaTabelaPalavras(t_tabela *t, char *ficheiro);
int  NovaPalavra(t_tabela * t, char *palavra, int n_palavras);
int  PreencheTabelaPalavras(t_tabela *t, char *ficheiro);
void EscreveFicheiro(t_tabela *t, char *ficheiro, int n_palavras);
void LibertaTabelaPalavras(t_tabela *t, int nt_palavras);

int  lessAlfabetica(Item a, Item b);

void sort(Item a[], int l, int r, int (*less) (Item, Item, int*),int* n_ops);
int alphaLess(Item iPal1, Item iPal2, int* n_ops);
int alphaMore(Item iPal1, Item iPal2, int* n_ops);
int ocorrLess(Item iPal1, Item iPal2, int* n_ops);
int ocorrMore(Item iPal1, Item iPal2, int* n_ops);
int strlenLess(Item iPal1, Item iPal2, int* n_ops);
int strlenMore(Item iPal1, Item iPal2, int* n_ops);

#endif
