#pragma once
#include <string_view>
#include <array>
#include "str.hpp"

enum class User_Input{
    Empty,
    Top,
    Down,
    Left,
    Right,
    Space
};

constexpr User_Input input = User_Input::Input;

/*constexpr auto game_string = std::string_view(
    #include "current.txt"
);*/

constexpr auto game_string = std::string_view("");

constexpr auto test_string = STR(
    #include "current.txt"
);

constexpr std::size_t array_size = 9;
constexpr std::size_t row = array_size + 4;
constexpr std::size_t column = array_size*2+1;

//std::array<std::array<char, column>, array_size> chessboard;
char chessboard[array_size][column] = {};
