/*A frequencia é obtido no argumento em microsegundos */

#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/poll.h>

int teste()
{
    system("gpio mode 0 in");
    return digitalRead(0);
    
}

int main()
{
  long freq = 1;
  int pin = 7; // Pin out
  
  int i = 1;
  int iter=0;
  int pid_filho;

  int fd[2];
  int buffer;
  

  #Poll
  struct pollfd pfd;
  char iobuff;
  system("echo 17       > /sys/class/gpio/export");
  system("echo falling > /sys/class/gpio/gpio17/edge");
  system("echo in      > /sys/class/gpio/gpio17/direction");

  if (pfd.fd < 0)
  {
      printf("Erro");
      return 1;
  }
  pfd.fd = open("/sys/class/gpio/gpio17/value", O_RDONLY);
  read(pfd.fd, &iobuff, 1);
  pfd.events = POLLPRI | POLLERR;

  wiringPiSetup();
  pinMode(pin, OUTPUT);

  
  int val = 0; //valor lido no pin2
  int aux = 0;

  val = ;
  aux = val;
  pipe(fd);
  pid_filho = fork();

  if(pid_filho==0)
  {
    close(fd[1] );
    while(1)
       {
	       
         val = val_read(fd);
	       if(read(fd[0],&buffer,sizeof(int))>0)
              {
                 printf("valor no buffer read: %d\n", val);
                 freq = val;
               }
               if(iter%2 == 0)
               {
                       digitalWrite(pin, HIGH);
                       usleep((1000000/freq)/2);
               }
               else
               {
                       digitalWrite(pin, LOW);
                       usleep((1000000/freq)/2);
               }
               iter++;
               
       }
  }
  else
  {
    
    close(fd[0] );
    write(fd[1],&i,sizeof(int));
    while(1)
    {

      poll(&pfd, 1, -1);
      i*=2;
        
      if(i>64)
       i=1;
        
      write(fd[1],&i,sizeof(int));
      
    }
  }
  close(pfd.fd);
  system("echo 4 > /sys/class/gpio/unexport");
  return 0;
}

