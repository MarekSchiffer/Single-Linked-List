/***************************************************************************************************
*                                                                                                  *
*      This program tests the Singly Linked List and is heavily based on a test by Jerry Cain      *
*                                                                                                  *
***************************************************************************************************/
#include "linkedlist.h"
#include <ctype.h>
#include <DeckOfCards.h>

extern void printPtrCard(void *elem, void *fp);
extern void freePtrCard(void *v1);
extern int cmpPtrCard(const void *cardin1,const void *cardin2);

void freePtrInt(void* v1) {
  free(*(int**)v1);
}

void freePtrChr(void* v1) {
  free(*(char**)v1);
}

void freeStr(void* v1) {
  free(*(char**)v1);
}

int intPtrCmp(const void* v1,const void* v2) {
  return **(int**)v1 - **(int**)v2;
}

int intPtrIntCmp(const void* v1,const void* v2) {
  return **(int**)v1 - *(int*)v2;
}

int chrPtrCmp(const void* v1,const void* v2) {
  return **(char**)v1 - **(char**)v2;
}

int chrPtrChrCmp(const void* v1,const void* v2) {
  return **(char**)v1 - *(char*)v2;
}

int strCmp(const void* v1,const void* v2) {
  return strcmp(*(char**)v1,*(char**)v2);
}

void printPtrChr(void* elm,void* file) {
  fprintf((FILE*)file,"%c",**(char**)elm);
  fflush((FILE*)file);
}

void printStr(void* elm,void* file) {
  fprintf((FILE*)file,"%s  ",*(char**)elm);
  fflush((FILE*)file);
}

static void InsertAlphabet_pointers(linked_list_t *l) {
  char *tmp;

  for(char letter = 'A'; letter <= 'Z'; letter++) {
    tmp = malloc(sizeof(char));
    *tmp = letter;
    ListInsert(l,&tmp);
  }
  printf("\x1B[35mAfter inserting Alphabet (ListInsert):\x1b[m \t\t\t\t\t\t\t  ");
  ListMap(l,printPtrChr,stdout);

  printf("\n");
}

static void InsertNumbers_pointers(linked_list_t *l) {
  int* tmp;

  for(int number = '0'; number <= '9'; number++) {
    tmp = malloc(sizeof(char));
    *tmp = number;
    ListInsert_front(l,&tmp);
  }
  printf("\x1b[35mAfter inserting some numbers in the same List (ListInsert_front):\x1b[m \t\t");
  ListMap(l,printPtrChr,stdout);

  fprintf(stdout,"\n");
}

static void TestCharSort_pointers(linked_list_t *l) {
  ListSort(l,chrPtrCmp);

  printf("\x1b[35mList after Sorting (ListSort):\x1b[m \t\t\t\t\t\t\t");
  ListMap(l,printPtrChr,stdout);
  printf("\n");
}

static void LowerLetters_pointers(linked_list_t *l) {

  for(int i=0; i< ListLength(l); i+=2) {
    char **elm;
    ListReturnNth(l,(void**)&elm,i);
    **elm = tolower(**elm);
  }

  fprintf(stdout,"\x1b[35mAfter lowering ever 2nd letter (ReturnNth):\x1b[m \t\t\t\t\t");
  ListMap(l,printPtrChr,stdout);

}

void TestInsertDelete_pointers(linked_list_t *l) {

  for (int i=3; i < ListLength(l); i+=4) {
    char *ch = malloc(sizeof(char));
    *ch ='-';
    ListInsertNth(l,&ch,i);
  }

  fprintf(stdout,"\n\x1b[35mAfter inserting dashes (ListInsertNth):\x1b[m \t\t\t     ");
  ListMap(l,printPtrChr,stdout);
  printf("\n");

  for (int i=3; i < ListLength(l); i+=3) {
    ListRemoveNth(l,NULL,i);
  }

  fprintf(stdout,"\x1b[35mAfter deleting dashes (ListRemoveNth):\x1b[m \t\t\t\t\t\t");
  ListMap(l,printPtrChr,stdout);

  for (int i=0; i<3; i++) {
  char* chf =  malloc(sizeof(char));
  char* chb =  malloc(sizeof(char));

  *chf ='*';
  *chb ='!';

  ListInsert(l,&chb);
  ListInsert_front(l,&chf);

}

  fprintf(stdout,"\n\x1b[35mAfter Inserting at both ends (ListInsert_front & ListInsert):\x1b[m  \t\t     ");
  ListMap(l,printPtrChr,stdout);

  void* resFront[3];
  void* resBack[3];

  for (int i=0; i<3; i++) {
  ListRemove(l,&resFront[i]);
  ListRemove_back(l,&resBack[i]);
  }

  fprintf(stdout,"\n\n\x1b[35mRemoving both, but saving the result (ListRemove & ListRemove_back):\x1b[m \t\t");
  ListMap(l,printPtrChr,stdout);
  printf("\n");
  for(int i=0; i<3; i++) {
    fprintf(stdout,"\x1b[35mresFront[%i]:\x1b[m %c, \x1b[35m resBack[%i]:\x1b[m  %c\t",i,*(char*)resFront[i],i,*(char*)resBack[i]);
  }
  fprintf(stdout,"\n\x1b[35mWe took ownership back, we need to free the items (free):\x1b[m\n");
  for(int i=0; i<3; i++) {
    free(resFront[i]);
    free(resBack[i]);
  }
  for(int i=0; i<3; i++) {
    fprintf(stdout,"\x1b[35mresFront[%i]:\x1b[m %c,\x1b[35m resBack[%i]:\x1b[m %c\t",i,*(char*)resFront[i],i,*(char*)resBack[i]);
  }
  fprintf(stdout,"\n\x1b[35mAnd, they're gone.\x1b[m\n\n");
}

