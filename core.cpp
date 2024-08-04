#include "core.h"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <ios>
#include <limits>


using namespace std;

bool Functionality::chance(){
  bool TrueFalse = (rand() % 100) < 15;

  return TrueFalse;
}

void Functionality::help_menu() {
    cout << "------------------------------------------------------\n";
    cout << "                   Game Help Menu                    \n";
    cout << "------------------------------------------------------\n";
    cout << "1. **Displaying Your Balance**\n";
    cout << "   - Use \"bal\" to display your current money, gems, boosts, and super boosts.\n";
    cout << "\n";
    cout << "2. **Begging for Money**\n";
    cout << "   - Use \"beg\" to beg for money. Depending on your boosts and super boosts, you can earn more money and gems.\n";
    cout << "   - If you have boosts or super boosts, you will earn more money based on their levels.\n";
    cout << "\n";
    cout << "3. **Purchasing Boosts**\n";
    cout << "   - Use \"shop\" to buy boosts. Each boost costs cash, and the cost increases with the number of boosts you already have.\n";
    cout << "   - You can buy multiple boosts at once.\n";
    cout << "\n";
    cout << "4. **Purchasing Super Boosts**\n";
    cout << "   - Use \"shop2\" to buy super boosts. Each super boost costs gems, and the cost increases with the number of super boosts you already have.\n";
    cout << "   - You can buy multiple super boosts at once.\n";
    cout << "\n";
    cout << "5. **Clearing the Screen**\n";
    cout << "   - Use \"clear\" to clear the terminal screen for better readability.\n";
    cout << "\n";
    cout << "6. **Help Menu**\n";
    cout << "   - Use \"help\" to display this help menu.\n";
    cout << "------------------------------------------------------\n";
    cout << "                Good luck and have fun!              \n";
    cout << "------------------------------------------------------\n";
}



void MoneyOp::getbal(PlayerData* player){
  cout << "Money Balance: " << player->money << "\n"; 
  cout << "Gems Balance: " << player->gems << "\n";
  cout << "Boosts: " << player->boost << "\n";
  cout << "Super Boosts: " << player->super_boost << "\n";
}

void MoneyOp::beg(PlayerData* player){
  Functionality Obj;
  if (player->boost == 0 && player->super_boost == 0){
       int random = 5 + (rand() % 100);
       player->money += random;
       cout << "You earned " << random << " from begging" << "\n";
       
       if (Obj.chance()){
          int gems_random = 1 + (rand() % 5);
          player->gems += gems_random;

          cout << "You earned " << gems_random << " gems!\n";
       }
  }
  else if (player->boost > 0 && player->super_boost == 0){
     int random = 5 + (rand() % (100 * player->boost));
     player->money += random;
     cout << "You earned " << random << " from begging" << "\n";

     if (Obj.chance()){
         int gems_random = 1 + (rand() % 5);
         player->gems += gems_random;

         cout << "You earned " << gems_random << " gems!\n";
     }

  }
  else if (player->boost == 0 && player->super_boost > 0){
     int random = 5 + (rand() % (100 * player->super_boost * SUPER_BOOST));
     player->money += random;
     cout << "You earned " << random << " from begging" << "\n";
    
     if (Obj.chance()){           
         int gems_random = 1 + (rand() % 5);
         player->gems += gems_random;
           
         cout << "You earned " << gems_random << " gems!\n";
       }
  }

  else{
     int random = 5 + (rand() % (100 * player->boost * (player->super_boost * SUPER_BOOST)));
     player->money += random;
     cout << "You earned " << random << " from begging" << "\n";
     
     if (Obj.chance()){
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
  long int amount = 0, cost = 0, realcost = 500;
  cout << "------------------------------------------------------\n";
  cout << "How many boost would you like to buy?(Enter a number)\n";
  cout << "-----------------------------------------------------\n";
  cin >> amount;
  if (cin.fail() || amount < 0){
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "Error with input: Enter a postive number only. Visit the shop again.\n";
      return;
  }
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
  long int amount = 0, cost = 0, realcost = 40;
  cout << "------------------------------------------------------\n";
  cout << "How many super boost would you like to buy?(Enter a number)\n";
  cout << "-----------------------------------------------------\n";
  cin >> amount;
  
   if (cin.fail() || amount < 0){
       cin.clear();
       cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       cout << "Error with input: Enter a postive number only. Visit the shop22 again.\n";
       return;
    }
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
