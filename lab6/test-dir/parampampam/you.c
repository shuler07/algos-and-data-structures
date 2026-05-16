#include <stdio.h>
#include <unistd.h>


int main() {
    char name[32];
    printf("what is your name?\n");
    scanf("%s", name);
    
    printf("I know your name!\n");
    sleep(1);
    printf("Your name is...\n");
    sleep(1);
    printf("MAWDWADJWAPKE!\n");
    sleep(1);

    return 0;
}