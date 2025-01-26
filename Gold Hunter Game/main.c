#include <stdio.h>
#include <windows.h>
#include <time.h>

#define SOL 75
#define SAG 77
#define YUKARI 72
#define ASAGI 80
	
#define SOLSINIR 1
#define SAGSINIR 20
#define ALTSINIR 10
#define USTSINIR 2

void gotoxy(int x, int y); //cursor konumu 
void hidecursor();   
int yemcagir,mayinla;
int sayix,sayiy,i;
int karx=10,kary=6; //KARAKTERIMIZIN BASLANGIC KONUMU
int skor,can=1;
//int canver = 20;
char harita[ALTSINIR][SAGSINIR]; //HAREKETLERIMIZI DIZIDE TUTUYORUZ
int cikis;

	void sinir_ciz() { //OYUN ALANIMIZI CIZIYORUZ
		
		int x,y;
		printf("\n");
		for(y = 0; y < ALTSINIR+1; y++) {

			for(x = 0; x < SAGSINIR+1; x++) {
					if(x == 0 && y == 0)
					printf("%c",201);
						else if(x == SAGSINIR && y == 0)
						printf("%c",187);
						else if(y == 0)
						printf("%c",205);
						else if(y == ALTSINIR && x == 0)
						printf("%c",200);
						else if(x == 0 && y > 0)
						printf("%c",186);
						else if(y == ALTSINIR && x == SAGSINIR)
						printf("%c",188);
						else if(x == SAGSINIR)
						printf("%c",186);
						else if(y == ALTSINIR)
						printf("%c",205);
					else
					printf(" ");
				}
			printf("\n");
		}
	}


	void yemle() { // RASGELE ALTIN ATIYORUZ
		
		int x,y;
		/*x = rand() %SAGSINIR;
		y = USTSINIR+1rand() %ALTSINIR;*/
		sayix = USTSINIR+rand() %ALTSINIR;
		sayiy = SOLSINIR+rand() %SAGSINIR;
		if(sayiy >= SAGSINIR) --sayiy;
		if(sayix >= ALTSINIR) --sayix;
		harita[sayix][sayiy]='*';
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos = {sayiy, sayix};
		SetConsoleCursorPosition(hConsole, pos);
		WriteConsole(hConsole, "*", 1, NULL, NULL);
	}

	void kontrol() {

		if(harita[kary][karx]== '*') {
			harita[kary][karx] = ' ';
			++skor;
			/*if(skor >= canver)
			{ 
				canver = canver + 5;
				++can;
				gotoxy(SAGSINIR+5,3);
				printf("CAN= %d",can);
				gotoxy(SAGSINIR+5,5);
				printf("SKOR= %d  ",skor);
			
			}*/
			gotoxy(SAGSINIR+5,5);
			printf("SKOR= %d", skor);	
		}
		
		if(harita[kary][karx]=='#') { //Karakter dokununca yanar 
			harita[kary][karx] = ' '; 
			--can;
			gotoxy(SAGSINIR + 5, 3);
			printf("CAN= %d", can);	
		}

		if(can == 0) {
			gotoxy(SOLSINIR+5,ALTSINIR/2);
			printf("GAME OVER");
			oyun_tekrar();
			FILE *fp;
			if((fp=fopen("skor.txt","a")) == NULL) {
				printf("dosya bulunamadi");
			}
			fprintf(fp, "  SKOR : %d \n ", skor);    	
		}
	}

	void mayin() { //RASGELE MAYIN ATIYORUZ
		int x, y;
		/*x = rand() %SAGSINIR;
		y = rand() %ALTSINIR;*/
		sayix = USTSINIR+rand() %ALTSINIR;
		sayiy = SOLSINIR+rand() %SAGSINIR;
		if(sayiy >= SAGSINIR) --sayiy;
		if(sayix >= ALTSINIR) --sayix;
		harita[sayix][sayiy]='#'; // kontrol icin diziye atiyoruz
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos = {sayiy, sayix};
		SetConsoleCursorPosition(hConsole, pos);
		WriteConsole(hConsole, "# ", 1, NULL, NULL); //mayindan sonra 1 karekter
	}

	void oyuna_basla() {

		printf("   **ALTIN AVCISI** ");
		sinir_ciz();
		
		gotoxy(SAGSINIR + 5, 5);
		printf("SKOR= %d", skor);
		
		gotoxy(SAGSINIR + 5, 3);
		printf("CAN= %d",can);
			
		gotoxy(SAGSINIR + 5, USTSINIR + 5);
		printf("'Hareket Ettikce Altinlar Artacaktir !' ");
		
		gotoxy(SAGSINIR + 5, USTSINIR + 7);
		printf("'Mayinlara Basmadan Altinlari Topla :)' ");
		
		gotoxy(ALTSINIR- 9, SAGSINIR - 8);
		printf("|* ALTIN | # MAYIN| \n");
		
		
		int x=15, y=10, ch1, ch2 ;
		hidecursor();
		
		gotoxy(karx, kary);
		printf("X");
		
		
		ch1 = getch(); 
		ch2 = 0;

		srand(time(NULL));

		if (ch1 == 0xE0) { 

			while(ch2 = getch()) {
				
				if(ch2 == 'X') exit(0);

					if(ch2 == SOL) {

						if(karx > SOLSINIR) {
							gotoxy(--karx, kary);
							printf("X");     
							gotoxy(karx+1, kary);
							printf(" ");
						}
					}

					yemcagir = 1 + rand() % 45; //Rasgele Altin Atiyoruz

					if(yemcagir == 40 || yemcagir == 31)  yemle();

					mayinla = 1 + rand() %10; // Rasgele Mayin Atiyoruz

					if(mayinla == 1)  mayin();

						if(ch2 == SAG) {
							if(karx + 1 < SAGSINIR)
							{
								gotoxy(++ karx, kary);
								printf("X");
								gotoxy(karx-1, kary);
								printf(" ");
							}
						} 

						if(ch2 == YUKARI) {
							if(kary > USTSINIR){
								gotoxy(karx, --kary);
								printf("X");
								gotoxy(karx, kary+1);
								printf(" ");
							} 
						}

						if(ch2 == ASAGI) {
							if(kary < ALTSINIR) {
								gotoxy(karx, ++kary);
								printf("X");
								gotoxy(karx, kary-1);
								printf(" ");
							} 
						}
				kontrol();
			}
		} 
		getch();
	}

	void hidecursor() {
		CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & cursor_info);	
	}

	void gotoxy(int x, int y) {
		COORD Pos = {x, y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	oyun_tekrar() {
		
		printf("\n Yeniden oyuna baslamak icin (0) tuslayiniz cikmak icin (1) tuslayiniz = ");
		scanf("%d", &cikis);

			if(cikis == 0){
				system("cls");
				oyuna_basla();
			} else if(cikis == 1){
				oyun_bitti();
		    }
	}

	oyun_bitti() {
		printf("KAPANIYOR.....");
		Sleep(3000);
		sys("cls");
		exit(EXIT_SUCCESS);
	}

	int main() { 
		oyuna_basla();
	}
	


