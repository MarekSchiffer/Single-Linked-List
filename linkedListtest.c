/***************************************************************************************************
*                                                                                                  *
*      This program tests the Singly Linked List and is heavily based on a test by Jerry Cain      *
*                                                                                                  *
***************************************************************************************************/
#include "linkedlist.h"
#include <time.h>
#include <ctype.h>
#include <DeckOfCards.h>

extern void printCard(void *elem, void *fp);

void freeCard(void* v1) {
  free((card*)v1);
}

void freeInt(void* v1) {
  free((int*)v1);
}

void freeChr(void* v1) {
  free((char*)v1);
}

void freeStr(void* v1) {
  free(*(char**)v1);
}

int intCmp(const void* v1,const void* v2) {
  return *(int*)v1 - *(int*)v2;
}

int chrCmp(const void* v1,const void* v2) {
  return *(char*)v1 - *(char*)v2;
}

int strCmp(const void* v1,const void* v2) {
  return strcmp(*(char**)v1,*(char**)v2);
}

void printInt(void* elm,void* fp) {
  fprintf((FILE*)fp,"%i ",*(int*)elm);
  fflush((FILE*)fp);
}


void printChr(void* elm,void* file) {
  fprintf((FILE*)file,"%c",*(char*)elm);
  fflush((FILE*)file);
}


void printStr(void* elm,void* file) {
  fprintf((FILE*)file,"%s  ",*(char**)elm);
  fflush((FILE*)file);
}

static void InsertAlphabet(linked_list_t *l) {
  char* tmp;

  for(char letter = 'A'; letter <= 'Z'; letter++) {
    ListInsert(l,&letter);
  }
  printf("After inserting Alphabet (ListInsert): \t\t\t\t\t\t\t  ");
  ListMap(l,printChr,stdout);

  printf("\n");
}

static void InsertNumbers(linked_list_t *l) {

  for(int number = '0'; number <= '9'; number++) {
    ListInsert_front(l,&number);
  }
  printf("After inserting some numbers in the same List (ListInsert_front): \t\t");
  ListMap(l,printChr,stdout);

  printf("\n");
}

 static void TestCharSort(linked_list_t *l) {

   ListSort(l,chrCmp);

   printf("List after Sorting (ListSort): \t\t\t\t\t\t\t");
   ListMap(l,printChr,stdout);
   printf("\n");
 }

 static void LowerLetters(linked_list_t *l) {

   for(int i=0; i<ListLength(l); i+=2) {
     char *elm;
     ListReturnNth(l,(void**)&elm,i);
     *elm = tolower(*elm);
   }

   fprintf(stdout,"After lowering ever 2nd letter (ReturnNth): \t\t\t\t\t");
   ListMap(l,printChr,stdout);
   fprintf(stdout,"\n");

 }

 void TestInsertDelete(linked_list_t *l) {

   char ch ='-';
   for (int i=3; i<ListLength(l); i+=4) {
     ListInsertNth(l,&ch,i);
   }


  fprintf(stdout,"\nAfter inserting dashes (ListInsertNth): \t\t\t     ");
  ListMap(l,printChr,stdout);
  printf("\n");

  for (int i=3; i < ListLength(l); i+=3) {
    ListRemoveNth(l,NULL,i);
  }

  fprintf(stdout,"After deleting dashes (ListRemoveNth): \t\t\t\t\t\t");
   ListMap(l,printChr,stdout);

  for (int i=0; i<3; i++) {

    char chf = '*';
    char chb = '!';

    ListInsert(l,&chb);
    ListInsert_front(l,&chf);
  }

  fprintf(stdout,"\nAfter Inserting at both ends (ListInsert_front & ListInsert):  \t\t     ");
  ListMap(l,printChr,stdout);
 
   char resFront[3];
   char resBack[3];
   for (int i=0; i<3; i++) {
     ListRemove(l,&resFront[i]);
     ListRemove_back(l,&resBack[i]);
   }

   fprintf(stdout,"\n\nRemoving both, but saving the result (ListRemove & ListRemove_back): \t\t");
   ListMap(l,printChr,stdout);
   printf("\n");
   for(int i=0; i<3; i++) {
     fprintf(stdout,"resFront[%i]: %c, resBack[%i]: %c\t",i,resFront[i],i,resBack[i]);
   }
   fprintf(stdout,"\n");
}


