#ifndef SLIME_H
#define SLIME_H
#include <string>
using namespace std;

class slime {
private:
  string name;
  int level;
  double health;
  int strength;
  int defense;
  double speed;
  static int id;

public:
  slime(const string & _name, int _level, int _health, int _strength,
        int _defense, int _speed);
  string getName() const;
  int getlevel() const;
  int getHealth() const;
  int getStrength() const;
  int getDefense() const;
  int getSpeed() const;
  void setName(const string &_name);
  void setlevel(int _level);
  void setHealth(int _health);
  void setStrength(int _strength);
  void setDefense(int _defense);
  void setSpeed(int _speed);
  virtual void print() const;
  virtual string getType() const = 0;
};
#endif