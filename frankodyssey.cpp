#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int frankX = 50;
int frankY = 10;

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

void printFrankUp();
void printFrankDown();
void printFrankLeft();
void printFrankRight();

void moveFrankLeft();
void moveFrankRight();
void moveFrankUp();
void moveFrankDown();
void eraseFrankRightLeftUpDown();

char legs = 227;
char gunRight = 169;
char gunLeft = 170;
char legsUpDown = 205;

char frankRight1[5] = {' ', '(', '-', ')', ' '};
char frankRight2[5] = {' ', '/', '|', gunRight, ' '};
char frankRight3[5] = {' ', '/', ' ', '\\', ' '};

char frankLeft1[5] = {' ', '(', '-', ')', ' '};
char frankLeft2[5] = {' ', gunLeft, '|', '\\', ' '};
char frankLeft3[5] = {' ', '/', ' ', '\\', ' '};

char frankUp1[5] = {' ', ' ', '!', ' ', ' '};
char frankUp2[5] = {'O', '-', '-', legsUpDown, legsUpDown};
char frankUp3[5] = {' ', ' ', '\\', ' ', ' '};

char frankDown1[5] = {' ', ' ', '/', ' ', ' '};
char frankDown2[5] = {'O', '-', '-', legsUpDown, legsUpDown};
char frankDown3[5] = {' ', ' ', '|', ' ', ' '};

int bulletX[100];
int bulletY[100];
bool isBulletActive[100];
string bulletDirection[100];
int bulletCount = 0;

void addScore();
void printScore();
void bulletCollisionWithCaptain();
void bulletCollisionWithChief();
void bulletCollisionWithCorporal();

int score = 0;

void generateBulletRight();
void generateBulletLeft();
void generateBulletUp();
void generateBulletDown();
void moveBullets();
void eraseBullet(int x, int y);
void printBullet(int x, int y);
void makeBulletInactive(int idx);

// Captain functions move vertically
char enemyCaptain1[5] = {' ', ' ', '^', ' ', ' '};
char enemyCaptain2[5] = {' ', '(', '-', ')', ' '};
char enemyCaptain3[5] = {' ', gunLeft, '|', '\\', ' '};
char enemyCaptain4[5] = {' ', '/', ' ', '\\', ' '};

int captainX = 80;
int captainY = 5;

int captainBulletY[100000];
int captainBulletX[100000];
bool isCaptainBulletActive[100000];
int captainBulletCount = 0;

void generateCaptainBullet();
void eraseCaptainBullet(int x, int y);
void printCaptainBullet(int x, int y);
void makeCaptainBulletInactive(int x);
void moveCaptainBullet();

void printCaptain();
void eraseCaptain();
void moveCaptain();

string captainDirection = "up";

// Chief functions intelligent enemy

char enemyChief1[5] = {' ', '^', ' ', '^', ' '};
char enemyChief2[5] = {' ', '(', '-', ')', ' '};
char enemyChief3[5] = {' ', gunLeft, '|', gunRight, ' '};
char enemyChief4[5] = {' ', '/', ' ', '\\', ' '};

int chiefX = 6;
int chiefY = 6;

void printCorporalRight();

void printChief();
void eraseChief();
void moveChief();

// corporal function horizontal enemy

char enemyCorporalLeft1[5] = {' ', '<', '-', '>', ' '};
char enemyCorporalLeft2[5] = {' ', '(', '-', ')', ' '};
char enemyCorporalLeft3[5] = {' ', gunLeft, '|', '\\', ' '};
char enemyCorporalLeft4[5] = {' ', '/', ' ', '\\', ' '};

char enemyCorporalRight1[5] = {' ', '<', '-', '>', ' '};
char enemyCorporalRight2[5] = {' ', '(', '-', ')', ' '};
char enemyCorporalRight3[5] = {' ', '/', '|', gunRight, ' '};
char enemyCorporalRight4[5] = {' ', '/', ' ', '\\', ' '};

int corporalX = 10;
int corporalY = 15;

void moveCorporal();
void eraseCorporal();
void printCorporalRight();
void prijtCorporalLeft();

