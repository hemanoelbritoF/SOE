/*A frequencia é obtido no argumento em hz */

#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[ ])
{
  if (argc!=2)
    exit(1);

  long freq = atol(argv[1]);
  long period = 1000000/freq;
  int pin = 7; // Pino GPIO4 é o 7 na WiringPi
  int i = 0;

  wiringPiSetup();
  pinMode(pin, OUTPUT);

  while(1)
       {
               if(i%2 == 0)
               {
                       digitalWrite(pin, HIGH);
                       usleep((period)/2);
               }
               else
               {
                       digitalWrite(pin, LOW);
                       usleep((period)/2);
               }
               i++;
       }
  return 0;
}
