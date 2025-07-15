#include "Board.h"




Board::Board()
{
    resetBoard();
}






void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player_1_position = 0;
    _player_2_position = 0;
}


/*
This is a random number generator I researched over break, I'm not 100% sure how it works but it was 
extremely useful for the project

*/
int Board :: randomNumGen2(int min, int max) {
    random_device rd;   // Obtain a random number from a hardware device
    mt19937 gen(rd());  // Seed the random number generator
    uniform_int_distribution<> distribution(min, max);  // Define the distribution

    return distribution(gen);  // Generate and return a random number
}

/*
Takes a random number and assigns a treasure to it
*/

void Board:: makeTreasureTiles(){
    int ran =randomNumGen2(0, _BOARD_SIZE-1);
    int ran2= randomNumGen2(0, _BOARD_SIZE-1);
    int ran3= randomNumGen2(0, _BOARD_SIZE-1);
    //
   
       
       
        _tiles[ran].bigiron=true; //need to change
        _tiles[ran2].skiis=true;
        _tiles[ran3].wallet=true;
}

//Checks if player one is one a treasure tile
string Board:: is1TreasureTile(){
     if(_tiles[_player_1_position].bigiron==true){
        return "big iron";
    }
    else if(_tiles[_player_1_position].skiis==true){
        return "Special Skiis";
    }
    else if(_tiles[_player_1_position].wallet==true){
        return "somebody's wallet";
    }
    return "";
}

// makes the tile no longer contain a treasure

void Board:: unTreasureTile1(){
    _tiles[getPlayer1Position()].bigiron=false;
    _tiles[getPlayer1Position()].wallet=false;
    _tiles[getPlayer1Position()].skiis=false;
}

void Board:: unTreasureTile2(){
    _tiles[getPlayer2Position()].bigiron=false;
    _tiles[getPlayer2Position()].wallet=false;
    _tiles[getPlayer2Position()].skiis=false;
}

//checks if a tile has a sticky effect on it

int Board:: is1TileSticky(){
    if(_tiles[getPlayer1Position()].sticky==true){
        return 1;
    }
    else if(_tiles[getPlayer1Position()].doublesticky==true){
        return 2;
    }
    return 0;

}


int Board:: is2TileSticky(){
    if(_tiles[getPlayer2Position()].sticky==true){
        return 1;
    }
    else if(_tiles[getPlayer2Position()].doublesticky==true){
        return 2;
    }
    return 0;

}


    


string Board:: is2TreasureTile(){
       if(_tiles[_player_2_position].bigiron==true){
        return "big iron";
    }
    else if(_tiles[_player_2_position].skiis==true){
        return "Special Skiis";
    }
    else if((_tiles[_player_2_position].wallet==true)){
        return "somebody's wallet";
    }
    return "";
}


/*
Makes a random number, then based on that random number assigns a card type to be returned
to the move from card function
*/
Card Board::drawCard()
{
    Card cardobj;
    cardobj.color="";
    cardobj.double_move=false;
    //make a rando between 1-36
    // 1/4 red, 1/4 green, 1/4 blue, 1/8 any doubles
    
    srand(time(0));
    
    string card_color ="";

    int card_type= 1 + rand()%35;

    cout<<"Drawing card"<<endl;
    if(card_type>=1 && card_type<8){
        cardobj.color= MAGENTA;
        card_color="Magenta";
        cardobj.double_move=false;
    }
    else if(card_type>=8&& card_type<16){
        cardobj.color= GREEN;
        card_color="Green";
        cardobj.double_move=false;
    }
    else if(card_type>=16 && card_type<24){
        cardobj.color= BLUE;
        card_color="Blue";
        cardobj.double_move=false;;
    }
    else if(card_type>=24 && card_type<28){
        cardobj.color= MAGENTA;
        card_color="Magenta";
        cardobj.double_move=true;
    }
    else if(card_type>=28 && card_type<32){
        cardobj.color= GREEN;
        card_color="Green";
        cardobj.double_move=true;
    }
    else if(card_type>=32 && card_type<=35){
        cardobj.color= BLUE;
        card_color="Blue";
        cardobj.double_move=true;
    }
    if(cardobj.double_move==true){
        cout<<"You drew a "<<card_color<<" double"<<endl;
    }
    else{
        cout<<"You drew a regular "<<card_color<<endl;
    }
    return cardobj;
    
}

//makes the riddles avalible

