#ifndef CARD_H
#define CARD_H
#include <string>

///Damon Jones 2014 INB371
///Card Class Header - card.h

///This class represent a playing card and stores Rank and Suit Information.


///Define Card Ranks and Suits
enum Rank {Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};
enum Suit {Clubs, Diamonds, Hearts, Spades};

class Card
{
    public:
        ///No argument constructor.
        Card();

        ///Constructor that sets the rank and suit for a Card object.
        Card(Rank rankp, Suit suitp);

        ///Constructor that sets the rank and suit for a Card object from an input string.
        Card(std::string card);

        ///Destructor
        ~Card();

        ///Accessor for the Rank instance variable.
        Rank getRank();

        ///Accessor for the Suit instance variable.
        Suit getSuit();

        ///Overloads the function operator to provide a comparison which sets an ordering between
        /// two Card objects.
        bool operator()(Card*, Card*);

        ///Puts a string representation of this Card on the output stream.
        friend std::ostream& operator<<(std::ostream& out, Card& card);

    private:
        ///Variables to store this cards value.
        Rank rank;
        Suit suit;
};

#endif // CARD_H
