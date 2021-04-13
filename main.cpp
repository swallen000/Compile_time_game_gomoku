#include <iostream>
#include "information.hpp"

using namespace std;

int main(){
    static_assert(game_string.size() > 0, "game string is null!");
    static_assert(array_size > 0, "incorrect array size");
    set_array(); //using STR
    return read_input(); //using STR
    //set_array_sv(); // using string_view
    //return read_input_sv(); // using string_view
    
}