static void TestFindAndRemove_pointers(linked_list_t *l) {
  fprintf(stdout,"\x1b[35mLet's search for H (ListFind):\x1b[m \t...\t");
  char to_find_H = 'H';
  int pos = ListFind(l,&to_find_H,chrPtrChrCmp,0);
  assert (pos != -1);
  fprintf(stdout,"\x1b[35mFound at Position\x1b[m %d\n",pos);
  fprintf(stdout,"\x1b[35mLet's search for @ (ListFind):\x1b[m \t...\t");
  pos = ListFind(l,"@",chrPtrChrCmp,0);
  assert (pos == -1);
  fprintf(stdout,"\x1b[35mResult:\x1b[m %i",pos);
  fprintf(stdout,"\x1b[35m, because it's not in there\x1b[m\n");

  char* chInsert1 = malloc(sizeof(char));
  char* chInsert2 = malloc(sizeof(char));
  *chInsert1 = '@';
  *chInsert2 = '@';

  ListInsertNth(l,&chInsert1,11);
  ListInsertNth(l,&chInsert2,13);

  fprintf(stdout,"\n\x1b[35mInsert some @ at position 11 and 13 (ListInsertNth) \x1b[m \t\t\t      ");
  ListMap(l,printPtrChr,stdout);

  fprintf(stdout,"\n\n\x1b[35mLet's search for @ (ListFind) from position  0:  ...  \x1b[m");
  int pos1 = ListFind(l,"@",chrPtrChrCmp,0);
  assert (pos1 != -1);
  fprintf(stdout,"\x1b[35mFound at Position: \x1b[m%i\n",pos1);
  fprintf(stdout,"\x1b[35mLet's search for @ (ListFind) from position 11:  ...  \x1b[m");
  int pos2 = ListFind(l,"@",chrPtrChrCmp,11);
  assert (pos2 != -1);
  fprintf(stdout,"\x1b[35mFound at Position \x1b[m %d\n",pos2);

  fprintf(stdout,"\n\x1b[35mRemove from the middle, position 18-21 and keep the result (ListRemoveNth):\x1b[m   ");
  ListMap(l,printPtrChr,stdout);

  fprintf(stdout,"\n");

  void* resMiddle[5];
  for (int i=0; i<4; i++) {
    ListRemoveNth(l,(resMiddle+i),18);
  }

  for (int i=0; i<4; i++) {
    fprintf(stdout,"\x1b[35mresMiddle[%i]:\x1b[m %c, ",i,*(char*)resMiddle[i]);
  }
  fprintf(stdout,"\n\x1b[35mThe Linked List now looks like this: \x1b[m \t\t\t\t\t\t");
  ListMap(l,printPtrChr,stdout);
  fprintf(stdout,"\n\x1b[35mWe took ownership of the elments back, we need to free them again ... \x1b[m");
  for (int i=0; i<4; i++) {
    free(resMiddle[i]);
  }
  fprintf(stdout,"\x1b[35mDone!\x1b[m\n\n");
}

static void TestDispose_pointers(linked_list_t *l) {
  fprintf(stdout,"\x1b[35mReturning the Element B (12): (ListReturnNth) ... \x1b[m");
  char **finalRemoval;
  ListReturnNth(l,(void**)&finalRemoval,12);
  fprintf(stdout,"\x1b[35mTaken out: \x1b[m%c \n",**finalRemoval);
  fprintf(stdout,"\x1b[35mThe element is still in the list we just got a pointer to it. \x1b[m");
  fprintf(stdout,"\x1b[35mDisposing the Linked List (LinkDispose): ...\x1b[m");
  ListDispose(l);
  fprintf(stdout,"\x1b[35mDone!\x1b[m\n");
  fprintf(stdout,"\x1b[35mThe free function also removed the element    ... Returned out: \x1b[m %s\n","(null)");
  fprintf(stdout,"\n");
}

