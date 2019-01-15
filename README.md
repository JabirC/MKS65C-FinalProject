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
2. Enter * ./server n * (n being a number between 2 and 4 indicating how many players there will be)
3. Enter a password that you will not forget
Once the server is set up, for a client to connect:
1. Enter in terminal ./client ip addresss from hostname -I 
2. Have fun!

## Bugs
