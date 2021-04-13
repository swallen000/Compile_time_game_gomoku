# Compile Game- Gomoku⚪ ⚫ 

## Motivation
- C++ is one of the most powerful languages that can handle compile-time implementations and generic programming. Especially with the `template` and `constexpr` feature.
- C++ evolution in 17/20: more and more functions/data structures can be supported in compile-time. For example, one of the C++20 features is that in the future, both std::vector and std::string can be implemented during compile-time (not yet supported by current compilers).
- Given that the final project should be interesting and interactive, we decide to perform compile-time implementations through a Gomoku game.

## Different approach in compile-time game and run-time game:
- Logic in run-time game:
![](https://i.imgur.com/xvw3Gyw.png)

- Logic in compile-time game:
![](https://i.imgur.com/2fttCp9.png)

## Major Design feature (of C++17/20):
- template meta programming
- `std::string_view` 
- `std::from_chars` (`stoi` for `string_view`)
- `std::integer_sequence` / `std::index_sequence`

## Manual
:black_circle: :arrow_left: :arrow_down: `+` <br>
:white_circle: :arrow_right: :arrow_up:  `space` <br>

1. Download Compile **Time Game: Gomoku** from GitHub
    `git clone  https://github.com/swallen000/Compile_time_game_gomoku.git`

2. Restore the game board to origin (no stones on the board).
    `cp original.txt current.txt`

3. Start the game!
    * `bash ./input.sh`
    * Use ⬆️ ⬅️ ⬇️ ➡️ to move the cursor(`+`).
    * Press `space` to place a stone.

4. (Optional) Run this if you want to see how the game works.
    * `bash ./loop_input.sh`

