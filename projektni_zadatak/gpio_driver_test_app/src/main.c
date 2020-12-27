#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_LEN 80

int main()
{
    int file_desc;
    char tmp[BUF_LEN];
    char stara = 'e';	//samo char stara; staviti
	
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

    if(read(file_desc, tmp, BUF_LEN) == -1){				// Citanje iz modula
		printf("\nGreska pri citanju iz modula!\n");
		return -1;
	}
	
    stara = tmp[0];											// Pocetna vrednost
	printf("Pocetna vrednost: %c", stara);
	
	close(file_desc);										// Zatvaranje modula

	while (1){
		file_desc = open("/dev/gpio_driver", O_RDWR);

		if(file_desc < 0)
		{
			printf("\nGreska pri otvaranju modula!\n");
			return -1;
		}
		
		if(read(file_desc, tmp, BUF_LEN) != -1){
			if (tmp[0] == '0' && stara == '1'){
				brojac++;
				printf("Brojac = %d\n", brojac);
			}
			stara = tmp[0];
		}
		else printf("\nGreska pri citanju iz modula!\n");
		
		
		close(file_desc);
    }
	
	brObrtaja = brojac / brPeraca;
	
	printf ("Broj obrtaja je %d", brObrtaja);
	
    close(file_desc);
    
    return 0;
}
