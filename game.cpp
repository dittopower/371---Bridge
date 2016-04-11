#include "game.h"
using namespace std;

///Damon Jones 2014 INB371
///Game Class Implementation - game.cpp

///The Game class is responsible for providing the main functionality of the game.
///It holds the Deck object and the array of Hands for the game. It also Tracks of
/// which Position is currently the dealer and stores the opening bid and who made
/// the bid.


///No args constructor, initialises the dynamic array of Hands and sets dealer to NORTH.
Game::Game()
{
    //Initialise hands
    players[North] = new Hand();
    players[East] = new Hand();
    players[South] = new Hand();
    players[West] = new Hand();

    //Set dealer
    dealer = North;
}

///Destructor, discards the array.
Game::~Game()
{
    players[North]->clear();
    players[East]->clear();
    players[South]->clear();
    players[West]->clear();
    delete players;
}

///If input is NOT to be read from a file, shuffle the deck. Call the reset method on the
/// deck. Also clears each Hand.
void Game::setup(bool fromfile){
    //If not a premade deck, shuffle it
    if (!fromfile){
        deck.shuffle();
    }
    //Ensure cards dealt is reset to 0.
    deck.reset();

    //Ensure no player already has any cards
    for (int i = 0; i < NUMPLAYERS;i++){
        players[i]->clear();
    }
}

///Deals the cards from the deck clockwise to each player in turn starting with the player
/// on the dealer’s left.
void Game::deal(){
    const int HANDSIZE = 13;
    //Interate throught the number of card that need to be dealt to each player
    for (int i = 0; i < HANDSIZE; i++){

        //Iterate through all players starting with the next player to the dealers left.
        for (int player = (dealer + 1); player <= (dealer + NUMPLAYERS) ; player++){

            //Deal each player a card.
            players[player % NUMPLAYERS]->addCard(deck.dealNextCard());
        }
    }
}

///Starting with the dealer, calls makeBid() to see what bid is made. If a bid other than
/// 'Pass' is received from the current Hand, the auction can stop.
void Game::auction(){
    //Default bid is pass
    bid = "PASS";

    //Iterate through players starting with the dealer
    for (int player = dealer; player < (dealer + NUMPLAYERS); player++){

        //Get the player's bid
        bid = players[player % NUMPLAYERS]->makeBid();

        //If A player Bids other than pass, that is the opening bid end the auction.
        if (bid != "PASS"){

            //Save who made the openning bid.
            Winner = Position(player % NUMPLAYERS);
            break;
        }
    }
}

///Increments the dealer Position to the next player.
void Game::nextDealer(){
    //Iterate the dealer.
    dealer = Position((int(dealer) + 1) % NUMPLAYERS);
}

///Puts a string representation of the game onto the output stream.
ostream& operator<<(ostream& out, Game& game){
    //Iterate throught players
    for (int player = game.dealer; player < (game.dealer + game.NUMPLAYERS); player++){

        //Get and output the player's name/position
        out << game.getPlayerName(Position(player % game.NUMPLAYERS)) << endl;

        //Output the player's hand
        out << *game.players[player % game.NUMPLAYERS] << endl;
    }
    //Output the opening bid and who made it or that everyone passed.
    if (game.bid != "PASS"){
        out << endl << "Opening Bid is " << game.bid << " made by " << game.getPlayerName(game.Winner) << endl;
    }else{
        out << "All hands PASS" << endl;
    }
    return out;
}

///Returns the Players "name" or position as a string.
string Game::getPlayerName(Position player){
    string temp;
    //Return string version of player/position.
    switch(player){
        case North:
            temp = "NORTH";
            break;
        case East:
            temp = "EAST";
            break;
        case South:
            temp = "SOUTH";
            break;
        case West:
            temp = "WEST";
            break;
        default:
            temp = "";
            break;
        }
        return temp;
}

///Passes the input stream onto the deck so that the cards can be read from a text file.
istream& operator>>(istream& in, Game& game){
    //Pass through to deck istream.
    in >> game.deck;
    return in;
}
