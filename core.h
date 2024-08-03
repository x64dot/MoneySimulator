#ifndef CORE_H
#define CORE_H

struct PlayerData{ 
  int money;
  int gems;
  int boost;
  int super_boost; 
};

class Functionality{
  public:
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

