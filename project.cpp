#define _CRT_SECURE_NO_WARNINGS
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define LINE printf("+---+---+---+\n")

void intro()
{
    time_t t;
    time(&t);

    time_t s, val = 1;
    struct tm* current_time;

    s = time(NULL);
    printf("\t\t\t+---------------------------------------------------------------+\n");
    printf("\n\t\t\t\t\t%s", ctime(&t));
    printf("\n\t\t\t\t\t |+| Welcome To The Menu |+|\t\t\t\t\t \n");
    current_time = localtime(&s);
    if (current_time->tm_hour >= 5 && current_time->tm_hour < 12)
        printf("\n\t\t\t\t\t\tGOOD MORNING\n");
    else if (current_time->tm_hour >= 12 && current_time->tm_hour < 17)
        printf("\n\t\t\t\t\t\tGOOD AFTERNOON\n");
    else if (current_time->tm_hour >= 17 && current_time->tm_hour < 21)
        printf("\n\t\t\t\t\t\tGOOD EVENING\n");
    else
        printf("\n\t\t\t\t\t\tGOOD NIGHT\n");
    printf("\t\t\t+---------------------------------------------------------------+\n");
}

int chooseGame()
{
    int game_number;

    printf("\t\t\t+--Press 1 for play TicTacToe with your friend.--+");
    printf("\n\t\t\t+--Press 2 for play TicTacToe with computer.-- +");
    printf("\n\t\t\t+--Press 3 for play with Sheldon Cooper(not TicTacToe).-- +");
    printf("\n\t\t\t+--Press 4 for find out name compatibility(not true).-- +");
    printf("\n\t\t\t+--Press 5 for play hangman.-- +");
    printf("\n\t\t\t+--Press 6 for play Dice Game.-- +");
    printf("\n\n\t\t\t+--Your choice : ");
    scanf("%d", &game_number);
    char temp;
    scanf("%c", &temp);
    return game_number;
}

