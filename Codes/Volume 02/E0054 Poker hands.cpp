# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
 In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:

 High Card: Highest value card.
 One Pair: Two cards of the same value.
 Two Pairs: Two different pairs.
 Three of a Kind: Three cards of the same value.
 Straight: All cards are consecutive values.
 Flush: All cards of the same suit.
 Full House: Three of a kind and a pair.
 Four of a Kind: Four cards of the same value.
 Straight Flush: All cards are consecutive values of same suit.
 Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
 The cards are valued in the order:
 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

 If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of eights beats a pair of 
 fives (see example 1 below). But if two ranks tie, for example, both players have a pair of queens, then highest cards in each hand are 
 compared (see example 4 below); if the highest cards tie then the next highest cards are compared, and so on.

 Consider the following five hands dealt to two players:

 Hand	 	Player 1	 	Player 2	 	 Winner
 1	 	5H 5C 6S 7S KD   2C 3S 8S 8D TD      Player 2
         Pair of Fives    Pair of Eights 

 2	 	5D 8C 9S JS AC 	 2C 5C 7D 8S QH      Player 1
        Highest card Ace Highest card Queen 

 3	 	2D 9C AS AH AC   3D 6D 7D TD QD      Player 2
           Three Aces    Flush with Diamonds 

 4	 	4D 6S 9H QH QC   3D 6D 7H QD QS      Player 1
         Pair of Queens    Pair of Queens 
       Highest card Nine Highest card Seven 

 5	 	2H 2D 4C 4D 4S   3C 3D 3S 9S 9D      Player 1
           Full House       Full House 
       With Three Fours  with Three Threes 

 The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the file contains ten cards (separated by a 
 single space): the first five are Player 1's cards and the last five are Player 2's cards. You can assume that all hands are valid (no 
 invalid characters or repeated cards), each player's hand is in no specific order, and in each hand there is a clear winner.

 How many hands does Player 1 win?
*/

class pokerHand{
private:
    static int value(char v){
        if(isdigit(v)) return v-'0';
        switch(v){
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case 'A':
            return 14;
        default:
            return -1;
        }
    }

    static bool cardComparator(const string &card1, const string &card2){
        return make_pair(value(card1[0]), card1[1]) < make_pair(value(card2[0]), card2[1]);
    }

    bool isHighCard(){
        rank = HIGH_CARD;
        for(int i = 4; i>=0; i--){
            tieBraker.push_back(value(cards[i][0]));
        }
        return true;
    }

    bool isOnePair(){
        for(int i = 0; i<4; i++){
            if(value(cards[i][0]) != value(cards[i+1][0])) continue;
            rank = ONE_PAIR;
            tieBraker.push_back(value(cards[i][0]));
            for(int j = 4; j>=0; j--){
                if(j == i || j == i+1) continue;
                tieBraker.push_back(value(cards[j][0]));
            }
            return true;
        }
        return false;
    }

    bool isTwoPairs(){
        for(int i = 0; i<5; i+=2){
            int j1 = ((i == 0)? 1 : 0);
            int j2 = ((i == 4)? 2 : 3);
            if(value(cards[j1][0]) != value(cards[j1+1][0])) continue;
            if(value(cards[j2][0]) != value(cards[j2+1][0])) continue;
            rank = TWO_PAIRS;
            tieBraker.push_back(value(cards[j2][0]));
            tieBraker.push_back(value(cards[j1][0]));
            tieBraker.push_back(value(cards[i][0]));
            return true;
        }
        return false;
    }

    bool isThreeOfAKind(){
        for(int i = 0; i<3; i++){
            if(value(cards[i][0]) != value(cards[i+2][0])) continue;
            rank = THREE_OF_A_KIND;
            tieBraker.push_back(value(cards[i][0]));
            int j1 = ((i == 0)? 3 : 0);
            int j2 = ((i == 2)? 1 : 4);
            tieBraker.push_back(value(cards[j2][0]));
            tieBraker.push_back(value(cards[j1][0]));
            return true;
        }
        return false;
    }

    bool isStraight(){
        for(int i = 0; i<4; i++) if(value(cards[i][0]) != value(cards[i+1][0])-1) return false;
        rank = STRAIGHT;
        tieBraker.push_back(value(cards[4][0]));
        return true;
    }

