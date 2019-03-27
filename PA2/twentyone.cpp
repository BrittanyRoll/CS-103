#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    int x; // random value to rep place in array
    int hold; //place holder for card swapping
    for (int i = 51; i >= 1; i--) {
        x = rand() % (i + 1);
        hold = cards[i];
        cards[i] = cards[x];
        cards[x] = hold;
    }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id) 
{
  /******** You complete ****************/
    char suits;
    char types;
    
    int posit = (id % 13);
    types = *(type[posit]);
    
    if ((id >= 0) && (id <= 12)) { 
        suits = suit[0];
        } else if ((id >= 13) && (id <= 25)) { 
        suits = suit[1];
        } else if ((id >= 26) && (id <= 38)) { 
        suits = suit[2];
        } else {
        suits = suit[3];
        }
    if (posit == 8) {
        cout << "10" << "-" << suits;
    } else {   
        cout << types << "-" << suits;
    }  
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */

int cardValue(int id)
{
  /******** You complete ****************/
    int val = (id % 13);
    int num;
    num = value[val];

    return num;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
    int counter = 0;
    while (counter < numCards) {
        printCard(hand[counter]);
        cout << " ";
        counter++;
    }
    cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
    int score = 0;
    int card_val;
    int counter = 0;
    int ace_counter = 0;
    
    while (counter < numCards) {
        card_val = cardValue(hand[counter]);
        if (card_val == 11) {
            ace_counter++;
        }
        score += card_val;
        counter++;
    }
    
    while ((score > 21) &&  (ace_counter > 0)) {
            score -= 10;
            ace_counter--;
    }
    return score;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  char inputs;
  char play_again;
  int pscore = 0;
  bool play = true;
   
  int pnum_Cards = 2; //keeps track of how many cards there are
  int dnum_Cards = 2; //keeps track of how many cards there are 
  int card_counter = pnum_Cards+dnum_Cards; //keep track of card on top of array
    
  bool hit = false;
  bool stay = false;
  
  while (play == true) {
      for (int i = 0; i < 52; i++) { //fill card array
          cards[i] = i; 
      }
    
      shuffle(cards);
      
      //fill player hand with array values (2 cards)
      for (int i = 0; i <= 2; i+=2) {
          int phand_posit = i/2;
          phand[phand_posit] = cards[i]; 
      }
      //fill dealer hand with array values (2 cards)
      for (int i = 1; i <= 3; i+=2) {
          int dhand_posit = (i-1)/2;
          dhand[dhand_posit] = cards[i];
      }  
      //First stage of game
      cout << "Dealer: ? ";
      printCard(dhand[1]);
      cout << endl;
      cout << "Player: ";
      printHand(phand, pnum_Cards);
      pscore = getBestScore(phand, pnum_Cards);
      int d = getBestScore(dhand, dnum_Cards);
      if (pscore == 21) { //already @ 21
          while (d < 17) { //increase dealer hand 
            dnum_Cards++;
            card_counter = ((pnum_Cards + dnum_Cards) - 1);
            dhand[dnum_Cards - 1] = cards[card_counter];
            d = getBestScore(dhand, dnum_Cards);    
          }

          cout << "Dealer: ";
          printHand(dhand, dnum_Cards);
          cout << "Win " << pscore << " " << d;
          cout << endl;
          //reset cards
          pnum_Cards = 2;
          dnum_Cards = 2;
          cout << "Play again? [y/n]" << endl;
          cin >> play_again;
          if (play_again == 'y') {
              play = true;
              hit = false;
          } else if (play_again != 'y') {
              return 0;
          }
      }
      
      else { //not already at 21
          cout << "Type 'h' to hit and 's' to stay:" << endl;
          cin >> inputs;
          
          if (inputs == 'h') {
              hit = true;
          } else if (inputs == 's') {
              stay = true;
          } else {
              return 0;
          }
          
          ////hit case
          while (hit == true) {
              pnum_Cards++;
              card_counter = ((pnum_Cards + dnum_Cards) - 1);
              phand[pnum_Cards - 1] = cards[card_counter];
              
              cout << "Player: ";
              printHand(phand, pnum_Cards);
              pscore = getBestScore(phand, pnum_Cards);
              if (pscore > 21) {//player busts
                  //dont update dhand
                  cout << "Player busts" << endl;
                  cout << "Lose " << pscore << " " << d << endl;
                  
                  cout << endl;
                  pnum_Cards = 2;
                  dnum_Cards = 2;
                  cout << "Play again? [y/n]" << endl;
                  cin >> play_again;
                  if (play_again == 'y') {
                      play = true;
                  } else if (play_again != 'y') {
                      return 0;
                  }
                  hit = false;
              }
              //player is still good
              else if (pscore < 21) {
                  cout << "Type 'h' to hit and 's' to stay:" << endl;
                  cin >> inputs;
                  
                  if (inputs == 'h') {
                      hit = true;
                  } else if (inputs == 's') {
                      d = getBestScore(dhand, dnum_Cards);
                      while (d < 17) { //increase dealer hand 
                        dnum_Cards++;
                        card_counter = ((pnum_Cards + dnum_Cards) - 1);
                        dhand[dnum_Cards - 1] = cards[card_counter];
                        d = getBestScore(dhand, dnum_Cards); 
                        printHand(dhand, dnum_Cards); //take out
                      }
                      
                      stay = true;
                      hit = false; //should this go before???
                  } else {
                      play = false;
                      return 0;
                  }
              }
              //add a tie of 21 to 21 in here
              //21!
              else {
                  while (d < 17) { //increase dealer hand 
                    dnum_Cards++;
                    card_counter = ((pnum_Cards + dnum_Cards) - 1);
                    dhand[dnum_Cards - 1] = cards[card_counter];
                    d = getBestScore(dhand, dnum_Cards);    
                  }
                  
                  cout << "Dealer: ";
                  printHand(dhand, dnum_Cards);
                  cout << "Win " << pscore << " " << d << endl;
                  cout << endl;
                  pnum_Cards = 2;
                  dnum_Cards = 2;
                  cout << "Play again? [y/n]" << endl;
                  cin >> play_again;
                  //play again code
                  if (play_again == 'y') {
                      play = true;
                  } else if (play_again != 'y') {
                      return 0;
                  }
                  hit = false;
              }
          }
          /////stay case
           while (stay == true) {
               while (d < 17) { //increase dealer hand 
                    dnum_Cards++;
                    card_counter = ((pnum_Cards + dnum_Cards) - 1);
                    dhand[dnum_Cards - 1] = cards[card_counter];
                    d = getBestScore(dhand, dnum_Cards);    
               }
               if (pscore > d) {
                  cout << "Dealer: ";
                  printHand(dhand, dnum_Cards);
                  cout << "Win " << pscore << " " << d;
               }
               //dealer won
               else if (pscore < d) {
                  //dealer won
                  if (d < 22) {
                     cout << "Dealer: ";
                     printHand(dhand, dnum_Cards);
                     cout << "Lose " << pscore << " " << d;
                  }
                  //dealer busts
                  else {
                     cout << "Dealer: ";
                     printHand(dhand, dnum_Cards);
                     cout << "Dealer busts" << endl;
                     cout << "Win " << pscore << " " << d;
                  }
               }
               //tie
               else {
                  cout << "Dealer: ";
                  printHand(dhand, dnum_Cards);
                  cout << "Tie " << pscore << " " << d;
              }
              
              cout << endl;
              //reset cards
              pnum_Cards = 2;
              dnum_Cards = 2;
            
              cout << "Play again? [y/n]" << endl;
              cin >> play_again; 
              //play again code
              if (play_again == 'y') {
                  play = true;
              } else if (play_again != 'y') {
                  return 0;
              }
              stay = false;
          }
       }
  } 
}

