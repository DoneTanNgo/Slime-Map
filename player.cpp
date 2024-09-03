#include <vector>
#include <iostream>
#include <string>
#include "player.h"
using namespace std;


player::player(const string &_name, int _level, int _health, int _strength,int _defense, int _speed,vector<string> _abilities) : slime(_name,_level,_health,_strength,_defense,_speed)
{
 for(int x = 0; x < _abilities.size(); x++)
   {
     abilities.push_back(_abilities[x]);
   }
}
//Classic Constructor stuff

player::~player() //If needed to see if player has deconstructed
{
  cout << "Player Defeated" << endl;
}

void player::print() const //Return abilities in print
{
  cout << "Abilities: " << endl;
  for(int x = 0; x < abilities.size(); x++)
    {
      cout << x <<":" << abilities[x] << endl;
    }
}
void player::levelup(int creature)//Getting new ability and additional stat boosting after defeating battle
{
    srand(time(0));
    setlevel(getlevel() + creature);
    string ab[10] = {"heal" , "speedHit" , "defenseHit" , "vampHit","IncreaseSpeed","IncreaseStr","IncreaseDef","flipStrDef","flipStrSpd","RandomFlip"};
    addAbility(ab[rand()%ab->size()]);

    for(int x = 0; x < 3;x++)
    {
    switch (int(rand()%3 + 1))
        {
        case 1:
            setHealth(getHealth() + 1);
            cout << "Health Increased" << endl;
            break;
        case 2:
            setStrength(getStrength() + 1);
            cout << "Strength Increased" << endl;
            break;
        case 3:
            setDefense(getDefense() + 1);
            cout << "Defense Increased" << endl;
            break;
        case 4:
            setSpeed(getSpeed() + 1);
            cout << "Speed Increased" << endl;
            break;
        default:
            cout << "WHAT" << endl;
            break;
        }
    }
}

string player::getType() const //Return Type of slime
{
  return "Player";
}

void player::display() const //Displays stats with icons better
{
  cout << "Player: " << getName() << endl;
  cout << "Health: " << getHealth() << endl;
  /*
  for(int x = 0;x < getHealth(); x++)
    {
      cout << "❤";
    }
  */
  cout << endl;
  cout << "Level: " << getlevel() << endl;
  cout << "Strength: " << getStrength() << endl;
  cout << "Defense: " << getDefense() << endl;
  cout << "Speed: " << getSpeed() << endl;
  print();
}
vector<string> player::getAbilities() const //Returns abilities
{
  return abilities;
}

void player::clearAbilities()
{
  abilities.clear(); //Clear the entire vector
}

void player::removeAbility(int index) //Remove ability from int index
{
  abilities.erase(index + abilities.begin()); 
} 

void player::addAbility(const string &ability) //Adding new ability but if the Player already has 5 ability already see if player wants to change an ability or not
{
  if(abilities.size() > 4)
  {
    cout << "You can't have more than 5 abilities" << endl;
    cout << "Delete which one" << endl;
    cout << "You are getting" << ability << endl;
    int input;
    print();
    while(!(cin >> input)&&input >= 5 || input < 0)
      {
        cout << "Pick an index" << endl;
      }
    if(input < 5 && input >= 0)
    {
      removeAbility(input);
      abilities.push_back(ability);
      cout << ability << " got added to your ability list." << endl;
    }
  }
  else
  {
    abilities.push_back(ability);
    cout << ability << " got added to your ability list." << endl;
  }
}