static void SimpleTest_pointers() {

  fprintf(stdout,"\n------------------------------------   Creating a Singly-Linked-List for \x1b[35mchars*\x1b[m  ---------------------------------------\n");
  fprintf(stdout,"------------------------------------   Testing every functionality implemented \x1b[35m(for pointers)\x1b[m  -------------------------\n\n");

  linked_list_t alphabet_pointers;
  ListInit(&alphabet_pointers,sizeof(char*),freePtrChr);

  InsertAlphabet_pointers(&alphabet_pointers);
  InsertNumbers_pointers(&alphabet_pointers);
  TestCharSort_pointers(&alphabet_pointers);
  LowerLetters_pointers(&alphabet_pointers);
  TestInsertDelete_pointers(&alphabet_pointers);
  TestFindAndRemove_pointers(&alphabet_pointers);
  TestDispose_pointers(&alphabet_pointers);
}

static void TestStringList() {

  fprintf(stdout,"\n--------------------------------------   Creating a Singly-Linked-List for Strings   ------------------------------------\n\n");

  linked_list_t stringList;
  ListInit(&stringList,sizeof(char*),freeStr);

  char* names[] = {strdup("Bob Dylan"), strdup("Shawn Clovin"), strdup("Linda Perry"), strdup("Neil Young"), strdup("Towns van Zandt"), strdup("Bradley Nowell"), strdup("Tom Petty") };

  for( int i =0; i<7; i++) {
    ListInsert(&stringList,&names[i]);
  }

    fprintf(stdout,"\nLinked List filled with Strings:\n");
    ListMap(&stringList,printStr,stdout);

    ListSort(&stringList,strCmp);

    fprintf(stdout,"\n\nLinked List sorted:\n");
    ListMap(&stringList,printStr,stdout);

    fprintf(stdout,"\n\nRegaining control of the first element (ListRemove): ");

    char *keep;
    ListRemove(&stringList,(void*)&keep);

    fprintf(stdout,"\t %s \nList now looks like this: \n\n",keep);

    ListMap(&stringList,printStr,stdout);

    fprintf(stdout,"\n\nPrinting names[%i] before freeing: %s ... ",6,names[6]);

    ListDispose(&stringList);

    fprintf(stdout,"Linked List Disposed ... ");
    fprintf(stdout,"Printing names[%i] after freeing (UB): %s\n",6,names[6]);
    fprintf(stdout,"We still have: \t %s \t",keep);
    fprintf(stdout,"Freeing the strdup memory with free(keep)\t");
    free(keep);
    fprintf(stdout,"Done!\n");
}

static void InsertPermutationOfNumber_pointers(linked_list_t *l, long n, long d) {
  clock_t start, end; char result[12];

  fprintf(stdout,"\x1b[35mGenerating one permutation of all numbers between [0,%ld] \x1b[m\n",d);

  for(long k=0; k<d; k++) {
     long *residue = malloc(sizeof(long));
     *residue = (long) (((long long)k * (long long)n) % d);
     ListInsert(l,&residue);
  }

}

static void FindANumber_pointers(linked_list_t *l,int* toFind) {
  int position;

  fprintf(stdout, "\x1b[35mLooking for number %i in the list \t\t ... \t\t \x1b[m",*toFind);
  fflush(stdout);

  position = ListFind(l,toFind,intPtrIntCmp,0);

  fprintf(stdout, "\x1b[35mFound! It's at position \x1b[m%d\n\n",position);
  fflush(stdout);

}

static void TestSort_pointers(linked_list_t *l) {
  fprintf(stdout, "\x1b[35mStarting sorting the list with %zu elements \t ... \x1b[m\t\t ",ListLength(l));
  fflush(stdout);
  ListSort(l,intPtrCmp);
  fprintf(stdout, "\x1b[35mDone!\x1b[m\n");
}

static void ConfirmSorting_pointers(linked_list_t *l) {
  int originalLength =ListLength(l);
  fprintf(stdout, "\x1b[35mChecking if it's indeed sorted: \t\t ... \x1b[m\t\t ");
  void* embeddedLong;
  for (int residue = 0; residue < originalLength; residue++) {
    ListRemove(l,&embeddedLong);
    assert( *(long*)embeddedLong == residue);
    free(embeddedLong);
  }
  fprintf(stdout, "\x1b[35mYes, it is!\x1b[m\n\n");
}

