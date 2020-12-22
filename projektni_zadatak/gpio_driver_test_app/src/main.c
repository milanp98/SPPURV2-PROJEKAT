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
    int ret_val;
    char tmp[BUF_LEN];
    char stara = '1';
	
	int brpr;
	int brojac = 0;
	int obrtaji;
	
	printf("Unesite broj peraca: ");
	scanf("%d", &brpr);

    /* Open dummy file. */
    file_desc = open("/dev/gpio_driver", O_RDWR);

    if(file_desc < 0)
    {
        printf("Error, 'dummy' not opened\n");
        return -1;
    }

    /* Write to dummy file. */
    //ret_val = write(file_desc, tmp, BUF_LEN);

    ret_val = read(file_desc, tmp, BUF_LEN);

    stara = tmp[0];

    /* Read from dummy file. */
	while (1){
		ret_val = read(file_desc, tmp, BUF_LEN);

		if (tmp[0] == '0' && stara == '1'){
			brojac++;
            printf("Brojac = %d", brojac);
		}

        stara = tmp[0];
        
		if (){  //semafor
			break;
		}
    }
	
	obrtaji = brojac / brpr;
	
	printf ("Broj obrtaja je %d", obrtaji);
	
    /* Close dummy file. */
    close(file_desc);
    
    return 0;
}
