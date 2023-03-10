#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pthread_unistd.h"

struct node
{
    struct node *prev;
    struct node *next;
    char song[30];
    char artist[30];
    char language[20];
    int likes;
    int year;
};

struct name
{
    char song[30];
};

struct search
{
    struct name array[100];
};

struct login
{
    char name[30];
    char username[30];
    char password[30];
};

struct node *head=NULL,*temp=NULL, *curr_song=NULL, *temp1=NULL, *temp2=NULL, *tail=NULL, *head2=NULL;
struct search x;
int f=0;

void registration()
{
    struct login l;
    FILE *log;
    log = fopen("users.txt", "w");
    if(!log)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }
    printf("Enter your name: ");
    fflush(stdin);
    scanf("%[^\n]s",l.name);
    printf("Username: ");
    fflush(stdin);
    scanf("%[^\n]s",l.username);
    printf("Password: ");
    fflush(stdin);
    scanf("%[^\n]s",l.password);
    fprintf(log,"\n%s %s %s",l.name, l.username, l.password);
    fclose(log);
    printf("\nConfirming details...\n...\nWelcome, %s!\n\n",l.name);
    printf("\nRegistration Successful!\n");
}

int login()
{
    char username[30],password[20], u[30], p[30], x[30];
    FILE *log;

    log = fopen("users.txt","r");
    if (!log)
    {
        fputs("Please sign up before logging in", stderr);
        exit(1);
    }

    printf("\nPlease Enter your login credentials below\n\n");
    printf("Username:  ");
    fflush(stdin);
    scanf("%[^\n]s",username);
    printf("\nPassword: ");
    fflush(stdin);
    scanf("%[^\n]s",password);

    while(!feof(log))
    {
        fscanf(log,"%s%s%s",x,u,p);
        if(strcmp(username,u)==0 && strcmp(password,p)==0)
        {
            printf("\nSuccessful Login\n");
            return 1;
        }
        else
        {
            printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
        }
    }

    fclose(log);

    return 0;
}

void writeData()
{
    if(head)
    {
        FILE *fp = fopen("playlist.txt", "w");
        temp = head;
        do
        {
            fprintf(fp,"\n%s %s %s %d %d",temp->song, temp->artist, temp->language, temp->likes, temp->year);
            temp = temp->next;
        }
        while (temp!=head);
        fclose(fp);
    }
    else
    {
        remove("playlist.txt");
    }
}

void readData2()
{
    char s[30], a[30], l[20];
    int x, y;
    FILE *fp=NULL;

    fp=fopen("Details.txt","r");

    if(fp==NULL)
    {
        return;
    }
    else
    {

        do
        {
            fscanf(fp,"%s%s%s%d%d",s,a,l,&x,&y);

            if(head2==NULL)
            {
                head2 = (struct node *)malloc(sizeof(struct node));
                strcpy(head2->song,s);
                strcpy(head2->artist,a);
                strcpy(head2->language,l);
                head2->likes = x;
                head2->year = y;
                head2->next = head2;
                head2->prev = head2;
            }
            else
            {
                struct node *newnode;
                newnode = (struct node *)malloc(sizeof(struct node));
                temp=head2;
                while(temp->next!=head2)
                {
                    temp=temp->next;
                }
                strcpy(newnode->song,s);
                strcpy(newnode->artist,a);
                strcpy(newnode->language,l);
                newnode->likes = x;
                newnode->year = y;
                newnode->next=head2;
                head2->prev=newnode;
                temp->next=newnode;
                newnode->prev=temp;
            }
        }
        while (!feof(fp));

        fclose(fp);
    }
}

void readData()
{
    char s[30], a[30], l[20];
    int x, y;
    FILE *fp=NULL;

    fp=fopen("playlist.txt","r");

    if(fp==NULL)
    {
        return;
    }
    else
    {

        do
        {
            fscanf(fp,"%s%s%s%d%d",s,a,l,&x,&y);

            if(head==NULL)
            {
                head = (struct node *)malloc(sizeof(struct node));
                strcpy(head->song,s);
                strcpy(head->artist,a);
                strcpy(head->language,l);
                head->likes = x;
                head->year = y;
                head->next = head;
                head->prev = head;
            }
            else
            {
                struct node *newnode;
                newnode = (struct node *)malloc(sizeof(struct node));
                temp=head;
                while(temp->next!=head)
                {
                    temp=temp->next;
                }
                strcpy(newnode->song,s);
                strcpy(newnode->artist,a);
                strcpy(newnode->language,l);
                newnode->likes = x;
                newnode->year = y;
                newnode->next=head;
                head->prev=newnode;
                temp->next=newnode;
                newnode->prev=temp;
            }
        }
        while (!feof(fp));

        fclose(fp);
    }
}

