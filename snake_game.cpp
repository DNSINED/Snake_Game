#include "snake_game.h"

int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int tail_length;
bool game_over;
Direction dir;


void Hide_Cursor() {
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.bVisible = false;
    cursor_info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Set_Console_Colour(int colour) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

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
    Set_Cursor_Position(0, 0);
    Set_Console_Colour(PURPLE);

    for (int i = 0; i < width; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                Set_Console_Colour(PURPLE);
            cout << "|";
            }
            else if (i == y && j == x){
                Set_Console_Colour(GREEN);
                cout << "O";
            }
            else if (i == fruit_y && j == fruit_x){
                Set_Console_Colour(RED);
                cout << "@";
            }
            else {
                bool print_tail = false;
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        Set_Console_Colour(GREEN);
                        cout << "o";
                        print_tail = true;
                        break;
                    }
                }
                if (!print_tail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    Set_Console_Colour(PURPLE);
    for (int i = 0; i < width; i++)
        cout << "-";
    cout << endl;

    Set_Console_Colour(YELLOW);
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
            case 'k':
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
    COORD cursor_pos;
    cursor_pos.X = x;
    cursor_pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
}

void Frame_Delay() {
    static auto last_time = std::chrono::high_resolution_clock::now();
    
    constexpr int frame_delay_ms = 80; // 80ms = 12.5 cadre pe secunda

    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count();

    if (elapsed < frame_delay_ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(frame_delay_ms - elapsed));
    }

    last_time = std::chrono::high_resolution_clock::now();
}

int main() {
    srand(time(0));

    Setup();
    Hide_Cursor();
    while (!game_over) {
        Draw();
        Input();
        Logic();
        Frame_Delay();
    }
    Set_Cursor_Position(0, height + 3);

    cout << "Game Over!" << endl;
    return 0;
}
