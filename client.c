#include "networking.h"
#include "fxn.c"


int check_buffer(char * buffer){
  if (!strcmp(buffer, "roll"))
    return 0;
  else return 1;
}


int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];
  srand(time(NULL));
  int rolled = 0;
  int player = -1;
  char color[10] = "";
  int turn = 0;
  int position= 0;

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );
  printf("Waiting for all players to connect.\n");
  read(server_socket, buffer, sizeof(buffer));

  system("clear");
  printf("\nWelcome to Snakes and Ladders!\nYour goal is to make it to the 100th box before the other players. Type 'roll' to roll the dice when it is your turn. The number of spaces you move forward depends on the number you roll. If you roll a 6 you get to roll again.\n\n");
  while (1) {
    printf("Waiting for your turn.\n");
    while (read(server_socket, buffer, sizeof(buffer))) {
      if (strcmp(buffer, ACK)) {
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
          memset(buffer, 0, BUFFER_SIZE);
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
    position = pos[player];
    printf("Player %d: %s %s %s Position: %d\n", player, player_token(player), color, "\x1B[0m", position );
    printf("You rolled a %d moving to %d.\n", rolled, pos[player]);
    print_board(pos, players_ingame);
   }
}
