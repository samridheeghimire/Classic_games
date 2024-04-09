#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define ROW 16
#define COL 32

int playerPoints = 0, highscore = 0;
int enemyPoints[4] = {0};
char board[ROW][COL];
char PLAYER = '@';
char ENEMY = 'E';
int PLAYER_X, PLAYER_Y;
int ENEMY_X[4], ENEMY_Y[4];
char username[30];

void setColor(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

void init_board()
{
    int i, j;
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            setColor(6, 0); 
            if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1 ||
                (i == 3 && j >= 3 && j <= 28) ||
                (i == 12 && j >= 3 && j <= 28) ||
                (j == 3 && i >= 3 && i <= 12) ||
                (j == 28 && i >= 3 && i <= 12))
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = '.';
            }
        }
    }
}

void place_player(int x, int y)
{
    PLAYER_X = x;
    PLAYER_Y = y;
    board[PLAYER_X][PLAYER_Y] = PLAYER;
}

void place_enemy(int index, int x, int y)
{
    ENEMY_X[index] = x;
    ENEMY_Y[index] = y;
    board[ENEMY_X[index]][ENEMY_Y[index]] = ENEMY;
}

void render()
{
    system("cls");
    int i, j;
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (board[i][j] == PLAYER)
            {
                setColor(2, 0); // Green text
                printf("%c", board[i][j]);
            }
            else if (board[i][j] == ENEMY)
            {
                setColor(4, 0); // Red text
                printf("%c", board[i][j]);
            }
            else if (board[i][j] == '#')
            {
                setColor(6, 0); // Brown text
                printf("%c", board[i][j]);
            }
            else if (board[i][j] == '.')
            {
                setColor(15, 0); // White text
                printf("%c", board[i][j]);
            }
            else
            {
                setColor(7, 0); // Light gray text
                printf("%c", board[i][j]);
            }
        }
        printf("\n");
    }
    setColor(15, 0); // White text
    printf("Player Score: %d\n", playerPoints);
    printf("last High Score: %d\n", highscore);
}

void movement(char input)
{
    int next_X = PLAYER_X, next_Y = PLAYER_Y;
    switch (input)
    {
    case 'w':
    case 'W':
        next_X--;
        break;
    case 's':
    case 'S':
        next_X++;
        break;
    case 'a':
    case 'A':
        next_Y--;
        break;
    case 'd':
    case 'D':
        next_Y++;
        break;
    default:
        break;
    }

    if (board[next_X][next_Y] != '#' && next_X > 0 && next_X < ROW - 1 && next_Y > 0 && next_Y < COL - 1)
    {
        if (board[next_X][next_Y] == '.')
        {
            playerPoints++;
        }
        board[PLAYER_X][PLAYER_Y] = ' ';
        PLAYER_X = next_X;
        PLAYER_Y = next_Y;
        board[PLAYER_X][PLAYER_Y] = PLAYER;
    }
}
void enemy_movement(int index)
{
    int direction = rand() % 4;
    int enemy_pre_x = ENEMY_X[index], enemy_pre_y = ENEMY_Y[index];

    switch (direction)
    {
    case 0:
        if (board[enemy_pre_x - 1][enemy_pre_y] != '#' && enemy_pre_x - 1 > 0)
            enemy_pre_x--;
        break;
    case 1:
        if (board[enemy_pre_x + 1][enemy_pre_y] != '#' && enemy_pre_x + 1 < ROW - 1)
            enemy_pre_x++;
        break;
    case 2:
        if (board[enemy_pre_x][enemy_pre_y - 1] != '#' && enemy_pre_y - 1 > 0)
            enemy_pre_y--;
        break;
    case 3:
        if (board[enemy_pre_x][enemy_pre_y + 1] != '#' && enemy_pre_y + 1 < COL - 1)
            enemy_pre_y++;
        break;
    default:
        break;
    }

    for (int i = 0; i < 4; i++)
    {
        if (enemy_pre_x == PLAYER_X && enemy_pre_y == PLAYER_Y)
        {
            printf("\n\nGame Over: Player Collided with Enemy\n");
            getch();
            exit(0);
        }
    }

    board[ENEMY_X[index]][ENEMY_Y[index]] = ' ';
    ENEMY_X[index] = enemy_pre_x;
    ENEMY_Y[index] = enemy_pre_y;
    board[ENEMY_X[index]][ENEMY_Y[index]] = ENEMY;
}

