# Report

## Implementation

### Major Design feature (of C++17/20):
- template meta programming
- `std::string_view` 
- `std::from_chars` (`stoi` for `string_view`)
- `std::integer_sequence` / `std::index_sequence`

### How to construct a compile-time game -> first we need to write a shell script
Here is the pseudo code:
```python
$keyboard = "Empty"
while :
    #user compile flag to pass user input
    #Here, -DInput=$keyboard is equal to #define Input $keyboard in C++ file
    g++ -O3 -std=c++2a main.cpp -DInput=$keyboard -o main
    
    #print chessboard current state
    ehco (./main)
    
    
    
    while (not receive user input):
        $keyboard = read user input
        if $keyboard is not empty:
            break
```

### How to read file and save

```cpp
constexpr auto my_string = std::string_view(
    #include "file.txt"
);
```

File should be written like this:
(The chars should all be in the ASCII Table.)

```cpp
R"(
your data...
)"
```

This is a useful method to read game state.
In this way, 

```cpp
my_string = ['y', 'o', 'u', 'r', ' ', 'd', 'a', 't', 'a', '.', '.', '.', '\n']
```

#### User-defined string (`class STR`)
##### Why?
- You need a string class that can be implemented in compile-time so that you can acquire the game states from a .txt file (read input and save) 
- std::string is not yet be supported in compile-time by current compilers(C++20)
- std::string_view is a good choice, and it's faster too!
- However, we want to implement some functions that std::string_view doesn't provide (e.g.: concatenate multiple strings), so we design a new class

##### Some support functions in `class STR`:
- `substr` 
    - similar to `string.substr()`, but here we use template to pass the size of the new STR
- `starts_with`
    - `STR("Michael Jordan").starts_with("Michael")` 
    - check whether the string starts with the given string
- `ends_with`
    - `STR("Michael Jordan").ends_with("Jordan")`
    - similar to the function starts_with
- `print_sequence`
    - print all elements in the STR
- `size()`, `length()`
    - return current `STR.size()`
- `empty()`
    - check whether current STR is empty
- `operator+`
    - support to concatenate STRs
- `operator==`
    - support to compare two STRs

```cpp
//"Hello"
STR("Hello World!").substr<0, 5>()

//"World!"
STR("Hello World!").substr<6>()

//true
STR("Michael Jordan").starts_with("Michael") 

//true
STR("Michael Jordan").ends_with("Jordan")

//output: Design Using C++
STR("Design Using C++").print_sequence()

//"COMS 4995"
STR("COMS")+" "+STR("4995")

//output "Columbia University"
constexpr STR a = "Columbia"
constexpr STR b = "University"
(a+" "+b).print_sequence()
```

#### How we construct the `class STR` (using template)
First, we need a constructor, that is, we can load information from char array.
```cpp
template <std::size_t N>
class STR{
public:
    template <typename... Elements>
    constexpr STR( Elements... elements )
        : arr{ elements...}{
    }

    template<std::size_t ..._N>
    constexpr STR( const char(&rhs)[N], const std::index_sequence<_N...>)
        : STR( rhs[_N]...){

    }

    //std::make_index_sequence<N-1>{} = {0, 1, 2, ..., N-1}
    constexpr STR( const char(&a)[N] )
        : STR( a, std::make_index_sequence<N>{} ){

    }

    constexpr char operator[]( const std::size_t pos ) const{
        return pos < N - 1 ? arr[pos] : throw std::out_of_range("Index out of range");
    }
    
private:
    char arr[N];
};
```
Sample implementation of `substr()` function

```cpp
template <std::size_t N>
class STR{
public:
    constexpr STR(const char* a, std::size_t size)
        : arr{}{
        for (std::size_t i = 0; i < size; ++i) {
            arr[i] = a[i];
        }
    }

    template<std::size_t start, std::size_t length>
    constexpr auto substr() const{
        if( start >= N - 1 || start + length >= N )
            throw std::out_of_range("Index out of range");
        STR<length+1> ans(arr + start, length);
        return ans;
    }
};
```


### Test
#### Basics
- To test the robustness of basic operations more conveniently, we use `loop_input.sh` to run the tests, and we replace human user inputs with the following pre-defined files by specifying `filename`.
    - `input-@win.txt`
    - `input-Owin.txt`
    - `input-draw.txt`
- [x] The program can run end-to-end without error.
- [X] The program can terminate when a draw situation or one of the players wins.
- [X] When the cursor(`+`) attempts to go out of the board, it stays at the same place.
- [X] When the player selects an occupied grid, this move would be neglected. Also, the player’s turn remains.

