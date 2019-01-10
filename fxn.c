#include "header.h"


char * player_token(int player_num){
  if(player_num == 0) return "\x1B[31m";  //red
  else if (player_num == 1) return "\x1B[34m";//blue
  else if (player_num == 2) return "\x1B[32m";//green
  else if (player_num == 3) return "\x1B[33m"; //yellow
}

int check_position(int pos, int location[] , int len){
  int player = -1;
  int size = len;
  int index = 0;
  while(index < size){
    if(pos == location[index]) player = index;
    index++;
  }
  return player;
}

void print_board(int location[], int num){
  int a[10][10];
  int i,j,k;
  for(i=0;i<10;i++)
  printf("+------");
  printf("+\n");
  for(int row = 0; row <10; row++){
    for (int collumn = 0; collumn < 10; collumn++){
      if(row%2 == 1){
        a[row][collumn] = (9 - row)* 10 + collumn + 1;
      }
      else{
        a[row][collumn] = (9 - row) * 10 + 10 - collumn;
      }
    }
  }
  for(i=0;i<10;i++)
  {
      for(j=0;j<10;j++)
      {  int player_here = check_position(a[i][j] , location, num);
         if(player_here != -1){
           if(i == 0 && j == 0){
             printf( "|  ");
             printf("%s" "*" "\x1B[0m", player_token(player_here) );
             printf("   ");
           }
           else if(i == 9){
             if(j == 9){
              printf("|   ");
              printf("%s" "%d " "\x1B[0m" ,player_token(player_here), a[i][j]);
            }
             else {
              printf("|   ");
              printf("%s" "%d  " "\x1B[0m" ,player_token(player_here), a[i][j]);
            }
           }
           else {
             printf("|  ");
             printf("%s" "%d  " "\x1B[0m" ,player_token(player_here),a[i][j]);
           }
         }
         else{
          if(i == 0 && j == 0){
            printf( "|  *   ");
          }
          else if(i == 9){
            if(j == 9) printf("|   %d " ,a[i][j]);
            else printf("|   %d  " ,a[i][j]);
          }
          else printf( "|  %d  " ,a[i][j]);
        }
      }
      printf("|\n");
      for(k=0;k<10;k++)
      printf("+------");

      printf("+\n");
  }
}

// int main(int argc, char **argv){
//   int loc[4];
//   loc[0] = 55;
//   loc[1] = 3;
//   loc[2] = 5;
//   loc[3] = 88;
//   print_board(loc , 4);
//   return 0;
// }
