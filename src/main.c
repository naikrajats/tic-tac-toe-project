#include <stdio.h>

char board[3][3];
int moves = 0;

void init_board() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '1' + i * 3 + j;
}

void print_board() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

int check_winner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;
    return 0;
}

int is_draw() {
    return moves >= 9;
}

int make_move(char symbol, int cell) {
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    if (cell < 1 || cell > 9 || board[row][col] == 'X' || board[row][col] == 'O')
        return 0;
    board[row][col] = symbol;
    moves++;
    return 1;
}

int main() {
    int cell;
    char player = 'X';
    init_board();

    while (1) {
        print_board();
        printf("Player %c, enter cell (1-9): ", player);
        scanf("%d", &cell);

        if (!make_move(player, cell)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        if (check_winner()) {
            print_board();
            printf("Player %c wins!\n", player);
            break;
        }

        if (is_draw()) {
            print_board();
            printf("It's a draw!\n");
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    return 0;
}
