#include <stdlib.h>
#include <stdio.h>

const char* GIFT = "GIMME GIMME SHELL /bin/sh";

void pwn()
{
    char buf[0x100-0x16];

    printf("Enter your comment:");
    scanf("%s", buf);
    printf("Got shell?");

}

void backdoor()
{
    system("echo FLAG");
}

int main()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    pwn();
}

