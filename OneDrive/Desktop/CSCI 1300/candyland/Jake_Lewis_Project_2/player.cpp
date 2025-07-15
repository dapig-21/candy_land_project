#include "Player.h"


//similar to read candy/read riddles
vector <Player>  Player :: readPlayers(){
    vector <Candy> player_inventory;
    vector <Player> playable_characters;
    string name;
    string stamina;

    string gold;
    string inventory;
    string candy;
    ifstream playersstream;
    string line="";
    playersstream.open("players.txt");
   
    if(playersstream.fail()){
        cout<<"Failed to open file"<<endl;
        return playable_characters;
    }
    else{
        while(getline(playersstream,line)){
            Player player1;
            stringstream ss(line);
            
            getline(ss, name, '|' );
            player1.setName(name);
            if(player1.getName()==""){
                continue;
            }
            getline(ss, stamina, '|');
            player1.setStamina(stoi(stamina));
            

            getline(ss, gold, '|');
            player1.setGold(stoi(gold));

            getline(ss, inventory, '|');
            stringstream ss2(inventory);
            //cout<<inventory<<endl;
            while(getline(ss2, candy, ',')){
                //cout<<candy<<endl;
                player1.addCandy(stringToCandy(candy));
                
            }
            playable_characters.push_back(player1);
            

            

        }
        playersstream.close();

    }
    return playable_characters;
}  

int Player :: randomNumGen3(int min, int max) {
    random_device rd;   
    mt19937 gen(rd());  
    uniform_int_distribution<> distribution(min, max);  

    return distribution(gen);  
}

bool compareString1(string str1, string str2){
    if(str1.length()!= str2.length()){
        return false;
    }
    int len = str1.length();
    for(int i=0; i<len; i++){
        if(tolower(str1[i])!=tolower(str2[i])){
            return 0;
        }
    }
    return true;
}
//transfers the inventory of a player to a diff player, used for char selection
void Player :: transferInventory(Player player){
    Candy candyobj;
    for(int i=0; i<8;i++){
        candyobj=player._inventory[i];
        addCandy(candyobj);
    }
}

void Player:: setRealName(string name){
    _real_name=name;
}

string Player:: getRealName(){
    return _real_name;
}


