#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

int i2c_fd;
void ctrl_c(int sig)
{
	close(i2c_fd);
	exit(-1);
}

int main(void)
{
	unsigned char msp430_ret, disp_addr = 0x0F, msp_data;
	signal(SIGINT, ctrl_c);
	i2c_fd = open("/dev/i2c-1", O_RDWR);
	ioctl(i2c_fd, I2C_SLAVE, slave_addr);
	int i = 0;
	int vals[100];

	while (1)
	{
		msp_data = 0x55;
		write(i2c_fd, &msp_data, 1);
		usleep(100);

		read(i2c_fd, &msp_data, 1);
		vals[i % 100] = ((int)msp_data);
		read(i2c_fd, &msp_data, 1);
		vals[i % 100] += ((int)msp_data)*256;

		if (i % 100 ==  99)
		{
			sum = 0;
			for (int a = 0; a < 100; a++)
			{
				sum += vals[a];

			}
			sum = sum / 100;
			printf("Media:%d\n", sum);
			
		}

		i++;
		usleep(10000);
		
	}

	return 0;
}