void Board :: setRiddlesArray(vector <Riddle> all_riddles){
    for(int i=0; i<RIDDLE_AMOUNT; i++){
        _riddles[i].question=all_riddles.at(i).question;
        _riddles[i].answer=all_riddles.at(i).answer;
        //cout<<"question for:"<< i<< " " <<_riddles[i].question<<endl;
        //cout<<"Answer: "<< i<< " " <<_riddles[i].answer<<endl;
    }
}

/*
Because a players position is updated at the end of loop, if player one's prev position is player
two's current position, then player one arrvied first, and visa versa 
*/

bool Board:: is2SameTile(){
    if(getPlayer1PrevPosition()==getPlayer2Position()){
        return true;
    }
    return false;
}

bool Board:: is1SameTile(){
    if(getPlayer2PrevPosition()==getPlayer1Position()){
        return true;
    }
    return false;
}

//similar to read candy function

void Board:: readRiddles(){
    
    vector <Riddle> all_riddles;
    Riddle riddleobj;
    string question;
    string answer;
    ifstream riddlesif;
    string line="";
    riddlesif.open("riddles.txt");
   
    if(riddlesif.fail()){
        cout<<"Failed to open file"<<endl;
        return;
    }
    else{
        while(getline(riddlesif,line)){
            stringstream ss(line);
            getline(ss, riddleobj.question, '|' );
            if(riddleobj.question==""){
                continue;
            }
            getline(ss, riddleobj.answer, '|');
            
            
            

            all_riddles.push_back(riddleobj);

        }
        riddlesif.close();
        setRiddlesArray(all_riddles);


    }
    return;
}

//checks user input of the riddle answer

bool Board :: displayRiddle(){
    int random = randomNumGen2(0, RIDDLE_AMOUNT-1);
    string answer;
    cout<<_riddles[random].question<<endl;
    cin.ignore(1000, '\n');
    getline(cin, answer);
    if(answer ==_riddles[random].answer){
        cout<<"Correct!"<<endl;
        return true;
    }
    else{
        cout<<"Wrong!"<<endl;
        return false;
    }
}


//checks if a calamity is to take place, then randomly generates the calamity that will take place
    
 string Board::checkCalamity(){
    /*
    Once functions for calamities are made, this will be a void and it will just run the function for each calamity
    */

     srand(time(0));
     int random = randomNumGen2(1,10);
     int calamity_random= randomNumGen2(1,100);
     bool calamity;
     string calamitytype="";
    //  cout<<"Num1 "<<random<<endl;
    //  cout<<calamity_random<<endl;
     if(random>=1 && random<=4){
        calamity=true;
       
     }
     else{
        calamity = false;
        //cout<<"No Calamity"<<endl;
        return calamitytype;
     
     }
     if (calamity==true){
        if(calamity_random>=1 && calamity_random<=30){
            calamitytype= "Candy Bandits";

        }
        else if(calamity_random>=31 && calamity_random<=66){
            calamitytype= "Labrynth";
            
        }
        else if(calamity_random>=67 && calamity_random<=82){
            calamitytype= "Avalanche";
            
        }
        else if(calamity_random>=83 && calamity_random<=100){
            calamitytype= "Sticky Taffy";
            
        }
     }
     return calamitytype;
}

/*
Moves baed on the card drawn in the draw card function
because a player is at most 3 spaces away from a same color tile,
the for loop is run three times and the value of i that makes the player
position and corresponding tile the same as the drawn tile is how many spaces
the player should move. Testing mode is a boolean value that will always return one,
meaning the player will always move one space to test all of the values
if it's a double, add three to the amount moved
*/

int Board:: moveFromCard1(Card card_drawn, bool testingmode){ //only works for p1, either make player an argument or make 2 functions
    bool double_move=false;
    int amount_to_move;
    string current_tile_color=_tiles[getPlayer1Position()].color;
    if (card_drawn.double_move==true){
        double_move=true;
    }
    for (int i=1; i<4; i++){
        if(_tiles[getPlayer1Position()+i].color==ORANGE){
            setPlayer1Position(83);
            amount_to_move=i;
            break;
        }
        else if(card_drawn.color==_tiles[getPlayer1Position()+i].color){
            amount_to_move=i;
            break;
        }

    }
    if(testingmode){
        return 1;
    }
    else if(double_move){
        cout<<"Moving "<<amount_to_move+3<<endl;
        return amount_to_move+3;
    }
    else{
        cout<<"Moving "<<amount_to_move<<endl;
        return amount_to_move;
    }
    

}

