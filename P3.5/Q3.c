#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int spi_fd;
void ctrl_c(int sig)
{
	close(spi_fd);
	exit(-1);
}

int main(void)
{
	unsigned char msp_data;
	int vals[100];
	unsigned int i = 0;

	signal(SIGINT, ctrl_c);
	if (wiringPiSetup() == -1)
	{
		printf("Erro\n");
		return -1;
	}
	//                  channel  speed
	spi_fd = wiringPiSPISetup(0, 500000);
	
	if (spi_fd == -1)
	{
		printf("Erro\n");
		return -1;
	}

	while (1)
	{
		msp_data = 0x55;
		wiringPiSPIDataRW(0, &msp_data, 1);
		if (msp_data == 0xAA)
		{
			usleep(100);
			msp_data = 0x01;
			wiringPiSPIDataRW(0, &msp_data, 1);
			vals[i % 100] = ((int)msp_data);

			msp_data = 0x02;
			wiringPiSPIDataRW(0, &msp_data, 1);
			vals[i % 100] += ((int)msp_data) * 256;
			i++
		}
		if (i % 100 == 99)
		{
			sum = 0;
			for (int a = 0; a < 100; a++)
			{
				sum += vals[a];

			}
			sum = sum / 100;
			printf("Media:%d\n", sum);
		}
		usleep(10000);

	}
	
	close(spi_fd);
	return 0;
}