#include <ncurses.h>
#include <string>

using namespace std;

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int height = 28;
    int width = 88;
    int starty = (LINES - height) / 4;
    int startx = (COLS - width) / 4;

    WINDOW * win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Dtlsh Commands");
    mvwprintw(win, 3, 1, "1.help - output table with commands; 2.ls - output files in this directory");
    mvwprintw(win, 4, 1, "3.pwd - output path to the directory; 4.cat - output content in file.");
    mvwprintw(win, 5, 1, "5.rm - remove directory or file; 6.touch - add file; 7.mkdir - add directory");
    mvwprintw(win, 6, 1, "8.cd - change directory; 9.dex - small editor. 10.exit - exit dltsh");
    mvwprintw(win, 7, 1, "11.ver - output dltsh version; 12.clear - clear screen");
    mvwprintw(win, 8, 1, "12.calc - calculator; 13.dltinfo - like neofetch, but for dltsh");
    mvwprintw(win, 10, 1, "Dltsh Commands on rust");
    mvwprintw(win, 11, 1, "1.dexide - dex rewritten on rust and without crates; 1.calc - calculator on rust");
    mvwprintw(win, 12, 1, "3.clocks");

    mvwprintw(win, 14, 1, "Enter 'q' for exit");
    wrefresh(win);
    while (wgetch(win) != 'q') {}

    delwin(win);
    endwin();
    return 0;
}
