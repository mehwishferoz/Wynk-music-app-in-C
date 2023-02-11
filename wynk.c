#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

struct login
{
    char name[30];
    char username[30];
    char password[30];
};

struct node *head=NULL,*temp=NULL, *curr_song=NULL, *temp1=NULL, *temp2=NULL, *tail=NULL;

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
        fputs("Error at opening File!", stderr);
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
        FILE *fp = fopen("Details.txt", "w");
        temp = head;
        do
        {
            fprintf(fp,"\n%s %s %s %d %d",temp->song, temp->artist, temp->language, temp->likes, temp->year);
            temp = temp->next;
        }
        while (temp!=head);
        fclose(fp);
        //printf("Linked list data is written to the File . . .\n");
    }
    else
    {
        remove("Details.txt");
    }
}

void readData()
{
    char s[30], a[30], l[20];
    int x, y;
    FILE *fp=NULL;

    fp=fopen("Details.txt","r");

    if(fp==NULL)
    {
        // printf("\nThe playlist is empty");
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

struct node  *getnode()
{
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));

    printf("\nEnter the name of the song: ");
    fflush(stdin);
    scanf("%[^\n]s",newnode->song);
    printf("\nEnter the name of the artist: ");
    fflush(stdin);
    scanf("%[^\n]s",newnode->artist);
    printf("\nEnter the language of the song: ");
    fflush(stdin);
    scanf("%[^\n]s",newnode->language);
    printf("\nEnter the likes of the song: ");
    scanf("%d",&newnode->likes);
    printf("\nEnter the year of release of the song: ");
    scanf("%d",&newnode->year);

    newnode->next=newnode;
    newnode->prev=newnode;

    return newnode;
}

void insert_song()
{
    if(head==NULL)
    {
        head=getnode();
    }
    else
    {
        struct node *newnode=getnode();
        temp=head;
        while(temp->next!=head)
        {
            temp=temp->next;
        }
        newnode->next=head;
        head->prev=newnode;
        temp->next=newnode;
        newnode->prev=temp;
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


void display()
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
            printf("Song : %s\n",temp->song);
            printf("Artist : %s\n",temp->artist);
            printf("Language : %s\n",temp->language);
            printf("Likes : %d\n",temp->likes);
            printf("Year : %d\n\n",temp->year);
            temp=temp->next;
        }
        printf("Song : %s\n",temp->song);
        printf("Artist : %s\n",temp->artist);
        printf("Language : %s\n",temp->language);
        printf("Likes : %d\n",temp->likes);
        printf("Year : %d\n\n",temp->year);
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
    int found=0;
    char song[30];
    printf("\nEnter the name of the song you want to play : ");
    fflush(stdin);
    scanf("%[^\n]s",song);

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
                printf("\nNow Playing : %s",temp->song);
                found = 1;
                break;
            }
            temp=temp->next;
        }
        if(!found)
        {
            if(!strcasecmp(song,temp->song))
            {
                printf("\nNow Playing : %s",temp->song);
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