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
  char color[4][10] = {"red" , "blue", "green", "yellow"};
  for (i = 0; i < num_players; i++) {
    write(players[i], buffer, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "You are player #%d. Your token is %s", i, color[i]);
    write(players[i], buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);
    snprintf(buffer, sizeof(buffer), "%d", i);
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
        position[i] += num_rolled;
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "Player %d has rolled a %d moving to position %d", i, num_rolled, position[i]);
        for (j = 0; j < num_players; j++)
          if (j != i)
            write(players[j], buffer, sizeof(buffer));
        turns[i] -=1;
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", i);
        write(players[i], buffer, sizeof(buffer));

        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%s", color[i]);
        write(players[i], buffer, sizeof(buffer));

        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", num_players);
        for (j = 0; j < num_players;j++){
          sprintf(buffer + strlen(buffer), " %d", position[j]);
        }
        write(players[i], buffer, sizeof(buffer));
      }
    }
  }
}
