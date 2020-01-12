#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int random();//Creates random value from 0 to 9
void generate(char plansza[9]);//prints out the board
void turn_o(char plansza[9]);//gets input from user and inserts to the board
void turn_x(char plansza[9]);//gets random position for x and insert it
void check(char plansza[9], int ruch);//check winning patterns
int sim(char plansza[9], int ruch);//simulates board and search for winning/loosing moves (stops player if he's about to win)

int win = 0;
int ruch = 0;
char symbol = 0;


int main() {
    //Board
    char plansza[9] = { 32, 32, 32, 32, 32, 32, 32, 32, 32 };
    printf("Chose coordinate x and y of place of your choice!\nRemember to stay in range from 1 to 3. Otherwise your input will not be used.\nGood Luck!\n\n");

    while (win == 0) {
        generate(plansza);
        turn_o(plansza);
        if (ruch >= 9) {
            generate(plansza);
            printf("remis\n");
            system("pause");
            exit(0);
        }
        check(plansza, ruch);
        if (win > 0) {
            break;
        }
        generate(plansza);
        ruch++;
        turn_x(plansza);
        check(plansza, ruch);
    }
    if (win == 2) {
        generate(plansza);
        printf("You win!\n");
        system("pause");
        exit(0);
    }
    else if (win == 1) {
        generate(plansza);
        printf("Bot win :<\n");
        system("pause");
        exit(0);
    }
    return 0;
}

int random() {
    static int r = 1;
    int i = 0;
    int ra = 0;

    srand(time(0));
    while (i < r) {
        ra = (rand() % 9);
        i++;
        // printf("%i\n", ra);
    }
    r++;
    i++;
    return ra;
}

void generate(char plansza[9]) {
    printf("Ruch #%i\n\n", ruch);
    printf("XX 1 XX 2 XX 3 XX\n");
    int n = 1;
    for (int i = 0; i < 9; i++) {
        if (i == 0) {
            printf("%i", n);
        }
        printf("| %c |", plansza[i]);
        if (i % 3 == 2) {
            n++;
            printf("\n");
            if (n < 4) {
                printf("%i", n);
            }
        }
    }
    printf("XXXXXXXXXXXXXXXXX\n");
}

void turn_o(char plansza[9]) {
    int x, y, coordinate;

    printf("Enter coordinate x: ");
    scanf_s("%i", &x);
    printf("Enter coordinate y: ");
    scanf_s("%i", &y);

    if (x >= 1 && x <= 3 && y >= 1 && y <= 3) {
        coordinate = (x + (y - 1) * 3) - 1;

        if (plansza[coordinate] == 32) {
            plansza[coordinate] = 'O';
        }
        else {
            printf("This coordinate is busy,try other one\n");
            system("pause");
            turn_o(plansza);
        }
    }
    else {
        printf("CRITICAL ERROR!\nWrong input, try using values from 1 to 3\n");
        system("pause");
        turn_o(plansza);
        ruch -= 1;

    }
    ruch += 1;
}

void turn_x(char plansza[9]) {
    int coordinate = sim(plansza, ruch);
    
    if (coordinate == -1) {
        coordinate = random();
        while (plansza[coordinate] != 32) {
            coordinate = random();
        }
        plansza[coordinate] = 'X';
    }
    else {
        plansza[coordinate] = 'X';
    } 
}

int sim(char plansza[9],int ruch) {
    int bestchoice = -1;
    int virtualturn = ruch;
    char virtualboard[9];
    for (int i = 0; i < 9; i++) {
        virtualboard[i] = plansza[i];
    }
    
    for (int i = 0; i < 9; i++) {
        virtualturn += 1;
        if (virtualturn % 2 == 1) {
            if (virtualboard[i] == 32) {
                virtualboard[i] = 'O';
                check(virtualboard, virtualturn);
                virtualboard[i] = 32;
                if (win == 2) {
                    bestchoice = i;
                    win = 0;
                    break;
                    
                }
                win = 0;
            }
        }
        virtualturn += 1;
        if (virtualboard[i] == 32) {
            virtualboard[i] = 'X';
            check(virtualboard, virtualturn);
            virtualboard[i] = 32;
            if (win == 1) {
                bestchoice = i;
                win = 0;
                break;
            }
            win = 0;
        }
    }
    return bestchoice;
    
}

void check(char plansza[9], int ruch) {
    int i = ruch % 2;
    if (i == 1) {
        symbol = 'O';
    }
    else {
        symbol = 'X';
    }

    while (win == 0) {
        if (plansza[4] == symbol ) {
            if (plansza[0] == symbol) {
                if (plansza[8] == symbol) {
                    win = i + 1;
                    break;
                }
            }
            if(plansza[3] == symbol){
                if(plansza[5] == symbol){
                    win = i + 1;
                    break;
                }
            }
            if (plansza[1] == symbol) {
                if (plansza[7] == symbol) {
                    win = i + 1;
                    break;
                }
            }
            if (plansza[2] == symbol) {
                if (plansza[6] == symbol) {
                    win = i + 1;
                    break;
                }
            }
        }
        if (plansza[2] == symbol) {
            if (plansza[0] == symbol) {
                if (plansza[1] == symbol) {
                    win = i + 1;
                    break;
                }
            }
            if (plansza[5] == symbol) {
                if (plansza[8] == symbol) {
                    win = i + 1;
                    break;
                }
            }  
        }
        if (plansza[6] == symbol) {
            if (plansza[7] == symbol) {
                if (plansza[8] == symbol) {
                    win = i + 1;
                    break;
                }
            }
            if (plansza[3] == symbol) {
                if (plansza[0] == symbol) {
                    win = i + 1;
                    break;
                }
            }
        }
        break;
    }
}
