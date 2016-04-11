#include "deck.h"
using namespace std;

///Damon Jones 2014 INB371
///Deck Class Implementation - deck.cpp

///The deck class is responsible for the creation, storage and managagement of card objects.


///No Argument constructor – Creates a dynamically allocated array of Card* objects and initialises
/// all class variables.
Deck::Deck(){
    //Initialise variables.
    cardsDealt = 0;
    maxCards = 52;

    //Iterate through the card suits.
    for (int s = 0; s < 4; s++){

        //Iterate through the card ranks.
        for (int r = 0; r < 13; r++){

            //Create one card of each suit & rank and assign it to the deck.
            Card* newCard = new Card(Rank(r),Suit(s));
            cardDeck[(s*13)+r] = newCard;
        }
    }
}

///Destructor – deletes the contents of the array of Card* pointers.
Deck::~Deck(){
    //Iterate through the deck deleting the contents.
    for (int i = 0; i < maxCards; i++){
        delete cardDeck[i];
    }
    delete cardDeck;
}

///Sets cardsDealt to 0.
void Deck::reset(){
    cardsDealt = 0;
}

///Returns a pointer to the next Card object from the deck, increments cardsDealt.
Card* Deck::dealNextCard(){
    //Get card reference.
    Card* temp = cardDeck[cardsDealt];

    //Increment cardsDealt.
    cardsDealt++;

    return temp;
}

///Shuffles the cards in the deck.
void Deck::shuffle(){
    //Initialise random object and temp card* pointer.
    Random rant;
    Card* temp;

    //Swap cards a more times than cards in the deck.
    for (int i = 0; i < maxCards*3/2; i++){

        //Get random card indexes.
        int firstIndex = rant.randomInteger(0,(maxCards-1));
        int secondIndex = rant.randomInteger(0,(maxCards-1));

        //Swap card pointers.
        temp = cardDeck[firstIndex];
        cardDeck[firstIndex] = cardDeck[secondIndex];
        cardDeck[secondIndex] = temp;
    }
}

///Puts a string representation of the Card objects in the deck to the screen.
ostream& operator<<(ostream& out, Deck& deck){
    Card* temp;

    //Interate through deck.
    for (int i = 0; i < deck.maxCards; i++){

        //Assign to tempary variable and output.
        temp = deck.cardDeck[i];
        out << *temp << " ";
    }
    return out;
}

///Reads 52 strings from an input stream, where each string represents a card e.g. 2C, AD, JH,
/// constructing a Card* and assigning them into the array of Card* pointers.
istream& operator>>(istream& in, Deck& deck){
    string textInput;

    //Repeat 52 times/ once for each card in the deck
    for (int i = 0; i < deck.maxCards; i++){

        //Get Input in string
        in >> textInput;

        //Create card from string and assign it to the deck.
        deck.cardDeck[i] = new Card(textInput);
    }
    return in;
}
