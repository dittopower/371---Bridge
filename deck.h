#include <iostream>
#include <iomanip>
#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "random.h"

///Damon Jones 2014 INB371
///Deck Class Header - deck.h

///The deck class is responsible for the creation, storage and managagement of card objects.


class Deck
{
    public:
        ///No Argument constructor – Creates a dynamically allocated array of Card* objects and initialises
        /// all instance variables.
        Deck();

        ///Destructor – deletes the contents of the array of Card* pointers.
        ~Deck();

        ///Sets cardsDealt to 0.
        void reset();

        ///Returns a pointer to the next Card object from the deck, increments cardsDealt.
        Card* dealNextCard();

        ///Shuffles the cards in the deck.
        void shuffle();

        ///Puts a string representation of the Card objects in the deck to the screen.
        friend std::ostream& operator<<(std::ostream& out, Deck& deck);

        ///Reads 52 strings from an input stream, where each string represents a card e.g. 2C, AD, JH,
        /// constructing a Card* and assigning them into the array of Card* pointers.
        friend std::istream& operator>>(std::istream& in, Deck& deck);

    private:
        ///Instance Variables
        Card* cardDeck[52];
        int cardsDealt;
        int maxCards;
};

#endif // DECK_H