#### Test the correctness of the user-defined `class STR` :
```cpp
    static_assert(STR("abc") == "abc", "s1 error");
    static_assert(STR("abc") == STR("abc"), "s2 error");
    static_assert( (STR("Hello")+" "+STR("World!")) ==  "Hello World!" , "s3 error" );

    static_assert( STR("Hello World!").starts_with("Hello") == true, "s4 error" );
    static_assert( STR("Hello World!").ends_with("World!") == true, "se5 error" );
    static_assert( STR("Hello World!").substr<0, 5>() == "Hello", "s6 error" );
    static_assert( STR("Hello World!")[0] == 'H', "s7 error" );
```

## Manual
:black_circle: :arrow_left: :arrow_down: `+` <br>
:white_circle: :arrow_right: :arrow_up:  `space` <br>

Environment:

OS: macOS Big Sur (Version 11.2.3)
Compiler: Apple clang version 12.0.0

1. Dowload Compile **Time Game: Gomoku** from GitHub
    `git clone  https://github.com/swallen000/Compile_time_game_gomoku.git`

2. Restore the game board to origin (no stones on the board).
    `cp original.txt current.txt`

3. Start the game!
    * `bash ./input.sh`
    * Use ⬆️ ⬅️ ⬇️ ➡️ to move the cursor(+).
    * Press `space` to place a stone.

4. (Optional) Run this if you want to see how the game works.
    * `bash ./loop_input.sh`


## Tutorial

Here we want to show you how to implement a minimal compile-time game. We would take "Rock paper scissors" as an example. The steps are as follows:

### Step 0. Design your game states

For the purpose of this example, we only want to count the times of wins, losing and draws, which means a file with the following content suffices:

```cpp
R"(
0
0
0
)

```
Let's call this file `states.txt` The first zero is the times of win. The second zero is the times of lose. The third zero is the times of draw. 

### Step 1. Assume user input and integrate it into your core game logic

Assume that we have a PRNG called `compile_time_random()` that can be called during compile-time. For how to implement such a function, please see [Constexpr pseudorandom numbers](https://mklimenko.github.io/english/2018/06/04/constexpr-random/) .

Now take a look at the following conceptual code. Noted that 1) the game states will be "something like a string", 2) there's a magical variable `input` representing the user input, and 3) you need to `cout` the game states for the next step.

```cpp
constexpr int rock_paper_scissors(){
    
    int computer = compile_time_random() % 3;
    // 0 means rock, 1 means paper, and 2 means scissors

    int win = state_line[0] - '0';
    int lose = state_line[2] - '0';
    int draw = state_line[4] - '0';
    // only support one digit, just to make it more
    // understandable, you might want to use std::from_chars instead
    
    if (computer == 2 && input == User_Input::Rock ||
        computer == 0 && input == User_Input::Paper ||
        computer == 1 && input == User_Input::Scissors) {
        win += 1;
    }

    // TODO implement the cases for lose and draw
    /* assume that you have implemented game logics here */

    std::cout << "R\"(\n";
    std::cout << win << "\n";
    std::cout << lose << "\n";
    std::cout << draw << "\n";
    std::cout << ")\""

    return 0;
}
```

### Step 2. Use Shell Scripts to Connect the modules

The magical variable `input` actually comes from the compile flag `-DInput` that you will use for the `g++` command. (you will have a `constexpr User_Input input = User_Input::Input` elsewhere in your source code)

Noted that you will "update" the game states by the `echo` command, as you can see in the last line of the skeleton code for your shell scripts, which is read during the compile time by using

```cpp
// somewhere in your .cpp or .hpp file
constexpr auto game_string = std::string_view( 
#include "states.txt"
);
```
Here is the skeleton code for your shell scripts:

```shell
IFS=
keyboard='Empty'

while :
do
    g++ -O3 -std=c++2a main.cpp -DInput=$keyboard -o main
    ./main
    while :
    do
        read -rsn1 input
        if [ $input == $'r' ]
        then
            keyboard='Rock'
        elif [ $input == 'p' ]
        then
            keyboard='Paper'
        elif [ $input == 's' ]
        then
            keyboard='Scissors'
        else
            keyboard='None'
        fi

        if [ $keyboard != 'None' ]
        then
            break
        fi
    done
    echo $(./main) > states.txt
```

## Measurement
### compile time

Testing environment:

CPU: 1.1 GHz Quad-Core Intel Core i5
RAM: 16 GB 3733 MHz LPDDR4X
OS: macOS Big Sur (Version 11.2.3)
Compiler: Apple clang version 12.0.0
Compile command: g++ -O3 -std=c++2a

