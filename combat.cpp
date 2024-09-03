#include <string>
#include <vector>
#include <iostream>
#include "combat.h"
#include "player.h"
#include "enemeyslime.h"
#include <stdlib.h>

using namespace std;

combat::combat(class player* _player) {
    player = _player;
}

void combat::damage(int damage, slime* target) // Basic Attack Method
{
    if (target != nullptr)
    {
        if(damage - target->getDefense()*0.5>0)
        {
            target->setHealth(target->getHealth() - (damage - target->getDefense() * (0.5)));
            std::cout << damage - target->getDefense() << " damage to " << target->getName() << endl;
        }
        else
        {
            cout << "NO DAMAGE" << endl;
        }
    }

}

void combat::setPlayer(class player& _player) // Setting Player
{
    player = &_player;
}

void combat::setEnemy(vector<enemey> _listEnemy) // Setting Enemy 
{
    listEnemy = _listEnemy;
}

void combat::abilities(string& ability, slime* self, slime* target)
{
    if (self != nullptr && target != nullptr)
    {
        if (ability == "heal") //Targets health increased ,but depends on half of the targets strength.
        {
            target->setHealth(target->getHealth() + target->getStrength() / 2);
            std::cout << "Healed for " << target->getStrength() / 2 << endl;
            std::cout << "Losses " << target->getStrength() / 2 << " Strength" << endl;
            target->setStrength(target->getStrength() - target->getStrength() / 2);

        }
        else if (ability == "speedHit")
        {
            target->setHealth(target->getHealth() - self->getSpeed());
            std::cout << "Hit for " << self->getSpeed() << endl;
            std::cout << "Losses " << self->getSpeed() / 3 << " Speed";
            self->setSpeed(self->getSpeed() - self->getSpeed() / 3);
        }
        else if (ability == "defenseHit")
        {
            target->setDefense(target->getDefense() - self->getDefense());
            std::cout << "Hit for " << self->getDefense() << endl;
            std::cout << "Losses " << self->getDefense() / 3 << " Defense";
            self->setDefense(self->getDefense() - self->getDefense() / 3);
        }
        else if (ability == "vampHit")
        {
            std::cout << target->getName() << " has got bit by " << self->getName() << endl;
            std::cout << self->getName() << " gain and damged by " << self->getStrength() / 2 << endl;
            self->setHealth(self->getHealth() + abs(self->getStrength() / 2));
            target->setHealth(target->getHealth() - self->getStrength() / 2);
        }
        else if (ability == "IncreaseSpeed")
        {

            std::cout << target->getName() << " got a increase in Speed by 5." << endl;
            target->setSpeed(target->getSpeed() + 5);
        }
        else if (ability == "IncreaseStr")
        {
            std::cout << target->getName() << " got a increase in Strength by 5." << endl;
            target->setStrength(target->getStrength() + 5);
        }
        else if (ability == "IncreaseDef")
        {
            std::cout << target->getName() << " got a increase in Defense by 5." << endl;
            target->setDefense(target->getDefense() + 5);
        }
        else if (ability == "flipStrDef")
        {

            std::cout << target->getName() << " got a flipped Strength and Defense " << endl;
            int temp = target->getDefense();
            target->setDefense(target->getStrength());
            target->setStrength(temp);
        }
        else if (ability == "flipStrSpd")
        {
            std::cout << target->getName() << " got a flipped Strength and Speed " << endl;
            int temp = target->getSpeed();
            target->setDefense(target->getStrength());
            target->setStrength(temp);
        }
        else if (ability == "RandomFlip")
        {
            int temp;
            std::cout << target->getName() << " got a random fliping of stats";
            switch (rand() % 2)
            {
            case 0:
                temp = target->getDefense();
                switch (rand() % 2)
                {
                case 0:
                    target->setDefense(target->getStrength());
                    target->setStrength(temp);
                    break;
                case 1:
                    target->setDefense(target->getSpeed());
                    target->setSpeed(temp);
                    break;
                case 2:
                    target->setDefense(target->getHealth());
                    target->setHealth(temp);
                    break;

                }
                break;
            case 1:
                temp = target->getStrength();
                switch (rand() % 2)
                {
                case 0:
                    target->setStrength(target->getDefense());
                    target->setDefense(temp);
                    break;
                case 1:
                    target->setStrength(target->getSpeed());
                    target->setSpeed(temp);
                    break;
                case 2:
                    target->setStrength(target->getHealth());
                    target->setHealth(temp);
                    break;
                }
                break;
            case 2:
                temp = target->getSpeed();
                switch (rand() % 2)
                {
                case 0:
                    target->setSpeed(target->getDefense());
                    target->setDefense(temp);
                    break;
                case 1:
                    target->setSpeed(target->getStrength());
                    target->setStrength(temp);
                    break;
                case 2:
                    target->setSpeed(target->getHealth());
                    target->setHealth(temp);
                    break;
                }
                break;
            }

        }
    }
    else
    {
        std::cout << "Couldn't Find Ability" << endl;
    }
}



