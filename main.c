#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>
#define N 20 //rows
#define M 40 //columns

int i,j,Field[N][M],x,y,gy,Head,Tail,Game,Food,a,b,var,dir,Score,HighScore,Speed;
char play_again;
FILE *ptr;

void Gameover(){

    PlaySound(TEXT("Dead.wav"),NULL,SND_ASYNC);
    Sleep(2500);
    system("Cls");

    if(Score>HighScore){
        PlaySound(NULL, NULL, 0);
        Sleep(500);
        PlaySound(TEXT("Highscore.wav"),NULL,SND_ASYNC);
        printf("Congrats!!!! New HighScore : %d\n\n",Score);
        system("pause");
        ptr=fopen("HighScore.txt","w");
        fprintf(ptr,"%d",Score);
        fclose(ptr);
    }

    system("Cls");
    printf("\n\n Game Over !!!!");
    printf("\n\n Score : %d\n\n",Score);
    printf("Press Enter to play again or esc to exit\n\n");

    while(1){
        var=get_no_block();
        if( var == 13){
            PlaySound(NULL, NULL, 0);
            Game=0;
            snakeInitialization();
            break;
        }


        else if(var==27){
            PlaySound(NULL, NULL, 0);
            Game=1;
            break;
        }


    }
    system("Cls");
}

void snakeInitialization(){

    ptr=fopen("HighScore.txt","r");
    fscanf(ptr,"%d",&HighScore);
    fclose(ptr);


    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            Field[i][j]=0;
        }
    }

    //to assign value in the Field array for snake printing
    x=N/2; //row coordinate = 10
    y=M/2; //column coordinate = 20
    gy=y;
    Head=5;
    Tail=1;
    Game=0;
    Food=0;
    dir='d';
    Score=0;
    Speed=300;

    for(i=0;i<Head;i++){
        gy++;
        Field[x][gy-Head]=i+1; // for Field[10][16]=1,Field[10][17]=2....Field[10][21]
    }

}

void print(){
    for(i=0;i<=M+1;i++)
    {
        if(i==0)
            printf("%c",201); //╔

        else if(i==M+1)
            printf("%c",187); //╗
        else
            printf("%c",205); //═
    }

    printf("\tScore : %d\tHighScore : %d",Score,HighScore);
    printf("\n");

    for(i=0;i<N;i++){
        printf("%c",186); //║

        for(j=0;j<M;j++){
            if(Field[i][j]==0)
                printf(" ");
            if(Field[i][j]>0 && Field[i][j]!=Head)
                printf("%c",176);
            if(Field[i][j]==Head)
                printf("%c",177);
            if(j==M-1)
                printf("%c\n",186);
            if(Field[i][j]==-1)
                printf("%c",15);
        }
    }

    for(i=0;i<=M+1;i++)
    {
        if(i==0)
            printf("%c",200); //╚

        else if(i==M+1)
            printf("%c",188); //╝
        else
            printf("%c",205);
    }
}

void resetScreenPosition(){
HANDLE hOut;
COORD Position;
hOut = GetStdHandle(STD_OUTPUT_HANDLE);
Position.X=0;
Position.Y=0;
SetConsoleCursorPosition(hOut,Position);
}

void Food_random(){
    srand(time(0));
    a =  1+rand()%18;
    b =  1+rand()%38;

    if(Food==0 && Field[a][b]==0){
        Field[a][b] = -1;
        Food = 1;
        if(Speed>5&&Score!=0)
        Speed-=5;

    }
}

int get_no_block(){
    if(_kbhit())
        return _getch();
    else
        return -1;
}

void movement(){
    var = get_no_block();
    var = tolower(var);

    if(((var=='d'||var=='a')||(var=='w'||var=='s')) && (abs(dir-var)>5) )
        dir=var;

    if(dir=='d'){
        y++;
        if(Field[x][y]!=0 && Field[x][y]!=-1) Gameover();
        if(y==M) Gameover();
        if(Field[x][y]==-1){
            PlaySound(TEXT("food_sound.wav"),NULL,SND_ASYNC);
            Food = 0;
            Tail-=1;
            Score++;
        }
        Head++;
        Field[x][y] = Head;

    }

    if(dir=='w'){
        x--;
        if(Field[x][y]!=0 && Field[x][y]!=-1) Gameover();
        if(x==-1) Gameover();
        if(Field[x][y]==-1){
            PlaySound(TEXT("food_sound.wav"),NULL,SND_ASYNC);
            Food = 0;
            Tail-=1;
            Score++;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(dir=='a'){
        y--;
        if(Field[x][y]!=0 && Field[x][y]!=-1) Gameover();
        if(y==-1) Gameover();
        if(Field[x][y]==-1){
            PlaySound(TEXT("food_sound.wav"),NULL,SND_ASYNC);
            Food = 0;
            Tail-=1;
            Score++;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(dir=='s'){
        x++;
        if(Field[x][y]!=0 && Field[x][y]!=-1) Gameover();
        if(x==N) Gameover();
        if(Field[x][y]==-1){
            PlaySound(TEXT("food_sound.wav"),NULL,SND_ASYNC);
            Food = 0;
            Tail-=1;
            Score++;
        }
        Head++;
        Field[x][y] = Head;
    }
}

void Tailremove(){
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            if(Field[i][j]==Tail)
                Field[i][j]=0;
        }
    }
Tail++;
}

printarray(){
printf("score: %d \t Head: %d\t Game: %d",Score,Head,Game);
    printf("\n\n");
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            printf("%d ",Field[i][j]);
        }
    printf("\n");
    }
}

void hidecursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void main()
{
    snakeInitialization();
    hidecursor();

    //PlaySound(TEXT("The-Pink-Panther-Theme-Song.wav"),NULL,SND_LOOP | SND_ASYNC);

    while(Game==0){

    print();
    resetScreenPosition();
    Food_random();
    movement();
    Sleep(Speed);
    Tailremove();
    //printarray();
    }











}
