#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char* GIFT = "GIMME GIMME SHELL /bin/sh";

void pwn()
{
    char buf[0x100-0x16];

    printf("Enter your comment:");
    scanf("%256s", buf);
    printf("Got shell?\n");
}

int main()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    pwn();
}

void backd00r()
{
    execve("/bin/sh", 0, 0);
}