- The average compile time for each step is 0.885 sec.
- We include a .txt in compile time at every move, and this is the reason why the compile time is so slow. An insight here is that when deciding to build a game, managing the game in compile time would not give you a explicit boost on CPU time. 

### test user-defined `class STR` vs `std::string_view` (speed):
Testing environment:

CPU: 2.3 GHz Duo-Core Intel Core i5
RAM: 8 GB 2133 MHz LPDDR3
OS: macOS Catalina (Version 10.15.4)
Compiler: Apple clang version 12.0.0
Compile command: g++ -O3 -std=c++2a

- Running 10000000 times when try to initialize the very long string to STR and string_view: string_view is 4 times faster than user-defined string
(user-defined string: 74971µs, std::string_view: 16593µs)
- Running 10000000 times when try to get the substr to STR and std: string_view: string_view is 3 times faster than user-defined string
(user-defined string: 42593µs, std::string_view: 14619µs
- However, STR support "+" operator, that is, we can concatenate multiple STRs together. For example:
```cpp
constexpr STR test_str = STR("Design")+" "+STR("Using")+" "+STR("C++");
```
- Conclusion: if you don't need the function to support concatenating multiple strings, using std::string_view would be more efficient

### In-Memory vs On-Disk Game States

Testing environment:

CPU: 1.6 GHz duo-core Intel Core i5
RAM: 16 GB 2133 MHz LPDDR3
OS: macOS Big Sur
Compiler: Apple clang version 12.0.0 (clang-1200.0.32.29)
Compile command: `g++ -O3 -std=c++2a` 

We save the game states as a file, so we need to read from and write into it once per player turn. We want to see if these operations can be less expensive by using an in-memory file system. 

We compare two scenarios. In the first scenario, the game state is a file on the disk. In the other scenario, the game state is a file on an in-memory file system. For each scenario, we use the `time` command to collect data for 10 player turns and calculate the corresponding statistics.

| On Disk       | AVE   | STD   |
|---------------|-------|-------|
| compile       | 1.80  | 0.11  |
| write to file | 0.019 | 0.004 |

| In Memory     | AVE   | STD   |
|---------------|-------|-------|
| compile       | 1.69  | 0.14  |
| write to file | 0.019 | 0.006 |

As a result, there's no significant difference between the two scenarios. It seems that the cache is functioning well for the purpose of our tasks. The fact that our game states are only hundreds of bytes is probably why an in-memory file system is no better than a disk file system. The game states can stay in memory and has low access cost while being a file on the disk.

## Bad attempts we made

### Using in-memory file systems or memory-mapped file seems like a premature optimization.

### Using non `const`/`constexpr` element to pass into template
```cpp
for(std::size_t i=0; i<9; ++i)
    constexpr auto str = game_string.substr<i, column_size>();
```

### Using std::cout to debug
```cpp
(X) std::cout << string;
(O) static_asser(string == "O @ O @", "string comparison error")
```
If we can see what is wrong in compile time, we should not wait until run time.



### What we have learned
* C++ is very powerful
* using static_assert to help debug when we tried to write functions in compile-time
* template mega recursions have limited depth, we can use compile flag `-ftemplate-depth=` to set required depth. However, due to the compiler limitation and hardware limitation, we can't set the value arbitrarily high as we want.


## Future Work
### Implement an AI player, so that a user can play with the computer.

* By using alpha-beta pruning or similar algorithms

### MVC design pattern

In terms of the **model-view-controller** (MVC) design pattern, our view is the executable, our controller is the shell script, and our model, the compiler.

Ideally, what is displayed to the user should be separated from the internal representation, or the internal game states, to allow the development of more complex games. However, we didn't make this the nature of our design.

## Reference
[Error spliting an std::index_sequence](https://stackoverflow.com/questions/20874388/error-spliting-an-stdindex-sequence) <br>
[Compile-time strings and string concatenation](https://gist.github.com/dominicusin/b4008ab9895240f615be6a886eb81829) <br>
[dsanders11/StringConstant.h](https://gist.github.com/dsanders11/8951887) <br>
[std::basic_string_view](https://en.cppreference.com/w/cpp/string/basic_string_view) <br>
[std::integer_sequence](https://en.cppreference.com/w/cpp/utility/integer_sequence) <br>
[Jiwan/meta_crush_saga](https://github.com/Jiwan/meta_crush_saga) <br>[Constexpr pseudorandom numbers](https://mklimenko.github.io/english/2018/06/04/constexpr-random/) <br>