#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_LEN 80

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new = old; /* make new settings same as old settings */
    new.c_lflag &= ~ICANON; /* disable buffered i/o */
    new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
    return getch_(0);
}

static int kraj = 0;
static pthread_mutex_t mKraj;

void* izlaznaNit(void *param){
	while(1){
		if(getch() == 'q'){
			pthread_mutex_lock(&mKraj);
			kraj = 1;
			pthread_mutex_unlock(&mKraj);
			break;
		}
	}
	return 0;
}

int main()
{
	pthread_t hThread;
	
    int file_desc;
    char nova[BUF_LEN];
    char stara, re;
	
	int brPeraca;
	int brojac;
	int brObrtaja;
	
	printf("***Brojac obrtaja***\n");
	
	do{
		printf("\n*******************\n");
		printf("Unesite broj peraca: ");
		scanf("%d", &brPeraca);
		
		kraj = 0;
		brojac = 0;
		re = 'n';
		
		file_desc = open("/dev/gpio_driver", O_RDWR);			// Otvaranje modula

		if(file_desc < 0)
		{
			printf("Greska pri otvaranju modula!\n");
			return -1;
		}

		if(read(file_desc, nova, BUF_LEN) == -1){				// Citanje iz modula
			printf("\nGreska pri citanju iz modula!\n");
			return -2;
		}
		
		stara = nova[0];										// Pocetna vrednost
		//printf("Pocetna vrednost: %c\n", stara);
		
		close(file_desc);										// Zatvaranje modula

		pthread_mutex_init(&mKraj, NULL);
		pthread_create(&hThread, NULL, izlaznaNit, NULL);
		
		printf("\nBrojac je pokrenut. Pritisnite q da biste ga zaustavili.\n\n");
		
		while (1){
			pthread_mutex_lock(&mKraj);
			if(kraj) break;
			pthread_mutex_unlock(&mKraj);
			
			file_desc = open("/dev/gpio_driver", O_RDWR);

			if(file_desc < 0)
			{
				printf("\nGreska pri otvaranju modula!\n");
				return -1;
			}
			usleep(50);
			if(read(file_desc, nova, BUF_LEN) != -1){
				if (nova[0] == '0' && stara == '1'){
					brojac++;
					printf("Brojac = %d\n", brojac);
				}
				stara = nova[0];
			}
			else{
				printf("\nGreska pri citanju iz modula!\n");
				return -2;
			}

			close(file_desc);
		}
		
		brObrtaja = brojac / brPeraca;
		
		printf ("Broj obrtaja je %d\n", brObrtaja);
		
		pthread_mutex_destroy(&mKraj);
		
		printf("Pritisnite y ukoliko zelite ponovo da pokrenete brojac ");
		re = getch();
		printf("\n");
	}while(re == 'y');
    
    return 0;
}
