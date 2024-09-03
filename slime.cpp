#include "slime.h"
#include <iostream>

using namespace std;


slime::slime(const string &_name, int _level, int _health, int _strength, int _defense, int _speed)
{
    name = _name;
    level = _level;
    health = _health;
    strength = _strength;
    defense = _defense;
    speed = _speed;
}

string slime::getName() const//Self explantory for get functions
{
    return name;
}
int slime::getlevel() const
{
    return level;
}
int slime::getHealth() const
{
    return health;
}
int slime::getStrength() const
{
    return strength;
}
int slime::getDefense() const
{
    return defense;
}
int slime::getSpeed() const
{
    return speed;
}
void slime::setName(const string &_name)
{
    name = _name;
}
void slime::setlevel(int _level)
{
    level = _level;
}
void slime::setHealth(int _health)
{
    health = _health;
}
void slime::setStrength(int _strength)
{
    strength = _strength;
}
void slime::setDefense(int _defense)
{
    defense = _defense;
}
void slime::setSpeed(int _speed)
{
    speed = _speed;
}
void slime::print() const
{
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Health: " << health << endl;
  cout << "Strength: " << strength << endl;
  cout << "Defense: " << defense << endl;
  cout << "Speed: " << speed << endl;
}
