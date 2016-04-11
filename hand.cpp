#include "hand.h"
#include <algorithm>
using namespace std;

///Damon Jones 2014 INB371
///Hand Class Implmentation - hand.cpp

///The Hand class is responsible for storing the cards dealt to a particular player and
/// determining the bid that the hand can make using the bidding logic provided.

//No arguments constructor, initialises all suit collections.
Hand::Hand(){
    //Class variable listed in the header file are automatic created when this object is.
}

///Destructor – deletes each Card* in the Hand.
Hand::~Hand(){
    //Delete elements from each vector until the vector is empty.
    while (!clubs.empty()){
        clubs.pop_back();
    }
    while (!diamonds.empty()){
        diamonds.pop_back();
    }
    while (!hearts.empty()){
        hearts.pop_back();
    }
    while (!spades.empty()){
        spades.pop_back();
    }
}

///Clears all of the suit collections, resets any instance variables to their initial values.
void Hand::clear(){
    //run the clear method for each vector.
    clubs.clear();
    diamonds.clear();
    hearts.clear();
    spades.clear();
}

///Adds a Card* to the Hand placing the card with other cards of the same suit.
void Hand::addCard(Card* card){
    //Check which suit the card is and put it in the right collection.
        //Add the card
        //Sort that suit
    switch(card->getSuit()){
    case Clubs:
        clubs.push_back(card);
        sort(clubs.begin(),clubs.end(),Card());
        break;

    case Diamonds:
        diamonds.push_back(card);
        sort(diamonds.begin(),diamonds.end(),Card());
        break;

    case Hearts:
        hearts.push_back(card);
        sort(hearts.begin(),hearts.end(),Card());
        break;

    case Spades:
        spades.push_back(card);
        sort(spades.begin(),spades.end(),Card());
        break;
    }
}

///Responsible for implementing the bidding logic and for deciding on the bid to be made for this hand.
///That bid could be PASS. Returns the bid as a string.
string Hand::makeBid(){
    int strength = 0;
    //Calculate hand strength.
    addSuitStrength(strength,clubs);
    addSuitStrength(strength,diamonds);
    addSuitStrength(strength,hearts);
    addSuitStrength(strength,spades);

    Suit longSuit;
    int longLength = 0;
    //Default bid set to pass.
    string bid = "PASS";
    //check if had is balanced.
    if (balanced(longSuit, longLength)){
        //Balance: Strength 0-12 pass.
        if (strength <= 12){
            //bid is already pass.

        //Balance: Strength 13-14 bid minor suit.
        }else if (strength <= 14){
            bidMinorSuit(bid);

        //Balance: Strength 15-17 bid 1NT.
        }else if (strength <= 17){
            bid = "1 NT";

        //Balance: Strength 18-19 bid minor suit.
        }else if (strength <= 19){
            bidMinorSuit(bid);

        //Balance: Strength 20-21 bid 2NT.
        }else if (strength <= 21){
            bid = "2 NT";

        //Balance: Strength 22+ bid 2C.
        }else if (strength >= 22){
            bid = "2C";

        }
    //Unbalanced
    }else{
        const string suits[] = {"C","D","H","S"};
        //Unbalanced: strength 0-12, length 6/7/8 bid 2/3/4 others pass
        //In a tie the higher value suit is bid.
        //The suit length/value calcuations were saved during balanced hand calculations.
        if (strength <= 12){
            switch(longLength){
            case 6:
                //Any 6-card suit but clubs, bid 2.
                if (!(Suit(longSuit)==Clubs)){
                    bid = "2" + suits[longSuit];
                }
                break;

            case 7:
                //Any 7-card suit, bid 3.
                bid = "3" + suits[longSuit];
                break;

            case 8:
                //Any 8-card suit bid 4.
                bid = "4" + suits[longSuit];
                break;

            default:
                break;
            }

        //Unbalanced: strength 13-21, bid 1 longest suit
        //In a tie with length 4 the lowest value suit is used, otherwise the highest is used.
        //The suit length/value calcuations were saved during balanced hand calculations.
        }else if (strength <= 21){
            bid = "1" + suits[longSuit];

        //Unbalanced: strength 22+ bid 2C
        }else if (strength >= 22){
            bid = "2C";
        }
    }

    return bid;
}

