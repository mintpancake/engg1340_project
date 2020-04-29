# ENGG1340 Project

## Catch Me
***
## Team Members
Lu Meng             3035639379<br />
Chen Xueqing        3035638351
***
## How to Use
- For Windows
   1. Go to `game_app.h`
   2. Undefine `LINUX`
   3. Compile using `g++ -pedantic-errors -std=c++11 game_app.cpp -o game_app.exe`
   4. Run `game_app.exe`
- For Linux
   1. Go to `game_app.h`
   2. Define `LINUX`
   3. Compile using `g++ -pedantic-errors -std=c++11 game_app.cpp -o game_app -lpthread`
   4. Run `game_app`
- For Mac OS
   - Oops! We don't support that. 
***
## Game Description
### Overall Description
The game is a word-guessing game with a countdown. 
### Detailed Gameplay
At first, the player will get an incomplete word with only part of its letters displayed, other hidden letters will be displayed as short dashes. The player needs to use a basket to catch letters falling from the top of the screen within a given time. 

If he/she catches the right letter, the letter will be revealed by replacing the corresponding dash. If he/she catches the wrong letter, the left time will be reduced. 

If the player fills the word within the given time, he/she can challenge the next level, and the left time will be added to the countdown of the next level. 

If time runs out before the word is filled, the game is over directly. 
### Ranking Method
If a player passes all ten levels, he/she could be credited to the leaderboard. The player with more time left will get a higher ranking.
***
## Planned Functions
### 1. Preparation
- include macro definitions and function declarations stored in game_app.h ***5.Program codes in multiple files*** 

### 2. Initialization
- Output the greeting words and the menu to the screen
- Get the commands of the player as input
- Initialize all kinds of data
   - Initialize the basket which is controlled by the player
   - Initialize the letters falling from the top of the screen ***2.Data structures for storing game status***
   - Initialize the hidden words for this level ***1.Generation of random game sets or events***
   - Initialize the countdown for this level

### 3. Process with judgement and update
- Move the basket according to the player's operation
- Judge whether the player has caught the right letter
- Update the letters falling from the top of the screen ***3.Dynamic memory management***
- Update the word by revealing the hidden letter if the player has caught the right one
- Show the passage of time
- Display all updated data
- Judge whether the player has passes the game

### 4. Record of result
- Record the performance of the player ***4.File input/output***