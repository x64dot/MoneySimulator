#include <iostream>
#include <string>
#include "core.h"

using namespace std;

int main(){
  
  MoneyOp MoneyObj;
  Functionality FuncObj;

  PlayerData* player = new (nothrow) PlayerData;
  if (player == nullptr){
      cout << "Memory allocation failed.";
  }

  player->money = 0;
  player->gems = 0;
  player->boost = 0;
  player->super_boost = 0;

  while (1){
    string input;
    cout << "What will be your input? ";
    
    getline(cin, input);

    if (input == "exit"){
        delete player;
        return 0;
    }
    else if (input == "bal"){
        MoneyObj.getbal(player); 
    }
    else if (input == "beg"){
       MoneyObj.beg(player); 
    }
    else if (input == "clear"){
       FuncObj.clear();     
    }
    else if (input == "shop"){
       FuncObj.shop(player);
    }   
    else if (input == "shop2"){
       FuncObj.shop2(player);
    } 
    else{
       cout << "Invalid Input: " << input << "\n";
    }
  }


  return 0;
}


