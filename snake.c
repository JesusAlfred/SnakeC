//Snake

#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define An 60
#define Al 30
#define MAX 100

struct XY{
	int x;
	int y;
};

void rec(int ancho, int alto);
int selectlevel(void);
void setup(void);
void pintarCuadro(int, int, int);
void info(int nivel, int puntos, int puntos2);

int main(void){
	struct XY cola[MAX], cola2[MAX], comida;
	int mx=2, my=0, x=10, y=5, puntos=3, i, sig = 1, nivel, tecla;
	int mx2=2, my2=0, x2=10, y2=10, puntos2=3, j, sig2;
	char tecla2;
	nivel = selectlevel();
	setup();
	comida.x = 4;
	comida.y = 5;
	for(i=1; i<puntos; i++){
		cola[puntos-i].x=x-i*2;
		cola[puntos-i].y=y-i;
		
		cola[puntos-i].x=x2-i*2;
		cola[puntos-i].y=y2-i;
	}
	pintarCuadro(comida.x, comida.y, RED);
	info(nivel, puntos, puntos2);
	do{
		if(kbhit()){
			tecla = getch();
			if(tecla == 0)
				tecla = getch();
			switch(tecla){
				case 75:
					mx = -2;
					my = 0;
				break;
				case 77:
					mx = 2;
					my = 0;
				break;
				case 72:
					mx = 0;
					my = -1;
				break;
				case 80:
					mx = 0;
					my = 1;
				break;
				case 'a':
					mx2 = -2;
					my2 = 0;
				break;
				case 'd':
					mx2 = 2;
					my2 = 0;
				break;
				case 'w':
					mx2 = 0;
					my2 = -1;
				break;
				case 's':
					mx2 = 0;
					my2 = 1;
				break;
			}
		}
		x+=mx;
		y+=my;
		
		x2+=mx2;
		y2+=my2;
		
		cola[puntos].x = x;
		cola[puntos].y = y;
		
		cola2[puntos2].x = x2;
		cola2[puntos2].y = y2;
		
		for(i=0; i<puntos; i++){
			cola[i].x = cola[i+1].x;
			cola[i].y = cola[i+1].y;	
			if(i!=0)
				if(x == cola[i-1].x && y == cola[i-1].y)
					sig = 0;
		}
		for(i=0; i<puntos2; i++){
			cola2[i].x = cola2[i+1].x;
			cola2[i].y = cola2[i+1].y;	
			if(i!=0)
				if(x2 == cola2[i-1].x && y2 == cola2[i-1].y)
					sig = 0;
		}
		
		if(x >= An || x <= 1 || y >= Al || y <= 1 || !sig)
			break;
		if(x2 >= An || x2 <= 1 || y2 >= Al || y2 <= 1 || !sig)
			break;
			
		pintarCuadro(cola[0].x, cola[0].y, BLACK);
		pintarCuadro(x, y, WHITE);
		
		pintarCuadro(cola2[0].x, cola2[0].y, BLACK);
		pintarCuadro(x2, y2, GREEN);
		
		if(comida.x == x && comida.y == y){
			puntos++;
		rep:comida.x = 2*(rand()%(An/2-2)+1);
			comida.y = rand()%(Al-2)+2;
			for(i = 0; i< puntos; i++){
				if(comida.x == cola[i].x && comida.y == cola[i].y)
					goto rep;
			}
			for(i = 0; i< puntos2; i++){
				if(comida.x == cola2[i].x && comida.y == cola2[i].y)
					goto rep;
			}
			pintarCuadro(comida.x, comida.y, RED);
			info(nivel, puntos, puntos2);
		}
		
		if(comida.x == x2 && comida.y == y2){
			puntos2++;
		rep2:comida.x = 2*(rand()%(An/2-2)+1);
			comida.y = rand()%(Al-2)+2;
			for(i = 0; i< puntos2; i++){
				if(comida.x == cola2[i].x && comida.y == cola2[i].y)
					goto rep2;
			}
			for(i = 0; i< puntos; i++){
				if(comida.x == cola[i].x && comida.y == cola[i].y)
					goto rep2;
			}
			pintarCuadro(comida.x, comida.y, RED);
			info(nivel, puntos, puntos2);
		}
		
		Sleep(200-nivel*50);
	}while(puntos < MAX && puntos2 < MAX);
	while(kbhit())
		getch();
	gotoxy(An/2-5,Al/2);
	textbackground(WHITE);
	textcolor(BLACK);
	if(puntos < MAX)
		cprintf(" Perdiste ");
	else
		cprintf(" Ganaste ");
	getch();
	return 0;
}

void rec(int ancho, int alto){
	int i;
	for(i=1; i<=ancho; i++){
		gotoxy(i, 1);
		cprintf("%c",196);
		gotoxy(i, alto);
		cprintf("%c",196);
	}
	for(i=1; i<=alto; i++){
		gotoxy(1, i);
		cprintf("%c",179);
		gotoxy(ancho, i);
		cprintf("%c",179);
	}
	gotoxy(1,1);
	cprintf("%c", 218);
	gotoxy(ancho,1);
	cprintf("%c", 191);
	gotoxy(1,alto);
	cprintf("%c", 192);
	gotoxy(ancho,alto);
	cprintf("%c", 217);
}

int selectlevel(void){
	int nivel;
	system("cls");
	printf("Seleccione un nivel\n1)\n2)\n3)\n\n");
	scanf("%i", &nivel);
	system("cls");
	return nivel;
}

void setup(void){
	randomize();
	rec(An,Al);
}

void pintarCuadro(int x, int y, int color){
	gotoxy(x,y);
	textcolor(color);
	cprintf("%c%c", 219, 219);
}

void info(int nivel, int puntos, int puntos2){
	textcolor(WHITE);
	gotoxy(An+1, 2);
	cprintf("Nivel: %i", nivel);
	gotoxy(An+1, 3);
	cprintf("Puntos: %i", puntos-3);
	gotoxy(An+1, 4);
	cprintf("Puntos2: %i", puntos2-3);
}