#include <stdio.h>
#include <termios.h>
#include <unistd.h> /*sleep(10); 10 secondes et sur windows c'est windows.h avec Sleep();*/
#include <stdlib.h>
/*#include <ncurses.h> pour aller plus loin avec la console*/
#include <time.h>
#include <iostream>
using namespace std;

/*attention avec celle de ncurses si on utilise ncurses il y aura des conflits de nom*/
int getch(void)
{

    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
struct termios new_setting;
int kbhit(void)
{

    unsigned char ch;
    int nread;
    struct termios old;
    tcgetattr(0, &old);
    if (old.c_oflag != new_setting.c_oflag)
    {
        new_setting.c_oflag = old.c_oflag;
    }
    //if (peek_character != -1)
    //  return 1;
    new_setting.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &new_setting);
    nread = read(0, &ch, 1);
    new_setting.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_setting);
    if (nread == 1)
    {
        ungetc(ch, stdin);
        //peek_character = ch;
        return 1;
    }
    return 0;
}