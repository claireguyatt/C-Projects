#include <iostream>
#include <list>
#include <iterator>
#include <random>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// enums used for Card attributes
enum Rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum Type {CLUBS, DIAMONDS,HEARTS, SPADES};

class Card
{
public:
    Card(Type type, Rank rank);
    int getValue();
    void displayCard();

private:
    Rank rank;
    Type type;
};

// constructor using input paramaters
Card::Card(Type type, Rank rank) : rank(rank), type(type)
{
}

// get method for Card's rank
int Card::getValue() { return rank; }

// display a Card
void Card::displayCard() {
    switch (this->rank) 
    {
        case ACE: cout << "1";
            break;
        case TWO: cout << "2";
            break;
        case THREE: cout << "3";
            break;
        case FOUR: cout << "4";
            break;
        case FIVE: cout << "5";
            break;
        case SIX: cout << "6";
            break;
        case SEVEN: cout << "7";
            break;
        case EIGHT: cout << "8";
            break;
        case NINE: cout << "9";
            break;
        case TEN: cout << "10";
            break;
        case JACK: cout << "11";
            break;
        case QUEEN: cout << "12";
            break;
        case KING: cout << "13";
    }
    switch(this->type)
    {
        case CLUBS: cout << "C ";
            break;
        case DIAMONDS: cout << "D ";
            break;
        case HEARTS: cout << "H ";
            break;
        case SPADES: cout << "S ";
    }
}

class Hand
{
public:
    void add(Card newCard);
    void clear();
    int getTotal();
    void displayHand();

private:
    list<Card> cards;
};

// add a new card to the hand (end of the card list)
void Hand::add(Card newCard)
{
cards.push_back(newCard);
}

// clear hand (remove all cards from card list)
void Hand::clear() 
{
    cards.clear();
}

// calculate the total value of the set of cards in the
int Hand::getTotal()
{
    int total = 0;
    int aceCount = 0;
    // loop through cards in the hand using an iterator
    list<Card>::iterator iter = cards.begin(); 
    while (iter != cards.end()) 
    {
        // retrieve the Card the iterator is pointing at
        Card& c = *iter;
        // add the value of the card to the total value
        // special case for aces
        if (c.getValue() == ACE)
        {
            aceCount++;
        }
        else if (c.getValue() == JACK || c.getValue() == QUEEN || c.getValue() == KING) total += 10;
        else total += c.getValue();
        // move to the next Card in the hand
        iter++;
    }
    // calculate aces by getting as high as possible without going over 21
    for (int i = 0; i<aceCount; i++)
    {
        if (total + 10 > 21-(aceCount-1-i)) total = total+1;
        else total = total+10;
    }
    return total;
}

// display a hand of Cards
void Hand::displayHand()
{
    list<Card>::iterator iter = cards.begin();
    while (iter != cards.end())
    {
        Card& c = *iter;
        c.displayCard();
        iter++;
    }
    cout << "\n";
}

class Deck
{
public:
    void populate();
    void shuffle();
    Card deal(Hand* hand);
private:
    list<Card> cards;
};

// fill a fresh Deck of cards
void Deck::populate()
{
    Card temp = Card(CLUBS, ACE);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 14; j++) {
            temp = Card(Type(i), Rank(j));
            cards.push_back(temp);
        }
    }
}

// shuffle the Cards in the Deck
void Deck::shuffle()
{
    // copy list of Cards into a vector and shuffle it
    std::vector<Card> temp(cards.begin(), cards.end());
    std::random_shuffle(temp.begin(), temp.end());

    // copy the shuffled vector back into the list
    std::copy(temp.begin(), temp.end(), cards.begin());
}

// deal a Card from the Deck to the input Hand
Card Deck::deal(Hand* hand) 
{
    // access top Card in the deck (last card in the list)
    Card temp = cards.back();

    // remove card from the deck (Card list)
    // and add it to the input Hand of Cards
    cards.pop_back();
    hand->add(temp);
    return temp;
}

class AbstractPlayer
{
public:
    // *****
    // need to figure out how to add const
    AbstractPlayer();
    virtual ~AbstractPlayer();
    virtual bool isDrawing() = 0;
    bool isBusted();
    Hand* getHand();
private:
    Hand* hand;
};

// constructor
AbstractPlayer::AbstractPlayer() : hand(new Hand)
{
}

// destructor
AbstractPlayer::~AbstractPlayer() { delete hand; }

bool AbstractPlayer::isBusted()
{
    if (hand->getTotal() > 21) return true;
    else return false;
}

