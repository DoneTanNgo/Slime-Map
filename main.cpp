#include <iostream>
#include <string>
#include <fstream>
#include "slime.h"
#include "enemeyslime.h"
#include "map.h"
#include "combat.h"
#include "player.h"
using namespace std;

void save(player &player)//Saving Player Variables
{
  ofstream od;
  od.open("save_player.txt");
  if(od.is_open())
  {
    cout << "Saving..." << endl;
    od << player.getName()  << "\t";
    od << player.getlevel() << "\t";
    od << player.getHealth() << "\t";
    od << player.getStrength() << "\t";
    od << player.getDefense() << "\t";
    od << player.getSpeed() << "\t";
    od << player.getAbilities().size() << "\t";
    for(int x = 0; x < player.getAbilities().size(); x++)
      {
        od << player.getAbilities()[x] << "\t";            
      }
  
    od.close();
  }
}


int main()
{
  Map m(10,10);
  string status = "map";
  player p("Temp",1,5,5,2,5,vector<string>{"heal"});
  combat battle(&p);
  //Instanlization of variables 

  //Continue Save File Time
  char input;
  cout << "Welcome To DUNGEON SLIME" << endl;
  cout << "Enter any thing to start from fresh or Type \"C\" to continue" << endl << "Case Sensitive" << endl;
  cin >> input;
  if(input == 'C' || input == 'c')
  {
    p.clearAbilities();
    string name;
    int level;
    int health;
    int strength;
    int defense;
    int speed;
    int size;
    ifstream fd;
    fd.open("save_player.txt");
    if(fd.is_open() == true)
    {
      fd >> name >> level >> health >> strength >> defense >> speed >> size;
      p.setName(name);
      p.setlevel(level);
      p.setHealth(health);
      p.setStrength(strength);
      p.setDefense(defense);
      p.setSpeed(speed);
      for(int x = 0; x < size; x++)
        {
          string ability;
          fd >> ability;
          p.addAbility(ability);
        }
    }
    fd.close();
    string temp = "save_map.txt";
    m.loadMap(temp);
    battle.setPlayer(p);
  }
  else//New Game with 
  {
    string name;
    cout << "New Game" << endl << "Set Name:" << endl;
    cin >> name;
    cout << endl;
    p.setName(name);
  }


  while(true)
  {
    
    if(status=="map"){
      //cout << ("\033c");//This removes last thing printed out in terminal
      m.display(); //Displays map in a way it's readable
      cout << "Enter WASD to move" << endl; 
      cout << "Player Stats "; 
      p.display(); //Displays Player Stats
      cout << "Enter \"R\" to reset the map if you can't get to the next floor" << endl; //If players need to
      cout << "Enter \"P\" to save" << endl;
      cin >> input;

      if(toupper(input) != 'P')
      {
        status = m.movePlayer(input);
      }
      else
      {
        //cout << ("\033c");
        save(p);
        string temp = "save_map.txt";
        m.saveMap(temp);
      }
      if(status=="fight")
      {
        battle.startBattle(m.getLevel());
        battle.setPlayer(p);
      }
        
    }
    else if(status=="fight") //Battle Time
    {
     // cout << ("\033c");
      battle.display();
      battle.turnTick();
      status = battle.checkStatus();
    }
    else
    {
      break;
    }
  }
  return 0;
}