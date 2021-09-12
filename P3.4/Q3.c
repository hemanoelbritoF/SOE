#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>

#define TTY "/dev/ttyS0"

int uart0_fd;
void ctrl_c(int sig)
{
	close(uart0_fd);
	exit(-1);
}


int main(void)
{
	struct termios options;
	char user_input, msp430_return = 0;
	char val_recebido;
	int vals[100];
	int sum;
	signal(SIGINT, ctrl_c);
	uart0_fd = open(TTY, O_RDWR); // | O_NOCTTY); // | O_NDELAY);

	if (uart0_fd == -1)
	{
		printf("Erro \n");
		return -1;
	}


	tcgetattr(uart0_fd, &options);
	options.c_cflag = CS8 | CREAD | CLOCAL;
	options.c_iflag = 0;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN] = 1;
	cfsetospeed(&options, B9600);
	cfsetispeed(&options, B9600);
	tcsetattr(uart0_fd, TCSANOW, &options);
	system("stty -F " TTY);
	

	unsigned int i = 0;
	while(1)
	{
		while (read(uart0_fd, &val_recebido, 1) != 1)
		{

		}
		vals[i % 100] = ((int)val_recebido);

		while (read(uart0_fd, &val_recebido, 1) != 1)
		{

		}
		
		vals[i % 100] += ((int)val_recebido)*256;

		if (i % 100 == 99)
		{
			sum = 0;
			for (int a = 0; a < 100; a++)
			{
				sum += vals[a];
				
			}
			sum = sum / 100;
			printf("Media:%d\n",sum );
		}
		i++;
		usleep(10000);
	}

	return 0;
}