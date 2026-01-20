
    #include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

typedef struct {
    char cells[SIZE][SIZE];
    int moves;
} Board;

/* ---------- GLOBAL SCORE ---------- */
int scoreX = 0, scoreO = 0, scoreDraw = 0;

/* ---------- BOARD FUNCTIONS ---------- */
void init_board(Board *b) {
    b->moves = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            b->cells[i][j] = '1' + i * SIZE + j;
}

void print_board(const Board *b) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf(" %c | %c | %c ", b->cells[i][0], b->cells[i][1], b->cells[i][2]);
        if (i < SIZE - 1)
            printf("\n---|---|---\n");
    }
    printf("\n");
}

/* ---------- GAME LOGIC ---------- */
int valid_line(char a, char b, char c) {
    return (a == b && b == c && (a == 'X' || a == 'O'));
}

int check_winner(const Board *b) {
    for (int i = 0; i < SIZE; i++) {
        if (valid_line(b->cells[i][0], b->cells[i][1], b->cells[i][2])) return 1;
        if (valid_line(b->cells[0][i], b->cells[1][i], b->cells[2][i])) return 1;
    }
    if (valid_line(b->cells[0][0], b->cells[1][1], b->cells[2][2])) return 1;
    if (valid_line(b->cells[0][2], b->cells[1][1], b->cells[2][0])) return 1;
    return 0;
}

int is_draw(const Board *b) {
    return b->moves == SIZE * SIZE;
}

int make_move(Board *b, char symbol, int cell) {
    if (cell < 1 || cell > 9) return 0;

    int r = (cell - 1) / SIZE;
    int c = (cell - 1) % SIZE;

    if (b->cells[r][c] == 'X' || b->cells[r][c] == 'O')
        return 0;

    b->cells[r][c] = symbol;
    b->moves++;
    return 1;
}

/* ---------- INPUT ---------- */
int read_cell_input(int *cell) {
    while (scanf("%d", cell) != 1 || *cell < 1 || *cell > 9) {
        printf("Invalid input. Enter 1-9: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return 1;
}

/* ---------- COMPUTER MOVE ---------- */
void computer_move(Board *b) {
    int cell;
    do {
        cell = rand() % 9 + 1;
    } while (!make_move(b, 'O', cell));
}

/* ---------- GAME MODES ---------- */
void play_game(int vsComputer) {
    Board board;
    char player = 'X';
    int cell;

    init_board(&board);

    while (1) {
        print_board(&board);

        if (player == 'O' && vsComputer) {
            printf("Computer is making a move...\n");
            computer_move(&board);
        } else {
            printf("Player %c, enter cell (1-9): ", player);
            read_cell_input(&cell);

            if (!make_move(&board, player, cell)) {
                printf("Invalid move. Try again.\n");
                continue;
            }
        }

        if (check_winner(&board)) {
            print_board(&board);
            printf("Player %c wins!\n", player);
            (player == 'X') ? scoreX++ : scoreO++;
            break;
        }

        if (is_draw(&board)) {
            print_board(&board);
            printf("It's a draw!\n");
            scoreDraw++;
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
}

/* ---------- MENU ---------- */
void show_score(void) {
    printf("\nSCOREBOARD\n");
    printf("X Wins : %d\n", scoreX);
    printf("O Wins : %d\n", scoreO);
    printf("Draws : %d\n\n", scoreDraw);
}

int main(void) {
    int choice;
    char again;

    srand(time(NULL));

    do {
        printf("\n--- TIC TAC TOE ---\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs Computer\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        if (choice == 1)
            play_game(0);
        else if (choice == 2)
            play_game(1);
        else
            printf("Invalid choice!\n");

        show_score();

        printf("Play again? (y/n): ");
        scanf(" %c", &again);
        while (getchar() != '\n');

    } while (again == 'y' || again == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}