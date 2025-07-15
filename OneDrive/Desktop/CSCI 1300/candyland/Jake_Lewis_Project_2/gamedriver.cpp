#include "Board.h"
#include "candystore.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// useful for player inputs`
bool compareString(string str1, string str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }
    int len = str1.length();
    for (int i = 0; i < len; i++)
    {
        if (tolower(str1[i]) != tolower(str2[i]))
        {
            return 0;
        }
    }
    return true;
}

//returns whichever player is not currently taking a turn
int switchPlayers(int currentPlayer)
{
    int player;
    if (currentPlayer == 0)
    {
        player = 1;
    }
    else
    {
        player = 0;
    }
    return player;
}

/*
Because calamites have functions that are both from the player and board class,
I decided to implement this function in the driver so I only had to write it once
this function takes the string of a calamity, which is decided in the check special tile
function, and then executes the changes needed based on that input

*/
void doSpecialTile(string calamity, Player players[2], int current_player, Board &board)
{
    bool testingmode = false;
    Candy immunityremove = {"immunity_remove", "Removes immunity", "poision", 10, 0, "other"};
    Candy immunitystolen;
    int randomGold;
    if (current_player == 0)
    {
        if (calamity == "Shortcut Tile")
        {
            cout << "You landed on a Shortcut Tile. You get to move 4 tiles forward!" << endl;
            if (board.getPlayer1Position() >= 79)
            {
                board.setPlayer1Position(83);
            }
            else
            {
                board.setPlayer1Position(board.getPlayer1Position() + 4);
            }
            return;
        }
        else if (calamity == "Gumdrop Forest Tile")
        {
            randomGold = board.randomNumGen2(5, 10);
            cout << "You landed on a Gumdrop Forest Tile. You have to move back 4 spaces and lose " << randomGold << " gold." << endl;
            if (board.getPlayer1Position() <= 4)
            {
                board.setPlayer1Position(0);
            }
            else
            {
                board.setPlayer1Position(board.getPlayer1Position() - 4);
            }
            players[0].setGold(players[0].getGold() - randomGold);
            return;
        }
        else if (calamity == "Ice Cream Shop Tile")
        {
            cout << "You landed on a Ice Cream Shop Tile. You get to draw another card. Note: special tile effects and calamities are voided after this tile" << endl;
            board.movePlayer1(board.moveFromCard1(board.drawCard(), testingmode));
            if (board.getPlayer1Position() >= 82)
            {
                board.setPlayer1Position(83);
            }
            players[0].setStamina(players[0].getStamina() - 1);
            return;
            // check if same tile
            // board.checkCalamity();
        }
        else
        {
            cout << "You landed on a Gingerbread Tile House. You get moved back to your previous position and lose an immunity candy" << endl;
            board.setPlayer1Position(board.getPlayer1PrevPosition());
            immunitystolen= players[0].checkImmunityCandy(immunityremove);
            if(immunitystolen.name!=""||immunitystolen.name!="Empty"){
                players[0].removeCandy(immunitystolen.name);
            }
        }
    }
    else
    {
        if (calamity == "Shortcut Tile")
        {
            cout << "You landed on a Shortcut Tile. You get to move 4 tiles forward!" << endl;
            if (board.getPlayer2Position() >= 79)
            {
                board.setPlayer2Position(83);
            }
            else
            {
                board.setPlayer2Position(board.getPlayer2Position() + 4);
            }
        }
        else if (calamity == "Gumdrop Forest Tile")
        {
            randomGold = board.randomNumGen2(5, 10);
            cout << "You landed on a Gumdrop Forest Tile. You have to move back 4 spaces and lose " << randomGold << " gold." << endl;
            if (board.getPlayer2Position() <= 4)
            {
                board.setPlayer2Position(0);
            }
            else
            {
                board.setPlayer2Position(board.getPlayer2Position() - 4);
            }
            players[1].setGold(players[1].getGold() - randomGold);
        }
        else if (calamity == "Ice Cream Shop Tile")
        {
            cout << "You landed on a Ice Cream Shop Tile. You get to draw another card." << endl;
            board.movePlayer2(board.moveFromCard1(board.drawCard(), testingmode));
            if (board.getPlayer2Position() >= 82)
            {
                board.setPlayer2Position(82);
            }
            players[1].setStamina(players[1].getStamina() - 1);
            // check if same tile
            // board.checkCalamity();
        }
        else
        {
            cout << "You landed on a Gingerbread Tile House. You get moved back to your previous position and lose an immunity candy" << endl;
            board.setPlayer2Position(board.getPlayer2PrevPosition());
            immunitystolen= players[1].checkImmunityCandy(immunityremove);
            if(immunitystolen.name!=""||immunitystolen.name!="Empty"){
                players[1].removeCandy(immunitystolen.name);
            }
        }
    }
}
/*
Similar to do special tile, this function takes the input of check calamity, and then makes the changes
to the players position and stats as needed. However, this function also checks if the player has a 
special item to void the effect of a calmity, such as the big iron or special skiis

*/
void doCalamites(string calamity, Player players[2], int current_player, Board &board)
{
    int tilesMoved = board.randomNumGen2(1, 5);
    int coinsStolen = board.randomNumGen2(5, 10);
    if (calamity == "")
    {
        return;
    }
    else if (calamity == "Candy Bandits")
    {
        cout << "Oh no! Candy Bandits" << endl;
        if (!players[current_player].hasBigiron())
        {
            cout << "The bandits have swiped " << coinsStolen << " coins from you" << endl; // maybe do a robbers rapel type thing, if time
            players[current_player].setGold(players[current_player].getGold() - coinsStolen);
        }
        else
        {
            cout << "The bandits fear your big iron and have left you alone" << endl;
        }
    }

    else if (calamity == "Labrynth")
    {
        cout << "Oh no! You're trapped in the lollipop labrynth, and have to use a turn to get back out. However, if you win rock paper scissors, you can get your turn back" << endl;
        if (players[current_player].playRockPaperScissors(players[current_player]))
        {
            cout << "You don't lose a turn!" << endl;
        }
        else
        {
            cout << "You have to skip a turn" << endl;
            players[current_player].setTurnSkipCount(1); // this might work
        }
    }
    else if (calamity == "Avalanche")
    {
        cout << "You've been caught in a candy avalanche!" << endl;
        if (!players[current_player].hasSpecialSkiis())
        {
            cout << "You've been moved " << tilesMoved << " tiles backwards" << endl;
            if (current_player == 0)
            {
                board.movePlayer1(-tilesMoved);
            }
            else
            {
                board.movePlayer2(-tilesMoved);
            }
        }
        else
        {
            cout << "Your special skiis move you forward " << tilesMoved << endl;
            if (current_player == 0)
            {
                board.movePlayer1(tilesMoved);
            }
            else
            {
                board.movePlayer2(tilesMoved);
            }
        }
    }
    else
    {
        cout << "You've been caught in sticky taffy. You are stuck for one turn!" << endl;
        players[current_player].setTurnSkipCount(1);
    }
}
//This function prints player stats to a results txt file at the end of a game
void printResults(Player players[2])
{
    ofstream results("results.txt");
    if (results.fail())
    {
        cout << "Failed to open file" << endl;
    }
    else
    {
        results << "Player one name: " << players[0].getRealName() << endl;
        results << "Player one character: " << players[0].getName() << endl;
        results << "Player one stamina remaining: " << players[0].getStamina() << endl;
        results << "Player one candies amount: " << players[0].getCandyAmount() << endl;
        results << "Player one inventory: " << endl;
        for (int i = 0; i < 9; i++)
        {
            if (i == 3 || i == 6 || i == 9)
            {
                results << "|" << endl;
            }
            string whattoprint = "";
            if (players[0].findCandyati(i) == "Empty")
            {
                whattoprint = "Empty";
            }
            else
            {
                whattoprint = players[0].findCandyati(i);
            }
            results << "|[" << whattoprint << "]";
        }
        results << "|" << endl;
    }

    results << "Player two name: " << players[1].getRealName() << endl;
    results << "Player two character: " << players[1].getName() << endl;
    results << "Player two stamina remaining: " << players[1].getStamina() << endl;
    results << "Player two candies amount: " << players[1].getCandyAmount() << endl;
    results << "Player two inventory: " << endl;
    for (int i = 0; i < 9; i++)
    {
        if (i == 3 || i == 6 || i == 9)
        {
            results << "|" << endl;
        }
        string whattoprint = "";
        if (players[1].findCandyati(i) == "Empty")
        {
            whattoprint = "Empty";
        }
        else
        {
            whattoprint = players[1].findCandyati(i);
        }
        results << "|[" << whattoprint << "]";
    }
    results << "|" << endl;
}

