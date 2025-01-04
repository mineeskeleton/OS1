#include "../include/print.h"
#include "../include/input.h"

char *vgaBuff = (char *)0xb8000;
int vgaBuffPos = 0;

void clear_screen(void)
{
    int screen_size = (VGA_WIDTH * 2) * VGA_HEIGHT;

    for (int i = 0; i < screen_size; i++)
    {
        vgaBuff[i] = 0;
    }
    vgaBuffPos = 0;
}

void scroll_screen(void)
{
    for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH * 2; i++)
    {
        vgaBuff[i] = vgaBuff[i + VGA_WIDTH * 2];
    }

    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH * 2; i < VGA_HEIGHT * VGA_WIDTH * 2; i += 2)
    {
        vgaBuff[i] = ' ';
        vgaBuff[i + 1] = 15;
    }

    vgaBuffPos = (VGA_HEIGHT - 1) * VGA_WIDTH * 2;
}

void handle_next_line(void)
{
    int current_row = vgaBuffPos / (VGA_WIDTH * 2);
    if (current_row >= VGA_HEIGHT - 1)
    {
        scroll_screen();
    }
    else
    {
        vgaBuffPos = (current_row + 1) * VGA_WIDTH * 2;
    }
}

void output(const char *msg)
{
    int i = 0;

    while (msg[i] != '\0')
    {
        if (msg[i] == '\n')
        {
            handle_next_line();
        }
        else
        {
            vgaBuff[vgaBuffPos] = msg[i];
            vgaBuff[vgaBuffPos + 1] = 15;
            vgaBuffPos += 2;

            if ((vgaBuffPos / 2) % VGA_WIDTH == 0)
            {
                handle_next_line();
            }
        }
        i++;
    }
}