// getter method for a player's Hand
Hand* AbstractPlayer::getHand() { return hand; }

class ComputerPlayer : public AbstractPlayer
{
public:
    bool isDrawing();
private:
};

// overridden virtual method from base class
// decide whether comp should draw again
bool ComputerPlayer::isDrawing()
{
    if (this->getHand()->getTotal() <= 16) 
    {
        cout << "Casino is drawing another card. \n";
        return true;
    }
    else return false;
}

class HumanPlayer : public AbstractPlayer
{
public:
    bool isDrawing();
    void announce(ComputerPlayer* comp, bool gameOver);
private:
};

// overridden virtual method from base class
// determine if player would like to draw another card
bool HumanPlayer::isDrawing()
{
    cout << "The sum of your hand is: ";
    cout << this->getHand()->getTotal() << "\n";
    cout << "Would you like to draw another card? (y/n)";
    char a;
    cin >> a;
    return (a == 'y' ? true : false);
}

// display any game updates to the player
void HumanPlayer::announce(ComputerPlayer* comp, bool gameOver)
{
    // if they lost
    if (this->isBusted()) cout << "You've exceeded 21, you lose!";
    // if they won
    else if (comp->isBusted()) cout << "Casino has exceeded 21, you win!";
    // if the game is over
    if (gameOver == false)
    {
        int compTotal = comp->getHand()->getTotal();
        int playerTotal = this->getHand()->getTotal();
        cout << "Your total is " << playerTotal << "\n";
        cout << "Casino's total is " << compTotal << "\n";
        if (compTotal > playerTotal) cout << "You lose!\n";
        else if (compTotal < playerTotal) cout << "You win!\n";
        else cout << "No one wins!";
    }
}

class BlackJackGame
{
public:
    BlackJackGame();
    ~BlackJackGame();
    void play();
private:
    Deck* m_deck;
    ComputerPlayer* m_casino;
};

// constructor
BlackJackGame::BlackJackGame()
{
    // create a new Deck object, populate it with a fresh deck of Cards, & shuffle it twice for good measure
    m_deck = new Deck;
    m_deck->populate();
    m_deck->shuffle();
    m_deck->shuffle();
    // create a new casino (comp player)
    m_casino = new ComputerPlayer(); 
}

// destructor
BlackJackGame::~BlackJackGame()
{
    delete m_deck;
    delete m_casino;
}

void BlackJackGame::play()
{
    // create Human player & a bool to keep track of the game
    HumanPlayer* human = new HumanPlayer();
    bool gameOver = false;
    
    // deal Human 2 cards & comp 1 card
    m_deck->deal(human->getHand());
    m_deck->deal(human->getHand());
    m_deck->deal(m_casino->getHand());
    
    // update the player
    cout << "You have been dealt: ";
    human->getHand()->displayHand();
    cout << "The casino has been dealt: ";
    m_casino->getHand()->displayHand();
    
    // continue dealing to the player until they're done
    bool drawAgain = human->isDrawing();
    while (drawAgain == true && gameOver == false)
    {
        Card temp = m_deck->deal(human->getHand());
        cout << "You have been dealt: ";
        temp.displayCard();
        cout << "\n";
        // continue to check if player has busted
        if (human->isBusted()) {
            gameOver = true;
            human->announce(m_casino, gameOver);
        }
        if (gameOver == false) drawAgain = human->isDrawing();
    }
    drawAgain = true;
    // when player is done, deal to comp
    while (drawAgain == true && gameOver == false)
    {
        Card temp = m_deck->deal(m_casino->getHand());
        cout << "Casino drew a ";
        temp.displayCard();
        cout << "\n";
        // continue to check if comp has busted
        if (m_casino->isBusted()) {
            gameOver = true;
            human->announce(m_casino, gameOver);
        }
        if (gameOver == false) drawAgain = m_casino->isDrawing();
    }
    // check totals if game hasn't ended
    if (gameOver == false) human->announce(m_casino, gameOver); 
    human->getHand()->clear();
    m_casino->getHand()->clear(); 
}


int main()
{
    cout << "\tWelcome to the Comp322 Blackjack game!" << endl << endl;
    
    BlackJackGame game;
    
    // The main loop of the game
    bool playAgain = true;
    char answer = 'y';
    while (playAgain)
    {
        game.play();
    
        // Check whether the player would like to play another round
        cout << "Would you like another round? (y/n): ";
        cin >> answer;
        cout << endl << endl;
        playAgain = (answer == 'y' ? true : false);
    }
    cout <<"Game over!";
}