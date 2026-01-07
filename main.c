#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void game_vs_player(char board[3][3], char player1, char player2);
void game_vs_computer(char board[3][3], char player1, char player2);
void print_board(char board[3][3]);
void reset_board(char board[3][3]);
void computer_move(char board[3][3], char player);
int  write_move(char board[3][3], int x, int y, char value);
int check_board_full(char board[3][3]);
int check_winner(char board[3][3], char player);
int check_column(char board[3][3], int col, char player);
int check_row(char board[3][3], int row, char player);

int main(void) {
    srand(time(NULL));
    char board[3][3] = {0};
    char player1;
    char player2;
    int option = 0;

    printf("Player 1, select your letter (X - O) -> ");
    scanf(" %c", &player1);

    if (player1 == 'x') player1 = 'X';
    if (player1 == 'o') player1 = 'O';

    player2 = 'O';
    if (player1 == 'O') player2 = 'X';

    while (option != 3) {
        reset_board(board);
        printf("1) Play again player \n");
        printf("2) Play again computer\n");
        printf("3) Exit \n");
        printf("Select an option 1, 2 or 3 -> ");
        scanf("%i", &option);

        if (option == 1) {
            game_vs_player(board, player1, player2);
        } else if (option == 2){
            game_vs_computer(board, player1, player2);
        } else if (option == 3 ) {
            break;
        } else {
            printf("Error, please select a valid option\n");
        }
    }

    return 0;
}

void game_vs_player(char board[3][3], char player1, char player2) {
    int player_turn = 0;
    int x = 0, y = 0;

    while (!check_board_full(board)) {
        print_board(board);

        char current_symbol = (player_turn == 0) ? player1 : player2;
        printf("Player %d turn (%c):\n", player_turn + 1, current_symbol);

        printf("Select coordinate, x (0-2) =  ");
        scanf("%i", &x);
        printf("Select coordinate, y (0-2) =  ");
        scanf("%i", &y);

        if (write_move(board, x, y, current_symbol) == 0) {
            continue;
        }

        if (check_winner(board, current_symbol)) {
            print_board(board);
            printf("Player %d wins this match!\n", player_turn + 1);
            break;
        }

        player_turn = !player_turn;
    }

    if (check_board_full(board)) {
        print_board(board);
        printf("It's a draw!\n");
    }
}

void game_vs_computer(char board[3][3], char player1, char player2) {
    int player_turn = 0;
    int x = 0, y = 0;

    while (!check_board_full(board)) {
        print_board(board);

        char current_symbol = (player_turn == 0) ? player1 : player2;
        printf("Player %d turn (%c):\n", player_turn + 1, current_symbol);

        if (!player_turn) {
            printf("Select coordinate, x (0-2) =  ");
            scanf("%i", &x);
            printf("Select coordinate, y (0-2) =  ");
            scanf("%i", &y);

            if (write_move(board, x, y, current_symbol) == 0) {
                continue;
            }
        }else {
            computer_move(board, player2);
        }


        if (check_winner(board, current_symbol)) {
            print_board(board);
            printf("Player %d wins this match!\n", player_turn + 1);
            break;
        }

        player_turn = !player_turn;
    }

    if (check_board_full(board)) {
        print_board(board);
        printf("It's a draw!\n");
    }
}

void computer_move(char board[3][3], char cpu_player) {
    int x, y;

    printf("Thinking...\n");

    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != 0 && board[x][y] != ' ');

    board[x][y] = cpu_player;
}

void print_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
            if (j != 2) printf("|");
        }
        printf("\n");
    }
    printf("\n");
}

void reset_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

int write_move(char board[3][3], int x, int y, char value) {
    if (x > 2 || x < 0 || y > 2 || y < 0) { // Validar rango 0-2
        printf("Invalid coordinates! Use 0, 1 or 2.\n");
        return 0;
    }
    if (board[x][y] != '\0' && board[x][y] != ' ') {
        printf("Box already occupied!\n");
        return 0;
    }
    board[x][y] = value;
    return 1;
}

int check_board_full(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '\0') return 0;
        }
    }
    return 1;
}

int check_winner(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (check_row(board, i, player)) return 1;
        if (check_column(board, i, player)) return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
    return 0;
}

int check_column(char board[3][3], int col, char player) {
    for (int i = 0; i < 3; i++) if (board[i][col] != player) return 0;
    return 1;
}

int check_row(char board[3][3], int row, char player) {
    for (int j = 0; j < 3; j++)  if (board[row][j] != player) return 0;
    return 1;
}