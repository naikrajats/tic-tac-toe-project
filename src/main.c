#include <stdio.h>

#define SIZE 3

typedef struct {
    char cells[SIZE][SIZE];
    int moves;
} Board;

void init_board(Board *b) {
    b->moves = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            b->cells[i][j] = '1' + i * SIZE + j;
        }
    }
}

void print_board(const Board *b) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf(" %c | %c | %c ", b->cells[i][0], b->cells[i][1], b->cells[i][2]);
        if (i < SIZE - 1) {
            printf("\n---|---|---\n");
        }
    }
    printf("\n");
}

int check_winner(const Board *b) {
    // rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (b->cells[i][0] == b->cells[i][1] &&
            b->cells[i][1] == b->cells[i][2]) {
            return 1;
        }
        if (b->cells[0][i] == b->cells[1][i] &&
            b->cells[1][i] == b->cells[2][i]) {
            return 1;
        }
    }
    // diagonals
    if (b->cells[0][0] == b->cells[1][1] &&
        b->cells[1][1] == b->cells[2][2]) {
        return 1;
    }
    if (b->cells[0][2] == b->cells[1][1] &&
        b->cells[1][1] == b->cells[2][0]) {
        return 1;
    }
    return 0;
}

int is_draw(const Board *b) {
    return b->moves >= SIZE * SIZE;
}

int make_move(Board *b, char symbol, int cell) {
    if (cell < 1 || cell > 9) {
        return 0;
    }
    int row = (cell - 1) / SIZE;
    int col = (cell - 1) % SIZE;

    if (b->cells[row][col] == 'X' || b->cells[row][col] == 'O') {
        return 0;
    }

    b->cells[row][col] = symbol;
    b->moves++;
    return 1;
}

int read_cell_input(int *cell) {
    int result;
    while (1) {
        result = scanf("%d", cell);
        if (result == 1) {
            // valid integer, but may be out of range
            while (getchar() != '\n') {
                // clear extra chars from buffer
            }
            return 1;
        } else {
            // invalid input (non-integer), clear buffer
            printf("Invalid input. Enter a number between 1 and 9: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // discard
            }
        }
    }
}

void play_game(void) {
    Board board;
    char player = 'X';
    int cell;

    init_board(&board);

    while (1) {
        print_board(&board);
        printf("Player %c, enter cell (1-9): ", player);

        if (!read_cell_input(&cell)) {
            // should not reach here, but safety
            printf("Input error.\n");
            continue;
        }

        if (!make_move(&board, player, cell)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        if (check_winner(&board)) {
            print_board(&board);
            printf("Player %c wins!\n", player);
            break;
        }

        if (is_draw(&board)) {
            print_board(&board);
            printf("It's a draw!\n");
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
}

int main(void) {
    char choice;

    do {
        play_game();

        printf("Play again? (y/n): ");
        if (scanf(" %c", &choice) != 1) {
            break;
        }
        while (getchar() != '\n') {
            // clear input buffer
        }
    } while (choice == 'y' || choice == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}

