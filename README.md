# Snakes And Ladders
Jabir Chowdhury and Hasif Ahmed 

## Rules
The core part of our final project is centered around the centuries old board game, snakes and ladders. We incorparate the same rules as 
the actual board game does: 
1. Rolling a 6 means you can roll again
2. You win by reaching position 100
3. If your piece is at a position to win, but rolls a number that added on to your current position exceeds 100, you have to go back that many positions. 
4. Snakes only bring your piece down and ladders only bring your piece up, they are not bidirectional

## How to run the program
When starting up the project in the terminal:
1. Enter hostname -I in the terminal where you will host the server (an ip address should be returned by the terminal)
2. Enter **./server n** (n being a number between 2 and 4 indicating how many players there will be)
3. Enter a password that you will not forget <br>
Once the server is set up, for a client to connect:
1. Enter in terminal **./client ip-addresss** (The ip address is that of the server -- the one that was printed by hostname -I )
2. Have fun!

## Bugs
1. Sometimes the position of a player's token is mistakenly printed as a very high number, this bug however does not affect the overall gameplay as the error is fixed when the user rolls the die again.
2. Sometimes the input for the user does not show up. This prevents the players from typing "roll" which is required to roll the die. As a result, the game can't progress and needs to be restarted by recreating the server.