void combat::startBattle(int level) //Starting Battle
{
    string names[] = { "Bobber", "Bob", "Namer", "Gamer", "Soldier", "Gladitor","Slimebob"};
    string type[] = { "Healer", "Soldier", "Mage" };
    char color[] = { 'R','B','G' };
    listEnemy.clear(); // Clear the existing enemies
    for (int x = 0; x < 1 + int(rand() % 3); x++)
    {
        enemey newEnemy(names[rand() % names->size()], level, rand() % 3 + level/3, rand() % 3 + level/3, rand() % 3 + level/3, rand() % 3 + level/3, type[rand() % 3], color[rand() % 3]);
        listEnemy.push_back(newEnemy);
    }
}

void combat::playerTurn(char input) // Tick Player turn
{
    int index;
    int opponent;
    switch (input)
    {
    case 'j':
    case 'J':
        std::cout << "Which Target" << endl;
        //std::cin >> opponent;
        if (!(std::cin >> opponent) || opponent < 0 || opponent >= listEnemy.size()) {//Just in case they input a char
            std::cout << "Invalid input or target index out of range. Please enter a valid target index." << std::endl;
            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input(P.S Comment this out if Replit(Replit don't likey))
            playerTurn(input);
        }
        else
        {
            damage(player->getStrength(), &listEnemy[opponent]);

            if (listEnemy[opponent].getHealth() <= 0)
            {
                if(&listEnemy[opponent]!=nullptr)
                {
                    listEnemy.erase(listEnemy.begin() + opponent);
                }
            }
        }

        break;

    case 'k':
    case 'K':

        std::cout << "Which Ability:" << endl;
        if (!player->getAbilities().empty())
        {
            for (int x = 0; x < player->getAbilities().size(); x++)//Printing out ability for player to see
            {
                std::cout << x << ": " << player->getAbilities()[x] << endl;
            }

            std::cin >> index;

            if (index >= 0 && index <= player->getAbilities().size() - 1)
            {
                std::cout << "Pick an Opponent(index of the opponent) or Self(press 9) " << endl;
                while (!(std::cin >> opponent)) {//Just in case they input a char
                    std::cout << "Invalid input or target index out of range. Please enter a valid target index." << std::endl;
                    std::cin.clear(); // clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//(P.S Comment this out if Replit(Replit don't likey))
                }

                if (opponent == 9)
                {
                    abilities(player->getAbilities()[index], player, player);
                    player->removeAbility(index);
                }
                else
                {
                    while ((opponent < 0 || opponent >= listEnemy.size()))
                    {
                        if (!(std::cin >> opponent) || opponent < 0 || opponent >= listEnemy.size() && opponent != 9) {//Just in case they input a char
                            std::cout << "Invalid input or target index out of range. Please enter a valid target index." << std::endl;
                            std::cin.clear(); // clear error flags
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//(P.S Comment this out if Replit(Replit don't likey))

                        }
                        else if (opponent == 9)
                        {
                            abilities(player->getAbilities()[index], player, player);
                            player->removeAbility(index);
                        }
                        cout << opponent << endl;
                    }

                    if (opponent >= 0 && opponent <= listEnemy.size() - 1)//Double check if the variable opponent position is correct
                    {
                        abilities(player->getAbilities()[index], player, &listEnemy[opponent]);
                        player->removeAbility(index);
                        if (listEnemy[opponent].getHealth() <= 0)
                        {
                            listEnemy.erase(listEnemy.begin() + opponent);
                        }
                    }
                }

            }
            std::cin.ignore();
        }
        break; // Remeber to add isDigit function to check if Player inputs a char for an int;
    case 'l':
    case 'L':
        std::cout << "Choose Opponent's index" << endl;
        while (!(std::cin >> opponent) || opponent < 0 || opponent > listEnemy.size() - 1)
        {
            //Just in case they input a char
            std::cout << "Invalid input or target index out of range. Please enter a valid target index." << std::endl;
            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//(P.S Comment this out if Replit(Replit don't likey))

        }
        listEnemy[opponent].print();

        std::cout << "Choose Attack: J\t Abilities: K\t See Stat: L";
        char t;
        std::cin >> t;
        playerTurn(t);
        break;

    default:
        std::cout << "Invalid Input" << endl; //If it wasn't any of the cases
        char temp;
        std::cin >> temp;
        playerTurn(temp);
        break;
    }
}

void combat::cpuTurn(enemey target) // Tick CPU turn
{
    if (target.getHealth() > 0)
    {
        if (player->getHealth() > 0 && player!= nullptr)
        {
            string method = target.getMethod();//Depends on type of enemy it is
            if (method == "attack")
            {
                damage(target.getStrength(), player);
            }
            else if (method == "heal")
            {
                int lowest = 0;
                for (int x = 0; x < listEnemy.size(); x++)
                {
                    if (listEnemy[x].getHealth() < listEnemy[lowest].getHealth())
                    {
                        lowest = x;

                    }
                }
                abilities(method, &target, &listEnemy[lowest]);
            }
            else
            {
                abilities(method, &target, player);
            }
        }
    }
}

void combat::turnTick() // Next Round
{
    char input;

    std::cin >> input;
    playerTurn(input);
    std::cout << "Press Enter to continue" << endl;
    std::cin.ignore();
    for (int x = 0; x < listEnemy.size(); x++)
    {
        cout << "CPU TURN" << endl;
        cpuTurn(listEnemy[x]);
        std::cout << "Press Enter to continue" << endl;
        std::cin.ignore();
    }
}

string combat::checkStatus() //See if Results
{
    if (listEnemy.size() == 0)
    {

        player->levelup(1);
        std::cin.ignore();
        return "map";
    }
    else if (player->getHealth() <= 0)
    {
        std::cout << "GAME OVER" << endl;
        return "break";
    }
    else
    {
        return "fight";
    }
}
void combat::print() const //Shows Basic
{
    std::cout << "Player" << endl;
    player->print();
    std::cout << "Enemy:" << endl;
    for (int x = 0; x < listEnemy.size(); x++)
    {
        listEnemy[x].print();
        std::cout << endl;
    }
}


void combat::display() const //Shows UI Better
{
    for (int x = 0; x < listEnemy.size(); x++)
    {
        std::cout << x << "\n" << listEnemy[x].getName();
    }
    std::cout << endl;


    string art[3][11] = { {"                                   #%%","#+==*#=+*%##%##%              ##==***%","%#*#=..:--=+****%%           #*.==-%% "," ##*=-..:###*===**###      **::*-=%   "," %%**+***=--:::..::-=+#%%%+=+++#%%    ","   %%%*=-----::::-----***=++=#%       "," %%*+==---##-------%*=+#%#++%%        "," %%*+=##*-----+%----+####%%%          "," %%***====---%#-%*-===*##             "," %%#*****++++++++++++*##%             ","    %%%%%%%%%%%%%%%%%%                "}, {"       %%%###       ","    %%##**+**###    ","    %%###****##%    "," %%%*++=-:::::=+%%% ","%%################%%"," %%*+++--:::::-=+** ","%##++=-==-----==-**#","%#*++=-=+#---#+=-+*#","%#*+###=-------=####","%#**+++++=====+++*##","   %%%%%%%%%%%%%%   "},{"              %%%%%@@%%%    ","           #+=*%        %%  ","         #++++=*@        @  ","    --=*+++++++=-+%     %%  "," #*==++++++++++=--:=#%  %   ","*=#=%*+++++#*#=::...:*%%    ","+=*%#**++++@-@+:::::-=# %   ","+=+++++++++===-------=#  %  ","#==+++++++++=======--+%  #++"," #==+++++++++++++=--#%    %%","   %*+++++++++++=+#%        "} };
    //array for array for strings which contains the line for each art

    for (int x = 0; x < 11; x++) // Makes the art
    {
        for (int i = 0; i < listEnemy.size(); i++)
        {
            switch (listEnemy[i].getColor())
            {
            case 'R':
                std::cout << "\033[31m";
                break;
            case 'G':
                std::cout << "\033[32m";
                break;
            case 'B':
                std::cout << "\033[34m";
                break;
            }

            if (listEnemy[i].getType() == "Soldier")
            {
                std::cout << art[0][x];
            }
            else if (listEnemy[i].getType() == "Mage")
            {
                std::cout << art[1][x];
            }
            else if (listEnemy[i].getType() == "Healer")
            {
                std::cout << art[2][x];
            }
            else
            {
                std::cout << art[0][x];
            }
            std::cout << "\033[37m";

        }
        std::cout << endl;
    }
    /*for (int x = 0; x < attackOrder.size(); x++) Unused Attack Order Function
    {
        cout << attackOrder[x]->getName() << " -> ";
    }
    */
    std::cout << endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    std::cout << "Player Health: ";
    player->display();
    std::cout << "Fight: J\tAbilities: K\t";
    std::cout << "See Stats of Opponent: L" << endl;
}
