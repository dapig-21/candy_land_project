#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <random>
//#include "Player.h"


using namespace std;
struct Candy
{
    string name;
    string description;
    string effect_type;
    int effect_value;
    double price;
    string candy_type;
};




//vector <Candy> all_avalible_candies=readCandy(...)

//pick random candy to display


class CandyStore
{
    private:
    string _name;
    const static int max_candy_amount = 3;
    Candy _store_selection [max_candy_amount];
    int _candy_amount_in_store;
    int _location;
    


    public:
    CandyStore(string name);
    string getName();
    int getLocation();
    int randomNumGen(int min, int max);
    Candy buyCandy();
    
    void setLocation(int);
    int decideLocation(int candystore_number);
    void setInventory(vector <Candy> all_candies);
    void setName(string name);
    void printInventory();
    bool compareStringCandyStore(string one, string two);
    Candy findCandyInStore(string candy);
    bool removeCandyFromStore(string candy);
    static vector <Candy> readCandy();
    

 
};

#endif