string corporalDirection = "right";

void printLogo();
void printMainOptions();
void clearIt();
void instructionsMenu();
void levelOne();

main()

{

    char choice;
    bool isGameRunning = true;
    string frankFace = "right";

    while (isGameRunning == true)
    {
        system("CLS");
        printLogo();
        printMainOptions();
        cin >> choice;
        if (choice >= 49 && choice <= 51)
        {
            if (choice == 49)
            {
                system("CLS");
                levelOne();
                printFrankRight();
                printCaptain();
                printChief();

                int timer1 = 2;
                int timer2 = 10;
                while (true)
                {
                    printScore();
                    if (GetAsyncKeyState(VK_RIGHT))
                    {
                        moveFrankRight();
                        frankFace = "right";
                    }
                    if (GetAsyncKeyState(VK_LEFT))
                    {
                        moveFrankLeft();
                        frankFace = "left";
                    }
                    if (GetAsyncKeyState(VK_UP))
                    {
                        moveFrankUp();
                        frankFace = "up";
                    }
                    if (GetAsyncKeyState(VK_DOWN))
                    {
                        moveFrankDown();
                        frankFace = "down";
                    }
                    if (GetAsyncKeyState(VK_SPACE))
                    {
                        if (frankFace == "right")
                        {
                            generateBulletRight();
                        }
                        if (frankFace == "left")
                        {
                            generateBulletLeft();
                        }
                        if (frankFace == "up")
                        {
                            generateBulletUp();
                        }
                        if (frankFace == "down")
                        {
                            generateBulletDown();
                        }
                    }

                    if (timer1 == 2)
                    {
                        moveCaptain();
                        moveCaptainBullet();
                        moveCorporal();
                        moveChief();

                        timer1 = 0;
                    }
                    moveBullets();
                    bulletCollisionWithCaptain();
                    bulletCollisionWithChief();
                    bulletCollisionWithCorporal();

                    timer1++;

                    Sleep(75);
                }
            }
            if (choice == 50)
            {
                instructionsMenu();
            }
            if (choice == 51)
            {
                isGameRunning = false;
            }
        }

        else if (choice < 49 || choice > 51)
        {
            cout << "Invalid choice try again" << endl;
            clearIt();
        }
    }
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

void printLogo()
{
    cout << "#######                             ###                                                   " << endl;
    cout << "#       #####    ##   #    # #    # ###  ####      ####  #####  #   #  ####   ####  ###### #   #" << endl;
    cout << "#       #    #  #  #  ##   # #   #   #  #         #    # #    #  # #  #      #      #       # #" << endl;
    cout << "#####   #    # #    # # #  # ####   #    ####     #    # #    #   #    ####   ####  #####    #" << endl;
    cout << "#       #####  ###### #  # # #  #            #    #    # #    #   #        #      # #        #" << endl;
    cout << "#       #   #  #    # #   ## #   #      #    #    #    # #    #   #   #    # #    # #        #" << endl;
    cout << "#       #    # #    # #    # #    #      ####      ####  #####    #    ####   ####  ######   #" << endl;
}

void printMainOptions()
{
    cout << endl
         << endl
         << endl;
    cout << "1. Start game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. End game" << endl;
    cout << endl;
    cout << "Enter option=> ";
}

void clearIt()
{
    cout << "Press any key to continue=> ";
    getch();
}

void instructionsMenu()
{
    system("CLS");
    printLogo();
    cout << endl
         << endl
         << endl;
    cout << "1. Press arrow keys to control frank" << endl;
    cout << "2. Press spacebar to fire at your enemies" << endl;
    cout << "3. Your enemies will also fire at you, avoid their fire by using walls and hurdles" << endl;
    cout << "4. Frank has 3 lives" << endl;
    cout << "5. Collect coins and lives from enemy bases" << endl;
    cout << "6. Save your friends" << endl;
    clearIt();
}

void levelOne()
{

    cout << "############################################################################################################" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                ##                                                                         #" << endl;
    cout << "#                                ##                           ##                     ##                     #" << endl;
    cout << "#                                                             ##                     ##                     #" << endl;
    cout << "#                                                             ##                     ##                     #" << endl;
    cout << "#                               ##                            ##                     ##                     #" << endl;
    cout << "#                               ##                                                   ##                     #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                             ##                                            #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                                                                           #" << endl;
    cout << "#                                                        ##                                                 #" << endl;
    cout << "#                                                        ##                                                 #" << endl;
    cout << "#                                                        ##                                                 #" << endl;
    cout << "############################################################################################################" << endl;
}

// Printing frank
void printFrankUp()
{
    gotoxy(frankX, frankY);

    for (int x = 0; x < 5; x++)
    {
        cout << frankUp1[x];
    }
    gotoxy(frankX, frankY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << frankUp2[x];
    }
    gotoxy(frankX, frankY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << frankUp3[x];
    }
}
void printFrankDown()
{
    gotoxy(frankX, frankY);
    for (int x = 0; x < 5; x++)
    {
        cout << frankDown1[x];
    }
    gotoxy(frankX, frankY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << frankDown2[x];
    }
    gotoxy(frankX, frankY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << frankDown3[x];
    }
}
void printFrankLeft()
{
    gotoxy(frankX, frankY);

    for (int x = 0; x < 5; x++)
    {
        cout << frankLeft1[x];
    }
    gotoxy(frankX, frankY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << frankLeft2[x];
    }
    gotoxy(frankX, frankY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << frankLeft3[x];
    }
}

void printFrankRight()
{
    gotoxy(frankX, frankY);

    for (int x = 0; x < 5; x++)
    {
        cout << frankRight1[x];
    }
    gotoxy(frankX, frankY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << frankRight2[x];
    }
    gotoxy(frankX, frankY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << frankRight3[x];
    }
}

// Moving frank

void eraseFrankRightLeftUpDown()
{
    gotoxy(frankX, frankY);
    for (int i = 0; i < 5; i++)
    {
        cout << " ";
    }
    gotoxy(frankX, frankY + 1);
    for (int i = 0; i < 5; i++)
    {
        cout << " ";
    }
    gotoxy(frankX, frankY + 2);
    for (int i = 0; i < 5; i++)
    {
        cout << " ";
    }
}

void moveFrankRight()
{

    char next = getCharAtxy(frankX + 5, frankY);
    char next2 = getCharAtxy(frankX + 5, frankY + 1);
    char next3 = getCharAtxy(frankX + 5, frankY + 2);
    if (next == ' ' && next2 == ' ' && next3 == ' ')
    {
        eraseFrankRightLeftUpDown();
        frankX = frankX + 1;
        printFrankRight();
    }
}
void moveFrankLeft()
{
    char next;
    next = getCharAtxy(frankX - 1, frankY);
    char next2 = getCharAtxy(frankX - 1, frankY + 1);
    char next3 = getCharAtxy(frankX - 1, frankY + 2);
    if (next == ' ')
    {
        eraseFrankRightLeftUpDown();
        frankX = frankX - 1;
        printFrankLeft();
    }
}

void moveFrankUp()
{
    char next;
    next = getCharAtxy(frankX, frankY - 1);
    if (next == ' ')
    {
        eraseFrankRightLeftUpDown();
        frankY = frankY - 1;
        printFrankUp();
    }
}

void moveFrankDown()
{
    char next;
    next = getCharAtxy(frankX, frankY + 3);
    if (next == ' ')
    {
        eraseFrankRightLeftUpDown();
        frankY = frankY + 1;
        printFrankDown();
    }
}

// Frank bullet functions

void generateBulletRight()
{

    bulletX[bulletCount] = frankX + 6;
    bulletY[bulletCount] = frankY + 1;
    isBulletActive[bulletCount] = true;
    gotoxy(frankX + 6, frankY + 1);
    cout << ".";
    bulletDirection[bulletCount] = "right";
    bulletCount++;
}
void generateBulletLeft()
{

    bulletX[bulletCount] = frankX - 1;
    bulletY[bulletCount] = frankY + 1;
    isBulletActive[bulletCount] = true;
    gotoxy(frankX - 1, frankY + 1);
    cout << ".";
    bulletDirection[bulletCount] = "left";
    bulletCount++;
}
void generateBulletUp()
{

    bulletX[bulletCount] = frankX + 2;
    bulletY[bulletCount] = frankY - 1;
    isBulletActive[bulletCount] = true;
    gotoxy(frankX + 2, frankY - 1);
    cout << ".";
    bulletDirection[bulletCount] = "up";
    bulletCount++;
}
void generateBulletDown()
{

    bulletX[bulletCount] = frankX + 2;
    bulletY[bulletCount] = frankY + 4;
    isBulletActive[bulletCount] = true;
    gotoxy(frankX + 2, frankY + 4);
    cout << ".";
    bulletDirection[bulletCount] = "down";
    bulletCount++;
}
void moveBullets()
{

    for (int x = 0; x < bulletCount; x++)
    {
        if (bulletDirection[x] == "right")
        {
            if (isBulletActive[x] == true)
            {
                char next = getCharAtxy(bulletX[x] + 1, bulletY[x]);
                if (next != ' ')
                {
                    eraseBullet(bulletX[x], bulletY[x]);
                    makeBulletInactive(x);
                }
                else
                {
                    eraseBullet(bulletX[x], bulletY[x]);
                    bulletX[x] = bulletX[x] + 1;
                    printBullet(bulletX[x], bulletY[x]);
                }
            }
        }

        if (bulletDirection[x] == "left")
        {
            if (isBulletActive[x] == true)
            {
                char next = getCharAtxy(bulletX[x] - 1, bulletY[x]);
                if (next != ' ')
                {
                    eraseBullet(bulletX[x], bulletY[x]);
                    makeBulletInactive(x);
                }
                else
                {
                    eraseBullet(bulletX[x], bulletY[x]);
                    bulletX[x] = bulletX[x] - 1;
                    printBullet(bulletX[x], bulletY[x]);
                }
            }
        }
        if (bulletDirection[x] == "up")
        {
            if (isBulletActive[x] == true)
            {
                char next = getCharAtxy(bulletX[x], bulletY[x] - 1);
                if (next != ' ')
                {
                    eraseBullet(bulletX[x], bulletY[x]);
                    makeBulletInactive(x);
                }
                else
                {
                    eraseBullet(bulletX[x], bulletY[x]);
                    bulletY[x] = bulletY[x] - 1;
                    printBullet(bulletX[x], bulletY[x]);
                }
            }
        }
        if (bulletDirection[x] == "down")
        {
            if (isBulletActive[x] == true)
            {
                char next = getCharAtxy(bulletX[x], bulletY[x] + 1);
                if (next != ' ')
                {
                    eraseBullet(bulletX[x], bulletY[x]);
                    makeBulletInactive(x);
                }
                else
                {
                    eraseBullet(bulletX[x], bulletY[x]);
                    bulletY[x] = bulletY[x] + 1;
                    printBullet(bulletX[x], bulletY[x]);
                }
            }
        }
    }
}

void printBullet(int x, int y)
{
    gotoxy(x, y);
    cout << ".";
}
void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void makeBulletInactive(int idx)
{
    isBulletActive[idx] = false;
}

void bulletCollisionWithCaptain()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            if (bulletX[x] + 1 == captainX && (bulletY[x] == captainY || bulletY[x] == captainY + 1 || bulletY[x] == captainY + 2 || bulletY[x] == captainY + 4))
            {
                addScore();
            }
            if (captainX - 1 == bulletX[x] && captainY + 1 == bulletY[x])
            {
                addScore();
            }
            if (bulletY[x] - 1 == captainY + 4 && (bulletX[x] == captainX + 1 || bulletX[x] == captainX + 2 || bulletX[x] == captainX + 3))
            {
                addScore();
            }
            if (bulletY[x] + 1 == captainY && (bulletX[x] == captainX + 1 || bulletX[x] == captainX + 2 || bulletX[x] == captainX + 3))
            {
                addScore();
            }
        }
    }
}

