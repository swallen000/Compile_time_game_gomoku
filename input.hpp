#pragma once
#include <string_view>
#include <array>

enum class User_Input{
    Empty,
    Top,
    Down,
    Left,
    Right,
    Space
};

constexpr User_Input input = User_Input::Input;

constexpr auto game_string = std::string_view(
    #include "current.txt"
);
constexpr int array_size = 9;
constexpr int row = array_size+3;
constexpr int column = array_size*2+1;

std::array<std::array<char, column>, array_size> chessboard;