static void TestDelete_pointers(linked_list_t *l) {
  long **largestOriginalNumber;
  fprintf(stdout, "\x1b[35mRemoving every Node by repeatedlly removing the 100th-to-last Node, starting from 0 each time! This will take a moment!\x1b[m\n");
  fflush(stdout);
  ListReturnNth(l,(void**)&largestOriginalNumber,ListLength(l)-1);
  while (ListLength(l) >= 100) {
    ListRemoveNth(l,NULL,ListLength(l)-100);
  }
  fprintf(stdout, "\x1b[35mAlmost done! Removing the last 100 elements alternating from the font and back:\t ...\x1b[m \t");
  fflush(stdout);

  while(ListLength(l)>1) {
    ListRemove(l,NULL);
    ListRemove_back(l,NULL);
  }
    ListRemove(l,NULL);
  fprintf(stdout, " \x1b[35mDone!\x1b[m\n");
}

static void DisposeLargeList_pointers(linked_list_t *l) {
  fprintf(stdout, "\x1b[35mFinally, Disposing the list:\t ... \x1b[m \t");
  fflush(stdout);
  ListDispose(l);
  fprintf(stdout, "\x1b[35mAll clear!\x1b[m\n");


}

static void TestingALargeLinkedList_pointers() {

  fprintf(stdout,"\n--------------------------------   Performance Test for very large Singly-Linked-List \x1b[35mpoiners\x1b[m ----------------------------\n\n");
  static const long prime1 = 100391;
  static const long prime2 = 201577;

  int toFind = 711;

  linked_list_t numbers_pointers;
  ListInit(&numbers_pointers,sizeof(long*),freePtrInt);

  InsertPermutationOfNumber_pointers(&numbers_pointers,prime1,prime2);
  FindANumber_pointers(&numbers_pointers,&toFind);
  TestSort_pointers(&numbers_pointers);
  ConfirmSorting_pointers(&numbers_pointers);

  InsertPermutationOfNumber_pointers(&numbers_pointers,prime1,prime2); // Refilling the list.

  TestDelete_pointers(&numbers_pointers);
  DisposeLargeList_pointers(&numbers_pointers);
}

static void StructTest_pointers() {
  deck testDeck;
  int deckSize = 36;
  DeckInit(&testDeck,deckSize);
  DeckFill(&testDeck);
  Shuffle(&testDeck);

  linked_list_t cardList;
  ListInit(&cardList,sizeof(card*),freePtrCard);

  fprintf(stdout,"\n------------------------------   Creating a Singly-Linked-List for \x1b[35mcard* (struct*)\x1b[m  ---------------------------------\n");
  fprintf(stdout,"\n\x1b[35mFirst we insert a shuffled Deck of cards containing %d pointers to cards on the heap into a linked list\x1b[m\n\n",deckSize);
  for (int i=0; i<testDeck.size; ++i) {
    card *tmpCard = malloc(sizeof(card));
    *tmpCard = testDeck.deck[i];
    ListInsert(&cardList,&tmpCard);
  }
  DeckDestroy(&testDeck);

  ListMap(&cardList,printPtrCard,stdout);
  fprintf(stdout,"\n");

  fprintf(stdout,"\n\x1b[35mNow we use ListSort with compare function cmpPtrCard to sort the linked list\x1b[m\n");
  ListSort(&cardList,cmpPtrCard);

  ListMap(&cardList,printPtrCard,stdout);
  fprintf(stdout,"\n");

  fprintf(stdout,"\n\x1b[35mNext, we remove a card from the deck at position 11\x1b[m\n");
  card *cardReturned = NULL;
  ListRemoveNth(&cardList,(void*)&cardReturned,11);

  fprintf(stdout,"\x1b[35mThe removed card is: \x1b[m\t\t\t\t\t\t\t");
  fprintf(stdout,"\x1b[35mRemovedCard: \x1b[m%d%c \n",cardReturned->value, cardReturned->suit);

  fprintf(stdout,"\x1b[35mThe list now looks like this:\x1b[m\n\n");
  ListMap(&cardList,printPtrCard,stdout);
  fprintf(stdout,"\n");

  fprintf(stdout,"\n\x1b[35mFinally, we dispose the list ... \x1b[m");
  ListDispose(&cardList);
  fprintf(stdout,"\x1b[35mDone!\x1b[m\n");

  fprintf(stdout,"\x1b[35mBecause we're working with pointer, the Removed Card is still here\x1b[m\t");
  fprintf(stdout,"\x1b[35mRemovedCard: \x1b[m%d%c \n",cardReturned->value, cardReturned->suit);

  fprintf(stdout,"\x1b[31mBUT\x1b[m\x1b[35m, since we took ownership, we still need to free it as the caller ... \x1b[m");
  free(cardReturned);
  fprintf(stdout,"\x1b[35mDone!\x1b[m\n");


}

int main() {

  system("clear");

  SimpleTest_pointers();
  TestingALargeLinkedList_pointers();
  TestStringList();
  StructTest_pointers();
}
