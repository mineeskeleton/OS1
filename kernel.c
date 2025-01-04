#include "./include/print.h"
#include "./include/input.h"
#include "./include/string.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VIDEO_MEMORY 0xB8000
typedef unsigned int size_t;

#define MAX_FILES 16
#define FILE_NAME_LEN 16
#define MAX_FILE_SIZE 512

typedef struct {
    char name[FILE_NAME_LEN];
    char data[MAX_FILE_SIZE];
    int size;
    int used;
} File;

File file_table[MAX_FILES];

void init_fs() {
    for (int i = 0; i < MAX_FILES; i++) {
        file_table[i].used = 0;
    }
}

int create_file(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!file_table[i].used) {
            file_table[i].used = 1;
            strncpy(file_table[i].name, name, FILE_NAME_LEN - 1);
            file_table[i].size = 0;
            return i;
        }
    }
    return -1;
}

int str_to_int(const char *str, int *out) {
    if (str == 0 || *str == 0) {
        return 0;
    }

    int result = 0;
    int is_negative = 0;

    if (*str == '-') {
        is_negative = 1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str != 0) {
        if (*str < '0' || *str > '9') {
            return 0;
        }

        int digit = *str - '0';
        result = result * 10 + digit;
        str++;
    }

    if (is_negative) {
        result = -result;
    }

    *out = result;
    return 1;
}

void int_to_str(int num, char *str) {
    int is_negative = 0;
    int i = 0;

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int write_file(int file_index, const char *data, int size) {
    if (file_index < 0 || file_index >= MAX_FILES || !file_table[file_index].used) {
        return -1;
    }

    int write_size = (size > MAX_FILE_SIZE) ? MAX_FILE_SIZE : size;
    memcpy(file_table[file_index].data, data, write_size);
    file_table[file_index].size = write_size;
    return write_size;
}

int read_file(int file_index, char *buffer, int size) {
    if (file_index < 0 || file_index >= MAX_FILES || !file_table[file_index].used) {
        return -1;
    }

    int read_size = (size > file_table[file_index].size) ? file_table[file_index].size : size;
    memcpy(buffer, file_table[file_index].data, read_size);
    return read_size;
}

int delete_file(int file_index) {
    if (file_index < 0 || file_index >= MAX_FILES || !file_table[file_index].used) {
        return -1;
    }

    file_table[file_index].used = 0;
    return 0;
}

int find_file(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(file_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void kernel_main() {
    char buffer[2048];
    int cursor_row = 0;

    clear_screen();
    output("Welcome to NoobOS!\n");

    while (strcmp(buffer, "pwroff") != 0) {
        output("\nOS1-->: ");
        input(buffer, 2048);

        if (strncmp(buffer, "sinput", 6) == 0) {
            char *message = buffer + 7;
            output(message);

        } else if (strcmp(buffer, "") == 0) {
        } else if (strcmp(buffer, "clear") == 0) {
            clear_screen();
        } else if (strcmp(buffer, "write") == 0) {

            output("\nname of your file: ");
            input(buffer, 2048);

            int file_id = create_file(buffer);

            output("\nData of your file: ");
            input(buffer, 2048);

            write_file(file_id, buffer, strlen(buffer));

        } else if (strcmp(buffer, "read") == 0) {

            output("\nEnter the name of your file: ");
            input(buffer, 12);

            char file_buffer[1024];
            int file_id = find_file(buffer);

            if (file_id != -1) {
                int read_size = read_file(file_id, file_buffer, sizeof(file_buffer));
                output("\nFile contents:\n");
                output(file_buffer);
            } else {
                output("\nFile not found.\n");
            }

        } else if (strcmp(buffer, "delete") == 0) {
            output("\nEnter the name of the file to delete: ");
            input(buffer, 12);
            int file_id = find_file(buffer);
            if (file_id != -1) {
                delete_file(file_id);
                output("\nFile deleted successfully.\n");
            } else {
                output("\nFile not found.\n");
            }
        } else if (strcmp(buffer, "clear") == 0) {
            clear_screen();
        } else if (strcmp(buffer, "calc") == 0) {

            output("\nSelect First Number:");
            input(buffer, 2048);
            int *nmb1;
            str_to_int(buffer, nmb1);
            output("\nSelect Second Number:");
            input(buffer, 2048);
            int *nmb2;
            str_to_int(buffer, nmb2);
            output("\nSelect Operation(1.Add-2.Subtract-3.Multiply-4.Divide):");
            input(buffer, 2048);
            int *Operation;
            str_to_int(buffer, Operation);
            if (*Operation == 1) {
                int result = *nmb1 + *nmb2;
                char resultstr[8048];
                int_to_str(result, resultstr);
                output("\nResult: ");
                output(resultstr);
                output("\n");
            }
            if (*Operation == 2) {
                int result = *nmb1 - *nmb2;
                char resultstr[8048];
                int_to_str(result, resultstr);
                output("\nResult: ");
                output(resultstr);
                output("\n");
            }
            if (*Operation == 3) {
                int result = *nmb1 * *nmb2;
                char resultstr[8048];
                int_to_str(result, resultstr);
                output("\nResult: ");
                output(resultstr);
                output("\n");
            }
            if (*Operation == 4) {
                int result = *nmb1 / *nmb2;
                char resultstr[8048];
                int_to_str(result, resultstr);
                output("\nResult: ");
                output(resultstr);
                output("\n");
            }

        } else {
            output("\nInvalid Command.\n");
        }

        cursor_row++;
        if (cursor_row >= SCREEN_HEIGHT) {
            scroll_screen();
            cursor_row = SCREEN_HEIGHT - 1;
        }
    }
}
