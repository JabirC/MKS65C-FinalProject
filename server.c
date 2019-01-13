#include "networking.h"
#include "fxn.c"


int main(int argc, char **argv) {
  int num_players = 0;

  if (argc < 2) {
    printf("Invalid arguments.\n");
    exit(1);
  }
  else {
    sscanf(argv[1], "%d", &num_players);
    if(num_players > 4 || num_players < 2){
      printf("You can only choose 2 to 4 people inclusive!\n");
      exit(1);
    }
  }

  int listen_socket, i = 0, j;
  int players[num_players], subservers[num_players], turns[num_players], position[num_players];
  memset(position,0, sizeof(position));
  listen_socket = server_setup();

  while (i < num_players) {
    players[i] = server_connect(listen_socket);
    turns[i] = 0;
    subservers[i] = fork();
    if (!subservers[i]) {
      close(players[i]);
      return 0;
    }
    i++;
  }
  printf("Server is no longer accepting players.\n");
  shutdown(listen_socket, SHUT_RD);
  char buffer[BUFFER_SIZE];



  //setup players
  char color[4][10] = {"magenta" , "red", "green", "yellow"};
  int snake_heads[4] = {97, 39, 67, 51};
  int snake_tails[4] = {58, 17, 45, 28};
  int ladder_bot[4] = {41 , 57, 7, 68};
  int ladder_top[4] = {61, 87, 25, 90};
  for (i = 0; i < num_players; i++) {
    write(players[i], buffer, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "You are player #%d. Your token is %s", i, color[i]);
    write(players[i], buffer, sizeof(buffer));
  }

  memset(buffer, 0, BUFFER_SIZE);
  int num_rolled = 0;

  while(1) {
    for (i = 0; i < num_players; i++) {
      turns[i] += 1;
      while (turns[i]) {
        write(players[i], ACK, sizeof(ACK));
        read(players[i], buffer, sizeof(buffer));
        num_rolled = atoi(buffer);
        if(num_rolled==6)turns[i]++;
        printf("%d\n",position[i] );
        position[i] += num_rolled;
        printf("%d\n",position[i] );
        int wrap = 0;
        if(position[i] > 100){
          wrap = position[i] - 100;
          printf("%d\n",wrap );
          position[i] = 100 - wrap;
          printf("%d\n",position[i] );
        }
        int is_snake = find_index(snake_heads, 4, position[i]);
        int is_ladder = find_index(ladder_bot, 4, position[i]);
        memset(buffer, 0, BUFFER_SIZE);
        if(wrap){
          if(is_snake != -1){
            sprintf(buffer, "Player %d has rolled a %d passing 100, wraps around to a snake at %d, goes back to %d", i, num_rolled, position[i], snake_tails[is_snake]);
            position[i] = snake_tails[is_snake];
          }
          else sprintf(buffer, "Player %d has rolled a %d passing 100, wraps around to position %d", i, num_rolled, position[i]);
        }
        else{
          if(is_snake != -1){
            sprintf(buffer, "Player %d has rolled a %d moving to a snake at %d, goes back to %d", i, num_rolled, position[i], snake_tails[is_snake]);
            position[i] = snake_tails[is_snake];
          }
          else if(is_ladder != -1){
            sprintf(buffer, "Player %d has rolled a %d moving to a ladder at %d, skips to %d", i, num_rolled, position[i], ladder_top[is_ladder]);
            position[i] = ladder_top[is_ladder];
          }
          else sprintf(buffer, "Player %d has rolled a %d moving to position %d", i, num_rolled, position[i]);
        }
        for (j = 0; j < num_players; j++){
          if (j != i) {
             write(players[j], buffer, sizeof(buffer));
           }
        }
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", num_players);
        for (j = 0; j < num_players; j++){
          if (j != i) {
             write(players[j], buffer, sizeof(buffer));
           }
        }
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer + strlen(buffer), "%d ", position[0]);
        for (int k = 1; k < num_players;k++){
          sprintf(buffer + strlen(buffer), " %d", position[k]);
        }
        for (j = 0; j < num_players; j++){
          if (j != i) {
             write(players[j], buffer, sizeof(buffer));
           }
        }
        turns[i] -=1;
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", i);
        write(players[i], buffer, sizeof(buffer));
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%s", color[i]);

        // ----------
        write(players[i], buffer, sizeof(buffer));
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", num_players);
        for (j = 0; j < num_players;j++){
          sprintf(buffer + strlen(buffer), " %d", position[j]);
        }
        write(players[i], buffer, sizeof(buffer));
        int win = find_index(position, num_players, 100);
        if(win != -1){
           printf("PLAYER %d HAS WON THE GAME. SERVER IS SHUTTING DOWN.\n", win );
           exit(0);
        }
       }
    }
  }
}
