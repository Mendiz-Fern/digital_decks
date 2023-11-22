#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
__uint16_t recieve(int controller)
{
    char *port = malloc(13);
    __uint8_t msb;
    __uint8_t lsb;
    __uint16_t output = -1;
    switch(controller)
    {
        case 1: 
        port = "/dev/ttyACM0";
        break;
        case 2: 
        port = "/dev/ttyACM1";
        break;
        case 3:
        port = "/dev/ttyACM2";
        break;
        case 4:
        port = "/dev/ttyACM3";
        break;
        default: "err";
    }
    if(port == "err")
    {
        printf("Wrong Controller Input");
        return -1;
    }
    int serial_port = open(port, O_RDWR);
    if(serial_port < 0)
    {
        printf("Error opening serial port. \n");
        return -1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if(tcgetattr(serial_port,&tty) != 0)
    {
        printf("Error getting serial port attributes 1 \n");
        return -1;

    }
    cfsetospeed(&tty,B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag != (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag != CS8;
    if (tcsetattr(serial_port,TCSANOW,&tty) != 0)
    {
        printf("Error setting serial port attributes \n");
        return -1;
    }
    unsigned char buffer[2];
    int bytes_read = read(serial_port, buffer, 2);
    if(bytes_read != 2)
    {
        printf("Error reading from serial port.\n");
    }
    else 
    {
        char ack[] = "hi";

        msb = buffer[0];
        lsb = buffer[2];
        int bytes_written = write(serial_port, ack, sizeof(ack));
        if(bytes_written < 0)
        {
            printf("Failed to write to serial port. \n");
        }
        else
        {
            printf("Acknowledged");
        }
        output = (msb << 8) + lsb;
    }
    free(port);
    close(serial_port);
    return output; 


}

void send(int controller, __uint16_t data)
{
    __uint8_t msb = data & 0xFF;
    __uint8_t lsb = data >> 8;
    char *port = malloc(13);
    switch(controller)
    {
        case 1: 
        port = "/dev/ttyACM0";
        break;
        case 2: 
        port = "/dev/ttyACM1";
        break;
        case 3:
        port = "/dev/ttyACM2";
        break;
        case 4:
        port = "/dev/ttyACM3";
        break;
        default: "err";
    }    
    if(port == "err")
    {
        printf("Wrong Controller Input");
        
    }
    int serial_port = open(port, O_RDWR);
    if(serial_port < 0)
    {
        printf("Error opening serial port. \n");
        
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if(tcgetattr(serial_port,&tty) != 0)
    {
        printf("Error getting serial port attributes 2\n");
        

    }
    cfsetospeed(&tty,B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag != (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag != CS8;
    if (tcsetattr(serial_port,TCSANOW,&tty) != 0)
    {
        printf("Error setting serial port attributes \n");
        
    }
    __uint8_t buffer[2] = {msb, lsb};
    int bytes_written = write(serial_port, buffer, 2);
    if(bytes_written != 2)
    {
        printf("Error writing to serial port");
    }
    free(port);
    close(serial_port);
}

__uint16_t ferns_receive(int controller){
    char *port = malloc(13);
    char *port_use = port;
    __uint8_t msb;
    __uint8_t lsb;
    __uint16_t output = -1;
    switch(controller)
    {
        case 1: 
        port_use = "/dev/ttyACM0";
        break;
        case 2: 
        port_use = "/dev/ttyACM1";
        break;
        case 3:
        port_use = "/dev/ttyACM2";
        break;
        case 4:
        port_use = "/dev/ttyACM3";
        break;
        default: port_use = "err";
    }
    if(port_use == "err")
    {
        printf("[RECV] Wrong Controller Input\n");
        free(port);
        return -1;
    }


    int serial_port = open(port_use, O_RDWR);
    // printf("%d\n", serial_port);
    if(serial_port < 0)
    {
        printf("[RECV] Error opening serial port. \n");
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if(tcgetattr(serial_port,&tty) != 0)
    {
        printf("[RECV] Error getting serial port attributes 3\n");
    }
    cfsetospeed(&tty,B1152000);
    cfsetispeed(&tty, B1152000);

    tty.c_cflag != (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag != CS8;
    if (tcsetattr(serial_port,TCSANOW,&tty) != 0)
    {
        printf("[RECV] Error setting serial port attributes \n");
        free(port);
        return -1; 
    }
    char readbuff[256];
    memset(&readbuff, '\0',sizeof(readbuff));
    printf("[RECV] waiting... \n");

    int num_bytes = 0;
    while(num_bytes < 2)
    {
        num_bytes = read(serial_port, &readbuff, sizeof(readbuff));
        if(num_bytes > 0)
        {
            // printf("Recieved [%s]\n", readbuff);
            msb = (__uint16_t)readbuff[0]; // set MSB
            // printf("msb: %x\n", msb);
            lsb = (__uint16_t)readbuff[1]; // set LSB
            // printf("lsb: %x\n", lsb);
            memset(&readbuff, '\0', sizeof(readbuff)); // DELETE BUFFER
        }
    }
    
    free(port);
    output = (msb << 8) + lsb; // set output
    return output;
}

int main()
{
    __uint16_t inty_djer = 0;
    while(inty_djer != 0x4C20){
        inty_djer = ferns_receive(1);
        if(inty_djer != 0x0A0D){
            printf("Given: %x\n", inty_djer);
        }
    }
    return 0;
}