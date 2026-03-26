#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define TOP_OFFSET 2
#define FRUIT_COUNT 5

#define MODE_EASY 1
#define MODE_NORMAL 2
#define MODE_HARD 3

typedef struct Node{
    int x,y;
    struct Node *next;
}Node;

typedef struct{
    int x,y;
}Fruit;

Node *head=NULL;
Node *tail=NULL;

Fruit fruits[FRUIT_COUNT];

int dirX=0;
int dirY=0;

int score=0;
int level=1;
int gameOver=0;

int mapWidth=40;
int mapHeight=15;

int gameMode=MODE_NORMAL;
int speed=140;

HANDLE hConsole;

/* util */

void setColor(int color){
    SetConsoleTextAttribute(hConsole,color);
}

void gotoxy(int x,int y){
    COORD coord={x,y};
    SetConsoleCursorPosition(hConsole,coord);
}

void hideCursor(){
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize=1;
    ci.bVisible=FALSE;
    SetConsoleCursorInfo(hConsole,&ci);
}

/* menu principal */

int menu(){

    system("cls");

    setColor(11);
    gotoxy(22,5);
    printf("=== SNAKE GAME ===");

    setColor(7);

    gotoxy(22,8);
    printf("1 - Jogar");

    gotoxy(22,9);
    printf("2 - Selecionar modo");

    gotoxy(22,10);
    printf("3 - Sair");

    while(1){

        char key=_getch();

        if(key=='1') return 1;
        if(key=='2') return 2;
        if(key=='3') return 3;
    }
}

void mode_menu(){

    system("cls");

    setColor(11);
    gotoxy(20,5);
    printf("=== SELECIONE O MODO ===");

    setColor(7);

    gotoxy(22,8);
    printf("1 - Facil");

    gotoxy(22,9);
    printf("2 - Normal");

    gotoxy(22,10);
    printf("3 - Dificil");

    char key=_getch();

    if(key=='1') gameMode=MODE_EASY;
    if(key=='2') gameMode=MODE_NORMAL;
    if(key=='3') gameMode=MODE_HARD;
}

/* corpo da cobra */

void insert_head(int x,int y){

    Node *newNode=malloc(sizeof(Node));

    newNode->x=x;
    newNode->y=y;

    if(!head){
        head=tail=newNode;
        newNode->next=newNode;
    }
    else{
        newNode->next=head;
        tail->next=newNode;
        head=newNode;
    }
}

void remove_tail(){

    if(head==tail) return;

    Node *temp=head;

    while(temp->next!=tail)
        temp=temp->next;

    gotoxy(tail->x,tail->y);
    printf(" ");

    temp->next=head;

    free(tail);
    tail=temp;
}

/* mapa */

void draw_border(){

    setColor(11);

    for(int i=0;i<=mapWidth;i++){

        gotoxy(i,TOP_OFFSET);
        printf("=");

        gotoxy(i,mapHeight+TOP_OFFSET);
        printf("=");
    }

    for(int i=TOP_OFFSET;i<=mapHeight+TOP_OFFSET;i++){

        gotoxy(0,i);
        printf("|");

        gotoxy(mapWidth,i);
        printf("|");
    }

    setColor(7);
}

void draw_score() {
    // Score no topo (opcional, já que teremos na lateral)
    setColor(10);
    gotoxy(2, 0);
    printf("Score: %d | Fase: %d          ", score, level);
    
    // Desenha a barra lateral
    draw_sidebar();
    setColor(7);
}

void draw_sidebar() {
    int sideX = mapWidth + 5; // Posiciona 5 espaços após a borda direita
    int startY = TOP_OFFSET;

    setColor(11); // Ciano para o cabeçalho
    gotoxy(sideX, startY);
    printf("======= STATUS =======");

    setColor(15); // Branco
    gotoxy(sideX, startY + 2);
    printf("MODO: ");
    if(gameMode == MODE_EASY)   { setColor(10); printf("FACIL  "); }
    if(gameMode == MODE_NORMAL) { setColor(14); printf("NORMAL "); }
    if(gameMode == MODE_HARD)   { setColor(12); printf("DIFICIL"); }

    setColor(15);
    gotoxy(sideX, startY + 4);
    printf("DIFICULDADE: %dms", speed);

    setColor(15);
    gotoxy(sideX, startY + 6);
    printf("SCORE ATUAL: ");
    setColor(10); // Verde para o score
    printf("%06d", score);

    setColor(11);
    gotoxy(sideX, startY + 8);
    printf("======================");
    
    // Pequeno tutorial rápido embaixo
    setColor(8); // Cinza
    gotoxy(sideX, startY + 10);
    printf("Use WASD ou Setas");
}

/* colisão */

