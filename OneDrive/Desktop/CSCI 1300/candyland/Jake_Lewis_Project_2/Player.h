#ifndef CANDY_H
#define CANDY_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "candystore.h"
using namespace std;





class Player{
    private:
        string _name;
        string _real_name;
        const static int _MAX_ITEM_AMOUNT=3;
        const static int _MAX_CANDY_AMOUNT=9;
        int	_stamina;
        double	_gold;
        string	_effect;
        int	_candy_amount;
        Candy _inventory [_MAX_CANDY_AMOUNT];
        int _PLAYER_AMOUNT = 2;
        string _backpack [_MAX_ITEM_AMOUNT]={"","",""};
        int _turn_skip_count;
        
        
    public:
        Player();
        Player(int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE);
        
        int getCandyAmount();

        int randomNumGen3(int min, int max);
        
        bool isPlayerAllowed();

        void setRealName(string name);
        string getRealName();

        void setStamina(int stamina);

        int getStamina();

        bool addToBackPack(string item_to_add);

        void setTurnSkipCount(int turn_ship_count);

        int getTurnSkipCount();
        bool hasBigiron();
        bool hasSpecialSkiis();

        string findCandyati(int i);
        
        void setGold(double gold);

        void transferInventory(Player player);
        
        double getGold();

        string getName();

        void setName(string name);

        void setEffect(string effect);

        void printStats(Player player);

        Candy checkImmunityCandy(Candy posion_applied);

        bool checkRobbersRepel();

        bool swapCandy(string candytoSwap);

        bool playRockPaperScissors(Player player);

        bool hasNineCandies();

        string getEffect();

        void printInventory();
        
        Candy findCandy(string candy_name);

        bool addCandy(Candy candy);

        bool removeCandy(string candy_name);
        
        vector <Player> readPlayers();

         Candy stringToCandy(string candy);


};
#endif

