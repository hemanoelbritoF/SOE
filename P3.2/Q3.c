/*A frequencia é obtido no argumento em microsegundos */

#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


int teste()
{
    system("gpio mode 0 in");
    return digitalRead(0);
    
}

int val_read(int fd[2])
{
  int buffer;
  if (read(fd[0],&buffer,sizeof(int))<0)
    return 0;
  return buffer;
  
}

int val_write(int fd[2], int val)
{
  int buffer = val;
  write(fd[1],&val,sizeof(int));
}

int main()
{
  long freq = 1;
  int pin = 7; // Pin out
  int pin2 = 0;
  int i = 1;
  int iter=0;
  int pid_filho;

  int fd[2];
  int buffer;
  


  wiringPiSetup();
  pinMode(pin, OUTPUT);
  pinMode(pin2, INPUT);
  
  int val = 0; //valor lido no pin2
  int aux = 0;

  val = digitalRead(pin2);
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

      val = teste();
      

      if(val!=aux && val ==0)
      {
        i*=2;
        
        if(i>64)
        {
          i=1;
        }
        
      }
      aux = val;
      
      
      
      

      usleep((1000000/i));
      write(fd[1],&i,sizeof(int));
      
    }
  }
  return 0;
}