int collision(int x,int y){

    if(x<=0 || x>=mapWidth ||
       y<=TOP_OFFSET || y>=mapHeight+TOP_OFFSET)
       return 1;

    Node *temp=head->next;

    while(temp!=head){

        if(temp->x==x && temp->y==y)
            return 1;

        temp=temp->next;
    }

    return 0;
}

int snake_on_position(int x,int y){

    Node *temp=head;

    do{

        if(temp->x==x && temp->y==y)
            return 1;

        temp=temp->next;

    }while(temp!=head);

    return 0;
}

/* sistema da fruta*/

void generate_fruit(int i){

    do{

        fruits[i].x=rand()%(mapWidth-2)+1;
        fruits[i].y=rand()%(mapHeight-1)+1+TOP_OFFSET;

    }while(snake_on_position(fruits[i].x,fruits[i].y));

    setColor(13);

    gotoxy(fruits[i].x,fruits[i].y);
    printf("@");

    setColor(7);
}

void init_fruits(){

    for(int i=0;i<FRUIT_COUNT;i++)
        generate_fruit(i);
}

/* input */

void input(){

    if(_kbhit()){

        int key=_getch();

        if(key==224){

            key=_getch();

            if(key==72 && dirY!=1){dirX=0;dirY=-1;}
            if(key==80 && dirY!=-1){dirX=0;dirY=1;}
            if(key==75 && dirX!=1){dirX=-1;dirY=0;}
            if(key==77 && dirX!=-1){dirX=1;dirY=0;}
        }

        if((key=='w'||key=='W') && dirY!=1){dirX=0;dirY=-1;}
        if((key=='s'||key=='S') && dirY!=-1){dirX=0;dirY=1;}
        if((key=='a'||key=='A') && dirX!=1){dirX=-1;dirY=0;}
        if((key=='d'||key=='D') && dirX!=-1){dirX=1;dirY=0;}
    }
}

/* sistema de level*/

void update_level(){

    if(score>=1000 && level==1){

        level=2;

        mapWidth=50;
        mapHeight=18;

        system("cls");
        draw_border();
        init_fruits();
    }

    if(score>=3000 && level==2){

        level=3;

        mapWidth=60;
        mapHeight=22;

        system("cls");
        draw_border();
        init_fruits();
    }
}

/* sistema de up */

void update(){

    if(dirX==0 && dirY==0) return;

    int newX=head->x+dirX;
    int newY=head->y+dirY;

    if(collision(newX,newY)){
        gameOver=1;
        return;
    }

    setColor(2);
    gotoxy(head->x,head->y);
    printf("o");

    insert_head(newX,newY);

    setColor(14);
    gotoxy(newX,newY);
    printf("O");

    int ate=0;

    for(int i=0;i<FRUIT_COUNT;i++){

        if(newX==fruits[i].x && newY==fruits[i].y){

            score+=15;
            generate_fruit(i);
            ate=1;
        }
    }

    if(!ate)
        remove_tail();

    update_level();
    draw_score();
}

/* tela game over  */

int game_over_screen(){

    system("cls");

    setColor(12);
    gotoxy(25,8);
    printf("GAME OVER");

    setColor(14);
    gotoxy(23,10);
    printf("Score: %d",score);

    setColor(7);

    gotoxy(20,13);
    printf("1 - Jogar novamente");

    gotoxy(20,14);
    printf("2 - Menu");

    gotoxy(20,15);
    printf("3 - Sair");

    while(1){

        char key=_getch();

        if(key=='1') return 1;
        if(key=='2') return 2;
        if(key=='3') return 3;
    }
}

/* sistema de resetar*/

void reset_game(){

    head=NULL;
    tail=NULL;

    score=0;
    level=1;

    dirX=0;
    dirY=0;

    gameOver=0;

    mapWidth=40;
    mapHeight=15;

    system("cls");

    insert_head(mapWidth/2,mapHeight/2+TOP_OFFSET);

    draw_border();
    init_fruits();

    setColor(14);
    gotoxy(head->x,head->y);
    printf("O");

    draw_score();
}

/* mains */

int main(){

    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

    srand(time(NULL));
    hideCursor();

    int choice;

    while(1){

        choice=menu();

        if(choice==1) break;
        if(choice==2) mode_menu();
        if(choice==3) return 0;
    }

    if(gameMode==MODE_EASY) speed=170;
    if(gameMode==MODE_NORMAL) speed=140;
    if(gameMode==MODE_HARD) speed=90;

    reset_game();

    while(1){

        while(!gameOver){

            input();
            update();

            Sleep(speed);
        }

        int option=game_over_screen();

        if(option==1) reset_game();
        if(option==2) main();
        if(option==3) return 0;
    }

    return 0;
}
