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

    /* Read from dummy file. */
	while (1){
		ret_val = read(file_desc, tmp, BUF_LEN);
		if (ret_val == 1){
			brojac++;
		}
		if (){
			break;
		}
    }
	
	obrtaji = brojac / brpr;
	
	printf ("Broj obrtaja je %d", obrtaji);
	
    /* Close dummy file. */
    close(file_desc);
    
    return 0;
}
