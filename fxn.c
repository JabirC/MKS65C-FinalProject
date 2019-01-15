#include "header.h"


char * player_token(int player_num){
  if(player_num == 0) return "\x1B[1;34m";  //magenta
  else if (player_num == 1) return "\x1B[31m";//red
  else if (player_num == 2) return "\x1B[32m";//green
  else if (player_num == 3) return "\x1B[33m"; //yellow
}

int check_snakes_vertical(int i, int j){
  if(i == 3 && j == 7) return 1;
  else if(i == 3 && j == 6) return 1;
  else if(i == 4 && j == 6) return 1;
  else if(i == 4 && j == 7) return 1;
  else if(i == 4 && j == 5) return 1;
  else if(i == 5 && j == 6) return 1;
  else if(i == 5 && j == 5) return 1;
  else if(i == 5 && j == 4) return 1;
  else if(i == 5 && j == 4) return 1;
  else if(i == 7 && j == 7) return 1;
  else if(i == 7 && j == 8) return 1;
  else if(i == 7 && j == 9) return 1;
  else if(i == 6 && j == 8) return 1;
  else if(i == 6 && j == 9) return 1;
  else if(i == 5 && j == 8) return 1;
  else if(i == 5 && j == 9) return 1;
  else if(i == 4 && j == 9) return 1;
  else if(i == 6 && j == 1) return 1;
  else if(i == 6 && j == 2) return 1;
  else if(i == 7 && j == 1) return 1;
  else if(i == 7 && j == 2) return 1;
  else if(i == 7 && j == 3) return 1;
  else if(i == 7 && j == 4) return 1;
  else if(i == 8 && j == 4) return 1;
  else if(i == 8 && j == 3) return 1;
  else if(i == 0 && j == 3) return 1;
  else if(i == 0 && j == 4) return 1;
  else if(i == 1 && j == 3) return 1;
  else if(i == 1 && j == 4) return 1;
  else if(i == 2 && j == 2) return 1;
  else if(i == 2 && j == 3) return 1;
  else if(i == 2 && j == 4) return 1;
  else if(i == 3 && j == 2) return 1;
  else if(i == 3 && j == 3) return 1;
  else if(i == 4 && j == 2) return 1;
  else if(i == 4 && j == 3) return 1;
  return 0;
}

int check_snakes_horizontal(int i, int k){
  if(i == 4 && k == 6) return 1;
  else if(i == 3 && k == 5) return 1;
  else if(i == 5 && k == 5) return 1;
  else if(i == 5 && k == 4) return 1;
  else if(i == 4 && k == 4) return 1;
  else if(i == 4 && k == 5) return 1;
  else if(i == 3 && k == 6) return 1;
  else if(i == 2 && k == 6) return 1;
  else if(i == 7 && k == 7) return 1;
  else if(i == 6 && k == 7) return 1;
  else if(i == 6 && k == 8) return 1;
  else if(i == 7 && k == 8) return 1;
  else if(i == 5 && k == 8) return 1;
  else if(i == 3 && k == 9) return 1;
  else if(i == 4 && k == 8) return 1;
  else if(i == 4 && k == 9) return 1;
  else if(i == 5 && k == 9) return 1;
  else if(i == 5 && k == 1) return 1;
  else if(i == 6 && k == 1) return 1;
  else if(i == 6 && k == 2) return 1;
  else if(i == 6 && k == 3) return 1;
  else if(i == 7 && k == 1) return 1;
  else if(i == 7 && k == 2) return 1;
  else if(i == 7 && k == 3) return 1;
  else if(i == 8 && k == 3) return 1;
  else if(i == 0 && k == 3) return 1;
  else if(i == 1 && k == 3) return 1;
  else if(i == 2 && k == 3) return 1;
  else if(i == 1 && k == 2) return 1;
  else if(i == 2 && k == 2) return 1;
  else if(i == 3 && k == 2) return 1;
  else if(i == 4 && k == 2) return 1;
  return 0;
}

int check_partial_horizontal(int i, int k){
  if(i == 0 && k == 4) return 1;
  else if(i == 1 && k == 4) return 1;
  else if(i == 4 && k == 3) return 1;
  else if(i == 5 && k == 2) return 1;
  else if(i == 6 && k == 4) return 1;
  else if(i == 7 && k == 4) return 1;
  else if(i == 8 && k == 4) return 1;
  else if(i == 5 && k == 6) return 1;
  else if(i == 4 && k == 7) return 1;
  else if(i == 3 && k == 7) return 1;
  else if(i == 6 && k == 9) return 1;
  else if(i == 7 && k == 9) return 1;
  else if(i == 2 && k == 7) return 1;
  return 0;
}
int check_partial_Ladders(int i, int k){
  if(i == 3 && k == 1) return 1;
  else if(i == 4 && k == 1) return 1;
  else if(i == 7 && k == 6) return 1;
  else if(i == 8 && k == 7) return 1;
  else if(i == 6 && k == 5) return 1;
  return 0;
}

int check_vertical_ends(int i){
  if(i == 5) return 1;
  else if(i == 4) return 1;
  return 0;
}

