SOURCE := linkedListTest.c
SOURCE1 := linkedList.c
SRCEXT := /Users/schiffer/Documents/Coding/C/DeckOfCardsInC/DeckOfCards.c
HDREXT := $(SRCEXT:.c=.h)
LIB_DIR := ./libs
LIB := $(LIB_DIR)/$(notdir $(basename $(SRCEXT))).dylib
OBJ := $(SOURCE1:.c=.o)
MAIN := test$(basename $(SOURCE1))

all: $(OBJ) $(MAIN) copy_header $(LIB)

$(MAIN): $(LIB) $(OBJ) $(SOURCE)
	clang -g -I $(LIB_DIR) -o $@ $^

$(LIB): $(SRCEXT)
	clang -dynamiclib -o $@ $<

$(OBJ): $(SOURCE1)
	clang -I $(LIB_DIR) -g -c $<

copy_header:
	cp $(HDREXT) $(LIB_DIR)

clean:
	rm -fr ./??*.dSYM -f ./??*.o  $(MAIN) 
