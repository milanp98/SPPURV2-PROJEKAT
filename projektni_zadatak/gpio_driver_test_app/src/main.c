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

void* izlaznaNit(void *param){
	while(1){
		if(getch() == 'q'){
			kraj = 1;
			break;
		}
	}
	return 0;
}

int main()
{
    int file_desc;
    char nova[BUF_LEN];
    char stara;
	
	int brPeraca;
	int brojac = 0;
	int brObrtaja;
	
	printf("***Brojac obrtaja***\n\n");
	printf("Unesite broj peraca: ");
	scanf("%d", &brPeraca);

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
	printf("Pocetna vrednost: %c\n", stara);
	
	close(file_desc);										// Zatvaranje modula

	pthread_t hThread;
	pthread_create(&hThread, NULL, izlaznaNit, NULL);
	
	while (1){
		if(kraj) break;
		file_desc = open("/dev/gpio_driver", O_RDWR);

		if(file_desc < 0)
		{
			printf("\nGreska pri otvaranju modula!\n");
			return -1;
		}
		
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
    
    return 0;
}
