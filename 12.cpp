#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#define CLEAR() system("cls")
#else
#include <unistd.h>
#define CLEAR() system("clear")
#endif

#define SIZE 10
#define MAX_HEALTH 100

int currentSize = SIZE; // Track the current maze size

char lastRoomMsg[100] = "";

// Difficulty Levels
typedef enum {
    EASY,
    MEDIUM,
    HARD,
    INSANE
} Difficulty;

Difficulty currentDifficulty = EASY; // Start with Easy difficulty
int gameLevel = 1;  // Current game level

typedef enum {
    NORMAL,
    LUCKY,
    UNLUCKY,
    CHALLENGE,
    BLOCKED,
    REAL_EXIT,
    FAKE_EXIT
} RoomType;

typedef struct {
    RoomType type;
    int revealed;
} Room;

typedef struct {
    int x, y;
    int health;
} Player;

Room maze[SIZE][SIZE];
Player player;
Player bots[4]; // Support up to 4 bots
int exitX = -1, exitY = -1;

// Forward declarations
void enterRoom();
int challenge0(int *health, int penalty, char *feedback);
int challenge1(int *health, int penalty, char *feedback);
int challenge2(int *health, int penalty, char *feedback);
void showInstructions();

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

const char* getRoomTypeName(RoomType type) {
    switch (type) {
        case NORMAL: return "Normal Room";
        case LUCKY: return "Lucky Room";
        case UNLUCKY: return "Unlucky Room";
        case CHALLENGE: return "Challenge Room";
        case BLOCKED: return "Blocked Room";
        case REAL_EXIT: return "Real Exit";
        case FAKE_EXIT: return "Fake Exit";
        default: return "Unknown";
    }
}

void generateMaze(int level) {
    int i, j;
    int size = SIZE;

    if (level == 2) size = 8;
    else if (level == 3) size = 6;
    else if (level >= 4) size = 5;
    currentSize = size;

    for (i = 0; i < size; ++i)
        for (j = 0; j < size; ++j) {
            maze[i][j].type = NORMAL;
            maze[i][j].revealed = 0;
        }

    int startY = randomInRange(0, size - 1);
    player.x = 0;
    player.y = startY;
    player.health = MAX_HEALTH;
    maze[startY][0].type = NORMAL;
    maze[startY][0].revealed = 1;

    while (1) {
        int edge = rand() % 4;
        int x = 0, y = 0;
        switch (edge) {
            case 0: x = 0; y = randomInRange(0, size - 1); break;
            case 1: x = size - 1; y = randomInRange(0, size - 1); break;
            case 2: x = randomInRange(0, size - 1); y = 0; break;
            case 3: x = randomInRange(0, size - 1); y = size - 1; break;
        }
        if ((x != player.x || y != player.y)) {
            maze[y][x].type = REAL_EXIT;
            exitX = x;
            exitY = y;
            break;
        }
    }

    int placed = 0;
    while (placed < 4) {
        int x = 0, y = 0, edge = rand() % 4;
        switch (edge) {
            case 0: x = 0; y = randomInRange(0, size - 1); break;
            case 1: x = size - 1; y = randomInRange(0, size - 1); break;
            case 2: x = randomInRange(0, size - 1); y = 0; break;
            case 3: x = randomInRange(0, size - 1); y = size - 1; break;
        }
        if (maze[y][x].type == NORMAL) {
            maze[y][x].type = FAKE_EXIT;
            placed++;
        }
    }

    int blockMin = 10 + (level - 1) * 3;
    int blockMax = 14 + (level - 1) * 4;
    int blockCount = randomInRange(blockMin, blockMax);

    placed = 0;
    while (placed < blockCount) {
        int x = rand() % size;
        int y = rand() % size;
        if (maze[y][x].type == NORMAL && (x != player.x || y != player.y)) {
            maze[y][x].type = BLOCKED;
            placed++;
        }
    }

    int unluckyMin = 8 + (level - 1) * 3;
    int unluckyMax = 11 + (level - 1) * 4;
    int unluckyCount = randomInRange(unluckyMin, unluckyMax);

    placed = 0;
    while (placed < unluckyCount) {
        int x = rand() % size;
        int y = rand() % size;
        if (maze[y][x].type == NORMAL) {
            maze[y][x].type = UNLUCKY;
            placed++;
        }
    }

    int luckyMin = 5;
    int luckyMax = 8;
    int luckyCount = randomInRange(luckyMin, luckyMax);

    placed = 0;
    while (placed < luckyCount) {
        int x = rand() % size;
        int y = rand() % size;
        if (maze[y][x].type == NORMAL) {
            maze[y][x].type = LUCKY;
            placed++;
        }
    }

    int challengeMin = 10 + (level - 1) * 3;
    int challengeMax = 14 + (level - 1) * 4;
    int challengeCount = randomInRange(challengeMin, challengeMax);

    placed = 0;
    while (placed < challengeCount) {
        int x = rand() % size;
        int y = rand() % size;
        if (maze[y][x].type == NORMAL) {
            maze[y][x].type = CHALLENGE;
            placed++;
        }
    }

    int botMin = (level == 1) ? 1 : (level == 2) ? 1 : (level == 3) ? 2 : 3;
    int botMax = (level == 1) ? 1 : (level == 2) ? 2 : (level == 3) ? 3 : 4;
    int botCount = randomInRange(botMin, botMax);

    for (int b = 0; b < 4; ++b) {
        bots[b].x = -1;  // Reset unused bots off-map
        bots[b].y = -1;
    }

    for (int b = 0; b < botCount; ++b) {
        bots[b].x = randomInRange(0, size - 1);
        bots[b].y = randomInRange(0, size - 1);
    }
}

