#include<stdio.h>
#include "pthread_unistd.h"

void welcome()
{
    unsigned int mSeconds = 100000;
    printf("_________________________________________________________________________________________\n");

    printf("__        __           _         __  __           _              _                 \n");
    usleep(mSeconds);
    printf("\\ \\      / /   _ _ __ | | __    |  \\/  |_   _ ___(_) ___        / \\   _ __  _ __   \n");
    usleep(mSeconds);
    printf(" \\ \\ /\\ / / | | | '_ \\| |/ /    | |\\/| | | | / __| |/ __|      / _ \\ | '_ \\| '_ \\  \n");
    usleep(mSeconds);
    printf("  \\ V  V /| |_| | | | |   <     | |  | | |_| \\__ \\ | (__      / ___ \\| |_) | |_) | \n");
    usleep(mSeconds);
    printf("   \\_/\\_/  \\__, |_| |_|_|\\_\\    |_|  |_|\\__,_|___/_|\\___|    /_/   \\_\\ .__/| .__/  \n");
    usleep(mSeconds);
    printf("           |___/                                                     |_|   |_|     \n");
    printf("_________________________________________________________________________________________\n");
    usleep(1000000);

}

int main()
{
    welcome();
    return 0;
}