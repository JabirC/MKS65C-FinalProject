#include "networking.h"
#include "fxn.c"


int check_buffer(char * buffer){
  if (!strcmp(buffer, "roll"))
    return 0;
  else return 1;
}


static void sighandler(int signo){
  if(signo == SIGINT){
    printf("\nExiting game...\n");
    exit(0);
  }
}

int main(int argc, char **argv) {
  signal(SIGINT, sighandler);
  int server_socket;
  char buffer[BUFFER_SIZE];
  srand(time(NULL));
  int rolled = 0;
  int player = -1;
  char color[10] = "";
  int prev_turn = 0;
  int turn = 0;
  int position= 0;
  int special_case = 0;

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );
  printf("Enter the password: ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  write(server_socket, buffer, sizeof(buffer));
  memset(buffer, 0, BUFFER_SIZE);
  read(server_socket, buffer, sizeof(buffer));
  if(!atoi(buffer)){
    printf("Wrong Password\n");
    exit(0);
  }
  system("clear");
  printf("\nWaiting for all players to connect.\n");
  printf("\nWelcome to Snakes and Ladders!\nYour goal is to make it to the 100th box before the other players. Type 'roll' to roll the dice when it is your turn. The number of spaces you move forward depends on the number you roll. If you roll a 6 you get to roll again.\n\n");
  memset(buffer, 0, BUFFER_SIZE);
  while (1) {
    if(!special_case){
          while (read(server_socket, buffer, sizeof(buffer))) {
            if(strlen(buffer) == 0) continue;
            else if (strcmp(buffer, ACK)) {
              if (strlen(buffer) == 1){
                int player_len = atoi(buffer);
                int temp_pos[player_len];

                memset(buffer, 0, BUFFER_SIZE);
                read(server_socket, buffer, sizeof(buffer));
                int a =0;
                char *z = strtok (buffer, " ");
                char *arr[10];
                while (z != NULL)
                {
                    arr[a++] = z;
                    z = strtok (NULL, " ");
                }
                a = 0;
                while(a < player_len){
                  temp_pos[a] = atoi(arr[a]);
                  a++;
                }
                print_board(temp_pos, player_len);
                int temp_win = find_index(temp_pos, player_len, 100);
                if(temp_win != -1){
                  printf(":( PLAYER %d HAS WON THE GAME, BETTER LUCK NEXT TIME!\n", temp_win);
                  exit(0);
                }
                memset(buffer, 0, BUFFER_SIZE);
                printf("Waiting for your turn.\n");
              }
              else{
                system("clear");
                if(turn){
                  printf("Player %d: %s %s %s Position: %d\n", player, player_token(player), color, "\x1B[0m", position );
                }
                printf("received: [%s]\n", buffer);
                memset(buffer, 0, BUFFER_SIZE);
              }
            }
            else {
              turn++;
              break;
            }
          }
        }
    if (special_case == 1){
      turn++;
      special_case = 0;
    }
    if(prev_turn == turn){
      printf("Server connection lost, Exiting\n");
      exit(0);
    }
    while(check_buffer(buffer)){
      printf("Type 'roll' to roll the die: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
     }
    rolled = rollDice();
    system("clear");
    memset(buffer, 0, BUFFER_SIZE);
    sprintf(buffer, "%d", rolled);
    write(server_socket, buffer, sizeof(buffer));

    memset(buffer, 0, BUFFER_SIZE);
    read(server_socket, buffer, sizeof(buffer));
    player = atoi(buffer);

    memset(buffer, 0, BUFFER_SIZE);
    read(server_socket, buffer, sizeof(buffer));
    strcpy(color, buffer);

    memset(buffer, 0, BUFFER_SIZE);
    read(server_socket, buffer, sizeof(buffer));

    int i =0;
    char *p = strtok (buffer, " ");
    char *array[10];
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, " ");
    }
    int players_ingame = atoi(array[0]);
    int pos[players_ingame];
    for(int e = 0; e < players_ingame; e++){
      pos[e] = 0;
    }
    i = 1;
    while(i <= players_ingame){
      pos[i - 1] = atoi(array[i]);
      i++;
    }
    int win = find_index(pos, players_ingame, 100);
    position = pos[player];

    printf("Player %d: %s %s %s Position: %d\n", player, player_token(player), color, "\x1B[0m", position );
    memset(buffer, 0, BUFFER_SIZE);
    read(server_socket, buffer, sizeof(buffer));
    printf("%s\n", buffer);
    memset(buffer, 0, BUFFER_SIZE);

    print_board(pos, players_ingame);
    if(win == player){
      printf("CONGRATULATIONS! YOU WON THE GAME.\n");
      exit(0);
    }
    prev_turn = turn;
    if(rolled ==6){
      printf("You rolled a 6, roll again.\n");
      memset(buffer, 0, BUFFER_SIZE);
    }
    else printf("Waiting for your turn.\n");
    if(argc == 2){
      memset(buffer, 0, BUFFER_SIZE);
      read(server_socket, buffer, sizeof(buffer));
      if(rolled == 6) special_case = 1;
      memset(buffer, 0, BUFFER_SIZE);
    }
    else{
      memset(buffer, 0, BUFFER_SIZE);
    }

  }
}
