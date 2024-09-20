#include <stdio.h>

int main() {
    char operation[10];
    char code[20];
    char title[100];
    char author[100];
    int year;

    char inputLine[] = "ADD OL29969W; Impro; Keith Johnstone; 1979";

    // Parse the line using sscanf
    sscanf(inputLine, "%s %[^;]; %[^;]; %[^;]; %d", operation, code, title, author, &year);

    // Output the parsed data
    printf("Operation:%s\n", operation);
    printf("Code: %s\n", code);
    printf("Title: %s\n", title);
    printf("Author: %s\n", author);
    printf("Year: %d\n", year);

    return 0;
}