static void TestFindAndRemove(linked_list_t *l) {
  fprintf(stdout,"\nLet's search for H (ListFind): \t...\t");
  char to_find_H = 'H';
  int pos = ListFind(l,&to_find_H,chrCmp,0);
  assert (pos != -1);
  fprintf(stdout,"Found at Position %i\n",pos);
  fprintf(stdout,"Let's search for @ (ListFind): \t...\t");
  char to_find_at = '@';
  pos = ListFind(l,&to_find_at,chrCmp,0);
  assert (pos == -1);
  fprintf(stdout,"Result: %i",pos);
  fprintf(stdout,", because it's not in there\n");

  char chInsert1 = '@';
  char chInsert2 = '@';

  ListInsertNth(l,&chInsert1,11);
  ListInsertNth(l,&chInsert2,13);

  fprintf(stdout,"\nInsert some @ at position 11 and 13 (ListInsertNth) \t\t\t      ");
  ListMap(l,printChr,stdout);

  fprintf(stdout,"\n\nLet's search for @ (ListFind) from position  0:  ...  ");
  node_t *found_node;
  int pos1 = ListFind(l,&to_find_at,chrCmp,0);
  assert (pos1 != -1);
  fprintf(stdout,"Found at Position %i\n",pos1);
  fprintf(stdout,"Let's search for @ (ListFind) from position 11:  ...  ");
  int pos2 = ListFind(l,&to_find_at,chrCmp,11);
  assert (pos2 != -1);
  fprintf(stdout,"Found at Position %i\n",pos2);

  fprintf(stdout,"\nRemove from the middle, position 18-22 and keep the result (ListRemoveNth):   ");
  ListMap(l,printChr,stdout);
  fprintf(stdout,"\n");

  char resMiddle[5];
  for (int i=0; i<4; i++) {
    ListRemoveNth(l,&resMiddle[i],18);
  }

  for (int i=0; i<4; i++) {
    fprintf(stdout,"resMiddle[%i]: %c, ",i,resMiddle[i]);
  }
  fprintf(stdout,"\nThe Linked List now looks like this: \t\t\t\t\t\t");
  ListMap(l,printChr,stdout);
//  fprintf(stdout,"\nWe took ownership of the elments back, we need to free them again ... ");
//  for (int i=0; i<4; i++) {
//    free(resMiddle[i]);
//  }
//  fprintf(stdout,"Done!\n\n");
}

static void TestDispose(linked_list_t *l) {
  fprintf(stdout,"\nReturning the Element B (12): (ListReturnNth) ... ");
//
  char finalRemoval;
  ListRemoveNth(l,&finalRemoval,12);
  fprintf(stdout,"Taken out: %c \n",finalRemoval);
  fprintf(stdout,"Disposing the Linked List (LinkDispose): ...");
  ListDispose(l);
  fprintf(stdout,"Done!\n");
//  fprintf(stdout,"The free function also removed the element    ... Taken out: %s\n", (char*)finalRemoval);
  printf("\n");

}

static void SimpleTest() {

  fprintf(stdout,"\n------------------------------------   Creating a Singly-Linked-List for chars   ---------------------------------------\n");
  fprintf(stdout,"------------------------------------   Testing every functionality implemented   ---------------------------------------\n\n");

  linked_list_t alphabet;
  ListInit(&alphabet,sizeof(char),NULL);

  InsertAlphabet(&alphabet);
  InsertNumbers(&alphabet);
  TestCharSort(&alphabet);
  LowerLetters(&alphabet);
  TestInsertDelete(&alphabet);
  TestFindAndRemove(&alphabet);
  TestDispose(&alphabet);
}

static void TestStringList() {

  fprintf(stdout,"\n--------------------------------------   Creating a Singly-Linked-List for Strings   ------------------------------------\n\n");

  linked_list_t stringList; 
  ListInit(&stringList,sizeof(char*),freeStr);

  char *names[] = {strdup("Bob Dylan"), strdup("Shawn Clovin"), strdup("Linda Perry"), strdup("Neil Young"), strdup("Towns van Zandt"), strdup("Bradley Nowell"), strdup("Tom Petty") };

  for( int i =0; i<7; i++) {
    ListInsert(&stringList,&names[i]);
  }

    fprintf(stdout,"\nLinked List filled with Strings:\n");
      ListMap(&stringList,printStr,stdout);

    ListSort(&stringList,chrCmp);

    fprintf(stdout,"\n\nLinked List sorted:\n");
    ListMap(&stringList,printStr,stdout);

    fprintf(stdout,"\n\nRegaining control of the first element (ListRemove): ");

    char *keep;
    ListRemove(&stringList,&keep);

    fprintf(stdout,"\t %s \nList now looks like this: \n\n",keep);

    ListMap(&stringList,printStr,stdout);

    fprintf(stdout,"\n\nPrinting names[%i] before freeing: %s ... ",6,(char*)names[6]);

    ListDispose(&stringList);

    fprintf(stdout,"Linked List Disposed ... ");
    fprintf(stdout,"Printing names[%i] after freeing: %s\n",6,(char*)names[6]);
    fprintf(stdout,"We still have: \t %s \t",keep);
    fprintf(stdout,"Freeing the strdup memory with free(keep)\n");
    free(keep);
}


static void InsertPermutationOfNumber(linked_list_t *l, long n, long d) {
  clock_t start, end; char result[12];

  fprintf(stdout,"Generating one permutation of all numbers between [0,%ld] \n",d);

  long residue;
  for(long k=0; k<d; k++) {
    residue = (long) (((long long)k * (long long)n) % d);
    ListInsert(l,&residue);
  }

}

