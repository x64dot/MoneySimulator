#ifndef CORE_H
#define CORE_H

struct PlayerData{ 
  int money;
  int gems;
  int boost; 
};

class Functionality{
  public:
    void clear();
};

class MoneyOp{
  public:
    void getbal(PlayerData* player);
    void beg(PlayerData* player);    
};

#endif