struct node *getnode()
{
    char s[30], a[30], l[20], SONG[30];
    int x, y, flag=0;
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));

    printf("\nEnter the name of the song: ");
    fflush(stdin);
    scanf("%[^\n]s",SONG);

    FILE *fp = fopen("Details.txt", "r");

    do
    {
        fscanf(fp,"%s%s%s%d%d",s,a,l,&x,&y);
        if(strcasecmp(SONG,s)==0)
        {
            flag=1;
            strcpy(newnode->song,s);
            strcpy(newnode->artist,a);
            strcpy(newnode->language,l);
            newnode->likes = x;
            newnode->year = y;
            newnode->prev = newnode->next = newnode;
        }
    }
    while (!feof(fp));
    if(!flag)
    {
        printf("Song not found :(\n");
        return NULL;
    }
    fclose(fp);
    return newnode;
}

void insert_song()
{
    int flag=0;
    struct node *newnode=getnode();
    if(!newnode)
    {
        printf("Cannot insert\n");
        return;
    }
    if(head==NULL)
    {
        head=newnode;
    }
    else if(head->next==head)
    {
        if(!strcasecmp(head->song,newnode->song))
        {
            printf("\nSong already in the playlist");
            newnode=NULL;
            free(newnode);
            flag=1;
        }
        if(flag==0)
        {
            newnode->next=head;
            head->prev=newnode;
            head->next=newnode;
            newnode->prev=head;
        }
    }
    else
    {
        temp=head;
        do
        {
            if(!strcasecmp(temp->song,newnode->song))
            {
                printf("\nSong already in the playlist");
                newnode=NULL;
                free(newnode);
                flag=1;
                break;
            }
            temp=temp->next;
        }
        while(temp!=head);
        temp=temp->prev;
        if(flag==0)
        {
            newnode->next=head;
            head->prev=newnode;
            temp->next=newnode;
            newnode->prev=temp;
        }
    }
    writeData();
}

void delete_song()
{
    int d=0;
    char song[30];
    printf("\nEnter the name of the song you want to delete : ");
    fflush(stdin);
    scanf("%[^\n]s",song);

    if(head==NULL)
    {
        printf("\nThe playlist is empty");
    }
    else if(head->next == head)
    {
        temp=head;
        if(!strcasecmp(song,temp->song))
        {
            printf("\n%s deleted",song);
            d=1;

            if(curr_song==temp)
            {
                curr_song = NULL;
            }

            head=NULL;
            free(temp);
        }
    }
    else
    {

        if(!strcasecmp(head->song,song))
        {
            temp=head;

            if(curr_song==temp)
            {
                curr_song=NULL;
            }
            temp1=temp->prev;
            temp2=temp->next;

            temp1->next=temp2;
            temp2->prev=temp1;
            temp->next=NULL;
            temp->prev=NULL;

            temp=NULL;
            free(temp);

            head=temp2;

            printf("\n%s deleted",song);
            d=1;
        }

        else
        {
            temp=head->next;
            do
            {
                if(!strcasecmp(temp->song,song))
                {
                    if(curr_song==temp)
                    {
                        curr_song=NULL;
                    }
                    temp1=temp->prev;
                    temp2=temp->next;

                    temp1->next=temp2;
                    temp2->prev=temp1;
                    temp->next=NULL;
                    temp->prev=NULL;

                    temp=NULL;
                    free(temp);

                    printf("\n%s deleted",song);
                    d=1;
                    break;
                }

                temp=temp->next;

            }
            while(temp!=head);
        }
    }
    writeData();
}

