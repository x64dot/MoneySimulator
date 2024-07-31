#include "core.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void MoneyOp::getbal(PlayerData* player){
  cout << "Money Balance: " << player->money << "\n"; 
  cout << "Gems Balance: " << player->gems << "\n";
  cout << "Multiplier: " << player->boost << "\n";
}

void MoneyOp::beg(PlayerData* player){
  srand((unsigned) time(NULL));
  if (player->boost == 0){
       int random = 5 + (rand() % 100);
       player->money = player->money + random;
       cout << "You earned " << random << " from begging" << "\n";
  }
}

void Functionality::clear(){
  cout << "\033[2J\033[1;1H";
}
