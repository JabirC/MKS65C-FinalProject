#include "networking.h"
#include "fxn.c"


static void sighandler(int signo){
  if(signo == SIGINT){
    printf("Server is exiting...\n");
    exit(0);
  }
}

int main(int argc, char **argv) {
  signal(SIGINT, sighandler);
  int num_players = 0;
  char pass[BUFFER_SIZE] = "";
  char buffer[BUFFER_SIZE];
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
    while(1){
      printf("What do you want the password to be? : ");
      fgets(pass, sizeof(pass), stdin);
      *strchr(pass, '\n') = 0;
      if (strlen(pass) == 0 || strlen(pass) > 20){
        printf("Password has to be atleast 1 and atmost 20 characters long.\n");
        memset(pass, 0, 22);
      }
      else break;
    }
  }

  int listen_socket, i = 0, j;
  int players[num_players], subservers[num_players], turns[num_players], position[num_players];
  memset(position,0, sizeof(position));
  listen_socket = server_setup();

  while (i < num_players) {
    players[i] = server_connect(listen_socket);
    read(players[i], buffer, sizeof(buffer));
    if(strcmp(buffer, pass)){
      memset(buffer, 0, BUFFER_SIZE);
      sprintf(buffer, "%d", 0);
      write(players[i], buffer, sizeof(buffer));
      printf("51 %s\n", buffer);
      close(players[i]);
      continue;
    }
    memset(buffer, 0, BUFFER_SIZE);
    sprintf(buffer, "%d", 1);
    write(players[i], buffer, sizeof(buffer));
    printf("58 %s\n", buffer);
    memset(buffer, 0, BUFFER_SIZE);

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



  //setup players
  char color[4][10] = {"magenta" , "red", "green", "yellow"};
  int snake_heads[4] = {97, 39, 67, 51};
  int snake_tails[4] = {58, 17, 45, 28};
  int ladder_bot[4] = {41 , 57, 7, 68};
  int ladder_top[4] = {61, 87, 25, 90};
  for (i = 0; i < num_players; i++) {
    printf("82 %s\n", buffer);
    snprintf(buffer, sizeof(buffer), "You are player #%d. Your token is %s", i, color[i]);
    write(players[i], buffer, sizeof(buffer));
    printf("85 %s\n", buffer);
  }

  memset(buffer, 0, BUFFER_SIZE);
  int num_rolled = 0;

  while(1) {
    for (i = 0; i < num_players; i++) {
      turns[i] += 1;
      while (turns[i]) {
        write(players[i], ACK, sizeof(ACK));
        printf("95 %s\n", buffer);
        if(read(players[i], buffer, sizeof(buffer)) == 0){
          printf("Player %d is no longer in the game\n", i);
          exit(0);
        }
        num_rolled = atoi(buffer);
        if(num_rolled==6)turns[i] = turns[i] + 1;
        position[i] += num_rolled;
        int wrap = 0;
        if(position[i] > 100){
          wrap = position[i] - 100;
          position[i] = 100 - wrap;
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
             if(write(players[j], buffer, sizeof(buffer)) == 0){
                printf("A player has left the game, server sutting down...\n");
             }
           }
           printf("136 %s\n", buffer);
        }
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", num_players);
        for (j = 0; j < num_players; j++){
          if (j != i) {
            if(write(players[j], buffer, sizeof(buffer)) == 0){
               printf("A player has left the game, server sutting down...\n");
            }
           }
           printf("146 %s\n", buffer);
        }
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer + strlen(buffer), "%d ", position[0]);
        for (int k = 1; k < num_players;k++){
          sprintf(buffer + strlen(buffer), " %d", position[k]);
        }
        for (j = 0; j < num_players; j++){
          if (j != i) {
            if(write(players[j], buffer, sizeof(buffer)) == 0){
               printf("A player has left the game, server sutting down...\n");
            }
           }
           printf("159 %s\n", buffer);
        }
        turns[i] -=1;
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", i);
        write(players[i], buffer, sizeof(buffer));
        printf("165 %s\n", buffer);
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%s", color[i]);

        // ----------
        write(players[i], buffer, sizeof(buffer));
        printf("171  %s\n", buffer);
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", num_players);
        for (j = 0; j < num_players;j++){
          sprintf(buffer + strlen(buffer), " %d", position[j]);
        }
        write(players[i], buffer, sizeof(buffer));
        memset(buffer, 0, BUFFER_SIZE);
        if(wrap){
          if(is_snake != -1){
            sprintf(buffer, "You rolled a %d passing 100, wrapped around to a snake at %d, went back to %d", num_rolled, 97, snake_tails[is_snake]);
          }
          else sprintf(buffer, "You rolled a %d passing 100, wrapped around to position %d", num_rolled, position[i]);
        }
        else{
          if(is_snake != -1){
            sprintf(buffer, "You rolled a %d moving to a snake at %d, went back to %d",num_rolled, snake_heads[is_snake], snake_tails[is_snake]);
          }
          else if(is_ladder != -1){
            sprintf(buffer, "You rolled a %d moving to a ladder at %d, skipped to %d", num_rolled, ladder_bot[is_ladder], ladder_top[is_ladder]);
          }
          else sprintf(buffer, "You rolled a %d moving to position %d",num_rolled, position[i]);
        }
        write(players[i], buffer, sizeof(buffer));
        printf("178 %s\n", buffer);


        int win = find_index(position, num_players, 100);
        if(win != -1){
           printf("PLAYER %d HAS WON THE GAME. SERVER IS SHUTTING DOWN.\n", win );
           exit(0);
        }
        memset(buffer, 0, BUFFER_SIZE);
       }
    }
  }
}
