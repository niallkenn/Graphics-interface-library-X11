#include "utils.h"
#include "unistd.h"

int main(void) {
    Canvas* c = create_canvas(100, 100);

    update_canvas(c);

    sleep(1);
    close_canvas(c);
    
    return 0;
}