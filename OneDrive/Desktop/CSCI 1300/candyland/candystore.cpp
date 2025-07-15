#include "candystore.h"


int CandyStore :: randomNumGen(int min, int max) {
    random_device rd;   
    mt19937 gen(rd());  
    uniform_int_distribution<> distribution(min, max);  

    return distribution(gen);  
}



//reads the candy txt file and returns a vector to store them in
vector <Candy> CandyStore :: readCandy(){
    vector <Candy> all_candies;
    Candy candyobj;
    string price;
    string effect_value = "";
    ifstream candys;
    string line="";
    candys.open("candy.txt");
   
    if(candys.fail()){
        cout<<"Failed to open file"<<endl;
        return all_candies;
    }
    else{
        while(getline(candys,line)){
            stringstream ss(line);
            getline(ss, candyobj.name, '|' );
            if(candyobj.name==""){
                continue;
            }
            getline(ss, candyobj.description, '|');
            

            getline(ss, candyobj.effect_type, '|');

            getline(ss, effect_value, '|');
            candyobj.effect_value=stoi(effect_value);

            getline(ss, candyobj.candy_type, '|');

            getline(ss, price, '|');
            candyobj.price=stod(price);
            
            

            all_candies.push_back(candyobj);

        }
        candys.close();

    }
    return all_candies;
}  

