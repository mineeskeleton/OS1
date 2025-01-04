#include "../include/input.h"
#include "../include/print.h"

#define KEYBOARD_PORT 0x60
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

const char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b', 
    '\t',
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0,
    '*',
    0,
    ' ',
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0,
    0,
    0,
    0,
    0,
    0, 0, 0,
    0,
    0,
};

const char scancode_to_ascii_shift[] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',
    '(', ')', '_', '+', '\b',
    '\t',
    'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
    '"', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N',
    'M', '<', '>', '?', 0,
    '*',
    0,
    ' ',
    0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0,
    0,
    0,
    0,
    0,
    0, 0, 0,
    0,
    0,
};

char get_char() {
    static int shift = 0;
    char c = 0;
    uint8_t scancode = 0;

    while (scancode == 0) {
        scancode = inb(KEYBOARD_PORT);
    }

    if (scancode & 0x80) {
        scancode -= 0x80;
        if (scancode == 0x2A || scancode == 0x36) {
            shift = 0;
        }
        return 0;
    }

    if (scancode == 0x2A || scancode == 0x36) {
        shift = 1;
    } else {
        if (shift) {
            c = scancode_to_ascii_shift[scancode];
        } else {
            c = scancode_to_ascii[scancode];
        }
    }

    while (inb(KEYBOARD_PORT) != (scancode | 0x80));

    return c;
}

void input(char* buffer, int max_length) {
    int i = 0;
    char c;

    while (i < max_length - 1) {
        c = get_char();

        if (c == 0) {
            continue;
        }

        if (c == '\n') {
            break;
        }

        if (c == '\b') {
            if (i > 0) {
                i--;
            }
        } else {
            buffer[i++] = c;
            output(&c);
            buffer[i] = '\0';
        }
    }

    buffer[i] = '\0';
    output("\n");
}
