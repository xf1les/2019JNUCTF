#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char* GIFT = "GIMME GIMME SHELL /bin/sh";

void pwn()
{
    struct __attribute__ ((packed)) {
        char name[0x18];
        char comment[0x100-0x8];
        long password;
    } locals;

    memset(&locals, 0, 0x110);

    locals.password = 0xabc1337;

    printf("Enter your name:");
    read(0, locals.name, 0x18);
    printf("Enter your comment:"); 
    read(0, locals.comment, 0x100);
    
    printf("Hello, %s, your comment is %s.\n", locals.name, locals.comment);
    if(locals.password == 0x1337abc) {
        printf("you are an eligible user to obtain shell prompt.\n");
        system("/bin/sh");
    } else {
        printf("you don't have permission to access shell.\n");
    }
}

int main()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    pwn();
}

