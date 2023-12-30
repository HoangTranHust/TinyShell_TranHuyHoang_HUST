#include "CommandLib.h"

// Tran Huy Hoang 20210386 - Hanoi University of Science and Technology
// gcc -o TinyShell TinyShell.c -lreadline && ./TinyShell

// Init Tiny Shell
void initShell() {
    clear();
    printf("\n\n******************************************");
    printf("\n\n****WELCOME TO MY LINUX TINY SHELL****");
    printf("\n\n****Tran Huy Hoang 20210386****");
    printf("\n\n******************************************");
    sleep(0.5);
    clear();
}

// Get input from user
int getInput(char *str) {
    char *buf;
    buf = readline(":TINY_SHELL>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else
        return 1;
}

int main() {
    initShell();
    handleCtrl_C();
    while (1) {
        printDir();
        char str[100];
        getInput(str);
        processCmd(str);     
    }
    return 1;
}