void bulletCollisionWithChief()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            if (bulletX[x] + 1 == chiefX && (bulletY[x] == chiefY || bulletY[x] == chiefY + 1 || bulletY[x] == chiefY + 2 || bulletY[x] == chiefY + 4))
            {
                addScore();
            }
            if (chiefX - 1 == bulletX[x] && chiefY + 1 == bulletY[x])
            {
                addScore();
            }
            if (bulletY[x] - 1 == chiefY + 4 && (bulletX[x] == chiefX + 1 || bulletX[x] == chiefX + 2 || bulletX[x] == chiefX + 3))
            {
                addScore();
            }
            if (bulletY[x] + 1 == chiefY && (bulletX[x] == chiefX + 1 || bulletX[x] == chiefX + 2 || bulletX[x] == chiefX + 3))
            {
                addScore();
            }
        }
    }
}
void bulletCollisionWithCorporal()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            if (bulletX[x] + 1 == corporalX && (bulletY[x] == corporalY || bulletY[x] == corporalY + 1 || bulletY[x] == corporalY + 2 || bulletY[x] == corporalY + 4))
            {
                addScore();
            }
            if (corporalX - 1 == bulletX[x] && corporalY + 1 == bulletY[x])
            {
                addScore();
            }
            if (bulletY[x] - 1 == corporalY + 4 && (bulletX[x] == corporalX + 1 || bulletX[x] == corporalX + 2 || bulletX[x] == corporalX + 3))
            {
                addScore();
            }
            if (bulletY[x] + 1 == corporalY && (bulletX[x] == corporalX + 1 || bulletX[x] == corporalX + 2 || bulletX[x] == corporalX + 3))
            {
                addScore();
            }
        }
    }
}

