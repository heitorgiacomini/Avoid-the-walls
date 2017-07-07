#include <stdio.h> //printf
#include <windows.h> //gotoxy
#include <unistd.h> //sleep
#include <conio.h> /* getch() and kbhit() */
#include <time.h> //srand
//HANDLE hConsole; //color
//SETConsoleTextAttribute(hConsole, ORANGE);//color
//#include<stdlib.h>

void gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}
void clrscr(){
    system("@cls||clear");
}
void draw_line(int x,int y,int lim,char direction,int caracter){
	int aux = 0;
	for(;aux<lim;aux++){
		if(direction == 'h')
			gotoxy(aux+x,y);
		else			
			gotoxy(x,aux+y);
		printf("%c",caracter);	
	}	
}
int x_posi_wall = 40;
int x_posi_wall1 = 70;
int x_posi_wall2 = 100;
int y_axis = 2;
int y_axis1 = 13;
int y_axis2 = 20;
void wall(){	
    draw_line(x_posi_wall,y_axis,5,'v',17);//linha vertical	
    draw_line(x_posi_wall1,y_axis1,5,'v',17);//linha vertical 
 	draw_line(x_posi_wall2,y_axis2,5,'v',17);//linha vertical 
	if(x_posi_wall>3){
		x_posi_wall--;	
		x_posi_wall1--;
		x_posi_wall2--;	
	}
	//x_posi_wall = (x_posi_wall==3) ? 100 : x_posi_wall;	
 	if(x_posi_wall == 3){
		x_posi_wall = 100;
		y_axis = 2 + rand() % (21-3+1);
	}
	if(x_posi_wall1 == 3){
		x_posi_wall1 = 100;	
		y_axis1 = 2 + rand() % (21-3+1);
	} 		
	if(x_posi_wall2 == 3){
		x_posi_wall2 = 100;
		y_axis2 = 2 + rand() % (21-3+1); // 2 + rand() % (21-3+1);
	}
}
void scene(){		
    draw_line(3,1,98,'h',205);//linha superior
	draw_line(3,27,98,'h',205);//linha inferior
    draw_line(2,2,25,'v',186);//linha vertical
    draw_line(100,2,25,'v',186);//linha vertical1
    draw_line(2,1,1,'h',201); //cant sup esq
	draw_line(100,1,1,'h',187); //cant inf esq
    draw_line(2,27,1,'h',200); //cant inf rgt
	draw_line(100,27,1,'h',188); //cant inf lft 
}
int y_position = 18;
void bird_position(){
	int lel = 15;
	for(;lel<23;lel++){
		draw_line(lel,y_position,4,'v',219);	
	}
}
void bird(int where){
	if(where == 1){
		if(y_position > 2){
			bird_position();		
			y_position--;
		}	
	}else if(where == 0){
		if(y_position < 23){
			bird_position();
			y_position++;
		}		
	}else if(where == -1)
		bird_position();		
}
int pontuation;
int verify(){	
	if(x_posi_wall == 23)
		if(y_position >= y_axis && y_position <= y_axis+4 || y_position+3 >= y_axis && y_position+3 <= y_axis+4 )
			return 0;//y_axis >= y_position >= y_axis+4 || y_axis >= y_position+3 >= y_axis+4 Math notation
		else
			pontuation++;	
	else if(x_posi_wall1 == 23)
		if(y_position >= y_axis1 && y_position <= y_axis1+4 || y_position+3 >= y_axis1 && y_position+3 <= y_axis1+4 )
			return 0;
		else
			pontuation++;	
	else if(x_posi_wall2 == 23)
		if(y_position >= y_axis2 && y_position <= y_axis2+4 || y_position+3 >= y_axis2 && y_position+3 <= y_axis2+4 )
			return 0;		
		else
			pontuation++;
		/*else if(x_posi_wall1 == 23)
	else if(x_posi_wall2 == 23)
	gotoxy(120,5);
	printf("%d\t%d\n%d\t%d\n%d\t%d\n%d\t%d",y_position,y_position+3,y_axis,y_axis+4,y_axis1,y_axis1+4,y_axis2,y_axis2+4);
		xx = 1;*/
	
		/*if(y_position >= y_axis && y_position <= y_axis+4 || y_position >= y_axis && y_position <= y_axis+4)
			return 0;
	else if(x_posi_wall1 == 23)
		if(y_position >= y_axis1 && y_position <= y_axis1+4)
			return 0;
	else if(x_posi_wall2 == 23)
		if(y_position >= y_axis2 && y_position <= y_axis2+4)
			return 0;			
	*/
	return 1;		
}//typedef struct _display{int width=100, height=100;} Display;
 
