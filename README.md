# COMS 4995 final project⚪ ⚫ 

## Design document
### Motivation
- C++ is one of the most powerful languages that can handle compile-time implementations and generic programming. Especially with the `template` and `constexpr` feature.
- C++ evolution in C++ 17/20: more and more functions/data structures can be supported in compile-time. For example, one of the C++20 features is that in the future, both std::vector and std::string can be implemented during compile-time (not yet supported by current compilers).
- Given that the final project should be interesting and interactive, we decided to perform compile-time implementations via a Gomoku game.

### Different approach in compile-time game and run-time game:
- Logic in run-time game:
![](https://i.imgur.com/xvw3Gyw.png)

- Logic in compile-time game
![](https://i.imgur.com/2fttCp9.png)

### Major Design feature (of C++17/20):
- template meta programming
- std::string_view 
- std::from_chars_result from_chars (stoi for string_view)
- std::integer_sequence / std::index_sequence
- etc


### Test
#### Basic
- To test the robustness of basic operations more conveniently, we use `loop_input.sh` to run the tests, and we replace human user inputs with the following pre-defined files by specifying `filename`.
    - `input-@win.txt`
    - `input-Owin.txt`
    - `input-draw.txt`
- [x] The program can run end-to-end without error.
- [X] The program can terminate when a draw situation or one of the players wins.
- [X] When the cursor(+) attempt go out of the board, it stays at the same place.
- [X] When the player select the same grid to place the stone, this move would be neglected. Remains the player's turn.

#### Test user-defined STR correctness:
```cpp=
    static_assert(STR("abc") == "abc", "sentence1 error");
    static_assert(STR("abc") == STR("abc"), "sentence2 error");
    static_assert( (STR("Hello")+STR(" ")+STR("World!")) ==  "Hello World!" , "sentence3 error" );

    static_assert( STR("Hello World!").starts_with("Hello") == true, "sentence4 error" );
    static_assert( STR("Hello World!").ends_with("World!") == true, "sentence5 error" );
    static_assert( STR("Hello World!").substr<0, 5>() == "Hello", "sentence6 error" );
    static_assert( STR("Hello World!")[0] == 'H', "sentence7 error" );
```

### Manual
:black_circle: :arrow_left: :arrow_down: `+` <br>
:white_circle: :arrow_right: :arrow_up:  `space` <br>
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


### Tutorial
#### How to construct a compile-time game -> first we need to write a shell script
Here is the pseudo code:
```python=
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

#### User-defined string
##### Why?
Because we want to implement some functions that std::string_view doesn't provide (e.g.: concatenate multiple strings)

##### some support functions:
- substr 
    - similar to string.substr(), but here we use template to pass the size of the new STR
- starts_with
    - STR("Michael Jordan").starts_with("Michael") 
    - check whether the string starts with the given string
- ends_with
    - STR("Michael Jordan").ends_with("Jordan")
    - similar to the function starts_with
- print_sequence
    - print all elements in the STR
- size(), length()
    - return current STR.size()
- empty()
    - check whether current STR is empty  
- operator+
    - support to concatenate STRS
- operator==
    - support to compare two STRS
```cpp=
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
STR("COMS")+STR(" ")+STR("4995")

//"Columbia University"
constexpr STR a = "Columbia "
constexpr STR b = "University"
(a+b).print_sequence()
```

#### How we construct the class STR
```cpp=
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

    constexpr STR( const char(&a)[N] )
        : STR( a, std::make_index_sequence<N-1>{} ){

    }

    constexpr char operator[]( const std::size_t pos ) const{
        return pos < N - 1 ? arr[pos] : throw std::out_of_range("Index out of range");
    }

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
private:
    char arr[N];
};
```


### Mesurement
#### compile time

Testing environment:

CPU: 1.1 GHz Quad-Core Intel Core i5
RAM: 16 GB 3733 MHz LPDDR4X
OS: macOS Big Sur (Version 11.2.3)
Compiler: Apple clang version 12.0.0
Compile command: g++ -O3 -std=c++2a

- The average compile time for each step is 0.885 sec.
- We include .txt in compile time at every move, this is the reason why the compile time is slow.

#### test user-defined STR vs std::string_view (speed):
Testing environment:

CPU: 2.3 GHz Duo-Core Intel Core i5
RAM: 8 GB 2133 MHz LPDDR3
OS: macOS Catalilina (Version 10.15.4)
Compiler: Apple clang version 12.0.0
Compile command: g++ -O3 -std=c++2a

- Running 10000000 times when try to initialize the very long string to STR and string_view: string_view is 4 times faster than user-defined string
(user-defined string: 74971µs, std::string_view: 16593µs)
- Running 10000000 times when try to get the substr to STR and std: string_view: string_view is 3 times faster than user-defined string
(user-defined string: 42593µs, std::string_view: 14619µs
- However, STR support "+" operator, that is, we can concatenate multple STRs together. For example:
```=
constexpr STR test_str = STR("Design ")+STR("Using ")+STR("C++");
```
- Conclusion: if you don't need the function to support concatenating multiple strings, using std::string_view would be more efficient

#### In-Memory vs On-Disk Game States

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

### Bad attempts we made

#### Using in-memory file systems or memory-mapped file seems like an premature optimization.

#### Using non const/constexpr element to pass into template
```cpp=
for(std::size_t i=0; i<9; ++i)
    constexpr auto str = game_string.substr<i, column_size>();
```

#### Using std::cout to debug
```cpp=
(X) std::cout << string;
(O) static_asser(string == "O @ O @", "string comparison error")
```
If we can see what is wrong in compile time, we should not wait until run time.

#### Using game view directly as game model input

Our game view shows on the terminal, and the terminal may have other message on it. It is error-phone if we 

### What we have learned
* C++ is very powerful
* using static_assert to help debug when we tried to write functions in compile-time
* template mega recursions have limited depth, we can use compile flag ```-ftemplate-depth=``` to set required depth. However, due to the compiler limitation and hardware limitation, we can set the value arbitrarily high as we want.


### Future Work
#### Implement an AI player, so that a user can play with the computer.
    * By using alpha-beta pruning or similar algorithms
* 

### Reference
- https://stackoverflow.com/questions/20874388/error-spliting-an-stdindex-sequence
- https://gist.github.com/dominicusin/b4008ab9895240f615be6a886eb81829
- https://gist.github.com/dsanders11/8951887
- https://en.cppreference.com/w/cpp/string/basic_string_view
- https://en.cppreference.com/w/cpp/utility/integer_sequence
- https://github.com/Jiwan/meta_crush_saga
- https://gist.github.com/rxaviers/7360908
