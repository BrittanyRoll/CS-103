#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int MAXPOP = 100000;

int main()
{
  // Array with enough entries for the maximum population size possible.
  bool pop[MAXPOP];
 
  int N;
  int k;
  int M;
  int seed;
    
  int max_nights = -1;
  int min_nights = INT_MAX;

  cout << "Enter the following: N k M seed" << endl;
  cin >> N >> k >> M >> seed;
    
  srand(seed);
    
  if (k > N){ //if pop entered < zombie number, exit program
      abort();
  }
  
  for (int i = 0; i < N; i++) {//iterate pop array and "make" init zom and ppl, works
      if (i < k) {
          pop[i] = true;
      } else if ((i >= k) && (i < N)){
          pop[i] = false;
      }
  }
  
  
  int bites = rand() % N; //init # bites restricted population number;
  int counter = 0; //aligns with simulation while loop
  int zomb = k; //zomb is the dynamic zombie variable 
  int nights = 0;
  int new_zomb = 0;
  int n = 0;
    
  while (counter < M){ //will go through simulations
      while (zomb < N){ //one simulation
         for (int j = 0; j < zomb; j++){ //iterates through one night 
             bites = rand() % N;
             //successful bites
             if (pop[bites] != true){
                 pop[bites] = true;
                 new_zomb++; //keeps track of new zombies  
             }
         }
         nights++;
         zomb+=new_zomb;
         new_zomb = 0; //reset new zomb to 0 for next night
     }
      n+=nights; //gather nights
      //max and min nights
      if (nights > max_nights) {
          max_nights = nights;
      }
      if (nights < min_nights) {
          min_nights = nights;
      }
      nights = 0;// reset nights
      //reset population to initial ratio, putting in old array makes infinite loop
      for (int l = 0; l < N; l++) {
          if (l < k) {
              pop[l] = true;
          } else if ((l >= k) && (l < N)){
              pop[l] = false;
          }
      }
      zomb = k; //reset zomb to inital zombie for new simulation
      counter++; //goes to next simulation
  }
      //compute avg with full #nights/# simulations
      double avg_nights = (double)n/M;

  //Print out your average, max, and min number of nights here
  cout << "Average Nights: " << avg_nights << endl;
  cout << "Max Nights: " << max_nights << endl;
  cout << "Min Nights: " << min_nights << endl;

  return 0;
}