int check_ladders_horizontal(int i , int k){
  if(i ==8 && k == 6)return 1;
  else if(i ==8 && k == 5)return 1;
  else if(i ==7 && k == 5)return 1;
  else if(i ==7 && k == 4)return 1;
  else if(i ==6 && k == 4)return 1;
  else if(i ==2 && k == 8)return 1;
  else if(i ==1 && k == 8)return 1;
  else if(i ==1 && k == 9)return 1;
  else if(i ==3 && k == 0)return 1;
  else if(i ==4 && k == 0)return 1;
  else if(i ==3 && k == 3)return 1;
  else if(i ==3 && k == 4)return 1;
  else if(i ==2 && k == 4)return 1;
  else if(i ==2 && k == 5)return 1;
  else if(i ==1 && k == 5)return 1;
  else if(i ==1 && k == 6)return 1;
  return 0;
}
int check_ladders_vertical(int i , int j){
  if(i ==3 && j == 8)return 1;
  else if(i ==8 && j == 6)return 1;
  else if(i ==8 && j == 5)return 1;
  else if(i ==7 && j == 5)return 1;
  else if(i ==2 && j == 8)return 1;
  else if(i ==2 && j == 9)return 1;
  else if(i ==1 && j == 9)return 1;
  else if(i ==5 && j == 0)return 1;
  else if(i ==5 && j == 1)return 1;
  else if(i ==4 && j == 0)return 1;
  else if(i ==4 && j == 1)return 1;
  else if(i ==3 && j == 0)return 1;
  else if(i ==3 && j == 1)return 1;
  else if(i == 4 && j == 4) return 1;
  else if(i == 3 && j == 4) return 1;
  else if(i == 3 && j == 5) return 1;
  else if(i == 2 && j == 5) return 1;
  else if(i == 2 && j == 6) return 1;
  else if(i == 1 && j == 6) return 1;
  return 0;
}

int check_both(int i, int k){
  if(i == 2 && k == 7) return 1;
  else if(i == 7 && k == 4) return 1;
  else if(i == 2 && k == 4) return 1;
  else if(i == 3 && k == 3) return 1;
  return 0;
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

int find_index(int arr[] , int arr_len, int val){
    int ret = -1;
    int index = 0;
    while(index < arr_len){
      if (arr[index] == val){
        ret = index;
        break;
      }
      index++;
    }
    return ret;
}

int rollDice() {
	//return LOWER_LIMIT + rand() % UPPER_LIMIT
    int num = 1 + abs(rand()) % 6;
    if(num < 0 || num > 6) return 1 + num % 6;
    else return num;

}

void print_board(int location[], int num){
  int a[10][10];
  int i,j,k;
  for(i=0;i<10;i++){
    if(i == 3)printf("\x1B[1;31m" "+------" "\x1B[0m");
    else if(i == 4) printf("\x1B[1;31m" "+%s------" , "\x1B[0m");
    else printf("+------");
  }
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
              printf("|  ");
              printf("%s" "%d  " "\x1B[0m" ,player_token(player_here), a[i][j]);
             }
             else if(j == 6){
              printf("\x1B[34m""|   ""\x1B[0m");
              printf("%s" "%d  " "\x1B[0m" ,player_token(player_here), a[i][j]);
             }
             else {
              printf("|   ");
              printf("%s" "%d  " "\x1B[0m" ,player_token(player_here), a[i][j]);
            }
           }
           else if(check_snakes_vertical(i, j)){
             printf("\x1B[1;31m""|  " "\x1B[0m");
             printf("%s" "%d  " "\x1B[0m" ,player_token(player_here),a[i][j]);
           }
           else if(check_ladders_vertical(i , j)){
             printf("\x1B[34m""|  " "\x1B[0m");
             printf("%s" "%d  " "\x1B[0m" ,player_token(player_here),a[i][j]);
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
            if(j == 9) printf("|  %d  " ,a[i][j]);
            else if(j == 6){
             printf("\x1B[34m""|%s   %d  " ,"\x1B[0m",a[i][j]);
            }
            else printf("|   %d  " ,a[i][j]);
          }
          else if(check_snakes_vertical(i,j)) printf( "%s|%s  %d  " ,"\x1B[1;31m","\x1B[0m", a[i][j]);
          else if(check_ladders_vertical(i , j)){
            printf( "%s|%s  %d  " ,"\x1B[34m","\x1B[0m", a[i][j]);
          }
          else printf( "|  %d  " ,a[i][j]);
        }
      }
      if(check_vertical_ends(i)){
         printf("\x1B[1;31m" "|\n" "\x1B[0m");
      }
      else printf("|\n");
      for(k=0;k<10;k++){
        if(check_both(i, k)){
          printf("%s+%s%s------%s", "\x1B[1;31m", "\x1B[0m", "\x1B[34m", "\x1B[0m");
        }
        else if(check_snakes_horizontal(i, k)){
          printf("\x1B[1;31m" "+------" "\x1B[0m");
        }
        else if(check_partial_horizontal(i, k)){
           printf("%s+%s------", "\x1B[1;31m", "\x1B[0m");
        }
        else if(check_ladders_horizontal(i, k)){
           printf("%s+------%s", "\x1B[34m", "\x1B[0m");
        }
        else if(check_partial_Ladders(i, k)){
           printf("%s+%s------", "\x1B[34m", "\x1B[0m");
        }
        else printf("+------");
      }
      if(i == 3 || i == 4 || i == 5)printf("\x1B[1;31m" "+\n" "\x1B[0m");
      else printf("+\n");
  }
}
