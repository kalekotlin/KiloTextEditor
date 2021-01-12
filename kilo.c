#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
    // Set the terminal attributes to the default, non-raw mode.
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);

    // Register this function to be called as the program exits.
    atexit(disableRawMode);

    // Termios struct holding flags. Set to the default struct.
    struct termios raw = orig_termios;

    // "c_lflag" is used for local, or misc., flags.
    // Use the NOT operater to flip the binary "...00001000" to "...11110111". 
    // Use the AND operateor to flip the fourth bit in the flags field to become 0.
    /**
     * "c_lflag" is used for local, or misc., flags.
     * Use the NOT operater to flip the binary "...00001000" to "...11110111
     * Use the AND operateor to flip the fourth bit in the flags field to become 0.
     * 
     * Turn OFF Echo and Canonical Mode.
    */
    raw.c_lflag &= ~(ECHO | ICANON);

    // Applies the attributes in the struct to the terminal.
    // "TCSAFLUSH" arg waits for pending output to be written to the terminal. 
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    char c;
    // Read 1 byte at a time from from the standard input into the variable c.
    while (
        read(STDIN_FILENO, &c, 1) == 1 
        && c != 'q'
    );

    return 0;
}