int main(void){
	char input, R[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}, color_string[20];
	system("COLOR C0");
    printf("Va em propriedades e aumente o tamanho do console.\nComo jogar: desvie dos obstaculos e ganhe pontos. \nApenas colisoes frontais sao consideradas. \nAperte:  \n[J] para subir\n[K] para descer. ");
    getch();
    srand(time(NULL));
    scene();
    bird(1);
    do{	
    	system("COLOR f0");
    	pontuation = 0;
		while(1){
			if (pontuation % 2){
				int Ra = rand() %16;
	       		int Rb = rand() %16;
	       		sprintf(color_string, "color %c%c", R[Ra], R[Rb]);
	        	system(color_string);				
			}
			
	    	if(kbhit()){ //if any key is pressed
	    		input = toupper(getch());
	            if(input == 'J'){
					bird(1);
					gotoxy(13,5);
					//printf("%d",y_position);
				}else if(input == 'K'){
					bird(0);
					gotoxy(13,5);
					//printf("%d",y_position);
				}				
	        }else{
				bird(-1);				
			}     	  
			gotoxy(13,28);
			printf("PONTUACAO:  %d",pontuation);      
			wall();
			//if (x_posi_wall == 23)
				if(!verify())
					break;		
			scene();
	        sleep(0.25);
	        clrscr();
		}
		clrscr();
		system("COLOR 0C");
		char* fut[] = { " ######      ###    ##     ## ########		 #######  ##     ## ######## ########"  ,
						"##    ##    ## ##   ###   ### ##      	  	##     ## ##     ## ##       ##     ##" ,
						"##         ##   ##  #### #### ##      	 	##     ## ##     ## ##       ##     ##" ,
						"##   #### ##     ## ## ### ## ######  	 	##     ## ##     ## ######   ########"  ,
						"##    ##  ######### ##     ## ##      	 	##     ##  ##   ##  ##       ##   ##"   ,
						"##    ##  ##     ## ##     ## ##      	 	##     ##   ## ##   ##       ##    ##"  ,
						" ######   ##     ## ##     ## ########  	 #######     ###    ######## ##     ## " };
		int i;
		for(i =0;i<7;i++)
			printf("%s\n",fut[i]);
		printf("\n\tSua pontuacao final: %d \n\tDeseja continuar?[s/n].",pontuation);		
		do{
			input = toupper(getch());
		}while(input != 'S' && input != 'N');
		x_posi_wall = 100;
		x_posi_wall1 = 40;
		x_posi_wall2 = 70;	
	}while( input != 'N');
}
/*
cant sup esq 201 
cant sup dir 187
lin hor 205 
cant inf esq 200
cant inf dir 188 
lin vert 186 
block 219 254
carinha 1;2
 
ponta
 left 17
 right 16
 up 30
 dowm 31 
 
65:    // key up
        break;
    case 66:    // key down
        break;
 
var keyDownHandler = function(evt) {
  if (evt.key === 'VolumeDown') {
    // process logic of volume-down
  } else if (evt.key === 'VolumeUp') {
    // process logic of volume-up
  }
  evt.preventDefault(); // to stop system app from processing keydown event
};
 
window.addEventListener('keydown', keyDownHandler);
*/
 
 
 
 
 
 
 
 
 
 
 
 




