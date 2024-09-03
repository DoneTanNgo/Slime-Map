#ifndef PLAYER_H
#define PLAYER_H
#include "slime.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class player : public slime {
private:
  vector<string> abilities;

public:
  player(const string &_name, int _level, int _health, int _strength,int _defense, int _speed, vector<string> _abilities);
  virtual ~player();
  virtual void print() const;
  void removeAbility(int index);
  vector<string> getAbilities() const;
  string getType() const;
  void clearAbilities();
  void levelup(int creature);
  void display() const;
  void addAbility(const string &ability);
};

#endif