void addScore()
{
    score++;
}
void printScore()
{
    gotoxy(15, 40);
    cout << "Score: " << score;
}

//  Captain Functions

void printCaptain()
{
    gotoxy(captainX, captainY);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCaptain1[x];
    }
    gotoxy(captainX, captainY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCaptain2[x];
    }
    gotoxy(captainX, captainY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCaptain3[x];
    }
    gotoxy(captainX, captainY + 3);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCaptain4[x];
    }
}

void eraseCaptain()
{
    gotoxy(captainX, captainY);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(captainX, captainY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(captainX, captainY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(captainX, captainY + 3);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
}

void moveCaptain()
{

    if (captainDirection == "up")
    {
        char next = getCharAtxy(captainX, captainY - 1);
        if (next == ' ')
        {
            eraseCaptain();
            captainY = captainY - 1;
            printCaptain();
        }
        if (next == '#')
        {
            captainDirection = "down";
        }
    }
    if (captainDirection == "down")
    {
        char next = getCharAtxy(captainX, captainY + 4);
        if (next == ' ')
        {
            eraseCaptain();
            captainY = captainY + 1;
            printCaptain();
        }
        if (next == '#')
        {
            captainDirection = "up";
        }
    }
}

void generateCaptainBullet()
{
    gotoxy(captainX, captainY + 2);
    cout << "*";
    captainBulletX[captainBulletCount] = captainX;
    captainBulletY[captainBulletCount] = captainY + 2;
    isCaptainBulletActive[captainBulletCount] = true;

    captainBulletCount++;
}
void eraseCaptainBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void makeCaptainBulletInactive(int x)
{
    isCaptainBulletActive[x] = false;
}
void printCaptainBullet(int x, int y)
{
    gotoxy(x, y);
    cout << "*";
}

void moveCaptainBullet()
{
    generateCaptainBullet();
    for (int x = 0; x < captainBulletCount; x++)
    {

        if (isCaptainBulletActive[x] == true)
        {
            char next = getCharAtxy(captainBulletX[x] - 1, captainBulletY[x]);
            if (next != ' ')
            {
                eraseCaptainBullet(captainBulletX[x], captainBulletY[x]);
                makeCaptainBulletInactive(x);
            }
            else
            {
                eraseBullet(captainBulletX[x], captainBulletY[x]);
                captainBulletX[x] = captainBulletX[x] - 1;
                printCaptainBullet(captainBulletX[x], captainBulletY[x]);
            }
        }
    }
}

// Chief functions the intelligent enemy

void printChief()
{
    gotoxy(chiefX, chiefY);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyChief1[x];
    }
    gotoxy(chiefX, chiefY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyChief2[x];
    }
    gotoxy(chiefX, chiefY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyChief3[x];
    }
    gotoxy(chiefX, chiefY + 3);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyChief4[x];
    }
}

