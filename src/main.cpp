/* Bence Magyar "Deck of Cards" Exercise
*  
*/

#include <queue>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/* 
* Class Card:  Each card has an enumerated suit and value.  For this exercise, 
* assume that Ace has value=1, J=11, Q=12, and K=13.  This class could be 
* sub-classed to implement other games.  For example, BlackJackCard : public Card, 
* where Ace can have value of 1 or 11. 
*/
class Card{

  public: 
    
    enum Suit{ 
      DIAMONDS, SPADES, CLUBS, HEARTS
    }; 
    
    Card(short v, Suit s){
      suit = s;
      value = v;
    };
  
    short getValue() { return value; };
    Suit getSuit()  { return suit; };

    static char enum2string(Suit s){
       switch(s){
          case HEARTS:
            return 'H';
          break;
          case CLUBS:
            return 'C';
          break;
          case SPADES:
            return 'S';
          break;
          case DIAMONDS:
            return 'D';
          break;
          default:
            return 'X';
          
       }
    };

  private:
    Suit suit;
    short value;

};
/*
* Class 'Dealer'.  A dealer is given a deck of cards can be asked
* to shuffle the deck or deal one card.
*/
class Dealer{

  public:
   
    Dealer(deque<Card> cards){
      deck = cards;
    };
    
    /* Method shuffle():  This method takes the remaining cards in the deck and 
    *  randomizes them in 0(n) time:  For a deck of n cards, we select a random card 
    *  and place it in the back of the deck.  Repeat n-1 times.  The permutation is 
    *  completed "in-place" and has no additional space requirement.
    */
    void shuffle(){

      // seed the random-number generator
      srand( time(NULL));
      for (int i = deck.size()-1; i > 0; i--){
        // generate a random number in [0,i]
        int j =  rand() % i;
        Card tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
      }
      
    };
  
    /* Method deal_one_card(): This method deals the top card in the deck.  
    *  This method could be overridden in a subclass if we wanted to change the deal 
    *  logic: For example, deal the bottom card, deal a random card, etc...
    *  Returns a null object if the deck is empty
    */ 
    Card deal_one_card(){
      if( !deck.empty()){
        Card card = deck.front();
        deck.pop_front();
        return card;
      }
      else throw "Dealer: Deck is empty";

    };
    
    /* Method:  show_cards():  This method is used for printing out the current
    *  deck held by the dealer */ 
    void show_cards(){
      deque<Card>::iterator it = deck.begin();
      
      while(it != deck.end()){
         printf("%d,%c|", it->getValue(),Card::enum2string(it->getSuit()));
         it++;
      }
      printf("\n\n"); 
    }

    /* Method: deck_size(): Returns the number of cards left in the dealer's deck
    */
    int deck_size(){ return deck.size(); }; 

  private:
     deque<Card> deck;
};

//  'main' test driver for card and dealer classes
int main(){


  // empty deck
  deque<Card> cards;

  // add the hearts...
  for(short v=1;v<=13;v++){
    Card c(v,Card::HEARTS);
    cards.push_back(c);
  }
  // add the spades...
  for(short v=1;v<=13;v++){
    Card c(v,Card::SPADES);
    cards.push_back(c);
  }
  // add the diamonds...
  for(short v=1;v<=13;v++){
    Card c(v,Card::DIAMONDS);
    cards.push_back(c);
  }
  // add the clubs...
  for(short v=1;v<=13;v++){
    Card c(v,Card::CLUBS);
    cards.push_back(c);
  }
    
  // create the dealer, give him the cards 
  Dealer* dealer = new Dealer(cards);
  
  for(int i=0;i < 53 ; i ++){ 
    try{
      
      printf("shuffling...\n"); 
      dealer->shuffle();
      
      printf("current deck state: (%d cards left)\n",dealer->deck_size());
      dealer->show_cards();
      
      Card c = dealer->deal_one_card();
      printf("Dealt card: %d,%c \n",c.getValue(),Card::enum2string(c.getSuit()));
    }
    catch (char const* e){
      printf("%s\n\n", e);
    }
  }
 
  delete dealer;
  return 0;
}



