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
void info(int nivel, int puntos);

int main(void){
	struct XY cola[MAX], comida;
	int mx=2, my=0, x=10, y=5, puntos=3, i, sig = 1, nivel;
	nivel = selectlevel();
	setup();
	comida.x = 4;
	comida.y = 5;
	for(i=1; i<puntos; i++){
		cola[puntos-i].x=x-i*2;
		cola[puntos-i].y=y-i;
	}
	pintarCuadro(comida.x, comida.y, RED);
	info(nivel, puntos);
	do{
		if(kbhit()){
			switch(getch()){
				case 'a':
					mx = -2;
					my = 0;
				break;
				case 'd':
					mx = 2;
					my = 0;
				break;
				case 'w':
					mx = 0;
					my = -1;
				break;
				case 's':
					mx = 0;
					my = 1;
				break;
			}
		}
		x+=mx;
		y+=my;
		cola[puntos].x = x;
		cola[puntos].y = y;
		for(i=0; i<puntos; i++){
			cola[i].x = cola[i+1].x;
			cola[i].y = cola[i+1].y;	
			if(i!=0)
				if(x == cola[i-1].x && y == cola[i-1].y)
					sig = 0;
		}
		if(x >= An || x <= 1 || y >= Al || y <= 1 || !sig)
			break;
		pintarCuadro(cola[0].x, cola[0].y, BLACK);
		pintarCuadro(x, y, WHITE);
		if(comida.x == x && comida.y == y){
			puntos++;
		rep:comida.x = 2*(rand()%(An/2-2)+1);
			comida.y = rand()%(Al-2)+2;
			for(i = 0; i< puntos; i++){
				if(comida.x == cola[i].x && comida.y == cola[i].y)
					goto rep;
			}
			pintarCuadro(comida.x, comida.y, RED);
			info(nivel, puntos);
		}
		Sleep(200-nivel*50);
	}while(puntos < MAX);
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

void info(int nivel, int puntos){
	textcolor(WHITE);
	gotoxy(An+1, 2);
	cprintf("Nivel: %i", nivel);
	gotoxy(An+1, 3);
	cprintf("Puntos: %i", puntos-3);
}