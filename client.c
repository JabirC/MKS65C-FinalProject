#include "networking.h"
#include "fxn.c"


int check_buffer(char * buffer){
  if (!strcmp(buffer, "roll"))
    return 0;
  else return 1;
}

int rollDice() {
	//return LOWER_LIMIT + rand() % UPPER_LIMIT
    return 1 + rand() % 6;
}

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];
  srand(time(NULL));
  int rolled = 0;
  int player = -1;
  char color[10] = "";

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );
  printf("Waiting for all players to connect.\n");
  read(server_socket, buffer, sizeof(buffer));

  system("clear");
  printf("\n\nWelcome to Snakes and Ladders!\nYour goal is to make it to the 100th box before the other players. Type 'roll' to roll the dice when it is your turn. The number of spaces you move forward depends on the number you roll. If you roll a 6 you get to roll again.\n\n");
  while (1) {
    printf("Waiting for your turn.\n");
    while (read(server_socket, buffer, sizeof(buffer))) {
      if (strcmp(buffer, ACK)) {
        printf("received: [%s]\n", buffer);
      }
      else break;
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
    i = 1;
    while(i <= players_ingame){
      pos[i - 1] = atoi(array[i]);
      i++;
    }
    printf("Player %d: %s %s\n" "\x1B[0m", player, player_token(player), color);
    printf("You rolled a %d moving to %d.\n", rolled, pos[player]);
    print_board(pos, players_ingame);
   }
}
