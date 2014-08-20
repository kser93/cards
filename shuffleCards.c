/*Emulation of mixing cards*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ERRINPUT 1
#define DECKCOUNT 54
#define MIXCOUNT 20
#define MIXCYCLMIN 3
#define MIXCYCLMAX 6
#define ROWS 6

char *suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
char *ranks[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

void printDeck(int *deck, int deckSize);
int shuffleDeck(int *deck, int deckSize);

int main()
{
	int deckSize = DECKCOUNT;
	int deck[deckSize];
	int code = shuffleDeck(deck, deckSize);
	return code;
}


int shuffleDeck(int *deck, int deckSize)
{
	for (int i = 0; i < deckSize; ++i)
		deck[i] = i;
	printDeck(deck, deckSize);
	srand(time(NULL));
	int *buf = (int *)malloc(deckSize * sizeof(int));
	int mixCount = MIXCOUNT;
	if (mixCount <= 0)
		return ERRINPUT;
	for (;mixCount > 0; --mixCount)
	{
		int shift = rand() % deckSize;
		int shiftCycles = MIXCYCLMIN + rand() % (MIXCYCLMAX - MIXCYCLMIN);
		memcpy(buf, deck, shift * sizeof(int));
		memmove(deck, deck + shift, (deckSize - shift) * sizeof(int));

		for (int i = shiftCycles; (shift > 0) && (i > 0); --i)
		{
			int miniShift = rand() % (shift + 1);
			memcpy(deck + deckSize - shift, buf + shift - miniShift, miniShift * sizeof(int));
			shift -= miniShift;
		}
		memcpy(deck + deckSize - shift, buf, shift * sizeof(int));
	}
	printDeck(deck, deckSize);
	free(buf);
	return 0;
}

void printDeck(int *deck, int deckSize)
{
	for (int i = 0; i < deckSize; ++i)
	{
		char cardName[20] = "\0";
		switch(deck[i])
		{
		case 52:
			strcat(cardName, "Joker of Black");
			break;
		case 53:
			strcat(cardName, "Joker of Red");
			break;
		default:
			strcat(cardName, ranks[deck[i] % 13]);
			strcat(cardName, " of "); 
			strcat(cardName, suits[deck[i] / 13]);
			break;
		}
		printf("%-20s", cardName);
		if (!((i + 1) % ROWS))
			putchar('\n');
	}
	putchar('\n');
}

