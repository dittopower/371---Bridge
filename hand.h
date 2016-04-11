#ifndef HAND_H
#define HAND_H
#include <vector>
#include <iostream>
#include <iomanip>
#include "card.h"

///Damon Jones 2014 INB371
///Hand Class Header - hand.h

///The Hand class is responsible for storing the cards dealt to a particular player and
/// determining the bid that the hand can make using the bidding logic provided.

class Hand
{
    public:
        ///Constructor
        Hand();

        ///Destructor
        ~Hand();

        ///Clears all of the suit collections, resets any instance variables to their initial values.
        void clear();

        ///Adds a Card* to the Hand placing the card with other cards of the same suit.
        void addCard(Card* card);

        ///Responsible for implementing the bidding logic and for deciding on the bid to be made for this hand.
        ///That bid could be PASS. Returns the bid as a string.
        std::string makeBid();

        ///Puts a string representation of a Hand on the output stream.
        friend std::ostream& operator<<(std::ostream& out, Hand& hand);

    private:
        ///Suit Collections
        std::vector<Card*> clubs;
        std::vector<Card*> diamonds;
        std::vector<Card*> hearts;
        std::vector<Card*> spades;

        ///Calculates and adds to handstrength for bidding decisions.
        void addSuitStrength(int& strength, std::vector<Card*> storage);

        ///Checks if the hand's suit composition is balanced and
        /// sets the longest suit and its length.
        bool balanced(Suit& suit, int& length);

        ///Reuseable code section for placing a bid with balanced hand of 13-14 or 18-19 strength.
        void bidMinorSuit(std::string& bid);
};

#endif // HAND_H
