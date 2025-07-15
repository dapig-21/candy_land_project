#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
// #include "Player.h"
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

// struct Candy
// {
//     string name;
//     string description;
//     double price;
//     string candy_type;
// };


struct Riddle{
    string question;
    string answer;
};
struct Tile
{
    string color;
    string tile_type;
    bool sticky;
    bool doublesticky;
    bool bigiron;
    bool wallet;
    bool skiis;
};

struct Card
{
    string color;
    bool double_move;
};


class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const int ITEM_AMOUNT=3;
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    int _player_1_position;
    int _player_1_prev_position;
    int _player_2_position;
    int _player_2_prev_position;
    static const int RIDDLE_AMOUNT=4;
    Riddle _riddles[RIDDLE_AMOUNT];
    string _special_items[3]={"Big Iron","Somebody's Wallet","Super Skiis"};

    // int _card_draw_probs [10] = {1,1,1,2,2,3,3,4,5,6};


public:
    Board();
    void resetBoard();
    void displayTile(int);
    void displayBoard();
    int  randomNumGen2(int min, int max);
    bool setPlayer1Position(int);
    bool setPlayer2Position(int);
    void readRiddles();
    void setRiddlesArray(vector <Riddle> all_riddles);
    bool displayRiddle();
    void setTileToSticky(int tile_to_stick);
    void setTileToDoubleSticky(int tile_to_stick);
    void setPlayer1PrevPosition(int position);
    void setPlayer2PrevPosition(int position);
    int getPlayer2PrevPosition();
    int getPlayer1PrevPosition();
    void makeTreasureTiles();
    string is1TreasureTile();
    string is2TreasureTile();
    string decideTreasureTile();
    bool is1SameTile();
    bool is2SameTile();
    void unTreasureTile1();
    void unTreasureTile2();
    int is1TileSticky();
    int is2TileSticky();


    
    
    
    
    Card drawCard();
    string checkCalamity();
    void makeSpecialTiles();
    void allChecks();
    void executeCalamity(string calamity);
    void executeSpecialTile(string speical_tile);
    void executeRiddles();
    void sameTileConstraint();
    


    
    int getBoardSize() const;
    int getCandyStoreCount() const;
    int getPlayer1Position() const;
    int getPlayer2Position() const;
    int moveFromCard1(Card card_drawn, bool testingmode);
    int moveFromCard2(Card card_drawn, bool testinmode);
    
    
    bool addCandyStore(int);
    bool isTileCandyStore(int);
    bool isPosition1CandyStore(int); 
    bool isPosition2CandyStore(int);
    bool isSpecialTile1(int);
    bool isSpecialTile2(int);
    string decideSpecialTile();
    bool isTileTreasure(int);


    bool movePlayer1(int tile_to_move_forward);
    bool movePlayer2(int tile_to_move_forward);
};

#endif