# pragma once
#include "input.hpp"
#include <charconv>

constexpr int judge(int &x, int &y, int &p, bool &placed);

// read current.txt to array
constexpr void set_array_sv(){
    for(int i=1, current = 0; i<row-2; ++i){
        auto sub = game_string.substr(i*(column+1)+1, column);
        for(int j=0; j<column; ++j)
            chessboard[current][j] = sub[j];
        current++;
    }
}

constexpr void set_array(){
    int current = 0;
    auto sub1 = test_string.substr<1*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub1[j];
    current++;
    auto sub2 = test_string.substr<2*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub2[j];
    current++;
    auto sub3 = test_string.substr<3*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub3[j];
    current++;
    auto sub4 = test_string.substr<4*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub4[j];
    current++;
    auto sub5 = test_string.substr<5*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub5[j];
    current++;
    auto sub6 = test_string.substr<6*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub6[j];
    current++;
    auto sub7 = test_string.substr<7*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub7[j];
    current++;
    auto sub8 = test_string.substr<8*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub8[j];
    current++;
    auto sub9 = test_string.substr<9*(column+1)+1, column>();
    for(int j=0; j<column; ++j)
            chessboard[current][j] = sub9[j];
}

// move the current position according to the keyboard input
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
        if(chessboard[y-1][x*2] == 'O' || chessboard[y-1][x*2] == '@')
            return false;
    }
    return true;
}


constexpr int read_input(){
    auto first_line = test_string.substr<1, column>();
    auto last_line = test_string.substr<(row-2)*(column+1)+1, 18>();
    auto cursor_line = test_string.substr<(row-2)*(column+1)+1, 18>();
    auto player_line = test_string.substr<(row-2)*(column+1)+19>();
    auto player = player_line.substr<7, 1>();
    //last_line.print_sequence();
    //std::cout<<"\n";
    //player_line.print_sequence();
    
    int p = player_line[7] - '0';
    bool placed = false;
    int x = last_line[last_line.size()-4] - '0';
    int y = last_line[last_line.size()-2] - '0';
    //std::cout<<x<<y;
    
    if(cursor_line[0] == 'n'){
        bool flag = move_chessboard(input,x ,y);
        if(flag == false){
            //std::cout<<"R\"(\n";
            first_line.print_sequence();
            std::cout<<"\n";
            for(int i=0; i<array_size; ++i){
                for(int j=0; j<column; ++j)
                    std::cout<<chessboard[i][j];
                std::cout<<"\n";
            }
            for(int i=0; i<column; ++i)
                std::cout<<" ";
            std::cout<<"\nnow position: "<<x<<" "<<y<<"\n";
            std::cout<<"player "<<p<<"'s turn\n";
        }
        else{
            if(input == User_Input::Space){
                if (p == 1)
                    chessboard[y-1][x*2] = 'O';
                else if (p == 2)
                    chessboard[y-1][x*2] = '@';
                placed = true;
            } 
            else if(chessboard[y-1][x*2] != 'O' && chessboard[y-1][x*2] != '@')
                chessboard[y-1][x*2] = '+';
            //std::cout<<"R\"(\n";
            first_line.print_sequence();
            std::cout<<"\n";
            for(int i=0; i<array_size; ++i){
                for(int j=0; j<column; ++j)
                    std::cout<<chessboard[i][j];
                std::cout<<"\n";
            }
            for(int i=0; i<column; ++i)
                std::cout<<" ";
            std::cout<<"\nnow position: "<<x<<" "<<y<<"\n";
            if (p == 1 && placed == true)
                std::cout<<"player 2's turn\n";
            else if (p == 2 && placed == true)
                std::cout<<"player 1's turn\n";
            else
                std::cout<<"player "<<p<<"'s turn\n";
        }
    }
    int result = judge(x, y, p, placed);
    if(result==12){
        std::cout<<"DRAW!\n";
        //std::cout<<")\"";
        return 12;
    }
    else if(result==1){
        std::cout<<"O Win!\n";
        //std::cout<<")\"";
        return 1;
    } 
    else if(result==2){
        std::cout<<"@ Win!\n";
        //std::cout<<")\"";
        return 2;
    }
    else std::cout<<"Game moving on...\n";
    //std::cout<<")\"";
    return 0;
}


