#include <iostream>
#include "information.hpp"


using namespace std;

int main(){
    //static_assert(game_string.size() > 0, "game string is null!");
    static_assert(array_size > 0, "incorrect array size");
    //test_string.print_sequence();

    set_array();
    
    //set_array_sv();
    /*for(int i=0; i<game_string.size(); ++i){
        cout<<i<<" "<<game_string[i]<<endl;
    }*/

    //read_input_sv(); 
    return read_input();  
}