//takes a name as a paramter for clarities sake
CandyStore :: CandyStore(string name){
    vector <Candy> all_candies=readCandy();
    _name=name;
    setInventory(all_candies);
    _location = 0;

}
/*
This one's a doozie. Because there is a tile constraint on where the candy stores can be, 
this function checks if the candystore's position is within the color contraints
placed on the candy stores and then returns the value of the candy store
*/
int CandyStore:: decideLocation(int candy_store_index){
    int rand1;
    int rand2;
    int rand3;
    if(candy_store_index==0){
        rand1 = randomNumGen(0,27);
        while(rand1!=3&&rand1!=6&&rand1!=9&&rand1!=12&&rand1!=15&&rand1!=18&&rand1!=21&&rand1!=24&&rand1!=27){
            rand1 = randomNumGen(0,27);
        }
        //cout<<rand1<<endl;
        return rand1;
        
    }
    else if(candy_store_index==1){
       rand2 = randomNumGen(28,54);
        while(rand2!=28&&rand2!=31&&rand2!=34&&rand2!=37&&rand2!=40&&rand2!=43&&rand2!=46&&rand2!=49&&rand2!=52){
            rand2 = randomNumGen(28,54);
        }
        //cout<<rand2<<endl;
        return rand2;
    }
    //rand==56||rand==59||rand==62||rand==65||rand==68||rand==71||rand==74||rand==77||rand==80)
    else if(candy_store_index==2){
    rand3 = randomNumGen(55,82);
        while(rand3!=56&&rand3!=59&&rand3!=62&&rand3!=65&&rand3!=68&&rand3!=71&&rand3!=74&&rand3!=77&&rand3!=80){
            rand3 = randomNumGen(55,82);
        }
        //cout<<rand3<<endl;
        return rand3;
    
    
}
    return 82;
}
//case sensitivy is not longer an issue
bool CandyStore:: compareStringCandyStore(string str1, string str2){
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

//simialr to find candy, but just using the menu of the candy store
Candy CandyStore:: findCandyInStore(string candy){
    
    Candy Empty{"Empty","","",0,0.0,""};
    Candy ReallyEmpty{"","","",0,0.0,""};
    //  bool found=false;
    for(int i=0; i<max_candy_amount; i++){
        if(_store_selection[i].name=="Empty"){
            // found=true;
            return ReallyEmpty;
            break;
        }
        /*
        compareString(_inventory[i].name, candy_name)
        */
        else if (compareStringCandyStore(_store_selection[i].name, candy)){
            return _store_selection[i];
        }
       
    }
    return Empty;

}
//similar to remove candy, kinda buggy but we ball
bool CandyStore:: removeCandyFromStore(string candy_name){
    
    bool erased=false;
    Candy Empty{"Empty","","",0,0.0,""};
    


    for(int i=0; i<max_candy_amount; i++){
        if(compareStringCandyStore(_store_selection[i].name, candy_name)&&!(_store_selection[i].name=="Empty")){ //new
            _store_selection[i]=Empty;
            _candy_amount_in_store--;
            erased=true;
            break;
            }
        }
     if(erased==true){
        for(int i=0; i<max_candy_amount-1; i++){
            if (_store_selection[i].name=="Empty"){
                _store_selection[i]=_store_selection[i+1];
                _store_selection[i+1] = Empty;
            }
        }
        return true;
     }
    else{
        return false;
    }

}

// THIS DIDNT WORK BC OF REFERENCE ERRORS 
// void CandyStore:: buyCandy(Player buying_player){
//     string name_of_candy_to_buy;
//     Candy candy_to_buy;
//     bool found=false;
//     bool enoughgold=false;
//     // while(found==false){
//     //     cout<<"What candy would you like to purchase?"<<endl;
//     //     getline(cin, candy_to_buy.name);
//     //     for(int i=0; i<max_candy_amount; i++){
//     //         if(compareStringCandyStore(candy_to_buy.name, _store_selection[i].name)){
//     //         candy_to_buy = _store_selection[i];
//     //         found=true;
//     //         break;
//     //         }

            
//     //     }
//     // }
//     cout<<"What candy would you like to purchase?"<<endl;
//     do{
//     do
//     {
        
//         getline(cin, candy_to_buy.name);
//         for(int i=0; i<max_candy_amount; i++){
//             if(compareStringCandyStore(candy_to_buy.name, _store_selection[i].name)){
//             candy_to_buy = _store_selection[i];
//             found=true;
//             break;
//             }

            
//         }
//         if (found==false){
//         cout<<candy_to_buy.name<<" not found in this store, enter a different name"<<endl;
//         }
//     } while (found==false);
    
//     if(buying_player.getGold()>=candy_to_buy.price&&found==true){
//             enoughgold=true;
//             cout<<buying_player.getRealName()<<" has succsessfully purchased "<< candy_to_buy.name<<endl;
//             buying_player.addCandy(candy_to_buy);
//             buying_player.setGold(buying_player.getGold()-candy_to_buy.price);
//             cout<<"Here is "<< buying_player.getName()<<"'s updated stats"<<endl;
//             buying_player.printStats(buying_player);
//         }
//         else{
//             cout<<"You don't have enough gold to purchase this item, enter a new item"<<endl;
//         }
        
//         // //if(buying_player.getGold()>=candy_to_buy.price){
//         //     enoughgold=true;
//         // }
        

//     }
//     while(enoughgold==false);

// }


string CandyStore :: getName(){
    return _name;
}


int CandyStore :: getLocation(){
    return _location;
}

void CandyStore :: setLocation(int location){
    _location=location;
}
void CandyStore :: setName(string name){
    _name=name;
}





//randonly assigns candys to a store
void CandyStore:: setInventory(vector <Candy> all_candies){
    for (int j=0; j<3; j++){
    _store_selection[j]=all_candies.at(randomNumGen(0, all_candies.size()-1));
}
    
    
}


//prints avalible candies in the store
void CandyStore :: printInventory(){
    cout<<"Avalible Candies"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Name: "<<_store_selection[i].name<<endl;
        cout<<"Description: "<<_store_selection[i].description<<endl;
        cout<<"Effect: "<<_store_selection[i].effect_type<<endl;
        cout<<"Effect Value: "<<_store_selection[i].effect_value<<endl;
        cout<<"Candy Type: "<<_store_selection[i].candy_type<<endl;
        cout<<"Price: "<<_store_selection[i].price<<endl;
        cout<<"------------------------"<<endl;
    }
}