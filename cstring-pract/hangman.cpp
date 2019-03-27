#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn", 
                          "science", "engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank
  const char* targetWord = wordBank[rand() % numWords];

  // More initialization code as needed
  char word[80];  // a blank array to use to build up the answer
                  // It should be initialized with *'s and then
                  
  int length = strlen (targetWord); //works
  for (int i = 0; i < length; i++) { // begin game fill up array w/asterix
      word[i] = '*';
  }

  word[length] = '\0'; //end word
 
    while (numTurns > 0) {//while user still has turns
        //game stuff
        cout << "Current word: " << word << endl;
        cout << numTurns << " remain...Enter a letter to guess:" << endl;
        cin >> guess;
        
        processGuess(word, targetWord, guess);
        int guesses = processGuess(word, targetWord, guess);
        
        if (guesses == 0) { //if guessed wrong word, decrement turn number
            numTurns--;
        }
        
        if ((strcmp(word,targetWord)) == 0) { //if word is right
            cout << "The word was: " << targetWord << ". You win!"<< endl;
            return 0;
        } //if word is wrong and user is out of turns
        else if (((strcmp(word,targetWord)) != 0) && (numTurns == 0) ) {
            cout << "Too many turns...You lose!" << endl;
            return 0;
        }
    }
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found

int processGuess(char* word, const char* targetWord, char guess)
{
// my attempt
    int good_guess = 0;
    int counter = 0;
    while (*(targetWord+counter) != '\0') { //while not at null character
          if (*(targetWord+counter) == guess) { //is target word letter = guessed character
              word[counter] = guess; //change displayed word to right character(s)
              good_guess++; //increase letter guessed right
          }
        counter++;
     }
       
  return good_guess;  
}