//adds a special item to a players backpack
bool Player:: addToBackPack(string what_to_add){
    for(int i=0; i<_MAX_ITEM_AMOUNT; i++){
        if(_backpack[i]==""){
            _backpack[i]=what_to_add;
            return true;
        }

    }
    return false;
}
//checks if a player is allowed to take a turn and checks stamina of a player
bool Player::isPlayerAllowed(){
    bool allowed = true;
    if(_turn_skip_count!=0){
        allowed=false;
        _turn_skip_count--;
    }
    else if(_stamina==0){
        allowed=false;
        _turn_skip_count=2;
    }
    return allowed;
}
/*
Plays rock paper scissors, but takes a random num gen for the second players input
Ties are still possible with this method
*/
bool Player:: playRockPaperScissors(Player player)
{

    
    char player1_choice;
    char player2_choice;
    char charinput;
    int random;
    
   
    
        cout << player.getRealName()<< ": Enter r, p, or s" << endl;
        cin >> charinput;
        while (cin.fail() || (charinput != 'r' && charinput != 'p' && charinput != 's'))
        {
            cout << "Invalid selection!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> charinput;
        }
        cin.clear();
        player1_choice = charinput;
        random= randomNumGen3(1,3);
        if (random==1){
            player2_choice='r';
        }
        else if(random == 2){
            player2_choice='p';
        }
        else{
            player2_choice='s';
        }
        cout<<"Computer chooses "<< player2_choice<<endl;




        
       
    
    while (player1_choice == player2_choice)
    {
        cout << "Tie! Play again" << endl;
        cout << player.getRealName()<< " Enter r, p, or s" << endl;
        cin >> charinput;
        player1_choice = charinput;
        random= randomNumGen3(1,3);
        if (random==1){
            player2_choice='r';
        }
        else if(random == 2){
            player2_choice='p';
        }
        else{
            player2_choice='s';
        }
        cout<<"Computer chooses "<< player2_choice<<endl;
    }
    if (player1_choice == 'r' && player2_choice == 's')
    {
        cout << "You win!" << endl;
        return true;
        // cout<<"Player 1 inventory after: "<<endl;
        // players[0].printInventory();
        // cout<<"Player two inventory after: "<<endl;
        // players[1].printInventory();
    }
    else if (player1_choice == 'p' && player2_choice == 'r')
    {
        cout << "You win!" << endl;
        return true;
        // cout<<"Player one inventory after: "<<endl;
        // players[0].printInventory();
        // cout<<"Player two inventory after: "<<endl;
        // players[1].printInventory();
    }
    else if (player1_choice == 's' && player2_choice == 'p')
    {
        cout << "You win!" << endl;
        return true;
        //     cout<<"Player one inventory after: "<<endl;
        //     players[0].printInventory();
        //     cout<<"Player two inventory after: "<<endl;
        //     players[1].printInventory();
    }
    else if (player2_choice == 'p' && player1_choice == 'r')
    {
        cout << "You lose!" << endl;
        return false;

        // cout<<"Player one inventory after: "<<endl;
        // players[0].printInventory();
        // cout<<"Player two inventory after: "<<endl;
        // players[1].printInventory();
    }
    else if (player2_choice == 's' && player1_choice == 'p')
    {
        cout << "You lose!" << endl;
        return false;
        // cout<<"Player one inventory after: "<<endl;
        // players[0].printInventory();
        // cout<<"Player two inventory after: "<<endl;
        // players[1].printInventory();
    }
    else if (player2_choice == 'r' && player1_choice == 's')
    {
        cout << "You lose!" << endl;
        return false;
        // cout<<"Player one inventory after: "<<endl;
        // players[0].printInventory();
        // cout<<"Player two inventory after: "<<endl;
        // players[1].printInventory();
    }
    else
    {
        cout << "You fucked something up" << endl;
        return false;
    }
}
Player::Player(){
    Candy Empty{"Empty","","",0,0.0,""};
    _stamina=0;
    _candy_amount=0;
    _gold=0;
    _effect="";
    for(int i=0;i<_MAX_CANDY_AMOUNT;i++){
    _inventory[i]= Empty;
    }
    Candy candy;
    //={Candy Empty, Empty, Empty, Empty};

}
//Parameterized constructor of a player
Player::Player(int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE ){
    Candy Empty{"Empty","","",0,0.0,""};
    _stamina=stamina;
    _gold=gold;
    _effect=effect;
    _candy_amount=0;
    if(CANDY_ARR_SIZE!=_MAX_CANDY_AMOUNT){
        for(int i=0;i<CANDY_ARR_SIZE;i++){
            if(candy_array[i].name.length()==0){
                    _inventory[i]=Empty;
                }
            else{
            _inventory[i]=candy_array[i];
            }
            }
    
    for(int i=1; i<=_MAX_CANDY_AMOUNT-CANDY_ARR_SIZE; i++){
        _inventory[_MAX_CANDY_AMOUNT-i]=Empty;
        }
    }
    else{
        for(int i=0;i<_MAX_CANDY_AMOUNT;i++){
            if(candy_array[i].name==""){
                _inventory[i]=Empty;
            }
        else{
            _inventory[i]=candy_array[i];}
        }
}
    for(int i=0; i<_MAX_CANDY_AMOUNT; i++){
        if (_inventory[i].name!="Empty"){
            _candy_amount++;
        }
    }
}

//very useful for taking string inputs and making them into candies
Candy Player:: stringToCandy(string candy){
    Candy candyobj;
    bool flag=false;
    vector <Candy> all_candies=CandyStore :: readCandy();
    
    for(int i=0; i<int(all_candies.size()); i++){
        if(compareString1(candy, all_candies.at(i).name)){
            candyobj=all_candies.at(i);
            flag=true;
        }

    }
    if(!flag){
        cout<<"bad!"<<endl;
    }
    //cout<< "stoc "<< candyobj.name<<endl;
    return candyobj;
}

int Player:: getTurnSkipCount(){
    return _turn_skip_count;
}

void Player:: setTurnSkipCount(int turnSkipCount){
    _turn_skip_count=turnSkipCount;
}

int Player::getCandyAmount(){
    return _candy_amount;
}

void Player:: setName(string name){
    _name=name;
}

string Player:: getName(){
    return _name;
}

void Player::setStamina(int stamina){
     _stamina=stamina;

}
int Player:: getStamina(){
    return _stamina;
}

void Player::setGold(double gold){
    _gold=gold;
}
double Player:: getGold(){
    return _gold;
}

void Player::setEffect(string effect){
    _effect=effect;
}

