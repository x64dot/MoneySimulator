#include "core.h"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <ios>
#include <limits>

using namespace std;

bool Functionality::chance(){
  srand((unsigned) time(NULL));
  bool TrueFalse = (rand() % 100) < 15;

  return TrueFalse;
}


void MoneyOp::getbal(PlayerData* player){
  cout << "Money Balance: " << player->money << "\n"; 
  cout << "Gems Balance: " << player->gems << "\n";
  cout << "Boosts: " << player->boost << "\n";
  cout << "Super Boosts: " << player->super_boost << "\n";
}

void MoneyOp::beg(PlayerData* player){
  srand((unsigned) time(NULL));
  Functionality Obj;
  if (player->boost == 0 || player->super_boost == 0){
       int random = 5 + (rand() % 100);
       player->money += random;
       cout << "You earned " << random << " from begging" << "\n";
       
       if (Obj.chance() == true){
          int gems_random = 1 + (rand() % 5);
          player->gems += gems_random;

          cout << "You earned " << gems_random << " gems!\n";
       }

  }
  else{
     int random = 5 + (rand() % (100 * player->boost * (player->super_boost * 20)));
     player->money += random;
     cout << "You earned " << random << " from begging" << "\n";
     
     if (Obj.chance() == true){
        int gems_random = 1 + (rand() % 5);
        player->gems += gems_random;

        cout << "You earned " << gems_random << " gems!\n";
     }
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
  cout << "The cost for " << amount << " boosts will be " << cost << " cash\n";
  cout << "Would you like to purchase?(y/n)\n";
  char input;

  cin >> input;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
           player->money -= cost; 
          }
      }
   }
void Functionality::shop2(PlayerData* player){
  int amount = 0, cost = 0, realcost = 40;
  cout << "------------------------------------------------------\n";
  cout << "How many super boost would you like to buy?(Enter a number)\n";
  cout << "-----------------------------------------------------\n";
  cin >> amount;

  if (amount == 0){
      return;
  }
  if (player->super_boost == 0){ 
      cost = realcost * amount;
  }
  else{
       cost = realcost * amount * player->super_boost;
  }
  cout << "The cost for " << amount << " super boosts will be " << cost << " gems\n";
  cout << "Would you like to purchase?(y/n)\n";
  char input;

  cin >> input;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  input = tolower(input);

  if (input == 'n'){
       return;
   }
   
   if (input == 'y'){
       if (player->gems < cost){
            cout << "Sorry you do not have enough!\n";
            return;
       }
       else{
           cout << "You have bought " << amount << " super boosts!\n";
           player->super_boost += amount; 
           player->gems -= cost; 
          }
      }
   } 