void displayMap() {
    printf("Map View (P = You, B = Bot, . = Seen, [] = Unknown):\n\n");
    for (int y = 0; y < currentSize; ++y) {
        for (int x = 0; x < currentSize; ++x) {
            if (x == player.x && y == player.y)
                printf(" [P] ");
            else {
                int isBot = 0;
                for (int b = 0; b < 4; ++b) {
                    if (x == bots[b].x && y == bots[b].y) {
                        printf(" [B] ");
                        isBot = 1;
                        break;
                    }
                }
                if (!isBot) {
                    if (maze[y][x].revealed)
                        printf(" [.] ");
                    else
                        printf(" [ ] ");
                }
            }
        }
        printf("\n");
    }
}

void moveBotTowardPlayer() {
    for (int b = 0; b < 4; ++b) {
        if (bots[b].x == -1 && bots[b].y == -1) continue;

        int moved = 0;
        if (bots[b].x != player.x) {
            int dx = (bots[b].x < player.x) ? 1 : -1;
            int nx = bots[b].x + dx;
            if (nx >= 0 && nx < currentSize && maze[bots[b].y][nx].type != BLOCKED) {
                bots[b].x = nx;
                moved = 1;
            }
        }
        if (!moved && bots[b].y != player.y) {
            int dy = (bots[b].y < player.y) ? 1 : -1;
            int ny = bots[b].y + dy;
            if (ny >= 0 && ny < currentSize && maze[ny][bots[b].x].type != BLOCKED) {
                bots[b].y = ny;
            }
        }

        if (bots[b].x == player.x && bots[b].y == player.y) {
            sprintf(lastRoomMsg, "The Maze Monster caught you!");
            player.health = 0;
        }
    }
}

void showInstructions() {
    printf("\n--- Instructions ---\n");
    printf("- Use WASD keys to move (w=up, a=left, s=down, d=right)\n");
    printf("- Reach the REAL EXIT on the maze border to win\n");
    printf("- Avoid the bot(s) and traps\n");
    printf("- Some rooms help you, some hurt you. Good luck!\n\n");
}

void movePlayer(char dir) {
    int dx = 0, dy = 0;
    if (dir == 'w') dy = -1;
    else if (dir == 's') dy = 1;
    else if (dir == 'a') dx = -1;
    else if (dir == 'd') dx = 1;
    else {
        sprintf(lastRoomMsg, "Invalid direction!");
        moveBotTowardPlayer();
        return;
    }

    int nx = player.x + dx;
    int ny = player.y + dy;
    if (nx < 0 || nx >= currentSize || ny < 0 || ny >= currentSize) {
        sprintf(lastRoomMsg, "Out of bounds!");
        moveBotTowardPlayer();
        return;
    }
    if (maze[ny][nx].type == BLOCKED) {
        sprintf(lastRoomMsg, "That room is blocked!");
        moveBotTowardPlayer();
        return;
    }

    player.x = nx;
    player.y = ny;
    enterRoom();
}

// Challenge implementations below
int challenge0(int *hp, int penalty, char *feedback) {
    int a[4];
    a[0] = rand() % 10 + 1;
    int diff = rand() % 5 + 2;
    printf("Guess the next number in sequence: %d ", a[0]);
    for (int i = 1; i < 4; i++) {
        a[i] = a[i - 1] + diff;
        if (i < 3) printf("%d ", a[i]);
    }
    printf("\nYou have %d seconds.\n", penalty);

    int answer;
    time_t start = time(NULL);
    scanf("%d", &answer);
    time_t end = time(NULL);

    if (end - start > penalty) {
        sprintf(feedback, "Too slow! Time's up. -%d HP!", penalty);
        *hp -= penalty;
        return 0;
    }
    if (answer == a[3]) {
        sprintf(feedback, "Correct!");
        return 1;
    } else {
        sprintf(feedback, "Wrong! -%d HP!", penalty);
        *hp -= penalty;
        return 0;
    }
}