void eraseChief()
{
    gotoxy(chiefX, chiefY);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(chiefX, chiefY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(chiefX, chiefY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(chiefX, chiefY + 3);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
}

void moveChief()
{

    int distanceX = (frankX - chiefX);
    int distanceY = (frankY - chiefY);

    if (distanceX > 0)
    {
        char next = getCharAtxy(chiefX + 6, chiefY);
        char next2 = getCharAtxy(chiefX + 6, chiefY + 1);
        char next3 = getCharAtxy(chiefX + 6, chiefY + 2);
        char next4 = getCharAtxy(chiefX + 6, chiefY + 3);

        if (next == ' ' && next2 == ' ' && next3 == ' ' && next4 == ' ')
        {

            eraseChief();
            chiefX = chiefX + 1;
            printChief();
        }
    }
    if (distanceX < 0)
    {
        char next = getCharAtxy(chiefX - 1, chiefY);
        char next2 = getCharAtxy(chiefX - 1, chiefY + 1);
        char next3 = getCharAtxy(chiefX - 1, chiefY + 2);
        char next4 = getCharAtxy(chiefX - 1, chiefY + 3);
        if (next == ' ' && next2 == ' ' && next3 == ' ' && next4 == ' ')
        {
            eraseChief();
            chiefX = chiefX - 1;
            printChief();
        }
    }

    if (distanceY > 0)
    {
        char next = getCharAtxy(chiefX, chiefY + 4);
        if (next == ' ')
        {
            eraseChief();
            chiefY = chiefY + 1;
            printChief();
        }
    }

    if (distanceY < 0)
    {
        char next = getCharAtxy(chiefX, chiefY - 1);
        if (next == ' ')
        {
            eraseChief();
            chiefY = chiefY - 1;
            printChief();
        }
    }
}

void printCorporalRight()
{
    gotoxy(corporalX, corporalY);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCorporalRight1[x];
    }
    gotoxy(corporalX, corporalY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCorporalRight2[x];
    }
    gotoxy(corporalX, corporalY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCorporalRight3[x];
    }
    gotoxy(corporalX, corporalY + 3);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCorporalRight4[x];
    }
}

