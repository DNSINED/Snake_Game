#include "snake_game.h"


int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int tail_length;
Direction dir;
bool game_over;

void Setup() {
    game_over = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruit_x = rand() % width;
    fruit_y = rand() % height;
    score = 0;
    tail_length = 0;
}

void Draw() {
    // Set the cursor to the top-left corner (0,0)
    Set_Cursor_Position(0, 0);

    // Draw the top border
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    // Draw the game area with snake, fruit, and borders
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "|";

            if (i == y && j == x)
                cout << "O";  // Snake head
            else if (i == fruit_y && j == fruit_x)
                cout << "#";  // Fruit
            else {
                bool print_tail = false;
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        cout << "o";  // Snake body
                        print_tail = true;
                    }
                }
                if (!print_tail)
                    cout << " ";  // Empty space
            }

            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    // Draw the bottom border
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    // Update the score display
    cout << "Score: " << score << endl;
}


void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                game_over = true;
                break;
        }
    }
}

void Logic() {
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    int prev_2x, prev_2y;
    tail_x[0] = x;
    tail_y[0] = y;

    for (int i = 1; i < tail_length; i++) {
        prev_2x = tail_x[i];
        prev_2y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = prev_2x;
        prev_y = prev_2y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height)
        game_over = true;

    for (int i = 0; i < tail_length; i++) {
        if (tail_x[i] == x && tail_y[i] == y)
            game_over = true;
    }

    if (x == fruit_x && y == fruit_y) {
        score += 10;
        fruit_x = rand() % width;
        fruit_y = rand() % height;
        tail_length++;
    }
}

void Set_Cursor_Position(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void Frame_Delay() {
    Sleep(2);
}

void Set_Console_Colour(int colour) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}
int main() {
    srand(time(nullptr));
    Setup();
    Set_Console_Colour(RED);
    while (!game_over) {
        Draw();
        Frame_Delay();
        Input();
        Logic();
    }

    Set_Cursor_Position(0, height + 3);

    cout << "Game Over!" << endl;
    return 0;
}
