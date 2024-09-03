#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"
#include "enemeyslime.h"
#include <string>
#include <vector>

class combat
{
  private:
    player *player;
    vector<enemey> listEnemy;
   // vector<slime*> attackOrder;
  public:
    combat(class player* _player);
    void damage(int damage, slime* target);
    void abilities(string &ability ,slime* self, slime* target);
    void setPlayer(class player& _player);
    void setEnemy(vector<enemey> _listEnemy);
    void startBattle(int level);
    void playerTurn(char input);
    void cpuTurn(class enemey target);
    void turnTick();
    string checkStatus();
    void print() const;
    void display() const;
};

#endif