#include<stdio.h>
#include "wynk.c"
#include "pthread_unistd.h"

void welcome()
{
    unsigned int mSeconds = 100000;
    printf("________________________________________________________________________________________\n");
    printf("\033[0;31m");
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
    printf("\033[0m");
    printf("________________________________________________________________________________________\n\n");
    usleep(1000000);
}

void menuSignin()
{
    printf("\033[0;32m");
    printf("-----------------------");
    printf("\n         MENU\n");
    printf("-----------------------\n");
    printf("1: Log in\n");
    printf("2: Sign In\n");
    printf("-----------------------\n");
    printf("\033[0m");
}

void menu()
{
    printf("\033[0;93m");
    printf("-----------------------");
    printf("\n         MENU\n");
    printf("-----------------------\n");
    printf("\033[0m");
    printf("\n1.Add song to the playlist\n\n");
    printf("2.Display all songs of the playlist\n\n");
    printf("3.Play first song of playlist\n\n");
    printf("4.Play last song of playlist\n\n");
    printf("5.Display songs by language\n\n");
    printf("6.Play previous song\n\n");
    printf("7.Play next song\n\n");
    printf("8.Count the number of songs in the playlist\n\n");
    printf("9.Search a song and play\n\n");
    printf("10.Delete a song from the playlist\n\n");
    printf("11.Exit\n");
}

int main()
{
    int choice, logstatus=0, x;
    welcome();
    readData();
    while(logstatus!=1)
    {
        menuSignin();
        scanf("%d", &x);
        switch (x)
        {
        case 1:
            logstatus=login();
            break;
        
        case 2:
            registration();
            break;

        default: printf("Please enter valid input..\n");
            break;
        }
    }
    menu();
    printf("\nEnter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            insert_song();
            break;

        case 2:
            display();
            break;

        case 3:
            curr_song = play_first_song();
            break;

        case 4:
            curr_song = play_last_song();
            break;

        case 5:
            display_by_language();
            break;

        case 6:
            curr_song = play_prev(curr_song);
            break;

        case 7:
            curr_song = play_next(curr_song);
            break;

        case 8:
            printf("%d",count());
            break;

        case 9:
            curr_song = search_and_play();
            break;

        case 10:
            delete_song();
            break;

        case 11:
            exit(0);
        }


    return 0;
}