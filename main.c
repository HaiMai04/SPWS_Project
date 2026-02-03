#include "spws_controller.h"
#include <unistd.h>

int main(void) {
    SPWS_Init();

    while (1) {
        SPWS_Run();
        sleep(1); 
    }
    return 0;
}