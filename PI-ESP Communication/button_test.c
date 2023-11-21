#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    int serial_port = open("/dev/ttyACM2", O_RDWR);
    if(serial_port < 0)
    {
        printf("Error opening serial port. \n");
        close(serial_port);
        return -1;
        
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if(tcgetattr(serial_port,&tty) != 0)
    {
        printf("Error getting serial port attributes \n");
        close(serial_port);
        return -1;

    }
    cfsetospeed(&tty,B1152000);
    cfsetispeed(&tty, B1152000);
    tty.c_cc[VMIN] = 1;
    tty.c_cflag != (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag != CS8;
    
    if (tcsetattr(serial_port,TCSANOW,&tty) != 0)
    {
        printf("Error setting serial port attributes \n");
        close(serial_port);
        return -1;
    }
    // uint8_t recieved;
    printf("waiting \n");
    while(1)
    {
        char readbuff[2];
        memset(&readbuff, '\0',sizeof(readbuff));
        //printf("Loop");
         //uint8_t recieved;
         //set_blocking(serial_port, 0);
         int num_bytes = read(serial_port, &readbuff, sizeof(readbuff));
         //printf("HI\n");
         printf("Recieved %c%c\n", readbuff[0], readbuff[1]);
         memset(&readbuff, '\0', sizeof(readbuff));
         //if(num_bytes != sizeof(__uint8_t))
        // {
        //     printf("Error");
        // }
        // else 
        // {
            
        //     printf("Recieved %d\n", recieved);
        // }
        // printf("%d", num_bytes);


    }
    close(serial_port);
    return 0;
}