void nextStep(int* play, int* game)
{
    int chose;
    printf("Do you want to continue?\nPress 1 to play again\nPress 2 to exit\nPress 3 to change game\n\nYour choice:");
    scanf("%d", &chose);
    switch (chose)
    {
    case 2:
        *play = chose;
        break;
    case 3:
        *game = 0;
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void writeYourName(char player[])
{

    printf("Write your name: ");
    for (int i = 0; i < 20; i++)
    {
        scanf("%c", &player[i]);
        if (player[i] == '\n')
        {
            player[i] = '\0';
            break;
        }
    }
}

void ticTacToe(char board[3][3])
{
    system("cls");
    printf("\n\n");
    LINE;
    printf("| %c | %c | %c |\n", board[0][0], board[0][1], board[0][2]);
    LINE;
    printf("| %c | %c | %c |\n", board[1][0], board[1][1], board[1][2]);
    LINE;
    printf("| %c | %c | %c |\n", board[2][0], board[2][1], board[2][2]);
    LINE;
}

int checkForAWinner(char board[3][3], int player)
{
    int winner = 0;
    if ((board[0][0] == board[1][1] &&              /*check for a winner*/
        board[0][0] == board[2][2]) ||
        (board[0][2] == board[1][1] &&
            board[0][2] == board[2][0]))
        winner = player;
    else
    {
        /*check row and col for winner*/
        for (int line = 0; line < 2; line++) {
            if ((board[line][0] == board[line][1] &&
                board[line][0] == board[line][2]) ||
                (board[0][line] == board[1][line] &&
                    board[0][line] == board[2][line]))
                winner = player;
        }
    }
    return winner;
}

void declareWinner(int winner, char player1[], char player2[])
{
    if (winner == 0) {
        printf("\nHow boring, it is a draw\n");
    }
    else {
        printf("\nPlayer %s, you are the winner\n\n", (winner == 1) ? player1 : player2);
    }
}

void playWithFriend()
{
    int turn;
    int player, winner = 0, choice;
    int row, col;

    char player1[20], player2[20];
    writeYourName(player1);
    writeYourName(player2);

    char board[3][3] = { {'1', '2', '3'},
                         {'4', '5', '6'},
                         {'7', '8', '9'} };

    /*draw*/
    for (turn = 0; turn < 9 && winner == 0; turn++) {
        ticTacToe(board);

        player = (turn % 2) + 1;

        /*player selection*/
        do {
            printf("\nPlay %s, enter your go %c: ",
                (player == 1) ? player1 : player2, (player == 1) ? 'X' : '0');
            scanf("%d", &choice);

            row = --choice / 3;
            col = choice % 3;

        } while (choice < 0 || choice > 9 || board[row][col] > '9');

        /*insert pleyer symbol*/
        board[row][col] = (player == 1) ? 'X' : '0';
        winner = checkForAWinner(board, player);
    }

    ticTacToe(board);
    declareWinner(winner, player1, player2);
}

char playerChosenSymbol()
{
    char res = ' ', select = 0;
    while (select == 0)
    {
        printf("Choose for which character you want to play X or 0: ");
        scanf("%c", &res);
        switch (res)
        {
        case 'X':
            select = 1;
            break;
        case 'x':
            res = 'X';
            select = 1;
            break;
        case '0':
            res = 'O';
            select = 1;
            break;
        case 'O':
            select = 1;
            break;
        case 'o':
            res = 'O';
            select = 1;
            break;
        }
    }
    return res;
}

int pcChose(char board[3][3], char playerSymbol, char PCSymbol)
{
    int move = 0, row, col, search = 0;

    do
    {
        move = (rand() % 9) + 1;
        row = --move / 3;
        col = move % 3;
        if (board[row][col] != 'X' || board[row][col] != 'O')
        {
            search = 1;
        }
    } while (search == 0);

    return move;
}

void playWithComp()
{
    int turn;
    int player, winner = 0, choice = 0;
    int row, col;
    char PCSymbol;

    char board[3][3] = { {'1', '2', '3'},
                         {'4', '5', '6'},
                         {'7', '8', '9'} };

    char player1[20], player2[3] = "PC";
    writeYourName(player1);

    char playerSymbol = playerChosenSymbol();
    if (playerSymbol == 'X')
        PCSymbol = 'O';
    else if (playerSymbol == 'O')
        PCSymbol = 'X';

    for (turn = 0; turn < 9 && winner == 0; turn++) {
        ticTacToe(board);

        player = (turn % 2) + 1;

        do {
            switch (player)
            {
            case 1:
                printf("\nPlay %s, enter your go: ",
                    player1);
                scanf("%d", &choice);
                break;
            case 2:
                choice = pcChose(board, playerSymbol, PCSymbol);
                break;
            }

            row = --choice / 3;
            col = choice % 3;

        } while (choice < 0 || choice > 9 || board[row][col] > '9');

        switch (player)
        {
        case 1:
            board[row][col] = playerSymbol;
            break;
        case 2:
            board[row][col] = PCSymbol;
            break;
        }

        winner = checkForAWinner(board, player);
    }

    ticTacToe(board);
    declareWinner(winner, player1, player2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void roundPlay(int* win)
{
    time_t t;
    int sec;
    struct tm* t_m;

    int  ent = 0, comp;

    while (!(ent == 1 || ent == 2 || ent == 3 || ent == 4 || ent == 5))
    {
        printf("\n\nWhat are you choosing?\n Rock - 1, Scissors - 2, Paper - 3, Lizard - 4, Spock - 5\n");
        scanf("%d", &ent);
    }

    printf("\nYou choosed\n");
    switch (ent)
    {
    case 1: 
        printf("Rock\n");   
        break;
    case 2: 
        printf("Scissors\n"); 
        break;
    case 3: 
        printf("Paper\n");  
        break;
    case 4: 
        printf("Lizard\n"); 
        break;
    case 5: 
        printf("Spock\n"); 
        break;
    }

    t = time(NULL);
    t_m = localtime(&t);
    sec = t_m->tm_sec;
    comp = (sec * rand()) % 5 + 1;

    printf("\n Computer chose\n");
    switch (comp)
    {
    case 1: 
        printf("Rock\n"); 
        break;
    case 2: 
        printf("Scissors\n"); 
        break;
    case 3: 
        printf("Paper\n"); 
        break;
    case 4: 
        printf("Lizard\n"); 
        break;
    case 5: 
        printf("Spock\n"); 
        break;
    }

    if (comp == ent) 
        *win = 0;
    //for human
    if (ent == 1 && comp == 2) 
        *win = 1;//1 win if
    if (ent == 1 && comp == 4)
        *win = 1;
    if (ent == 2 && comp == 3) 
        *win = 1;//2 win if
    if (ent == 2 && comp == 4) 
        *win = 1;
    if (ent == 3 && comp == 1)
        *win = 1;//3 win if
    if (ent == 3 && comp == 5)
        *win = 1;
    if (ent == 4 && comp == 5)
        *win = 1;//4 win if
    if (ent == 4 && comp == 3)
        *win = 1;
    if (ent == 5 && comp == 2)
        *win = 1; //5 win if
    if (ent == 5 && comp == 1)
        *win = 1;
    //for computer 
    if (ent == 1 && comp == 3)
        *win = 2;//1 win if
    if (ent == 1 && comp == 5)
        *win = 2;
    if (ent == 2 && comp == 1)
        *win = 2;//2 win if
    if (ent == 2 && comp == 5)
        *win = 2;
    if (ent == 3 && comp == 2)
        *win = 2;//3 win for
    if (ent == 3 && comp == 4)
        *win = 2;
    if (ent == 4 && comp == 1)
        *win = 2;//4 win if
    if (ent == 4 && comp == 2)
        *win = 2;
    if (ent == 5 && comp == 4)
        *win = 2;//5 win if
    if (ent == 5 && comp == 3)
        *win = 2;

    switch (*win)
    {
    case 0:
        printf("\nDraw\n");
        break;
    case 1:
        printf("\nyou won\n");
        break;
    case 2:
        printf("\nWon the computer\n");
        break;
    }
}

void playRSPLS()
{
    system("cls");

    printf("Hello. My name is Sheldon Cooper.\n\nWelcome to the rock-paper-scissors-lizard-Spock.\n\nThe rules are very simple: Scissors decapitate Scissors cuts paper, paper covers rock, rock crushes lizard, lizard poisons Spock, Spock smashes scissors, scissors decapitates lizard, lizard eats paper, paper disproves Spock, Spock valoseCountizes rock, and as it always has, rock crushes scissors.\n");

    int k = 0, winCount = 0, loseCount = 0, draw = 0, win = 0;
    int play = 1;

    while (play == 1)
    {
        roundPlay(&win);

        k++;
        if (win == 0) 
            draw = draw + 1;
        if (win == 1) 
            winCount = winCount + 1;
        if (win == 2) 
            loseCount = loseCount + 1;

        printf("\n Shall we play again?\n Yes - 1 No - 2\n");
        scanf("%d", &play);
    }

    printf("\n\n Total Games %d\n", k);
    printf(" victories %d\n", winCount);
    printf(" defeats %d\n", loseCount);
    printf(" The draw was %d\n", draw);
    _getch();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void abceda(char abcd[2][82])
{
    int n = 1;
    for (int j = 0; j < 82; j++)
    {
        abcd[1][j] = n + '0';
        j++;
        abcd[1][j] = n + '0';
        n++;
    }
}

int findLetter(char* name, char abcd[2][82])
{

    int find = 0, n = 0;

    while (name[n] != '\0')
    {
        for (int j = 0; j < 82; j++)
        {
            if (name[n] == abcd[0][j])
            {
                find += abcd[1][j] - '0';
                break;
            }
        }
        n++;
    }

    return find;
}

int howManyLetter(int sumName)
{
    int count = 0;
    while (sumName != 0)    
    {
        sumName /= 10;
        count++;
    }
    return count;
}

int countName(int sumName)
{
    int total = 0, count = howManyLetter(sumName), sum = sumName;
    do
    {
        int* arr = (int*)malloc(count * sizeof(int));

        for (int i = 0; i < count; i++)
        {
            arr[i] = sum % 10;   
            sum /= 10;    
        }
        sum = 0;
        for (int i = 0; i < count; i++)
            sum += arr[i];

        free(arr);
        count = howManyLetter(sum);
    } while (count > 1);

    if (count == 1)
        total = sum;

    return total;
}

void wrUName()
{
    system("cls");
    char name_1[20], name_2[20];
    char abcd[2][82] =
    {
        'A', 'a', 'Á', 'á', 'B', 'b', 'C', 'c', 'Č', 'č', 'D', 'd', 'Ď', 'ď', 'E', 'e', 'É', 'é', 'Ě', 'ě', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'Í', 'í', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'Ň', 'ň', 'O', 'o', 'Ó', 'ó', 'P', 'p', 'Q', 'q', 'R', 'r', 'Ř', 'ř', 'S', 's', 'Š', 'š', 'T', 't', 'Ť', 'ť', 'U', 'u', 'Ú', 'ú', 'Ů', 'ů', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Ý', 'ý', 'Z', 'z', 'Ž', 'ž',
    };
    int firstName, secondName, total;

    printf("\nEnter first name (czech language): ");
    scanf("%s", &name_1);
    printf("\nEnter second name (czech language): ");
    scanf("%s", &name_2);

    printf("\n%s, %s", name_1, name_2);
    abceda(abcd);
    firstName = findLetter(name_1, abcd);
    secondName = findLetter(name_2, abcd);
    printf("\n%s - %d, %s - %d\n", name_1, firstName, name_2, secondName);

    total = countName(firstName + secondName);
    printf("\ntotal=%d\n", total);
    switch (total)
    {
    case 1:
        printf("1 - the union of leaders, where everyone will pull the blanket over themselves. Learn how to compromise\n");
        break;
    case 2:
        printf("2 - such relationships are based more on friendship and respect\n");
        break;
    case 3:
        printf("3 - a guarantee of harmony, which will last until one of the partners takes over in a relationship\n");
        break;
    case 4:
        printf("4 - a calm couple without pretensions to each other.\n");
        break;
    case 5:
        printf("5 - passion, jealousy, feelings that are suitable for love, but not very good for work.\n");
        break;
    case 6:
        printf("6 - trusting, long-term relationships.\n");
        break;
    case 7:
        printf("7 - the condrawtion will be strong as long as the leader takes care of his ward, and the follower respects and appreciates his leader.\n");
        break;
    case 8:
        printf("8 - one is drawn to the other, but together it's sickening, and apart - it's completely sad. The couple then converges, then diverges, until they solve their problems.\n");
        break;
    case 9:
        printf("9 - a lot of common interests, ideas, views of the world. Perhaps the perfect unity in many ways.\n");
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int readFile(char word[20], char hideWord[20])
{
    int sizeFile = 0;
    FILE* file;

    if (!(file = fopen("dictionary.txt", "r")))
        return 0;
    else
    {
        while (fscanf(file, "%s", word) != EOF) 
            sizeFile++;
        fseek(file, 0, SEEK_SET); 
        int randString = rand() % sizeFile;
        for (int i = 0; i < randString; i++)
            fscanf(file, "%s", word);
        fclose(file);

        int i = 0;
        while (word[i] != '\0')
        {
            hideWord[i] = '_';
            i++;
        }
        hideWord[i] = '\0';
    }

    return sizeFile;
}

void scaffoldPrint(int n, char hideWord[])
{
    system("cls");
    switch (n)
    {
    case 0:
        printf("       |\n       |\n       |\n       |\n       |  ");
        break;
    case 1:
        printf("       |\n       |\n       |\n       |\n___    |  ");
        break;
    case 2:
        printf("       |\n |     |\n |     |\n |     |\n_|_    |  ");
        break;
    case 3:
        printf("  ____ |\n |     |\n |     |\n |     |\n_|_    |  ");
        break;
    case 4:
        printf("  ____ |\n |   | |\n |   O |\n |     |\n_|_    |  ");
        break;
    case 5:
        printf("  ____ |\n |   | |\n |   O |\n |   | |\n_|_    |  ");
        break;
    case 6:
        printf("  ____ |\n |   | |\n |   O |\n |  /| |\n_|_    |  ");
        break;
    case 7:
        printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_    |  ");
        break;
    case 8:
        printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_ /  |  ");
        break;
    case 9:
        printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_ / \\|  ");
        break;
    }
    printf("\n----------\n%s\n\n", hideWord);
}

int countGuessedLetters(int count, int hideCount, int scaffold)
{
    int check = 0;

    if (scaffold != 9)
    {
        if (count == hideCount)
            check = 2;
    }
    else
        check = 3;

    return check;
}

void finishGame(int flag, char word[])
{
    switch (flag)
    {
    case 2:
        printf("You WIN!!!\n\n");
        break;
    case 3:
        printf("You LOSE!!!\nCorrect answer: %s\n\n", word);
        break;
    }
}

void hangman()
{
    char word[20], hideWord[20], userLetter[20];
    int scaffold = 0, size = readFile(word, hideWord);
    if (size == 0)
    {
        printf("Error!!! Dictionary file not found");
        _getch();
    }
    else
    {
        int flag = 0, count = 0;
        while (scaffold <= 9)
        {
            flag = countGuessedLetters(count, strlen(hideWord), scaffold);
            if (flag == 0)
            {
                flag = 0;
                scaffoldPrint(scaffold, hideWord);
                printf("Write your letter: ");
                scanf("%s", userLetter);
                for (int i = 0; i < strlen(userLetter); i++)
                {
                    for (int j = 0; j < strlen(word); j++)
                    {
                        if (word[j] == userLetter[i])
                        {
                            hideWord[j] = userLetter[i];
                            flag = 1;
                            count++;
                        }
                    }
                }
                if (flag == 0)
                    scaffold++;
            }
            else
                break;
        }
        scaffoldPrint(scaffold, hideWord);
        finishGame(flag, word);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void nullDise(int** playersDesk)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 6; i++)
            playersDesk[j][i] = 0;
}

void diceRoll(int** playersDesk, int countDice[3][1])
{
    srand(time(NULL));

    for (int j = 0; j < 3; j++)
        for (int i = 0; i < countDice[j][0]; i++)
            playersDesk[j][i] = rand() % 6 + 1;
}

void dicePlayers(int** playersDesk)
{
    printf("\n\n-------------------");
    for (int j = 0; j < 3; j++)
    {
        if (j != 0)
            printf("\nPC %d  -  ", j);
        else
            printf("\nYour  -  ");

        for (int i = 0; i < 5; i++)
            printf("%d ", playersDesk[j][i]);
    }
    printf("\n-------------------\n");
}

void diceHuman(int** playersDesk)
{
    printf("\n-------------------");
    printf("\nYour  -  ");

    for (int i = 0; i < 5; i++)
        printf("%d ", playersDesk[0][i]);

    printf("\n-------------------\n");
}

void yourBid(int* lastBid)
{
    int* oldBid = (int*)calloc(2, sizeof(int));
    oldBid[0] = lastBid[0];
    oldBid[1] = lastBid[1];
    char bid[4];
    int repeat = 0;

    do
    {
        printf("Your bid (number-dice number): ");
        scanf("%s", bid);
        bid[3] = '\0';
        lastBid[0] = bid[0] - '0';
        lastBid[1] = bid[2] - '0';

        if (lastBid[0] >= oldBid[0])
            repeat = 1;
        else
            repeat = 0;
        if (lastBid[1] >= 1)
            repeat = 1;
        else
            repeat = 0;
        if (lastBid[1] <= 6)
            repeat = 1;
        else
            repeat = 0;

    } while (repeat == 0);

    oldBid = nullptr;
}

int whatHave(int** pl, int a, int who)
{
    int count = 0, i = 0;

    for (int i = 0; i < 5; i++)
        if (pl[who][i] == a)
            count++;

    return count;
}

int doubt(int* lastBid, int** playersDesk, int lastLoser)
{
    int newRound = 0, max = 0;
    dicePlayers(playersDesk);

    int** what = (int**)calloc(3, sizeof(int*));
    for (int i = 0; i < 3; i++)
        what[i] = (int*)calloc(6, sizeof(int));

    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 5; i++)
            what[j][playersDesk[j][i] - 1] = whatHave(playersDesk, playersDesk[j][i], j);

    for (int j = 0; j < 3; j++)
    {
        max += what[j][0];
        max += what[j][lastBid[1] - 1];
    }

    if (lastBid[0] > max)
        newRound = 1;
    else
        newRound = 2;

    free(what);
    return newRound;
}

void nowBid(int* lastBid, int who)
{
    if (who == 0)
        printf("\nPlayer bid %d - %d", lastBid[0], lastBid[1]);
    else
        printf("\nPC %d bid %d - %d", who, lastBid[0], lastBid[1]);
}

int actionChoice()
{
    int choice = 0;

    while (choice == 0 && choice < 2)
    {
        printf("\n\nChoise the action:\n1:Bid\n2:Doubt\n\nYour action: ");
        int action;
        scanf("%d", &action);

        switch (action)
        {
        case 1:
            choice = action;
            break;
        case 2:
            choice = action;
            break;
        }
    }

    return choice;
}

void playerAction(int* lastBid, int who, int* newRound, int** playersDesk, int lastLoser)
{
    switch (actionChoice())
    {
    case 1:
        yourBid(lastBid);
        nowBid(lastBid, who);
        break;
    case 2:
        *newRound = doubt(lastBid, playersDesk, lastLoser);
        break;
    }
}

void pcAction(int* lastBid, int who, int** playersDesk, int* newRound, int lastLoser)
{
    if (lastBid[0] > 8)
        *newRound = doubt(lastBid, playersDesk, lastLoser);
    else
    {
        int* what = (int*)calloc(7, sizeof(int*));
        int max[2] = { 0,0 };

        for (int i = 0; i < 5; i++)
            what[playersDesk[who][i] - 1] = whatHave(playersDesk, playersDesk[who][i], who);

        for (int i = 1; i < 6; i++)
            if (max[1] < what[i])
            {
                max[1] = what[i];
                max[0] = i;
            }

        lastBid[0] = what[0] + max[1] + lastBid[0];
        lastBid[1] = max[0] + 1;
        nowBid(lastBid, who);
        what = nullptr;
    }
}

int checkDise(int countDice[3][1])
{
    int check = 0;

    for (int j = 0; j < 3; j++)
    {
        int temp = 0;
        for (int i = 0; i < 3; i++)
            if (countDice[i][0] == 0)
            {
                temp = 1;
                break;
            }
            else
                temp = 0;
        check += temp;
    }

    return check;
}

void whoLose(int who)
{
    if (who == 0)
        printf("\nYou lose\n");
    else
        printf("\nPC %d lose\n", who);
}

void diceRules()
{
    system("cls");

    FILE* file;
    char c;

    file = fopen("DiceRules.txt", "r");

    while ((c = fgetc(file)) != EOF)
        printf("%c", c);
    fclose(file);
    printf("\n\nPress any key when you are ready to start the game");

    _getch();
    system("cls");
}

void declareWinner(int countDice[3][1])
{
    system("cls");
    for (int i = 0; i < 3; i++)
        if (countDice[i][0] != 0)
        {
            if (i == 0)
                printf("\n\n!!! You WIN !!!\n\n");
            else
                printf("\n\nYou Lose\nPC %d WIN\n\n", i);
        }
}

void diceGame()
{
    char* ans = (char*)calloc(3, sizeof(char));
    printf("\nDo you want to read the rules? (yes/no): ");
    scanf("%s", ans);
    if (strcmp(ans, "yes") == 0)
        diceRules();
    ans = nullptr;

    int play = 1, lastLoser = 1, lastMove, newRound = 0;

    int** playersDesk = (int**)calloc(3, sizeof(int*));
    for (int i = 0; i < 3; i++)
        playersDesk[i] = (int*)calloc(5, sizeof(int));

    int* lastBid = (int*)calloc(2, sizeof(int*));
    int countDice[3][1];
    countDice[0][0] = 5;
    countDice[1][0] = 5;
    countDice[2][0] = 5;

    while (play == 1)
    {
        lastMove = lastLoser;
        nullDise(playersDesk);
        diceRoll(playersDesk, countDice);
        if (countDice[0][0] == 0)
        {
            play = 0;
            newRound = 1;
        }
        else
            diceHuman(playersDesk);

        while (newRound == 0)
        {
            if (lastMove == 0 && countDice[lastMove][0] != 0)
                playerAction(lastBid, lastMove, &newRound, playersDesk, lastLoser);
            else
                if (countDice[lastMove][0] != 0)
                    pcAction(lastBid, lastMove, playersDesk, &newRound, lastLoser);

            if (newRound == 1)
            {
                countDice[lastMove][0]--;
                lastLoser = lastMove;
                whoLose(lastLoser);
            }
            else if (newRound == 2)
            {
                if (lastMove == 0)
                    lastMove = 2;
                else
                    lastMove--;

                countDice[lastMove][0]--;
                lastLoser = lastMove;
                whoLose(lastLoser);
            }

            if (lastMove == 2)
                lastMove = 0;
            else
                lastMove++;
        }

        int check = checkDise(countDice);
        if (check == 2)
            play = 0;
        else
        {
            newRound = 0;
            lastBid[0] = 0;
            lastBid[1] = 0;
        }
    }

    declareWinner(countDice);
    printf("---------\nGAME OVER");

    free(playersDesk);
    free(lastBid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    intro();
    int play = 0, game = 0;
    while (play == 0)
    {
        if (game == 0)
            game = chooseGame();
        switch (game)
        {
        case 1:
            playWithFriend();
            nextStep(&play, &game);
            break;
        case 2:
            playWithComp();
            nextStep(&play, &game);
            break;
        case 3:
            playRSPLS();
            nextStep(&play, &game);
            break;
        case 4:
            system("chcp 1250");
            wrUName();
            nextStep(&play, &game);
            break;
        case 5:
            hangman();
            nextStep(&play, &game);
            break;
        case 6:
            diceGame();
            nextStep(&play, &game);
            break;
        }
    }
    return 0;
}