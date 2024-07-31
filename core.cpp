#include "core.h"
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

void MoneyOp::getbal(PlayerData* player){
  cout << "Money Balance: " << player->money << "\n"; 
  cout << "Gems Balance: " << player->gems << "\n";
  cout << "Boosts: " << player->boost << "\n";
}

void MoneyOp::beg(PlayerData* player){
  srand((unsigned) time(NULL));
  if (player->boost == 0){
       int random = 5 + (rand() % 100);
       player->money = player->money + random;
       cout << "You earned " << random << " from begging" << "\n";
  }
  else{
     int random = 5 + (rand() % (100 * player->boost));
     player->money = player->money + random;
     cout << "You earned " << random << " from begging" << "\n";
  }
}



void Functionality::clear(){
  cout << "\033[2J\033[1;1H";
}


void Functionality::shop(PlayerData* player){
  int amount = 0, cost = 0, realcost = 500;
  cout << "------------------------------------------------------\n";
  cout << "How many boost would you like to buy?(Enter a number)\n";
  cout << "-----------------------------------------------------\n";
  cin >> amount;

  if (amount == 0){
      return;
  }
  if (player->boost == 0){ 
      cost = realcost * amount;
  }
  else{
       cost = realcost * amount * player->boost;
  }
  cost = realcost * amount;
  cout << "The cost for " << amount << " boosts will be " << cost << " cash\n";
  cout << "Would you like to purchase?(y/n)\n";
  char input;

  cin >> input;

  input = tolower(input);

  if (input == 'n'){
       return;
   }

   if (input == 'y'){
       if (player->money < cost){
            cout << "Sorry you do not have enough!\n";
            return;
       }
       else{
           cout << "You have bought " << amount << " boosts!\n";
           player->boost += amount;  
          }
      }
   }
