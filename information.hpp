# pragma once
#include "input.hpp"
#include <charconv>

class Info{
public:

private:
    int x;
    int y;
};

constexpr void set_array(){
    for(int i=1, current = 0; i<row-2; ++i){
        auto sub = game_string.substr(i*(column+1)+1, column);
        for(int j=0; j<column; ++j)
            chessboard[current][j] = sub[j];
        current++;
    }
}

template<class T>
constexpr bool move_chessboard(T& input, int& x, int& y){
    if(chessboard[y-1][x*2] == '+')
        chessboard[y-1][x*2] = ' ';
    if(input == User_Input::Top && y > 1){
        y--;
    }
    else if(input == User_Input::Down && y < array_size){
        y++;
    }
    else if(input == User_Input::Left && x > 1){
        x--;
    }
    else if(input == User_Input::Right && x < array_size){
        x++;
    }
    else if(input == User_Input::Space){
        if(chessboard[y-1][x*2] == 'O' || chessboard[y-1][x*2] == 'X')
            return false;
    }
    return true;
}

constexpr void read_input(){
    auto first_line = game_string.substr(1, column);
    auto last_line = game_string.substr((row-1)*(column+1)+1);
    if(last_line[0] == 'n'){
        int x_start = last_line.find(':')+2;
        int y_start = last_line.find_last_of(' ')+1;
        auto first = last_line.substr(x_start, y_start - x_start - 1);
        auto second = last_line.substr(y_start, last_line.size() - y_start);
        int x;
        std::from_chars(first.data(), first.data() + first.size(), x);
        int y;
        std::from_chars(second.data(), second.data() + second.size(), y);
        //std::cout<<x<<" "<<y<<"@\n";
        bool flag = move_chessboard(input,x ,y);
        if(flag == false){
            //to do
        }
        else{
            if(input == User_Input::Space)
                chessboard[y-1][x*2] = 'O';
            else if(chessboard[y-1][x*2] != 'O' && chessboard[y-1][x*2] != 'X')
                chessboard[y-1][x*2] = '+';
            std::cout<<"R\"(\n"<<first_line<<"\n";
            for(int i=0; i<chessboard.size(); ++i){
                for(int j=0; j<chessboard[i].size(); ++j)
                    std::cout<<chessboard[i][j];
                std::cout<<"\n";
            }
            for(int i=0; i<column; ++i)
                std::cout<<" ";
            std::cout<<"\nnow position: "<<x<<" "<<y<<"\n";
            std::cout<<")\"";
        }
    }
    
    //int x = 
}