    bool isFlush(){
        for(int i = 0; i<4; i++) if(cards[i][1] != cards[i+1][1]) return false;
        rank = FLUSH;
        for(int i = 4; i>=0; i--) tieBraker.push_back(value(cards[i][0]));
        return true;
    }

    bool isFullHouse(){
        for(int i = 0; i<3; i+=2){
            int j = ((i == 0)? 3 : 0);
            if(value(cards[i][0]) != value(cards[i+2][0]) || value(cards[j][0]) != value(cards[j+1][0])) continue;
            rank = FULL_HOUSE;
            tieBraker.push_back(value(cards[i][0]));
            tieBraker.push_back(value(cards[j][0]));
            return true;
        }
        return false;
    }

    bool isFourOfAKind(){
        for(int i = 0; i<2; i++){
            if(value(cards[i][0]) != value(cards[i+3][0])) continue;
            rank = FOUR_OF_A_KIND;
            tieBraker.push_back(value(cards[i][0]));
            int j = ((i == 0)? 4 : 0);
            tieBraker.push_back(value(cards[j][0]));
            return true;
        }
        return false;
    }

    bool isStraightFlush(){
        if(value(cards[4][0]) - value(cards[0][0]) != 4) return false;
        for(int i = 0; i<4; i++) if(cards[i][1] != cards[i+1][1]) return false;
        rank = STRAIGHT_FLUSH;
        tieBraker.push_back(value(cards[4][0]));
        return true;
    }

    bool isRoyalFlush(){
        if(value(cards[0][0]) != 10 || value(cards[4][0]) != 14) return false;
        for(int i = 0; i<4; i++) if(cards[i][1] != cards[i+1][1]) return false;
        rank = ROYAL_FLUSH;
        return true;
    }

public:
    enum RANK{INVALID, HIGH_CARD, ONE_PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, 
              FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH};
    
    vector<string> cards;
    pokerHand(vector<string> shuffledCards){
        assert(shuffledCards.size() == 5);
        cards = shuffledCards;
        sort(cards.begin(), cards.end(), cardComparator);

        rank = INVALID;
        if(isRoyalFlush()) return;
        else if(isStraightFlush()) return;
        else if(isFourOfAKind()) return;
        else if(isFullHouse()) return;
        else if(isFlush()) return;
        else if(isStraight()) return;
        else if(isThreeOfAKind()) return;
        else if(isTwoPairs()) return;
        else if(isOnePair()) return;
        else if(isHighCard()) return;
    }

    RANK getRank(){
        return rank;
    }

    const bool operator<(const pokerHand &other){
        if(rank != other.rank) return rank < other.rank;
        else return tieBraker < other.tieBraker;
    }
private:
    vector<int> tieBraker;
    RANK rank;
};

vector<string> tokenizeWithChar(string &text, char delim){
    vector<string> ret;
    stringstream ss(text);
    std::string parts;
    while(getline(ss, parts, delim))
        ret.push_back(parts);
    return ret;
}

vector<vector<string>> parseStringGrid(string grid){
    vector<vector<string>> retGrid;
    vector<string> rows = tokenizeWithChar(grid, '\n');
    for(string &row : rows){
        vector<string> words = tokenizeWithChar(row, ' ');
        retGrid.push_back(vector<string>());
        for(string &word : words){
            retGrid.back().push_back(word);
        }
    }
    return retGrid;
}

int countWinningHands(string filePath, int player){
    fstream file(filePath);
    string contents;
    if(file.is_open()){
        getline(file, contents, '\0');
        file.close();
    }
    vector<vector<string>> games = parseStringGrid(contents);
    
    int winCount = 0;
    for(auto &game : games){
        pokerHand hand1(vector<string>(game.begin(), game.begin()+5));
        pokerHand hand2(vector<string>(game.begin()+5, game.begin()+10));
        if(player == 1) winCount += (hand2 < hand1);
        else            winCount += (hand1 < hand2);
    }

    return winCount;
}

int main(){
    Time(
        cout<<countWinningHands("..\\..\\Data\\D0054 Poker hands.txt", 1)<<endl;
    )
    return 0;
}