void display_playlist()
{
    if(head==NULL)
    {
        printf("\nThe playlist is empty");
    }
    else
    {
        temp=head;
        while(temp->next!=head)
        {
            printf("-----------------------\n");
            printf("Song : %s\n",temp->song);
            printf("Artist : %s\n",temp->artist);
            printf("Language : %s\n",temp->language);
            printf("Likes : %d\n",temp->likes);
            printf("Year : %d\n\n",temp->year);
            printf("-----------------------\n");
            temp=temp->next;
        }
        printf("-----------------------\n");
        printf("Song : %s\n",temp->song);
        printf("Artist : %s\n",temp->artist);
        printf("Language : %s\n",temp->language);
        printf("Likes : %d\n",temp->likes);
        printf("Year : %d\n\n",temp->year);
        printf("-----------------------\n");
    }
}

void display()
{
    if(head2==NULL)
    {
        printf("\nThe playlist is empty");
    }
    else
    {
        temp=head2;
        while(temp->next!=head2)
        {
            printf("-----------------------\n");
            printf("Song : %s\n",temp->song);
            printf("Artist : %s\n",temp->artist);
            printf("Language : %s\n",temp->language);
            printf("Likes : %d\n",temp->likes);
            printf("Year : %d\n\n",temp->year);
            printf("-----------------------\n");
            temp=temp->next;
        }
        printf("-----------------------\n");
        printf("Song : %s\n",temp->song);
        printf("Artist : %s\n",temp->artist);
        printf("Language : %s\n",temp->language);
        printf("Likes : %d\n",temp->likes);
        printf("Year : %d\n\n",temp->year);
        printf("-----------------------\n");

    }
}

struct node *play_first_song()
{
    if(head==NULL)
    {
        printf("\nThe playlist is empty");
        return NULL;
    }
    else
    {
        temp = head;
        curr_song = temp;
        printf("\nNow Playing : %s",temp->song);
        return temp;
    }
}

struct node *play_last_song()
{
    if(head==NULL)
    {
        printf("\nThe playlist is empty");
        return NULL;
    }
    else
    {
        temp = head;
        curr_song = temp->prev;
        printf("\nNow Playing : %s",(temp->prev)->song);
        return (temp->prev);
    }
}

void display_by_language()
{
    char language[20];
    printf("\nEnter the language : ");
    fflush(stdin);
    scanf("%[^\n]s",language);

    if(head==NULL)
    {
        printf("\nThe playlist is empty");
    }
    else
    {
        temp=head;
        while(temp->next!=head)
        {
            if(!strcasecmp(language,temp->language))
            {
                printf("\n%s",temp->song);
            }
            temp=temp->next;
        }
        if(!strcasecmp(language,temp->language))
        {
            printf("\n%s",temp->song);
        }
    }
}

struct node *play_prev(struct node *curr_song)
{
    if(head==NULL)
    {
        printf("\nThe playlist is empty");
        return NULL;
    }
    if(curr_song==NULL)
    {
        printf("\nPlay a song first");
        return NULL;
    }
    else
    {
        temp=head;
        while(1)
        {
            if(!strcasecmp(temp->song,curr_song->song))
            {
                printf("\nNow Playing : %s",(temp->prev)->song);
                break;
            }
            temp=temp->next;
        }
        return (temp->prev);
    }
}

struct node *play_next(struct node *curr_song)
{
    if(head==NULL)
    {
        printf("\nThe playlist is empty");
        return NULL;
    }
    if(curr_song==NULL)
    {
        printf("\nPlay a song first");
        return NULL;
    }
    else
    {
        temp=head;
        while(1)
        {
            if(!strcasecmp(temp->song,curr_song->song))
            {
                printf("\nNow Playing : %s",(temp->next)->song);
                break;
            }
            temp=temp->next;
        }
        return (temp->next);
    }
}

int count()
{
    int c=0;
    if(head==NULL)
    {
        return 0;
    }
    else
    {
        temp=head;
        while(temp->next!=head)
        {
            c++;
            temp=temp->next;
        }
        c++;
        return c;
    }
}

struct node *search_and_play()
{
    unsigned int mSeconds = 100000;
    int found=0;
    char song[30];
    printf("\nEnter the name of the song you want to play : ");
    fflush(stdin);
    scanf("%[^\n]s",song);

