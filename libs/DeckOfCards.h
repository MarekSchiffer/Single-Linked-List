#ifndef _DECK_OF_CARDS_H_
#define _DECK_OF_CARDS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <string.h>
//#include "../sortingalgorithms/mysorting.h"

/* We have 2 bool and 1 char, which sum up to 3 bytes. The int consists of 4 bytes. Alltogether
 * we have 7 bytes. The compiler adds padding, so we end up with 8 bytes.
 * If we don't want padding, we can add typedef struct __attribute__((__packed__)) { ... }
 *           OUTDATED!
 */

typedef struct {
  void* graphics;   // 8
  int value;        // 4
  char suit;        // 1
  bool oriantation; // 1
  bool faceUp;      // 1
  bool color;       // 1
} card;

/* No we define a struct of 52 cards. It is unconvinient to work with 53 and ignore the 0 entry.
 * However going from 0..51 is more aligned with c.
 */

 typedef struct {
   int size;
   card *deck;
 } deck;

int cmpCard(const void* cardin1,const void* cardin2);
int cmpPtrCard(const void* cardin1,const void* cardin2);

void freePtrCard(void* v1);
void printCard(void *elem, void *fp);
void printPtrCard(void *elem, void *fp);

void DeckInit(deck *localDeck, int size);
void DeckDestroy(deck *localDeck);

void DeckFill(deck *localDeck); 
void DeckFillFaceDown(deck *localDeck);
void DeckRead(deck *localDeck, char **cards, int n);
void swapCards(void *el, int n1, int n2);
void DeckPrint(deck *s);

void StraddleFaro(deck *localDeck);
void OutFaro(deck *localDeck);
void PartialOutFaro(deck *localDeck, int n);
void InFaro(deck *localDeck);
void CutTheDeck(deck *localDeck, int CutPoint);
void StrippingTheDeck(deck *localDeck);

void RiffleShuffle(deck *localDeck);
void RiffleShuffleFaceUp(deck *localDeck);
void Shuffle(deck *localDeck);

void DeckSort(deck *localdeck);
bool DeckCmp(const deck *localdeck1,const deck* localdeck2);
void RunningCardsSingelyFaceDown(deck *localDeck, int n, bool throwBottomHalfOnTop);
void RunningCardsSingelyFaceUp(deck *localDeck, int n, bool throwBottomHalfOnTop);
void RemoveCardAtPosition(deck *localDeck, int position);
int cmpCardSameState(const void *card1, const void *card2);
bool cardsEqual(card *c1, card *c2); 
void TurnAllCardsFaceDown(deck *localDeck);
#endif
