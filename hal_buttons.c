#include "hal_buttons.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void HAL_Buttons_Init(void) {
    printf("[HW] Buttons Initialized (Press '1' for Mode, '2' for Manual Water).\n");
}

bool HAL_Button1_IsPressed(void) {
    if (kbhit()) {
        char c = getchar();
        if (c == '1') return true;
    }
    return false;
}

bool HAL_Button2_IsPressed(void) {
    if (kbhit()) {
        char c = getchar();
        if (c == '2') return true;
    }
    return false;
}