string Player:: getEffect(){
    return _effect;
}
//Similar to HW 7 print inventory
void Player:: printInventory(){
for (int i=0; i<_MAX_CANDY_AMOUNT;i++){
    if(i==3||i==6||i==9){
        cout<<"|"<<endl;
    }
    string whattoprint="";
    if(_inventory[i].name=="Empty"){
        whattoprint="Empty";
    }
    else{
        whattoprint=_inventory[i].name;
    }
    cout<<"|["<<whattoprint<<"]";
    }
    cout<<"|"<<endl;
}
//does he have a gun?
bool Player:: hasBigiron(){
    for(int i=0; i<3; i++){
        if(_backpack[i]=="big iron"){
            return true;
        }
    }
    return false;
}
//Does he have skiis?
bool Player:: hasSpecialSkiis(){
    for(int i=0; i<3; i++){
        if(_backpack[i]=="Special Skiis"){
            return true;
        }
    }
    return false;
}

string Player:: findCandyati(int i){
    return _inventory[i].name;
}


Candy Player:: findCandy(string candy_name){
    Candy Empty{"Empty","","",0,0.0,""};
    Candy ReallyEmpty{"","","",0,0.0,""};
    //  bool found=false;
    for(int i=0; i<_MAX_CANDY_AMOUNT; i++){
        if(_inventory[i].name=="Empty"){
            // found=true;
            return ReallyEmpty;
            break;
        }
        /*
        compareString(_inventory[i].name, candy_name)
        */
        else if (compareString1(_inventory[i].name, candy_name)){
            return _inventory[i];
        }
       
    }
    return Empty;
}
/*
This one takes the effect of the posion candy applied, and finds the candy in the 
players inventory that has the least positive difference between the posion candy
meaning the player automatically has the most viable immunity candy taken out of
their inventory, making the game flow much more smoothly than a player having 
to memorize the immunity effects and poision effects of each candy

*/
Candy Player::checkImmunityCandy(Candy posion_applied){
    

int lowest_difference = INT_MAX; 
Candy returncandy;

int posion_effect = abs(posion_applied.effect_value);

for(int i = 0; i < 8; i++) {
    if(_inventory[i].candy_type == "immunity" && _inventory[i].effect_value >= posion_effect) {
        int current_difference = abs(posion_effect - _inventory[i].effect_value);

        if (current_difference < lowest_difference) {
            lowest_difference = current_difference;
            returncandy = _inventory[i];
        }
    }
}

//cout << "Lowest dif " << lowest_difference << endl;
return returncandy;

}

 bool Player:: addCandy(Candy candy){
    string lowercandy;
    
    for(int i=0; i<_MAX_CANDY_AMOUNT; i++){
        if(_inventory[i].name=="Empty"){ // maybe change to candy object if empty is a test case
            _inventory[i]=candy;
            if(candy.name!=""&&candy.name!="Empty"){
            _candy_amount++;
            }
            return true;
        }
        
    }
    return false;
}

bool Player :: removeCandy(string candy_name){
    bool erased=false;
    Candy Empty{"Empty","","",0,0.0,""};
    


    for(int i=0; i<_MAX_CANDY_AMOUNT; i++){
        if(compareString1(_inventory[i].name, candy_name)&&!(_inventory[i].name=="Empty")){ //new
            _inventory[i]=Empty;
            _candy_amount=_candy_amount-1;
            erased=true;
            break;
            }
        }
     if(erased==true){
        for(int i=0; i<_MAX_CANDY_AMOUNT-1; i++){
            if (_inventory[i].name=="Empty"){
                _inventory[i]=_inventory[i+1];
                _inventory[i+1] = Empty;
            }
        }
        return true;
     }
    else{
        return false;
    }
}

void Player :: printStats(Player player){
    if(!(player.getRealName()=="")){
        cout<<"Player name: "<<player.getRealName()<<endl;
    }
    cout<< "Character name: "<<player.getName()<<endl;
    cout<< "Stamina: "<<player.getStamina()<<endl;
    cout<< "Gold: "<< player.getGold()<<endl;
    cout<< "Candy Inventory: "<<endl;
    player.printInventory();
}
//used when a player has to swap candies out, returns if it was a sucsess
bool Player:: swapCandy(string nameofcandytoswap){
    bool sucsess;
    Candy candytoswap=findCandy(nameofcandytoswap);
    if(candytoswap.name=="Empty"){
        sucsess= false;
    }
    else{
        for(int i=0; i<_MAX_CANDY_AMOUNT; i++){
            if(candytoswap.name==_inventory[i].name){
                _inventory[i]=candytoswap;
                sucsess= true;
            }
        }
    }
    return sucsess;
}
//checks if a player has 9 candies in their inventory
bool Player:: hasNineCandies(){
    if(getCandyAmount()==9){
        return true;
    }
    else{
        return false;
    }
}



