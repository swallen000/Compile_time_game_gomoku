# COMS 4995 final project

## Design document
### Motivation
- C++ is one of the most powerful languages that can handle compile-time implementations and generic programming. Especially with the `template` and `constexpr` feature.
- C++ evolution in C++ 17/20, more and more functions/data structures can be supported in compile-time. For example, one of the C++20 features is that in the future, both std::vector and std::string can be implemented during compile-time.
- Given that the final project should be interesting and interactive, we decided to perform compile-time implementations via a Gomoku game instead of a specific library.

### Different approach in compile-time game and run-time game:
- Logic in run-time game:
![](https://i.imgur.com/xvw3Gyw.png)

- Logic in compile-time game
![](https://i.imgur.com/2fttCp9.png)

### Major Design feature (of C++17/20):
- template mega programming
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
```=
    static_assert(STR("abc") == "abc", "sentence1 error");
    static_assert(STR("abc") == STR("abc"), "sentence2 error");
    static_assert( (STR("Hello")+STR(" ")+STR("World!")) ==  "Hello World!" , "sentence3 error" );

    static_assert( STR("Hello World!").starts_with("Hello") == true, "sentence4 error" );
    static_assert( STR("Hello World!").ends_with("World!") == true, "sentence5 error" );
    static_assert( STR("Hello World!").substr<0, 5>() == "Hello", "sentence6 error" );
    static_assert( STR("Hello World!")[0] == 'H', "sentence7 error" );
```


### Tutorial
#### How to start the compile-time game -> first we need to write a shell script
```=
$keyboard = "Empty"
while :
do
    g++ -O3 -std=c++2a main.cpp -DInput=$keyboard -o main

done
```

### Mesurement
#### compile time
- The average compile time for each step is 0.885 sec.
- We include .txt in compile time at every move, this is the reason why the compile time is slow.

#### test user-defined STR vs std::string_view (speed):
- Running 10000000 times when try to initialize the very long string to STR and string_view: string_view is 4 times faster than user-defined string
(user-defined string: 74971µs, std::string_view: 16593µs)
- Running 10000000 times when try to get the substr to STR and std: string_view: string_view is 3 times faster than user-defined string
(user-defined string: 42593µs, std::string_view: 14619µs
- However, STR support "+" operator, that is, we can concatenate multple STRs together. For example:
```=
constexpr STR test_str = STR("Design ")+STR("Using ")+STR("C++");
```
- Conclusion: if you don't need the function to support concatenating multiple strings, using std::string_view would be more efficient

### Reference
- https://github.com/Jiwan/meta_crush_saga
- https://stackoverflow.com/questions/20874388/error-spliting-an-stdindex-sequence
- https://gist.github.com/dominicusin/b4008ab9895240f615be6a886eb81829
- https://gist.github.com/dsanders11/8951887
- https://en.cppreference.com/w/cpp/string/basic_string_view
- https://en.cppreference.com/w/cpp/utility/integer_sequence
- 
