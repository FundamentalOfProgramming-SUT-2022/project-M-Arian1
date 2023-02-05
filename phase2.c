#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <string.h> 

int max(int a, int b){
    if(a>b) return a;
    return b;
}
int min(int a, int b){
    if(a<b) return a;
    return b;
}
FILE* filep;
int ARZ = 5;
int H = 5;
int wid = 30;
int hei = 30;
int curser_x = 0;
int curser_y = 0;
char filename[100];
char is_saved[1] = "+";
int filelines = 0;
int linemax = 0;
int selected[100][100];
int is_vis = 0;
void printboarders(){
    init_pair(90 , COLOR_BLUE , COLOR_BLUE);
    attron(COLOR_PAIR(90));
    for(int i=0; i<wid;i++){
        move(H, ARZ + i);
        printw(" ");
        
        move(H + hei, ARZ + i);
        printf(" ");
        
    }
    for(int i=0; i<hei;i++){
        move(H + i, ARZ);
        printw(" ");
        
        move(H + i, ARZ + wid);
        printf(" ");
    }
    //refresh();
}

void printfilename(){
    move(H+hei, ARZ+wid);
    init_pair(92 , COLOR_YELLOW , COLOR_BLACK);
    attron(COLOR_PAIR(92));
    printw(filename);
    init_pair(91 , COLOR_CYAN , COLOR_BLACK);
    attron(COLOR_PAIR(91));
    move(H+hei, ARZ+wid + 10);
    printw(is_saved);
    //refresh();
}

void printcurser(){
    move(curser_y, curser_x);
    init_pair(93 , COLOR_BLUE , COLOR_BLUE);
    attron(COLOR_PAIR(93));
    printw("|");
}


int check_inp(int inputt){
    if(inputt == (int) 'k' || inputt ==(int) KEY_LEFT) curser_y = max(H+5 , curser_y-1);
    if(inputt == (int) 'j') curser_y = min(filelines+H+5-1, curser_y+1);
    if(inputt == (int) 'l') curser_x = min(linemax-1, curser_x+1);
    if(inputt == (int) 'h') curser_x = max(ARZ+6, curser_x-1);
    if(inputt == (int) 'v') is_vis = !is_vis; 
}


int main(){
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            selected[i][j]=0;
        }
    }
    curser_x = ARZ+6;
    curser_y = H+5;
    strcpy(filename, "file.txt");
	filep = fopen(filename, "r+");



	initscr() ;
	start_color() ;
	noecho() ;
	nodelay(stdscr,1);
	
	int inputt ;
    int ci = 0;
	while(1){
		clear();

        printboarders();
        printfilename();
	    init_pair(100 , COLOR_WHITE , COLOR_BLACK) ;
        init_pair(101 , COLOR_WHITE , COLOR_CYAN) ;
        char line[100];
        char linenum[100];
        char check = ' ';
        rewind(filep);
        if(is_vis==1){
            selected[curser_y][curser_x]=1;
        }
        for(int i=0;i<15;i++){
	        attron(COLOR_PAIR(100)) ;
            if(selected[curser_y][curser_x]==1) attron(COLOR_PAIR(101)) ;
            fscanf(filep,"%[^\n]", line);
            check = fgetc(filep);
            move(5+i+H, 5 + ARZ+1);
            printw(line);
            move(5+i+H, 0 + ARZ+1);
            sprintf(linenum, "%d", i+1);
            printw(linenum);
            if(5+H+i==curser_y){
                linemax = ARZ + 6 + strlen(line);
            }
            if(check == EOF){filelines=i+1;break;}
        }
        if(ci>50/2) printcurser();
        ci++;
        if(ci>100/2) ci=0;
        // move(50,50);
        // printw("hello");
        inputt = getch();
        check_inp(inputt);
        move(50,50);
		refresh() ;
		usleep(10000);

	}

	clear() ;
	init_pair(10,COLOR_RED , COLOR_BLACK) ;
	attron(COLOR_PAIR(10)) ;
	char s[15] = "YOU LOST !! ..." ;
	char ss[] = " \\ \\   / / __ \\| |  | | | |    / __ \\ / ____|__   __| | | | | | |G  \\ \\_/ / |  | | |  | | | |   | |  | | (___    | |    | | | | | |G   \\   /| |  | | |  | | | |   | |  | |\\___ \\   | |    | | | | | |G    | | | |__| | |__| | | |___| |__| |____) |  | |    |_| |_| |_|G    |_|  \\____/ \\____/  |______\\____/|_____/   |_|    (_) (_) (_)" ;
	nodelay(stdscr,0);
	//print_border() ;
	for(int line = 0 , i = 0 ; i < 345 ; i++){
		move(5 + line,5+i%66) ;
		if(ss[i] != 'G') printw("%c" , ss[i]) ;
		else line++ ;
		move(40,120) ;
		refresh() ;
		usleep(20000) ;
	}
	move(15,5) ;
	printw("Enter any key to exit... YOUR SCORE = %d" , 5 ) ;
	refresh() ;
	getch() ;
	endwin() ; 
}