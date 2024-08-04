#ifndef CORE_H
#define CORE_H

#define SUPER_BOOST 5
struct PlayerData{ 
 long long int money;
 long int gems;
 long int boost;
 long int super_boost; 
};

class Functionality{
  public:
    void help_menu();
    void clear();
    void shop(PlayerData* player);
    bool chance();
    void shop2(PlayerData* player);
};

class MoneyOp{
  public:
    void getbal(PlayerData* player);
    void beg(PlayerData* player);    
};

#endif
