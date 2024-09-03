#ifndef ENEMEYSLIME_H
#define ENEMEYSLIME_H
#include "slime.h"
#include <string>

using namespace std;

class enemey : public slime {
private:
  string type;
  char color;

public:
  enemey(const string &_name, int _level, int _health, int _strength,
         int _defense, int _speed, const string &_type,
         char _color);
  virtual ~enemey();
 // bool operator == (const enemey& other) const;
  virtual void print() const;
  string getType() const;
  char getColor() const;
  string getMethod() const;
  void setType(const string &_type);
  void setColor(char _color);
};
#endif