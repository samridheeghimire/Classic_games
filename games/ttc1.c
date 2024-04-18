#include<stdio.h>
#include<conio.h>
void printBoard();
int checkWin();
void system();
char board[] = {'0','1','2','3','4','5','6','7','8','9'};

void main()
{
    char p1[30], p2[30];
    printf("Enter first player name\n");
    scanf("%s",p1);
    printf("Enter second player name\n");
    scanf("%s",p2);
  int player=1,input,status=-1,i;
  char mark;
  printBoard();

while(status==-1)
{
 player =(player%2==0)?2:1  ;
    if (player==1)
    {
        printf("Enter a number for player 1 (%s)\n", p1);

    }
    else
    {

        printf("Enter a number for player 2 (%s)\n", p2);
    }
    scanf("%d",&input);
    char mark= (player==1)? 'X' : 'O';
    if(input<1 || input>9 || board[input] == 'X' || board[input] == 'O')
    {
    
        printf("Invalid Input");
    }
    board[input]= mark;
    printBoard();
    int result=checkWin();
        if(result==1)
        {
            printf("Congratulations, player %d won!\n",player);
            break;
        }
       else if(result==0)
       {
    
          printf("DRAW\n");
          break;
       }
   
    player++;
}    
}
void printBoard()

{
    system("cls");
    printf("\n~~~~ WELCOME TO TIC TAC TOE ~~~~\n");
    printf("\n\n");
    printf("          |         |        \n");
    printf("    %c     |   %c     |   %c   \n", board[1] ,board[2] ,board[3] ); 
    printf(" _________|_________|________\n");
    printf("          |         |        \n");
    printf("    %c     |   %c     |   %c  \n", board[4] ,board[5] ,board[6]);
    printf(" _________|_________|________\n");
    printf("          |         |        \n");
    printf("    %c     |   %c     |   %c  \n", board[7],board[8],board[9]);
    printf("          |         |        \n");
    printf("\n\n");
}




int checkWin()
{
    if(board[1]==board[2] && board[2]==board[3])
    {
        return 1;
    }
    if(board[4]==board[5] && board[5]==board[6])
    {
        return 1;
    }
    if(board[7]==board[8] && board[8]==board[9])
    {
        return 1;
    }
    if(board[1]==board[4] && board[4]==board[7])
    {
        return 1;
    }
    if(board[2]==board[5] && board[5]==board[8])
    {
        return 1;
    }
    if(board[3]==board[6] && board[6]==board[9])
    {
        return 1;
    }
    if(board[1]==board[5] && board[5]==board[9])
    {
        return 1;
    }
    if(board[3]==board[5] && board[5]==board[7])
    {
        return 1;
    }
    int count = 0;
    for(int i=1; i<=9; i++)
    {
        if(board[i]=='X' || board[i]=='O')
        {
           count++;
        }  
    }
    if(count==9)
       return 0;

    return -1;
}