    strcpy(x.array[f].song,song);
    f++;

    if(head==NULL)
    {
        printf("\nThe playlist is empty");
        return NULL;
    }
    else
    {
        temp=head;
        while(temp->next!=head)
        {
            if(!strcasecmp(song,temp->song))
            {
                printf("\033[0;34m");
                printf("\n▁ ▂ ▄ ▅ ▆ ▇ █ Now Playing █ ▇ ▆ ▅ ▄ ▂ ▁\n %s\n",temp->song);
                printf("\033[0m");
                usleep(mSeconds);
                usleep(1000000);

                found = 1;
                break;
            }
            temp=temp->next;
        }
        if(!found)
        {
            if(!strcasecmp(song,temp->song))
            {
                printf("\033[0;34m");
                printf("\n▁ ▂ ▄ ▅ ▆ ▇ █ Now Playing █ ▇ ▆ ▅ ▄ ▂ ▁\n %s\n",temp->song);
                printf("\033[0m");
                usleep(mSeconds);
                usleep(1000000);

                found = 1;
            }
        }

        if(!found)
        {
            printf("\nSong not found in the playlist");
            return curr_song;

        }
        else
        {
            return temp;
        }

    }
}

void search_and_play2()
{
    unsigned int mSeconds = 100000;
    int found=0;
    char song[30];
    printf("\nEnter the name of the song you want to play : ");
    fflush(stdin);
    scanf("%[^\n]s",song);

    strcpy(x.array[f].song,song);
    f++;

    if(head2==NULL)
    {
        printf("\nThe playlist is empty");
    }
    else
    {
        temp=head2;
        while(temp->next!=head2)
        {
            if(!strcasecmp(song,temp->song))
            {
                printf("\033[0;34m");
                printf("\n▁ ▂ ▄ ▅ ▆ ▇ █ Now Playing █ ▇ ▆ ▅ ▄ ▂ ▁\n %s\n",temp->song);
                printf("\033[0m");
                usleep(mSeconds);
                usleep(1000000);

                found = 1;
                break;
            }
            temp=temp->next;
        }
        if(!found)
        {
            if(!strcasecmp(song,temp->song))
            {
                printf("\033[0;34m");
                printf("\n▁ ▂ ▄ ▅ ▆ ▇ █ Now Playing █ ▇ ▆ ▅ ▄ ▂ ▁\n %s\n",temp->song);
                printf("\033[0m");
                usleep(mSeconds);
                usleep(1000000);

                found = 1;
            }
        }

        if(!found)
        {
            printf("\nSong not found in the playlist");
        }
    }
}

void display_curr_song()
{
    if(curr_song==NULL)
    {
        printf("\nNo song is being played");
    }
    else
    {
        printf("\nNow Playing : %s",curr_song->song);
    }
}

void swap(struct node *a, struct node *b)
{
    int x;
    char z[50];

    x = a->year;
    a->year = b->year;
    b->year = x;

    x = a->likes;
    a->likes = b->likes;
    b->likes = x;

    strcpy(z,a->song);
    strcpy(a->song,b->song);
    strcpy(b->song,z);

    strcpy(z,a->artist);
    strcpy(a->artist,b->artist);
    strcpy(b->artist,z);

    strcpy(z,a->language);
    strcpy(a->language,b->language);
    strcpy(b->language,z);
}

void sort()
{
    if(head==NULL)
    {
        printf("\nNo songs in the playlist");
    }
    else if(head->next==head)
    {
        printf("\nSongs have been sorted");
    }
    else
    {
        int i,j;
        for(i=0; i<count()-1; i++)
        {
            temp1=head;
            temp2=head->next;

            for(j=0; j<count()-1-i; j++)
            {
                if(temp1->year > temp2->year)
                {
                    swap(temp1,temp2);
                }
                temp1=temp2;
                temp2=temp2->next;
            }
        }
        printf("\nSongs have been sorted");
    }
    writeData();
}

void display_recently_searched()
{
    int i;
    if(f==0)
    {
        printf("\nNo songs have been searched");
    }
    else
    {
        printf("\nRecently searched songs :");
        for(i=0; i<f; i++)
        {
            printf("\n%s",x.array[i]);
        }
    }
}