int main()
{

    //lots of data types, probably could've done this better :)
    Player players[2];
    Board board;
    Player functionman;
    Player tempplayer;
    Player displayplayer2;
    Player displayplayer3;
    string text_inputs;
    Candy candyobj;
    string treasureTile;
    int playerindex = 0;
    int randomWalletAmount;
    int randomGoldAmount;
    int prevPosition1;
    int prevPosition2;
    int menuselection;
    string name_of_candy_to_buy;
    Candy candy_to_buy;
    bool found = false;
    bool enoughgold = false;
    bool testingmode = false;
    bool leave;
    bool player1has9candies = players[0].hasNineCandies();
    bool player2has9candies = players[1].hasNineCandies();
    int randomGold;
    int candystoreindex;
    bool isaPlayer;
    bool wantsToLeave;
    bool nextPlayer = false;
    bool validmenuinput = false;
    bool validcandymove = false;
    string wantToVisitCandyStore;
    string playerrealname;
    string specialTile;
    bool startofgame = true;
    bool gameisover = false;
    vector<Player> playable_characters;
    playable_characters = functionman.readPlayers();
    CandyStore menu_store("Menu_store");
    vector<Candy> all_candies = menu_store.readCandy();
    board.readRiddles();
    menu_store.setInventory(all_candies);  //makes tiles special/treasure and makes candystores
    players[0].setTurnSkipCount(0);
    players[1].setTurnSkipCount(0);
    board.makeSpecialTiles();
    board.makeTreasureTiles();
    CandyStore candystore1("store1");
    CandyStore candystore2("store2");
    CandyStore candystore3("store3");
    // candystore1.setLocation(candystore1.decideLocation(0));
    candystore2.setLocation(candystore2.decideLocation(1));
    candystore3.setLocation(candystore3.decideLocation(2));
    // board.addCandyStore(candystore1.getLocation());
    board.addCandyStore(candystore2.getLocation());
    board.addCandyStore(candystore3.getLocation());
    candystore1.setInventory(all_candies);
    candystore2.setInventory(all_candies);
    candystore3.setInventory(all_candies);

    cout << "Welcome to candyland!" << endl;
    // getline(cin, text_inputs);
    while (startofgame == true) //this checks to make sure all players have had a chance to pick a character and go to the store
    {
        cout << "Please enter player " << playerindex + 1 << "'s name" << endl;
        getline(cin, playerrealname);
        if (playerrealname == "testmode") // if a player's name is testmode, it goes into testmode
        {
            testingmode = true;
            candystore1.setLocation(3);
            board.addCandyStore(candystore1.getLocation());
        }
        else
        {
            candystore1.setLocation(candystore1.decideLocation(0));
            board.addCandyStore(candystore1.getLocation());
        }
        players[playerindex].setRealName(playerrealname);
        cout << "What's up " << players[playerindex].getRealName() << "! Here is a list of playable characters to choose from" << endl;
        cout << endl;
        for (int i = 0; i < playable_characters.size(); i++)
        {
            Player displayplayer1 = playable_characters.at(i);
            displayplayer1.printStats(displayplayer1);
            cout << "---------------------------" << endl;
            cout << endl;
        }

        do
        {
            isaPlayer = false;
            cout << "Type the name of the character you'd like to use" << endl;
            getline(cin, text_inputs);
            // cout<<"Text input for character Selection: "<< text_inputs<<endl;
            for (int i = 0; i < playable_characters.size(); i++)
            {
                if (compareString(text_inputs, playable_characters.at(i).getName()))
                {
                    isaPlayer = true;
                    Player transferplayer = playable_characters.at(i);
                    players[playerindex].setStamina(playable_characters.at(i).getStamina());
                    players[playerindex].setName(playable_characters.at(i).getName());
                    players[playerindex].setGold(playable_characters.at(i).getGold());
                    players[playerindex].transferInventory(transferplayer);
                    playable_characters.erase(playable_characters.begin() + (i)); 
                    break;
                }
            }
            if (!isaPlayer)
            {
                cout << "Not a playable character, enter again" << endl;
            }

        } while (!isaPlayer); //checks to make sure a player has made a valid selection
        cout << endl;
        cout << "Good choice!. Here are your updated stats:" << endl;
        functionman.printStats(players[playerindex]);
        cout << "Would you like to visit the candystore before the game starts (y/n)" << endl;
        getline(cin, text_inputs);
        if (text_inputs == "y") //anything besides y voids the choice
        {
            menu_store.printInventory();

            cout << "What candy would you like to purchase?" << endl;
            do
            {
                do
                {

                    getline(cin, name_of_candy_to_buy);
                    // cin.ignore(1000, '\n');
                    candy_to_buy.name = name_of_candy_to_buy;
                    if (name_of_candy_to_buy == "L")
                    {
                        found = true;
                    }
                    else if (menu_store.findCandyInStore(candy_to_buy.name).name == "Empty"||name_of_candy_to_buy=="Empty")
                    {
                        found = false;
                    }

                    else if (menu_store.findCandyInStore(candy_to_buy.name).name == name_of_candy_to_buy)
                    {
                        candy_to_buy = menu_store.findCandyInStore(candy_to_buy.name);
                        found = true;
                    }

                    if (found == false)
                    {
                        cout << name_of_candy_to_buy << " not found in this store, enter a different name" << endl;
                    }
                } while (found == false); //makes sure the candy is present

                if (name_of_candy_to_buy == "L")
                {
                    enoughgold = true;
                    cout << "Exiting store" << endl;
                    playerindex++;
                }
                else if (players[playerindex].getGold() >= candy_to_buy.price && found == true)
                {
                    enoughgold = true;
                    cout << players[playerindex].getRealName() << " has succsessfully purchased " << candy_to_buy.name << endl;
                    players[playerindex].addCandy(candy_to_buy);
                    players[playerindex].setGold(players[playerindex].getGold() - candy_to_buy.price);
                    menu_store.removeCandyFromStore(name_of_candy_to_buy);
                    cout << "Here is " << players[playerindex].getRealName() << "'s updated stats" << endl;
                    players[playerindex].printStats(players[playerindex]);
                    cout << endl;
                    playerindex++;
                }

                else
                {
                    cout << "You don't have enough gold to purchase this item, enter a new item. If you need to leave, enter 'L'" << endl;
                }

            } while (enoughgold == false);//checks to make sure the player has enough gold to buy and item
        }
        else if (text_inputs == "n")
        {
            playerindex++;
        }
        if (playerindex > 1)
        {
            startofgame = false;
        }
    }
    cout << "Let's start the game! A coin toss will decide who gets to start" << endl;
    if (functionman.randomNumGen3(1, 2) == 1)
    {
        cout << "It's heads! Player one will start" << endl; // maybe do a chronos thread to add suspence
        playerindex = 0;
    }
    else
    {
        cout << "It's tails! Player two will start!" << endl;
        playerindex = 1;
    }
    cout << "Here is the board:" << endl;
    board.displayBoard();
    while (board.getPlayer1Position() < 82 && board.getPlayer2Position() < 82) //checks to make sure the game isn't over
    {
        do
        {

            cout << players[playerindex].getRealName() << ", please select an option below:" << endl;
            cout << "1. Draw a card" << endl;
            cout << "2. Use a candy" << endl;
            cout << "3. Show your current stats" << endl;
            cin >> menuselection;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(100000, '\n');
                validmenuinput = false;
                cout << "Invalid Input" << endl;
                cin >> menuselection;
            }
            if (menuselection == 1 || menuselection == 2 || menuselection == 3)
            {
                validmenuinput = true;
            }
            else
            {
                cout << "Invalid input" << endl;
            }
        } while (validmenuinput == false); //ensures a valid menu input

        if (menuselection == 1)
        {

            // cout<<"Drawing Card"<<endl;
            if (playerindex == 0)
            {
                board.movePlayer1(board.moveFromCard1(board.drawCard(), testingmode)); //moves a player based on the card
                if (board.getPlayer1Position() >= 82)
                {
                    board.setPlayer1Position(82); //if a player goes over the board, moves them back
                }
                if (board.getPlayer1Position() >= 82)
                {
                    board.setPlayer1Position(82);
                }
                if (board.is1SameTile()) //checks same tile contraints
                {
                    if (!players[playerindex].hasBigiron())
                    {
                        randomGold = board.randomNumGen2(5, 30);
                        cout << "Player one has landed on the same tile as player two and has had " << randomGold << " gold stolen" << endl;
                        players[playerindex].setGold(players[playerindex].getGold() - randomGold);
                        players[switchPlayers(playerindex)].setGold(players[switchPlayers(playerindex)].getGold() + randomGold);
                        board.setPlayer1Position(board.getPlayer1Position() - 1);
                       // playerindex = switchPlayers(playerindex);
                    }
                    else
                    {
                        cout << "Player one has landed on the same tile as player two. With the big iron on his hip, no gold can be taken" << endl;
                        board.setPlayer2Position(board.getPlayer2Position() - 1);
                        //playerindex = switchPlayers(playerindex);
                    }
                }

                else if (board.isPosition1CandyStore(board.getPlayer1Position())) //checks if a place is a candy store
                {
                    cout << "You landed on a candy store! Would you like to visit? (y/n)" << endl;
                    // cin.clear();
                    cin.ignore(10000, '\n');
                    getline(cin, wantToVisitCandyStore);
                    if (wantToVisitCandyStore == "y")
                    {
                        if (players[0].hasNineCandies() == true)
                        {
                            cout << "You already have 9 candies in your inventory. If you buy a candy, you will have to swap a candy in its place" << endl;
                        }
                        cout << "Here is the inventory: " << endl;
                        if (board.getPlayer1Position() == candystore1.getLocation())//checks what candy store the player has landed on
                        {

                            candystore1.printInventory();
                            do
                            {
                                do
                                {
                                    // cin.ignore(10000, '\n');
                                    getline(cin, name_of_candy_to_buy);
                                    candy_to_buy.name = name_of_candy_to_buy;
                                    if (name_of_candy_to_buy == "L")
                                    {
                                        found = true;
                                    }
                                    else if (candystore1.findCandyInStore(candy_to_buy.name).name == "Empty" || candystore1.findCandyInStore(candy_to_buy.name).name == ""||name_of_candy_to_buy=="Empty")
                                    {
                                        found = false;
                                    }

                                    else if (candystore1.findCandyInStore(candy_to_buy.name).name == name_of_candy_to_buy)
                                    {
                                        candy_to_buy = candystore1.findCandyInStore(candy_to_buy.name);
                                        found = true;
                                    }

                                    if (found == false)
                                    {
                                        cout << name_of_candy_to_buy << " not found in this store, enter a different name" << endl;
                                    }
                                } while (found == false);

                                if (name_of_candy_to_buy == "L")
                                {
                                    enoughgold = true;
                                    cout << "Exiting store" << endl;
                                    playerindex++;
                                }
                                else if (players[playerindex].getGold() >= candy_to_buy.price && found == true)
                                {
                                    enoughgold = true;
                                    cout << players[playerindex].getRealName() << " has succsessfully purchased " << candy_to_buy.name << endl;
                                    if (players[playerindex].hasNineCandies() == false) //puts candy in inventory
                                    {
                                        players[playerindex].addCandy(candy_to_buy);
                                    }
                                    else
                                    {
                                        cout << "What candy would you like to swap out of your inventory" << endl; //swaps a candy
                                        getline(cin, text_inputs);
                                        while (players[playerindex].findCandy(text_inputs).name == "Empty")
                                        {
                                            cout << "Candy not found in your inventory, please enter a different candy" << endl;
                                            getline(cin, text_inputs);
                                        }
                                        players[playerindex].swapCandy(candy_to_buy.name);
                                    }
                                    players[playerindex].setGold(players[playerindex].getGold() - candy_to_buy.price);
                                    candystore1.removeCandyFromStore(name_of_candy_to_buy);
                                    cout << "Here is " << players[playerindex].getName() << "'s updated stats" << endl;
                                    players[playerindex].printStats(players[playerindex]);
                                    cout << endl;
                                    playerindex++;
                                }

                                else
                                {
                                    cout << "You don't have enough gold to purchase this item, enter a new item. If you need to leave, enter 'L'" << endl;
                                }

                            } while (enoughgold == false);
                        }
                        else if (board.getPlayer1Position() == candystore2.getLocation())
                        {
                            candystore2.printInventory();
                            do
                            {
                                do
                                {
                                    cin.ignore(1000, '\n');
                                    getline(cin, name_of_candy_to_buy);
                                    candy_to_buy.name = name_of_candy_to_buy;
                                    if (name_of_candy_to_buy == "L")
                                    {
                                        found = true;
                                    }
                                    else if (candystore2.findCandyInStore(candy_to_buy.name).name == "Empty" || candystore2.findCandyInStore(candy_to_buy.name).name == ""||name_of_candy_to_buy=="Empty")
                                    {
                                        found = false;
                                    }

                                    else if (candystore2.findCandyInStore(candy_to_buy.name).name == name_of_candy_to_buy)
                                    {
                                        candy_to_buy = candystore2.findCandyInStore(candy_to_buy.name);
                                        found = true;
                                    }

                                    if (found == false)
                                    {
                                        cout << name_of_candy_to_buy << " not found in this store, enter a different name" << endl;
                                    }
                                } while (found == false);

                                if (name_of_candy_to_buy == "L")
                                {
                                    enoughgold = true;
                                    cout << "Exiting store" << endl;
                                    playerindex++;
                                }
                                else if (players[playerindex].getGold() >= candy_to_buy.price && found == true)
                                {
                                    enoughgold = true;
                                    cout << players[playerindex].getRealName() << " has succsessfully purchased " << candy_to_buy.name << endl;
                                    if (players[playerindex].hasNineCandies() == false)
                                    {
                                        players[playerindex].addCandy(candy_to_buy);
                                    }
                                    else
                                    {
                                        cout << "What candy would you like to swap out of your inventory" << endl;
                                        getline(cin, text_inputs);
                                        while (players[playerindex].findCandy(text_inputs).name == "Empty")
                                        {
                                            cout << "Candy not found in your inventory, please enter a different candy" << endl;
                                            getline(cin, text_inputs);
                                        }
                                        players[playerindex].swapCandy(candy_to_buy.name);
                                    }
                                    // players[playerindex].addCandy(candy_to_buy);
                                    players[playerindex].setGold(players[playerindex].getGold() - candy_to_buy.price);
                                    candystore2.removeCandyFromStore(name_of_candy_to_buy);
                                    cout << "Here is " << players[playerindex].getName() << "'s updated stats" << endl;
                                    players[playerindex].printStats(players[playerindex]);
                                    cout << endl;
                                    playerindex++;
                                }

                                else
                                {
                                    cout << "You don't have enough gold to purchase this item, enter a new item. If you need to leave, enter 'L'" << endl;
                                }

                            } while (enoughgold == false);
                        }
                        else
                        {
                            candystore3.printInventory();
                            do
                            {
                                do
                                {

                                    getline(cin, name_of_candy_to_buy);
                                    candy_to_buy.name = name_of_candy_to_buy;
                                    if (name_of_candy_to_buy == "L")
                                    {
                                        found = true;
                                    }
                                    else if (candystore3.findCandyInStore(candy_to_buy.name).name == "Empty" || candystore3.findCandyInStore(candy_to_buy.name).name == ""||name_of_candy_to_buy=="Empty")
                                    {
                                        found = false;
                                    }

                                    else if (candystore3.findCandyInStore(candy_to_buy.name).name == name_of_candy_to_buy)
                                    {
                                        candy_to_buy = candystore3.findCandyInStore(candy_to_buy.name);
                                        found = true;
                                    }

                                    if (found == false)
                                    {
                                        cout << name_of_candy_to_buy << " not found in this store, enter a different name" << endl;
                                    }
                                } while (found == false);

                                if (name_of_candy_to_buy == "L")
                                {
                                    enoughgold = true;
                                    cout << "Exiting store" << endl;
                                    playerindex++;
                                }
                                else if (players[playerindex].getGold() >= candy_to_buy.price && found == true)
                                {
                                    enoughgold = true;
                                    cout << players[playerindex].getRealName() << " has succsessfully purchased " << candy_to_buy.name << endl;
                                    if (players[playerindex].hasNineCandies() == false)
                                    {
                                        players[playerindex].addCandy(candy_to_buy);
                                    }
                                    else
                                    {
                                        cout << "What candy would you like to swap out of your inventory" << endl;
                                        getline(cin, text_inputs);
                                        while (players[playerindex].findCandy(text_inputs).name == "Empty")
                                        {
                                            cout << "Candy not found in your inventory, please enter a different candy" << endl;
                                            getline(cin, text_inputs);
                                        }
                                        players[playerindex].swapCandy(candy_to_buy.name);
                                    }
                                    // players[playerindex].addCandy(candy_to_buy);
                                    players[playerindex].setGold(players[playerindex].getGold() - candy_to_buy.price);
                                    candystore3.removeCandyFromStore(name_of_candy_to_buy);
                                    cout << "Here is " << players[playerindex].getName() << "'s updated stats" << endl;
                                    players[playerindex].printStats(players[playerindex]);
                                    cout << endl;
                                    playerindex++;
                                }

                                else
                                {
                                    cout << "You don't have enough gold to purchase this item, enter a new item. If you need to leave, enter 'L'" << endl;
                                }

                            } while (enoughgold == false);
                        }
                    }
                    players[0].setStamina(players[0].getStamina() - 1);
                }

                // cout<<"Position before "<<board.getPlayer1Position()<<endl;
                else if (board.isSpecialTile1(board.getPlayer1Position())) //checks if a player is on a special tile
                {

                    specialTile = board.decideSpecialTile();
                    doSpecialTile(specialTile, players, 0, board);
                }
                else if (board.is1TreasureTile() != "") //means a special tile has been landed on
                {
                    cout << "You've landed on a treasure tile. Answer a riddle to obtain a special prize" << endl;
                    if (board.displayRiddle())
                    {
                        treasureTile = board.is1TreasureTile();
                        cout << "You've obtained " << treasureTile << endl;
                        if (treasureTile == "somebody's wallet")
                        {
                            randomWalletAmount = board.randomNumGen2(20, 50);
                            cout << "You get " << randomWalletAmount << " gold and an expired target card!" << endl; //having a little fun
                            players[playerindex].setGold(players[playerindex].getGold() + randomWalletAmount);
                        }
                        players[playerindex].addToBackPack(treasureTile);
                        board.unTreasureTile1();
                    }
                    else
                    {
                        cout << "You do not get the special treasure" << endl;
                    }
                }
                else
                {
                    doCalamites(board.checkCalamity(), players, playerindex, board); //checks a calamity if all other conditions are false
                }
            }
            else //means it is player two's turn, does everything the same but with player two instead
            {
                board.movePlayer2(board.moveFromCard2(board.drawCard(), testingmode));
                if (board.getPlayer2Position() >= 82)
                {
                    board.setPlayer2Position(83);
                }
                players[1].setStamina(players[1].getStamina() - 1);
                if (board.is2SameTile())
                {
                    if (!players[playerindex].hasBigiron())
                    {
                        randomGold = board.randomNumGen2(5, 30);
                        cout << "Player two has landed on the same tile as player one and has had " << randomGold << " gold stolen" << endl;
                        players[playerindex].setGold(players[playerindex].getGold() - randomGold);
                        players[switchPlayers(playerindex)].setGold(players[switchPlayers(playerindex)].getGold() + randomGold);
                        board.setPlayer2Position(board.getPlayer2Position() - 1);
                        //playerindex = switchPlayers(playerindex);
                    }
                    else
                    {
                        cout << "Player two has landed on the same tile as player one. With the big iron on his hip, no gold can be taken" << endl;
                        board.setPlayer2Position(board.getPlayer2Position() - 1);
                        //playerindex = switchPlayers(playerindex);
                    }
                }

                else if (board.isPosition2CandyStore(board.getPlayer2Position()))
                {
                    cout << "You landed on a candy store! Would you like to visit?" << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    getline(cin, wantToVisitCandyStore);
                    if (wantToVisitCandyStore == "y")
                    {
                        if (players[1].hasNineCandies() == true)
                        {
                            cout << "You already have 9 candies in your inventory. If you buy a candy, you will have to swap a candy in its place" << endl;
                        }
                        cout << "Here is the inventory: " << endl;
                        if (board.getPlayer1Position() == candystore1.getLocation())
                        {

                            candystore1.printInventory();
                            do
                            {
                                do
                                {

                                    getline(cin, name_of_candy_to_buy);
                                    candy_to_buy.name = name_of_candy_to_buy;
                                    if (name_of_candy_to_buy == "L")
                                    {
                                        found = true;
                                    }
                                    else if (candystore1.findCandyInStore(candy_to_buy.name).name == "Empty"||name_of_candy_to_buy=="Empty")
                                    {
                                        found = false;
                                    }

                                    else if (candystore1.findCandyInStore(candy_to_buy.name).name == name_of_candy_to_buy)
                                    {
                                        candy_to_buy = candystore1.findCandyInStore(candy_to_buy.name);
                                        found = true;
                                    }

                                    if (found == false)
                                    {
                                        cout << name_of_candy_to_buy << " not found in this store, enter a different name" << endl;
                                    }
                                } while (found == false);

                                if (name_of_candy_to_buy == "L")
                                {
                                    enoughgold = true;
                                    cout << "Exiting store" << endl;
                                    playerindex++;
                                }
                                else if (players[playerindex].getGold() >= candy_to_buy.price && found == true)
                                {
                                    enoughgold = true;
                                    cout << players[playerindex].getRealName() << " has succsessfully purchased " << candy_to_buy.name << endl;
                                    if (players[playerindex].hasNineCandies() == false)
                                    {
                                        players[playerindex].addCandy(candy_to_buy);
                                    }
                                    else
                                    {
                                        cout << "What candy would you like to swap out of your inventory" << endl;
                                        getline(cin, text_inputs);
                                        while (players[playerindex].findCandy(text_inputs).name == "Empty")
                                        {
                                            cout << "Candy not found in your inventory, please enter a different candy" << endl;
                                            getline(cin, text_inputs);
                                        }
                                        players[playerindex].swapCandy(candy_to_buy.name);
                                    }
                                    players[playerindex].setGold(players[playerindex].getGold() - candy_to_buy.price);
                                    candystore1.removeCandyFromStore(name_of_candy_to_buy);
                                    cout << "Here is " << players[playerindex].getName() << "'s updated stats" << endl;
                                    players[playerindex].printStats(players[playerindex]);
                                    cout << endl;
                                    playerindex++;
                                }

                                else
                                {
                                    cout << "You don't have enough gold to purchase this item, enter a new item. If you need to leave, enter 'L'" << endl;
                                }

                                // //if(buying_player.getGold()>=candy_to_buy.price){
                                //     enoughgold=true;
                                // }

                            } while (enoughgold == false);
                        }
                        else if (board.getPlayer1Position() == candystore2.getLocation())
                        {
                            candystore2.printInventory();
                            do
                            {
                                do
                                {

                                    getline(cin, name_of_candy_to_buy);
                                    candy_to_buy.name = name_of_candy_to_buy;
                                    if (name_of_candy_to_buy == "L")
                                    {
                                        found = true;
                                    }
                                    else if (candystore2.findCandyInStore(candy_to_buy.name).name == "Empty"||name_of_candy_to_buy=="Empty")
                                    {
                                        found = false;
                                    }

                                    else if (candystore2.findCandyInStore(candy_to_buy.name).name == name_of_candy_to_buy)
                                    {
                                        candy_to_buy = candystore2.findCandyInStore(candy_to_buy.name);
                                        found = true;
                                    }

                                    if (found == false)
                                    {
                                        cout << name_of_candy_to_buy << " not found in this store, enter a different name" << endl;
                                    }
                                } while (found == false);

                                if (name_of_candy_to_buy == "L")
                                {
                                    enoughgold = true;
                                    cout << "Exiting store" << endl;
                                    playerindex++;
                                }
                                else if (players[playerindex].getGold() >= candy_to_buy.price && found == true)
                                {
                                    enoughgold = true;
                                    cout << players[playerindex].getRealName() << " has succsessfully purchased " << candy_to_buy.name << endl;
                                    if (players[playerindex].hasNineCandies() == false)
                                    {
                                        players[playerindex].addCandy(candy_to_buy);
                                    }
                                    else
                                    {
                                        cout << "What candy would you like to swap out of your inventory" << endl;
                                        getline(cin, text_inputs);
                                        while (players[playerindex].findCandy(text_inputs).name == "Empty")
                                        {
                                            cout << "Candy not found in your inventory, please enter a different candy" << endl;
                                            getline(cin, text_inputs);
                                        }
                                        players[playerindex].swapCandy(candy_to_buy.name);
                                    }
                                    // players[playerindex].addCandy(candy_to_buy);
                                    players[playerindex].setGold(players[playerindex].getGold() - candy_to_buy.price);
                                    candystore2.removeCandyFromStore(name_of_candy_to_buy);
                                    cout << "Here is " << players[playerindex].getName() << "'s updated stats" << endl;
                                    players[playerindex].printStats(players[playerindex]);
                                    cout << endl;
                                    playerindex++;
                                }

                                else
                                {
                                    cout << "You don't have enough gold to purchase this item, enter a new item. If you need to leave, enter 'L'" << endl;
                                }

                                // //if(buying_player.getGold()>=candy_to_buy.price){
                                //     enoughgold=true;
                                // }

                            } while (enoughgold == false);
                        }
                        else
                        {
                            candystore3.printInventory();
                            do
                            {
                                do
                                {

                                    getline(cin, name_of_candy_to_buy);
                                    candy_to_buy.name = name_of_candy_to_buy;
                                    if (name_of_candy_to_buy == "L")
                                    {
                                        found = true;
                                    }
                                    else if (candystore3.findCandyInStore(candy_to_buy.name).name == "Empty"||name_of_candy_to_buy=="Empty")
                                    {
                                        found = false;
                                    }

                                    else if (candystore3.findCandyInStore(candy_to_buy.name).name == name_of_candy_to_buy)
                                    {
                                        candy_to_buy = candystore3.findCandyInStore(candy_to_buy.name);
                                        found = true;
                                    }

                                    if (found == false)
                                    {
                                        cout << name_of_candy_to_buy << " not found in this store, enter a different name" << endl;
                                    }
                                } while (found == false);

                                if (name_of_candy_to_buy == "L")
                                {
                                    enoughgold = true;
                                    cout << "Exiting store" << endl;
                                    playerindex++;
                                }
                                else if (players[playerindex].getGold() >= candy_to_buy.price && found == true)
                                {
                                    enoughgold = true;
                                    cout << players[playerindex].getRealName() << " has succsessfully purchased " << candy_to_buy.name << endl;
                                    if (players[playerindex].hasNineCandies() == false)
                                    {
                                        players[playerindex].addCandy(candy_to_buy);
                                    }
                                    else
                                    {
                                        cout << "What candy would you like to swap out of your inventory" << endl;
                                        getline(cin, text_inputs);
                                        while (players[playerindex].findCandy(text_inputs).name == "Empty")
                                        {
                                            cout << "Candy not found in your inventory, please enter a different candy" << endl;
                                            getline(cin, text_inputs);
                                        }
                                        players[playerindex].swapCandy(candy_to_buy.name);
                                    }
                                    // players[playerindex].addCandy(candy_to_buy);
                                    players[playerindex].setGold(players[playerindex].getGold() - candy_to_buy.price);
                                    candystore3.removeCandyFromStore(name_of_candy_to_buy);
                                    cout << "Here is " << players[playerindex].getName() << "'s updated stats" << endl;
                                    players[playerindex].printStats(players[playerindex]);
                                    cout << endl;
                                    playerindex++;
                                }

                                else
                                {
                                    cout << "You don't have enough gold to purchase this item, enter a new item. If you need to leave, enter 'L'" << endl;
                                }

                                // //if(buying_player.getGold()>=candy_to_buy.price){
                                //     enoughgold=true;
                                // }

                            } while (enoughgold == false);
                        }
                    }
                }
                else if (board.isSpecialTile2(board.getPlayer2Position()))
                {
                    specialTile = board.decideSpecialTile();
                    cout << board.decideSpecialTile() << endl;
                    doSpecialTile(specialTile, players, 1, board);

                    // need execute special tile
                }
                else if (board.is2TreasureTile() != "")
                {
                    cout << "You've landed on a treasure tile. Answer a riddle to obtain a special prize" << endl;
                    if (board.displayRiddle())
                    {
                        treasureTile = board.is2TreasureTile();
                        cout << "You've obtained " << treasureTile << endl;
                        if (treasureTile == "somebody's wallet")
                        {
                            randomWalletAmount = board.randomNumGen2(20, 50);
                            cout << "You get " << randomWalletAmount << " gold and an expired target card!" << endl;
                            players[playerindex].setGold(players[playerindex].getGold() + randomWalletAmount);
                        }
                        players[playerindex].addToBackPack(treasureTile);
                        board.unTreasureTile2();
                    }
                    else
                    {
                        cout << "You do not get the special treasure" << endl;
                    }
                }
                else
                {
                    doCalamites(board.checkCalamity(), players, playerindex, board);
                }
            }
            cout << "Here is the updated board" << endl;
            board.displayBoard();
            if (players[switchPlayers(playerindex)].isPlayerAllowed())
            {
                playerindex = switchPlayers(playerindex);
            }
        }
        else if (menuselection == 3) //if they wanna see their stats
        {
            functionman.printStats(players[playerindex]);
        }

        else if (menuselection == 2)
        {
            validcandymove = false;
            // cout<<"P1 c amount "<<players[0].getCandyAmount()<<endl;
            // cout<<"P2 c amount "<<players[1].getCandyAmount()<<endl;
            if (players[playerindex].getCandyAmount() == 0)
            {
                cout << "You don't have any candy left. Enter \"Leave\" to exit the menu" << endl;
                validcandymove = true;
            }
            cout << "Here is your inventory" << endl;
            players[playerindex].printInventory();
            do
            {
                cout << "Enter the candy you'd like to use" << endl;
                cin.ignore(10000, '\n'); //buggy and annoying!!!!!!!!!!!!
                getline(cin, text_inputs);
                while (players[playerindex].findCandy(text_inputs).name == "")
                {
                    if (text_inputs == "Leave")
                    {
                        break;
                    }
                    cout << text_inputs << " is not in your candy inventory, enter a different candy or enter Leave to leave the menu" << endl;
                    getline(cin, text_inputs);
                }
                // use the candy
                if (text_inputs == "Leave")
                {
                    cout << "Leaving menu" << endl;
                    break;
                }
                else
                {
                    candyobj = functionman.stringToCandy(text_inputs); //makes a candy of the player input
                }
                // cout<<candyobj.candy_type<<endl;
                // cout<<candyobj.effect_value<<endl;
                if (candyobj.candy_type == "magical") //for magic candies
                {
                    players[playerindex].setStamina(players[playerindex].getStamina() + candyobj.effect_value);
                    cout << "Succsessfully used " << candyobj.name << " to increase stamina by " << candyobj.effect_value << endl;
                    players[playerindex].removeCandy(text_inputs);
                    cout << "Here are your updated stats" << endl;
                    players[playerindex].printStats(players[playerindex]);
                    // playerindex=switchPlayers(playerindex);
                    validcandymove = true;
                }
                else if (candyobj.candy_type == "poison")
                {
                    Candy immunitycandy = players[switchPlayers(playerindex)].checkImmunityCandy(candyobj);
                    if (immunitycandy.name == "") //if they don't have any immunity candy
                    {
                        cout << players[playerindex].getRealName() << " has used " << text_inputs << " to posion " << players[switchPlayers(playerindex)].getRealName() << " and subtract " << candyobj.effect_value << " stamina" << endl;
                        players[switchPlayers(playerindex)].setStamina(players[switchPlayers(playerindex)].getStamina() + candyobj.effect_value);
                        players[playerindex].removeCandy(candyobj.name);
                        cout << "Here are " << players[playerindex].getRealName() << "'s updated stats" << endl;
                        players[playerindex].printStats(players[playerindex]);
                        cout << "Here are " << players[switchPlayers(playerindex)].getRealName() << "'s updated stats" << endl;
                        players[switchPlayers(playerindex)].printStats(players[switchPlayers(playerindex)]);
                        // playerindex=switchPlayers(playerindex);
                        validcandymove = true;
                    }
                    else //if they do have a viable immunity candy
                    {
                        cout << players[switchPlayers(playerindex)].getRealName() << " used " << immunitycandy.name << " to block " << candyobj.name << endl;
                        players[playerindex].removeCandy(candyobj.name);
                        players[switchPlayers(playerindex)].removeCandy(immunitycandy.name);
                        cout << "Here are " << players[playerindex].getRealName() << "'s updated stats" << endl;
                        players[playerindex].printStats(players[playerindex]);
                        cout << "Here are " << players[switchPlayers(playerindex)].getRealName() << "'s updated stats" << endl;
                        players[switchPlayers(playerindex)].printStats(players[switchPlayers(playerindex)]);
                        // playerindex=switchPlayers(playerindex);
                        validcandymove = true;
                    }
                }
                else if (candyobj.candy_type == "immunity")
                {
                    cout << "Immunity candy is only used to defend against poison, please enter a different option" << endl;
                    validcandymove = false;
                }

                else if (candyobj.candy_type == "gummy")
                {
                    int gummytile;
                    cout << "What tile would you like to apply " << candyobj.name << " to?" << endl;
                    cin >> gummytile;
                    while (cin.fail() || gummytile > 82)
                    {
                        cin.clear();
                        cout << "Invalid input. Tiles range from 0-81" << endl;
                        cin >> gummytile;
                    }
                    while (board.isPosition1CandyStore(gummytile) || board.isSpecialTile1(gummytile))
                    {
                        cout << "You can't place " << candyobj.name << " on a candystore or special tile, please enter a different input" << endl;
                        cin >> gummytile;
                    }
                    if (candyobj.effect_value == -1)
                    {
                        board.setTileToSticky(gummytile); //makes a tile sticky or double sticky
                    }
                    else if (candyobj.effect_value == -2)
                    {
                        board.setTileToDoubleSticky(gummytile);
                    }
                    cout << "Tile " << gummytile << " is sticky!" << endl;
                    players[playerindex].removeCandy(candyobj.name);
                    validcandymove = true;
                }

            } while (validcandymove == false); //all while a valid candy move is being made


            if (players[switchPlayers(playerindex)].isPlayerAllowed() == true) //checks to make sure a player can have a turn
            {
                playerindex = switchPlayers(playerindex);
            }
        }

        board.setPlayer1PrevPosition(board.getPlayer1Position()); //updates positions
        board.setPlayer2PrevPosition(board.getPlayer2Position());

        player1has9candies = players[0].hasNineCandies(); //updates booleans of having nine candies
        player2has9candies = players[1].hasNineCandies();
        if (players[1].getGold() < 0) //ensures players don't go below zero
        {
            players[1].setGold(0);
        }
        else if (players[0].getGold() < 0)
        {
            players[0].setGold(0);
        }
    }
    if (board.getPlayer1Position() >= 82) //end of game condition
    {
        cout << "Player one wins!" << endl;
    }
    else if (board.getPlayer2Position() >= 82)
    {
        cout << "Player two wins!" << endl;
    }
    printResults(players);

}