#include "card.h"
using namespace std;

///Damon Jones 2014 INB371
///Card Class Implementation - card.cpp

///This class represent a playing card and stores Rank and Suit Information.


///No argument constructor.
Card::Card(){
    suit = Clubs;
    rank = Two;
}

///Destructor – does nothing as no objects are created dynamically by the constructor of this class.
Card::~Card(){
}

///Constructor that sets the rank and suit for a Card object.
 Card::Card(Rank rankp, Suit suitp){
     //Set suit
    suit = suitp;

    //Set rank
    rank = rankp;
}

///Constructor that sets the rank and suit for a Card object from an input string.
/// Only works with 2 digit strings.
Card::Card(string card){
    //Get and Set the Rank.
    switch(card[1]){
    case 'C':
        suit = Clubs;
        break;
    case 'D':
        suit = Diamonds;
        break;
    case 'H':
        suit = Hearts;
        break;
    case 'S':
        suit = Spades;
        break;
    }

    //Get and Set the Suit.
    switch(card[0]){
    case '2':
        rank = Two;
        break;
    case '3':
        rank = Three;
        break;
    case '4':
        rank = Four;
        break;
    case '5':
        rank = Five;
        break;
    case '6':
        rank = Six;
        break;
    case '7':
        rank = Seven;
        break;
    case '8':
        rank = Eight;
        break;
    case '9':
        rank = Nine;
        break;
    case 'T':
        rank = Ten;
        break;
    case 'J':
        rank = Jack;
        break;
    case 'Q':
        rank = Queen;
        break;
    case 'K':
        rank = King;
        break;
    case 'A':
        rank = Ace;
        break;
    }
}

///Accessor for the Rank instance variable.
Rank Card::getRank(){
    return rank;
}

///Accessor for the Suit instance variable.
Suit Card::getSuit(){
    return suit;
}

///Overloads the function operator to provide a comparison which sets an ordering between
/// two Card objects.
bool Card::operator()(Card* primary, Card* secondary){
    //if first card Suit is more valueable.
    if (primary->getSuit() > secondary->getSuit()){
        return true;

    //if second card suit is more valueable.
    }else if (primary->getSuit() < secondary->getSuit()){
        return false;

    //if same suit.
    }else{
        //first card rank is higher.
        if (primary->getRank() > secondary->getRank()){
            return true;

        //second card rank is higher.
        }else{
            return false;
        }
    }
}

///Puts a string representation of this Card on the output stream.
ostream& operator<<(ostream& out, Card& card){
    string value;
    //Get and Output the rank.
    switch(card.getRank()){
    case Two:
        value = "2";
        break;
    case Three:
        value = "3";
        break;
    case Four:
        value = "4";
        break;
    case Five:
        value = "5";
        break;
    case Six:
        value = "6";
        break;
    case Seven:
        value = "7";
        break;
    case Eight:
        value = "8";
        break;
    case Nine:
        value = "9";
        break;
    case Ten:
        value = "T";
        break;
    case Jack:
        value = "J";
        break;
    case Queen:
        value = "Q";
        break;
    case King:
        value = "K";
        break;
    case Ace:
        value = "A";
        break;
    }

    //Get and Output the suit.
    switch (card.getSuit()){
    case Clubs:
        value += "C";
        break;
    case Diamonds:
        value += "D";
        break;
    case Hearts:
        value += "H";
        break;
    case Spades:
        value += "S";
        break;
    }
    out << value;
    return out;
}
