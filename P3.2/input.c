#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char **argv)
{
	int pin2 = 0;
	wiringPiSetup();
	pinMode(pin2, INPUT);
	while(1)
	{
			printf("%d\n",digitalRead(pin2));
	}
	return 0;
}