constexpr int read_input_sv(){
    auto first_line = game_string.substr(1, column);
    auto cursor_line = game_string.substr((row-2)*(column+1)+1, 18);
    auto player_line = game_string.substr((row-2)*(column+1)+19);
    auto player = player_line.substr(7, 1);
    int p = player_line[7] - '0';
    bool placed = false;
    int x;
    int y;
    // static_assert(player_line[0] == 'p');
    // std::cout << player.data();
    
    // std::from_chars(player.data(), player.data() + player.size(), p);
    if(cursor_line[0] == 'n'){
        int x_start = cursor_line.find(':')+2;
        int y_start = cursor_line.find_last_of(' ')+1;
        auto first = cursor_line.substr(x_start, y_start - x_start - 1);
        auto second = cursor_line.substr(y_start, cursor_line.size() - y_start);
        std::from_chars(first.data(), first.data() + first.size(), x);
        std::from_chars(second.data(), second.data() + second.size(), y);
        //std::cout<<x<<" "<<y<<"@\n";
        bool flag = move_chessboard(input,x ,y);
        if(flag == false){
            //std::cout<<"R\"(\n"
            std::cout<<first_line<<"\n";
            for(int i=0; i<array_size; ++i){
                for(int j=0; j<column; ++j)
                    std::cout<<chessboard[i][j];
                std::cout<<"\n";
            }
            for(int i=0; i<column; ++i)
                std::cout<<" ";
            std::cout<<"\nnow position: "<<x<<" "<<y<<"\n";
            std::cout<<"player "<<p<<"'s turn\n";
        }
        else{
            if(input == User_Input::Space){
        if (p == 1)
                    chessboard[y-1][x*2] = 'O';
        else if (p == 2)
            chessboard[y-1][x*2] = '@';
        placed = true;
        } else if(chessboard[y-1][x*2] != 'O' && chessboard[y-1][x*2] != '@')
                chessboard[y-1][x*2] = '+';
            //std::cout<<"R\"(\n"
            std::cout<<first_line<<"\n";
            for(int i=0; i<array_size; ++i){
                for(int j=0; j<column; ++j)
                    std::cout<<chessboard[i][j];
                std::cout<<"\n";
            }
            for(int i=0; i<column; ++i)
                std::cout<<" ";
            std::cout<<"\nnow position: "<<x<<" "<<y<<"\n";
        if (p == 1 && placed == true)
            std::cout<<"player 2's turn\n";
        else if (p == 2 && placed == true)
            std::cout<<"player 1's turn\n";
        else
            std::cout<<"player "<<p<<"'s turn\n";
        }
    }
    int result = judge(x, y, p, placed);
    if(result==12){
        std::cout<<"DRAW!\n";
        //std::cout<<")\"";
        return 12;
    }
    else if(result==1){
        std::cout<<"O Win!\n";
        //std::cout<<")\"";
        return 1;
    } 
    else if(result==2){
        std::cout<<"@ Win!\n";
        //std::cout<<")\"";
        return 2;
    }
    else std::cout<<"Game moving on...\n";
    //std::cout<<")\"";
    return 0;
}

// Judge
constexpr int judge(int &x, int &y, int &p, bool &placed){
    if(placed){

    int count = 0;
    int r = y-1; // 0~8
    int c = x*2; // 2~18
    char sign[3] = {' ', 'O','@'};
    // Check Vertical WIN
    while(r>=0 && chessboard[r][c]==sign[p]){
        count++;
        r--;
        if(count==5) return p;
    }
    r = y-1+1;
    while(r<array_size && chessboard[r][c]==sign[p]){
        count++;
        r++;
        if(count==5) return p;
    }

    r = y-1;
    count = 0;
    // Check Horizontal WIN
    while(c>=2 && chessboard[r][c]==sign[p]){
        count++;
        c -= 2;
        if(count==5) return p;
    }
    c = x*2+2;
    while(c<=array_size*2 && chessboard[r][c]==sign[p]){
        count++;
        c += 2;
        if(count==5) return p;
    }
    
    c = x*2;
    count = 0;
    //Check Left Cross WIN
    while(r>=0 && c>=2 && chessboard[r][c]==sign[p]){
        count++;
        r--;
        c -= 2;
        if(count==5) return p;
    }
    r = y-1+1;
    c = x*2+2;
    while(r<array_size && c<=array_size*2 && chessboard[r][c]==sign[p]){
        count++;
        r++;
        c += 2;
        if(count==5) return p;
    }

    r = y-1;
    c = x*2;
    count = 0;
    //Check Right Cross WIN
    while(r>=0 && c<=array_size*2 && chessboard[r][c]==sign[p]){
        count++;
        r--;
        c += 2;
        if(count==5) return p;
    }
    r = y-1+1;
    c = x*2-2;
    while(r<array_size && c>=2 && chessboard[r][c]==sign[p]){
        count++;
        r++;
        c -= 2;
        if(count==5) return p;
    }

    // Check DRAW
    int num=0;
    for(int i=0; i<array_size; ++i)
        for(int j=1; j<=array_size; ++j)
            if(chessboard[i][2*j]=='O'||chessboard[i][2*j]=='@') num++;
    if(num==array_size*array_size) return 12;

    }
    return 0;
}