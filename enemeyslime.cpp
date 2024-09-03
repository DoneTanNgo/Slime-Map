#include "enemeyslime.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

enemey::enemey(const string &_name, int _level, int _health, int _strength, int _defense, int _speed,const string &_type,char _color) : slime(_name, _level, _health, _strength, _defense, _speed)
{
    type = _type;
    if (type == "Healer")
    {
        setStrength(getStrength() + 5);//Healer only heals and healing depends on strength
    }
    color = _color;
}
//Normal constructor stuff ,but with type differences 

enemey::~enemey()
{
  cout << "Enemy Defeated" << endl;//Deconstructor when enemy is defeated
}

char enemey::getColor() const
{
    return color; //Returns color
}

string enemey::getType() const
{
    return type; //Returns type of Enemy Like soldier, healer, mage
}

void enemey::setColor(char _color)
{
    color = _color; //Set color
}

void enemey::setType(const string &_type)
{
  type = _type; //Set type
}

string enemey::getMethod() const //Get Method for different type of monsters
{
  int var = 0;
  string method = "defend";
  if(type == "Soldier") //Only attacks
  {
    if(var==0)
    {
      method = "attack";
    }
  }
  else if (type == "Healer")//Only Healing
  {
      method = "heal";
  }
  else if (type == "Mage")//Only pulls from abilities 
  {
      srand(time(0));
      var = rand() % 3;

      switch(var)
      {
      case 0:
          method = "flipStrSpd";
          break;
      case 1:
          method = "RandomFlip";
          break;
      case 2:
          method = "flipStrDef";
          break;
      case 3:
          method = "vampHit";
          break;
      default:
          break;
      }

  }
  else
  {
      method = "attack";
  }
  return method;
}

void enemey::print() const
{  
    cout << "Health: " << getHealth() << endl;
    /*
    for(int x = 0;x < getHealth(); x++)
      {
        cout << "❤";
      }
    */
    cout << "Level: " << getlevel() << endl;
    cout << "Strength: " << getStrength() << endl;
    cout << "Defense: " << getDefense() << endl;
    cout << "Speed: " << getSpeed() << endl;
    cout << "Type: " << type << " Color: " << color << endl;

}