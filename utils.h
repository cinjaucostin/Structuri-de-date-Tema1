#ifndef utils
#define utils

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef char *Item;

typedef struct ListNode
{
	Item elem;
	struct ListNode *next;
} ListNode, *TList;

TList create(Item value);
TList insert_at_end(TList list, Item value);
TList insert_at_start(TList head, Item value);
TList copie_lista(TList head);
TList inversare(TList head);
TList amestecare_mongean(TList head);
TList intercalare(TList head);
TList n_piles(TList head, int N, int *indici);
TList amesteca(TList pachet, FILE *inputFile);
void razboi(TList pachet, FILE *inputFile, FILE *outputFile);
void rollingstone(TList pachet, FILE *inputFile, FILE *outputFile);
TList initializare_pachet();
TList deleteOnce(TList list, Item element);
TList freeTList(TList list);
TList primele_n_inversate(TList head, int nr_carti_intoarse);
TList concatenare(TList head, TList list1, TList list2, int nr_carti_intoarse);
TList sterge_primele_n(TList head, int nr_carti_intoarse);
void afisare_lista(TList head, FILE *output);
void rezolvare_amestecare();
int valoare_carte(char carte);
int rank_carte(char carte);
int *frecventa_carti(TList head);
int min(int a, int b);
int length(TList list);
int *frecventa_culori(TList head);
int win(int *frq);

#endif