int Board:: moveFromCard2(Card card_drawn, bool testingmode){ //only works for p1, either make player an argument or make 2 functions
    bool double_move=false;
    int amount_to_move;
    string current_tile_color=_tiles[getPlayer2Position()].color;
    if (card_drawn.double_move==true){
        double_move=true;
    }
    for (int i=1; i<4; i++){
        if(_tiles[getPlayer2Position()+i].color==ORANGE){
            setPlayer2Position(83);
            amount_to_move=i;
            break;

        }
        else if(card_drawn.color==_tiles[getPlayer2Position()+i].color){
            amount_to_move=i;
            break;
        }

    }
    if(testingmode){
        return 1;
    }
    else if(double_move){
        cout<<"Moving "<<amount_to_move+3<<endl;
        return amount_to_move+3;
    }
    else{
        cout<<"Moving "<<amount_to_move<<endl;
        return amount_to_move;
    }
    

}
    
//if a tile is a special tile, this function is called to determine what type of special tile
string Board :: decideSpecialTile(){
    int ran= randomNumGen2(1,4);
    if(ran==1){
        return "Shortcut Tile";
    }
    else if (ran==2){
        return " Ice Cream Shop Tile";
    }
    else if(ran==3){
        return "Gumdrop Forest Tile";
    }
    else{
        return "Gingerbread House Tile";
    }
}

bool Board:: isTileCandyStore(int position){
    for(int i=0; i<_MAX_CANDY_STORE;i++){
        if (position==_candy_store_position[i]){
            return true;
        }

    }
    return false;
}

bool Board::isSpecialTile1(int position){
    if(_tiles[_player_1_position].tile_type=="Special"){
        return true;
    }
    return false;
}

bool Board::isSpecialTile2(int position){
    if(_tiles[_player_2_position].tile_type=="Special"){
        return true;
    }
    return false;
}

//generates a random array of special tiles
void Board :: makeSpecialTiles(){
    int ran =randomNumGen2(0, _BOARD_SIZE);
    int ran2= randomNumGen2(0, _BOARD_SIZE);
    int ran3= randomNumGen2(0, _BOARD_SIZE);
    int ran4= randomNumGen2(0, _BOARD_SIZE);
    int ran5= randomNumGen2(0, _BOARD_SIZE);
    int ran6= randomNumGen2(0, _BOARD_SIZE);
    int ran7= randomNumGen2(0, _BOARD_SIZE);
    int ran8= randomNumGen2(0, _BOARD_SIZE);
    //
   
       
       
        _tiles[ran].tile_type="Special";
        _tiles[ran2].tile_type="Special";
        _tiles[ran3].tile_type="Special";
        _tiles[ran4].tile_type="Special";
        _tiles[ran5].tile_type="Special";
        _tiles[ran6].tile_type="Special";
        _tiles[ran7].tile_type="Special";
        _tiles[ran8].tile_type="Special";
       
    
  }

 void Board:: setPlayer1PrevPosition(int position){
    _player_1_prev_position=position;
 }

  void Board:: setPlayer2PrevPosition(int position){
    _player_2_prev_position=position;
 }

 int Board:: getPlayer1PrevPosition(){
    return _player_1_prev_position;
 }

 int Board:: getPlayer2PrevPosition(){
    return _player_2_prev_position;
 }

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    if (position == _player_1_position)
    {
        cout << "1";
    }
    else if(position == _player_2_position)
    {
        cout<<"2";
    }
    else if(isTileCandyStore(position)) //remove if not needed for interview
    {
        cout<<"C";
    }
    else if (_tiles[position].tile_type=="Special"){
        cout<<"S";
    }

    else if(_tiles[position].skiis==true||_tiles[position].bigiron==true||_tiles[position].wallet==true){
        cout<<"T";
    }
    
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
        //cout<<i;
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        //cout<<i;
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
        //cout<<i;
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        //cout<<i;
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
        //cout<<i;
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayer1Position(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_1_position = new_position;
        return true;
    }
    return false;
}

bool Board::setPlayer2Position(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_2_position = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayer1Position() const
{
    return _player_1_position;
}
int Board::getPlayer2Position() const
{
    return _player_2_position;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPosition1CandyStore(int player_1_board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == player_1_board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::isPosition2CandyStore(int player_2_board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == player_2_board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer1(int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player_1_position;
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_1_position = new_player_position;
    return true;
}

bool Board::movePlayer2(int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player_2_position;
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_2_position = new_player_position;
    return true;
}
//makes tiles sticky
void Board:: setTileToSticky(int tile_to_stick){
    _tiles[tile_to_stick].sticky=true;
}

void Board:: setTileToDoubleSticky(int tile_to_stick){
    _tiles[tile_to_stick].doublesticky=true;
}
