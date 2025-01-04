#define VGA_HEIGHT 25 // screen height
#define VGA_WIDTH 80  // screen width

void clear_screen(void);
void handle_next_line();
void output(const char* msg);
void scroll_screen(void);
