# TicTacToe in C++

TicTacToe terminal game written in C++ 20
* Local 1v1s
* Hostserver to play multiplayer
* Connect to server
* Game history
* Server history


NOTE: a player can also connect to a server via EX telnet

 
What i would want to fix
* a online player also should be able to enter a name ( not its hardcoded socketplayer )
* as of now the host of the server always starts the game, should be random maybe?
* Could create some kind of history class i think that handles filewriting or filehandler class maybe?
* Better error handling in the server, it exits the program now if error


Heap Allocation
* Player names
* GameSession moves
* The GameSession in online games. (i did this just to test the differences, no other reason)
- rest is on the stack


compile with gcc
```bash
g++ -o app main.cpp includes/*

```


## cons pros of c++ by me :D
### pros:
* Faster ( said to be.. atleast, i think its hard to notice in a small program like this )
* STL aka librarys ( made setting up a tcp socket server pretty simple.. Really annoying they are different on windows / unix tho..)
* fun with exe files
### cons:
* memory leaks / no garbage collection (scaryy, not so in this small program but...)
* pointers to pointers to pointers? I think if you code alot in c++ it makes alot of sense but when your new i can see how its pretty confusing


Doing this in java would be easier i think but you get more controll of memory etc in c++, but its a bit more complex, but much more low level controll.

## C++ over java
### pros:
* good to expand expertice / learn about memory allocation
* more low level control than java
* exe file :D
### cons:
* no jvm, cant run program on any machine with java


## STL
### pros:
* super easy to import or include...
* conistent interfaces? ( different libs for different system are really alike )
### cons:
* cant compile same libs on different systems ( windows / unix ) really annoying !!!


## OOP? ofcourse i love that guy
* Easy to understand, maintain and update
* Can reuse code

## Stack vs heap?
* On the stack the memory is automatically managed, they are auto deallocated when they are out of scope
* On the heap the data is stored on the memory until it is deallocated manually with delete. Heap data is harder to work with if ur new to it. Wider scope with pointers, larger objects dont need to be copied wich saves time and power. Scary with memory leaks if you forget to delete something on the heap, maybe not in this program but in larger i would prob sweat about it.

## Challenge
* Of course pointers, but also the compiling and learning header files was not obvious i think.

## Lesson
* For sure pointers, I think its good to know about memory management even if i dont enjoy it. I also really like to widen my experience across different languages.
