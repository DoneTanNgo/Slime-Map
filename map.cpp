#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include "map.h"
using namespace std;


Map::Map(int _width, int _height){//Sometimes Didn't have time for 
    level = 0;
    width = _width;
    height = _height;
    map.assign(width, vector<int>(height, 0));

    generateFloors();

    int stairsX = rand() % (width - 2) + 1;
    int stairsY = rand() % (height - 2) + 1; 
    map[stairsX][stairsY] = 2;
    do {
        playerX = rand() % (width - 2) + 1;
        playerY = rand() % (height - 2) + 1;
    } while (map[playerX][playerY] != 1);
}

int Map::getLevel() const
{
  return level;
}
int Map::getWidth() const
{
  return width;
}
int Map::getHeight() const
{
  return height;
}

int Map::getPlayerX() const
{
  return playerX;
}
int Map::getPlayerY() const
{
  return playerY;
}
vector<vector<int>> Map::getMap() const
{
  return map;
}

// Generate floors randomly
void Map::generateFloors(){
    for (int i = 1; i < width - 1; ++i) {
        for (int j = 1; j < height - 1; ++j) {
            if (rand() % 3 == 0) { 
                map[i][j] = 0; // Place a wall
            } else {
                map[i][j] = 1; // Place a floor
            }
        }
    }
}

// Display the map
void Map::display() const{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
               
            if (i == playerX && j == playerY) {
                cout << " 0 "; // Player Symbol
            } else {
              //cout << " " << map[i][j];
                if(map[i][j] == 1)
                  {
                  cout << "   "; // Walkable Tiles
                  }
                else if(map[i][j] == 0)
                  {
                  cout <<" 1 "; // Wall Tiles
                  }
                else if(map[i][j] == 3)
                {
                  cout <<" 3 "; // Monster Tiles
                }
              else
              {
                cout <<" 2 "; // Stairs
              }
              
            }
        }
        cout << endl;
        
    }
    cout << "Level you are on: " << level << endl;
}

// Move the player
string Map::movePlayer(char direction){
    int newX = playerX;
    int newY = playerY;

    switch (direction) {
        case 'W':
        case 'w':
            newX--;
            break;
        case 'S':
        case 's':
            newX++;
            break;
        case 'A':
        case 'a':
            newY--;
            break;
        case 'D':
        case 'd':
            newY++;
            break;
        case 'R':
        case 'r':
            generateNewMap(width, height);
            break;
        default:
            cout << "Invalid input! Use W, A, S, D to move." << endl;
    }

    if (map[newX][newY] == 0) {
        cout << "You hit a wall!" << endl;
    } else if (map[newX][newY] == 2) {
        cout << "You found stairs to a new map!" << endl;
        level = level + 1;
        int _width = width;
        int _height = height;
        if(level%10 == 0)
        {
          _width += 1;
          _height += 1;
        }
        generateNewMap(_width,_height);
    } else if (map[newX][newY] == 3) {
      cout << "You encountered a monster!" << endl;
      map[newX][newY] = 1;
      playerX = newX;
      playerY = newY;
      return "fight";
    } else {
        playerX = newX;
        playerY = newY;
    }
    return "map";
}

void Map::saveMap(string &fileName)
{
  ofstream of;
  of.open(fileName);
  if(of.is_open())
  {
    of << level << "\t";
    of << width << "\t";
    of << height << "\t";
    of << playerX << "\t";
    of << playerY << "\t";
    for(int x = 0; x < width-1; x++)
    {
    for(int y = 0; y < height-1; y++)
      {
        of << map[x][y] << "\t";
      }
    }
  }
  of.close();
  
}

void Map::loadMap(string &fileName)
{
  ifstream fd;
  fd.open(fileName);
  if(fd.is_open())
  {
    fd >> level >> width >> height>> playerX >> playerY;
    
  
  map.assign(width, vector<int>(height,0));
  for(int x = 0; x < width - 1; x++)
    for(int y = 0; y < height - 1;y++)
      {
        fd >> map[x][y];
      }
  }
  fd.close();
}
// Generate a new map
void Map::generateNewMap(int _width, int _height) {
  srand(time(0));//Randomizing better. Better player experience
  //srand(12345);
  //srand(80085);
  //srand(515735);


  map.assign(width, vector<int>(height, 0));
  generateFloors();
  int monsterCount = 5 + level;
  int monsterX;
  int monsterY;
  int stairsX;
  int stairsY;
  
  
  do{ //mosnter randomizer
    do{
      monsterX = rand() % (width - 2) + 1;
      monsterY = rand() % (height - 2) + 1;
    }while(map[monsterX][monsterY] == 2 && map[monsterX][monsterY] != 1);
    monsterCount--;
    map[monsterX][monsterY] = 3;
  }while(monsterCount > 0);
  
  do { //Stairs randomizer
      stairsX = rand() % (width - 2) + 1;
      stairsY = rand() % (height - 2) + 1;
  } while (map[stairsX][stairsY] != 0);

  map[stairsX][stairsY] = 2;
 

  do { //player Randomizer
    playerX = rand() % (width - 2) + 1;
    playerY = rand() % (height - 2) + 1;
  } while (map[playerX][playerY] != 1);


}   