#ifndef GAME_H
#define GAME_H
#include "hand.h"
#include "deck.h"
#include <iostream>
#include <iomanip>

///Damon Jones 2014 INB371
///Game Class Header - game.h

///The Game class is responsible for providing the main functionality of the game.
///It holds the Deck object and the array of Hands for the game. It also Tracks of
/// which Position is currently the dealer and stores the opening bid and who made
/// the bid.

///Define Positions
enum Position {North, East, South, West};

class Game
{
    public:
        ///No args constructor, initialises the dynamic array of Hands and sets dealer to NORTH.
        Game();

        ///Destructor, discards the array.
        ~Game();

        ///If input is NOT to be read from a file, shuffle the deck. Call the reset method on the
        /// deck. Also clears each Hand.
        void setup(bool fromfile);

        ///Deals the cards from the deck clockwise to each player in turn starting with the player
        /// on the dealer’s left.
        void deal();

        ///Starting with the dealer, calls makeBid() to see what bid is made. If a bid other than
        /// 'Pass' is received from the current Hand, the auction can stop.
        void auction();

        ///Increments the dealer Position to the next player.
        void nextDealer();

        ///Puts a string representation of the game onto the output stream.
        friend std::ostream& operator<<(std::ostream& out, Game& game);

        ///Passes the input stream onto the deck so that the cards can be read from a text file.
        friend std::istream& operator>>(std::istream& in, Game& game);

    private:
        ///Storage variables
        Deck deck;

        const int NUMPLAYERS = 4;
        Hand* players[4];

        Position dealer;
        Position Winner;

        ///Current bid
        std::string bid;

        ///Returns the Players "name" or position as a string.
        std::string getPlayerName(Position player);
};

#endif // GAME_H
