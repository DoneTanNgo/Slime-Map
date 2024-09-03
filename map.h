#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
using namespace std;

class Map {
private:
    vector<vector<int>> map;
    int level;
    int width;
    int height;
    int playerX;
    int playerY;

public:
    Map(int _width, int _height);
    void generateFloors();
    void display() const;
    int getLevel() const;
    int getWidth() const;
    int getHeight() const;
    int getPlayerX() const;
    int getPlayerY() const;
    void saveMap(string &fileName);
    void loadMap(string &fileName);
    vector<vector<int>> getMap() const;
    string movePlayer(char direction);
    void generateNewMap(int _width, int _height);
};
#endif