void printCorporalLeft()
{
    gotoxy(corporalX, corporalY);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCorporalLeft1[x];
    }
    gotoxy(corporalX, corporalY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCorporalLeft2[x];
    }
    gotoxy(corporalX, corporalY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCorporalLeft3[x];
    }
    gotoxy(corporalX, corporalY + 3);
    for (int x = 0; x < 5; x++)
    {
        cout << enemyCorporalLeft4[x];
    }
}

void eraseCorporal()
{
    gotoxy(corporalX, corporalY);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(corporalX, corporalY + 1);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(corporalX, corporalY + 2);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
    gotoxy(corporalX, corporalY + 3);
    for (int x = 0; x < 5; x++)
    {
        cout << " ";
    }
}

void moveCorporal()
{
    if (corporalDirection == "right")
    {
        char next = getCharAtxy(corporalX + 6, corporalY);
        if (next == ' ')
        {
            eraseCorporal();
            corporalX = corporalX + 1;
            printCorporalRight();
        }
        if (next == '#')
        {
            corporalDirection = "left";
        }
    }
    if (corporalDirection == "left")
    {
        char next = getCharAtxy(corporalX - 1, corporalY);
        if (next == ' ')
        {
            eraseCorporal();
            corporalX = corporalX - 1;
            printCorporalLeft();
        }
        if (next == '#')
        {
            corporalDirection = "right";
        }
    }
}