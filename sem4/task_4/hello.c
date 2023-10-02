#include <stdio.h>
#include <string.h>

void print_string(char* s);
void print_file(char* name);

// Вывести содержимое всех файлов переданных как аргумент командной строки
int main(int argc, char *argv[]){
    for (int count = 0 ; count < argc; count++)
    {
	    print_file(argv[count]);
    }
    return 0;
}


// Вывести содержимое файла
// #include <stdio.h>
// #include <string.h>
// #define _CRT_SECURE_NO_WARNINGS
// void print_string(char* s);
// void print_file(char* name);

// int main() {
//     char filename[128];
//     print_string("Please enter file name:\n");
//     if (fgets(filename, 128, stdin) != NULL) {
//         filename[strlen(filename) - 1] = '\0';
//         printf("filename = \"%s\"", filename);
//     }
//     print_file(filename);
//     return 0;
// }