int challenge1(int *hp, int penalty, char *feedback) {
    int a = rand() % 50 + 1;
    int b = rand() % 50 + 1;
    char ops[] = "+-*/";
    char op = ops[rand() % 4];
    int realAns = 0;
    switch (op) {
        case '+': realAns = a + b; break;
        case '-': realAns = a - b; break;
        case '*': realAns = a * b; break;
        case '/':
            b = (b == 0) ? 1 : b; // avoid division by zero
            realAns = a / b;
            break;
    }
    printf("Solve: %d %c %d = ? (You have %d seconds)\n", a, op, b, penalty);

    int answer;
    time_t start = time(NULL);
    scanf("%d", &answer);
    time_t end = time(NULL);

    if (end - start > penalty) {
        sprintf(feedback, "Too slow! Time's up. -%d HP!", penalty);
        *hp -= penalty;
        return 0;
    }
    if (answer == realAns) {
        sprintf(feedback, "Correct!");
        return 1;
    } else {
        sprintf(feedback, "Wrong! -%d HP!", penalty);
        *hp -= penalty;
        return 0;
    }
}

int challenge2(int *hp, int penalty, char *feedback) {
    int len = rand() % 11 + 10; // 10-20 chars
    char str[21];
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    int charsetLen = sizeof(charset) - 1;
    for (int i = 0; i < len; i++) {
        str[i] = charset[rand() % charsetLen];
    }
    str[len] = '\0';

    char target = str[rand() % len];
    printf("String: %s\nCount how many '%c' in the string (You have %d seconds)\n", str, target, penalty);

    int answer;
    time_t start = time(NULL);
    scanf("%d", &answer);
    time_t end = time(NULL);

    int count = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == target) count++;
    }

    if (end - start > penalty) {
        sprintf(feedback, "Too slow! Time's up. -%d HP!", penalty);
        *hp -= penalty;
        return 0;
    }
    if (answer == count) {
        sprintf(feedback, "Correct!");
        return 1;
    } else {
        sprintf(feedback, "Wrong! -%d HP!", penalty);
        *hp -= penalty;
        return 0;
    }
}

void enterRoom() {
    RoomType type = maze[player.y][player.x].type;
    maze[player.y][player.x].revealed = 1;

    switch (type) {
        case NORMAL:
            sprintf(lastRoomMsg, "You've entered a normal room.");
            break;
        case LUCKY:
            sprintf(lastRoomMsg, "Lucky Room! +10 HP!");
            player.health += 10;
            if (player.health > MAX_HEALTH) player.health = MAX_HEALTH;
            break;
        case UNLUCKY:
            sprintf(lastRoomMsg, "Unlucky Room! -10 HP!");
            player.health -= 10;
            break;
        case CHALLENGE: {
            int result = 0;
            int r = rand() % 3;
            char feedback[64] = "";
            if (r == 0) {
                result = challenge0(&player.health, 10, feedback);
            } else if (r == 1) {
                result = challenge1(&player.health, 10, feedback);
            } else {
                result = challenge2(&player.health, 15, feedback);
            }
            if (result)
                sprintf(lastRoomMsg, "%s\nYou passed the challenge! ", feedback);
            else
                sprintf(lastRoomMsg, "%s\nYou failed the challenge!", feedback);

            moveBotTowardPlayer();
            return;
        }
        case FAKE_EXIT:
            sprintf(lastRoomMsg, "Fake Exit! Trap triggered! -30 HP");
            player.health -= 30;
            break;
        case REAL_EXIT:
            printf("You escaped the maze! YOU WIN!\n");
            return;
        default:
            break;
    }
    moveBotTowardPlayer();
}

void gameLoop() {
    char input[10];
    while (player.health > 0) {
        CLEAR();
        printf("HP: %d\n", player.health);

        displayMap();
        printf("\n");

        RoomType type = maze[player.y][player.x].type;
        if (strlen(lastRoomMsg) > 0) {
            printf("%s\n", lastRoomMsg);
        } else {
            printf("You are standing in: %s\n", getRoomTypeName(type));
        }
        printf("Move (WASD): ");
        scanf("%s", input);
        movePlayer(tolower(input[0]));

        if (player.health <= 0) break;

        if (maze[player.y][player.x].type == REAL_EXIT) {
            printf("You escaped the maze! YOU WIN!\n");
            if (gameLevel < 5) gameLevel++;
            currentDifficulty = (gameLevel == 1) ? EASY :
                                (gameLevel == 2) ? MEDIUM :
                                (gameLevel == 3) ? HARD : INSANE;
            printf("Next level: %d\nPress Enter to continue...", gameLevel);
            getchar(); getchar();

            generateMaze(gameLevel);
        }
    }
    printf("You died in the maze...\n");
}

int mainMenu() {
    int choice;
    do {
        CLEAR();
        printf("\n--- CARDMAZE: The Labyrinth of Tricks ---\n");
        printf("1. Play\n");
        printf("2. Instructions\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        if (choice == 2) {
            CLEAR();
            showInstructions();
            printf("Press any key to return to menu...\n");
            getchar(); getchar();
        }
        else if (choice == 3) exit(0);
    } while (choice != 1);
    return 0;
}

int main() {
    srand(time(NULL));
    mainMenu();
    CLEAR();
    generateMaze(gameLevel);
    gameLoop();
    return 0;
}

