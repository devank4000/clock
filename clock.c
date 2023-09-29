#include <curses.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

const bool number[][15] =
{
     {1,1,1,1,0,1,1,0,1,1,0,1,1,1,1}, /* 0 */
     {0,0,1,0,0,1,0,0,1,0,0,1,0,0,1}, /* 1 */
     {1,1,1,0,0,1,1,1,1,1,0,0,1,1,1}, /* 2 */
     {1,1,1,0,0,1,1,1,1,0,0,1,1,1,1}, /* 3 */
     {1,0,1,1,0,1,1,1,1,0,0,1,0,0,1}, /* 4 */
     {1,1,1,1,0,0,1,1,1,0,0,1,1,1,1}, /* 5 */
     {1,1,1,1,0,0,1,1,1,1,0,1,1,1,1}, /* 6 */
     {1,1,1,0,0,1,0,0,1,0,0,1,0,0,1}, /* 7 */
     {1,1,1,1,0,1,1,1,1,1,0,1,1,1,1}, /* 8 */
     {1,1,1,1,0,1,1,1,1,0,0,1,1,1,1}, /* 9 */
};           

struct cursor_position {
    int x,y;
} pos;

void init() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

void center() {
    pos.y = (LINES-5)/2;
    pos.x = (COLS-51)/2;
    move(pos.y,pos.x);
}

void draw_num(int n)
{
    for(int i = 0; i < 15; i++) {
        if(number[n][i] == 0) {
            printw("  ");
        }
        else {
            printw("██");
        }
        pos.x += 2;
        
        if(i % 3 == 2) {
            pos.x -= 6;
            pos.y += 1;
            move(pos.y, pos.x);
        }
    }
    pos.x += 7;
    pos.y -= 5;
    move(pos.y, pos.x);
}

void draw_colon() {
    pos.x += 1;
    pos.y += 1;
    move(pos.y, pos.x);
    printw("██");
    pos.y += 2;
    move(pos.y, pos.x);
    printw("██");
    pos.x += 4;
    pos.y -= 3;
    move(pos.y, pos.x);
}

void draw_blank() {
    pos.x += 6;
    move(pos.y, pos.x);
}

int main() 
{
    init();

    time_t rawtime;
    struct tm * timeinfo;

    while(true) {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        
        clear();
        center();

        draw_num(timeinfo->tm_hour/10);
        draw_num(timeinfo->tm_hour%10);
        
        draw_colon();
        
        draw_num(timeinfo->tm_min/10);
        draw_num(timeinfo->tm_min%10);

        draw_colon();

        draw_num(timeinfo->tm_sec/10);
        draw_num(timeinfo->tm_sec%10);

        refresh();
        sleep(1);
    }

    endwin();
}