static void FindANumber(linked_list_t *l,int* toFind) {
  int position;

  fprintf(stdout, "Looking for number %i in the list \t\t ... \t\t ",*toFind);
  fflush(stdout);

  position = ListFind(l,toFind,intCmp,0);

  fprintf(stdout, "Found! It's at position %i\n\n",position);
  fflush(stdout);

}


static void TestSort(linked_list_t *l) {
  fprintf(stdout, "Starting sorting the list with %zu elements \t ... \t\t ",ListLength(l));
  fflush(stdout);
  ListSort(l,intCmp);
  fprintf(stdout, "Done!\n");
}

static void ConfirmSorting(linked_list_t *l) {
  size_t originalLength = ListLength(l);
  fprintf(stdout, "Checking if it's indeed sorted: \t\t ... \t\t ");
  long embeddedLong;
  for (int residue = 0; residue < originalLength; residue++) {
    ListRemove(l,&embeddedLong);
    assert( embeddedLong == residue);
  }
  fprintf(stdout, "Yes, it is!\n\n");
}


static void TestDelete(linked_list_t *l) {
  size_t *largestOriginalNumber;
  fprintf(stdout, "Removing every Node by repeatedlly removing the 100th-to-last Node, starting from 0 each time! This will take a moment!\n");
  fflush(stdout);
  ListReturnNth(l,(void**)&largestOriginalNumber,ListLength(l)-1);
  while (ListLength(l) >= 100) {
    ListRemoveNth(l,NULL,ListLength(l)-100);
  }
  fprintf(stdout, "Almost done! Removing the last 100 elements alternating from the front and back:\t ... \t");
  fflush(stdout);

  while( ListLength(l)>1 ) {
    ListRemove(l,NULL);
    ListRemove_back(l,NULL);
  }
    ListRemove(l,NULL);
  fprintf(stdout, " Done!\n");
}


static void DisposeLargeList(linked_list_t *l) {
  fprintf(stdout, "Finally, Disposing the list:\t ... \t");
  fflush(stdout);
  ListDispose(l);
  fprintf(stdout, "All clear!\n");
}

 static void TestingALargeLinkedList() {

   fprintf(stdout,"\n--------------------------------   Performance Test for very large Singly-Linked-List   ---------------------------------\n\n");
   static const long prime1 = 100391;
   static const long prime2 = 201577;

   int toFind = 711;

   linked_list_t numbers; 
   ListInit(&numbers,sizeof(long),NULL);

   InsertPermutationOfNumber(&numbers,prime1,prime2);

   FindANumber(&numbers,&toFind);
 
   TestSort(&numbers);
   ConfirmSorting(&numbers);

   InsertPermutationOfNumber(&numbers,prime1,prime2); // Refilling the list.

   TestDelete(&numbers);

   DisposeLargeList(&numbers);
}


static void StructTest() {
  deck testDeck;
  int deckSize=36;
  DeckInit(&testDeck,deckSize);
  DeckFill(&testDeck);
  Shuffle(&testDeck);

  linked_list_t cardList;
  ListInit(&cardList,sizeof(card),NULL);

  fprintf(stdout,"\n------------------------------   Creating a Singly-Linked-List for card (struct)  ---------------------------------\n");
  fprintf(stdout,"\nFirst we insert a shuffled Deck of cards containing %d cards, each of size %ld, into a linked list\n",deckSize,sizeof(card));

  for (int i=0; i<testDeck.size; ++i) {
    ListInsert(&cardList,&testDeck.deck[i]);
  }
  DeckDestroy(&testDeck);

  ListMap(&cardList,printCard,stdout);
  fprintf(stdout,"\n");

  fprintf(stdout,"\nNow we use ListSort with compare function cmpCard to sort the linked list\n");
  ListSort(&cardList,cmpCard);

  ListMap(&cardList,printCard,stdout);
  fprintf(stdout,"\n");

  card cardReturned;

  fprintf(stdout,"\nNext, we remove a card from the deck at position 11\n");
  ListRemoveNth(&cardList,&cardReturned,11);

  fprintf(stdout,"The removed card is: \t\t\t\t\t\t\t");
  fprintf(stdout,"RemovedCard: %d%c \n",cardReturned.value, cardReturned.suit);

  fprintf(stdout,"The list now looks like this:\n");
  ListMap(&cardList,printCard,stdout);
  fprintf(stdout,"\n");

  fprintf(stdout,"\nFinally, we dispose the list ... ");
  ListDispose(&cardList);
  fprintf(stdout,"Done!\n");

  fprintf(stdout,"Because we're working with values, the Removed Card is still here\t");
  fprintf(stdout,"RemovedCard: %d%c \n",cardReturned.value, cardReturned.suit);

}


int main() {

  system("clear");

  SimpleTest();
  TestingALargeLinkedList();
  TestStringList();
  StructTest();
}