int countRemainingDots()
{
    int count = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (board[i][j] == '.')
            {
                count++;
            }
        }
    }
    return count;
}

void checkWinCondition()

{
    int remainingDots = countRemainingDots();
    if (remainingDots == 0)
    {
        int maxPlayerPoints = playerPoints;
        for (int i = 0; i < 4; i++)
        {
            if (enemyPoints[i] > maxPlayerPoints)
            {
                printf("\n\nGame Over: Player Loses\n");
                exit(0);
            }
        }
        printf("\n\n\n\n\nGame Over:Player Wins\n");
        printf("\nPlayer points= %d \n", playerPoints);
        getch();

        exit(0);
    }
}
void pacman()
{
    playerusername();
    srand(time(NULL));
    init_board();
    place_player(10, 20);
    place_enemy(0, 4, 4);
    place_enemy(1, 4, 27);
    place_enemy(2, 12, 4);
    place_enemy(3, 12, 27);

    char username[30], input;
    while (1)
    {
        render();
        input = getch();
        if (input == 'q' || input == 'Q')
        {
            break;
        }

        movement(input);
        for (int i = 0; i < 4; i++)
        {
            enemy_movement(i);
        }
        checkWinCondition();
        Sleep(100);
    }

    // Update highscore if needed

    if (playerPoints > highscore)
    {
        highscore = playerPoints;
        FILE *fptr = fopen("Highscore_pacman.txt", "w");
        if (fptr != NULL)
        {
            fprintf(fptr, "%d\n", highscore);
            fclose(fptr);
        }
    }

    printf("\n\nGame Over\n");
    getch();
}

void playerusername()
{
    int LOGIN_SUCCESS = 0;
    FILE *fptr;
    fptr = fopen("userdata_pacman.txt", "a+");

    if (fptr == NULL)
    {
        printf("Userdata_pacman.txt file cannot be opened. Please try again.");
        exit(0);
    }

    char choice, username[30], password[30];
    int existingUser = 0;

    printf("Are you an existing user? [Y/N/q]: ");
    choice = getche();
    system("cls");

    if (choice == 'Y' || choice == 'y')
    {
        printf("\nEnter your username: ");
        scanf(" %s", username);
        printf("Enter your password: ");
        scanf(" %s", password);

        char temp_username[30], temp_password[30];
        while (fscanf(fptr, "%s %s", temp_username, temp_password) != EOF)
        {
            if (strcmp(username, temp_username) == 0 && strcmp(password, temp_password) == 0)
            {
                existingUser = 1;
                printf("\nWelcome back, %s!\n", username);
                LOGIN_SUCCESS = 1;
                break;
            }
        }
        if (!existingUser)
        {
            printf("\nUsername or password incorrect. Please try again.\n");

            fclose(fptr);
            getch();
            exit(0);
        }
    }

    else if (choice == 'q' || choice == 'Q')
    {
        printf("Exiting...");
        getche();
        exit(0);
    }
    else
    {
        printf("\nEnter your username: ");
        scanf(" %s", username);
        printf("Enter your password: ");
        scanf(" %s", password);
        fprintf(fptr, "%s %s\n", username, password);
        printf("\nNew user registered successfully!\n");
        getch();

        LOGIN_SUCCESS = 1;
    }

    fclose(fptr);
    if (LOGIN_SUCCESS == 1)
    {
        int temp_highscore;

        fptr = fopen("Highscore_pacman.txt", "r+");
        while (fscanf(fptr, "%d", &temp_highscore) != EOF)
        {
            fscanf(fptr, "%d", temp_highscore);
            highscore = temp_highscore;
            break;
        }
    }
    fclose(fptr);
}