///Calculates and adds to handstrength for bidding decisions.
void Hand::addSuitStrength(int& strength, vector<Card*> storage){
    for (int i = 0; i < storage.size(); i++){
        //Get each card reference.
        Card* temp = storage[i];

        //Give High card points
        switch(temp->getRank()){
        case Ace:
            strength+= 4;
            break;

        case King:
            strength+= 3;
            break;

        case Queen:
            strength+= 2;
            break;

        case Jack:
            strength+= 1;
            break;

        default:
            break;
        }
    }

    //Check length and give Length points for each card past the 4th.
    if (storage.size() > 4){
        strength+= storage.size() - 4;
    }
}

///Checks if the hand's suit composition is balanced and sets the longest suit and its length.
bool Hand::balanced(Suit& suit, int& length){
    //Save the sizes of the suit collections to save calculations
    const int suitSizes[] = {clubs.size(), diamonds.size(), hearts.size(), spades.size()};
    bool result = true;
    const int BalMin = 1;
    const int BalMax = 5;
    const int suits = 4;
    int twoLength = 0;

    for (int i = 0; i < (suits);i++){
        //Balanced hand suit size requirements
        if (suitSizes[i] <= BalMin || suitSizes[i] >= BalMax){
            result = false;
        //Only one suit may have 2 cards.
        }else if (suitSizes[i] == 2){
            if (twoLength++ > 1){
                result = false;
            }
        }

        if (suitSizes[i] >= length){
        //Sets the longest, highest value suit.
        //Suits are processed in ascending order so higher value suit will replace lower ones.
        //Except if the longest length is tied at 4.
            if (!(suitSizes[i] == 4 && length == 4)){
                suit = Suit(i);
                length = suitSizes[i];
            }
        }
    }
    return result;
}


///Reuseable code section for placing a bid with balanced hand of 13-14 or 18-19 strength.
void Hand::bidMinorSuit(string& bid){
    if (clubs.size() == diamonds.size()){
        //If suits are equal length:
        //  - length 3: bid 1C
        //  - length 4: bid 1D
        if (clubs.size() == 3){
            bid = "1C";
        }else{
            bid = "1D";
        }
    }else{
    //If unequal length bid 1 of the longer minor suit
        if (clubs.size() > diamonds.size()){
            bid = "1C";
        }else{
            bid = "1D";
        }
    }
}

///Puts a string representation of a Hand on the output stream.
ostream& operator<<(ostream& out, Hand& hand){
    //Representat of all spades cards.
    out << "Spades" << setw(3) << ":";
    if (!hand.spades.empty()){
        for (int i = 0;i<hand.spades.size();i++){
            out << " " << *hand.spades[i];
        }
    }

    //Representat of all heart cards.
    out << "\nHearts" << setw(3) << ":";
    if (!hand.hearts.empty()){
        for (int i = 0;i<hand.hearts.size();i++){
            out << " " << *hand.hearts[i];
        }
    }
    //Representat of all diamonds cards.
    out << "\nDiamonds" << setw(0) << ":";
    if (!hand.diamonds.empty()){
        for (int i = 0;i<hand.diamonds.size();i++){
            out << " " << *hand.diamonds[i];
        }
    }
    //Representat of all clubs cards.
    out << "\nClubs" << setw(4) << ":";
    if (!hand.clubs.empty()){
        for (int i = 0;i<hand.clubs.size();i++){
            out << " " << *hand.clubs[i];
        }
    }
    out << endl;
    return out;
}
