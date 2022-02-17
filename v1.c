#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <malloc.h>
#include <omp.h>
#include <fcntl.h>

#define N 1000
#define BUFSIZE 1024                 // Max length of buffer

int checkipaddress(char *a)
{
    int error=0; 
    int dot_cnt=0;// pontokat számoljuk meg tehát ha a pontok száma nem 3. akkor érvénytelen a cím
    char *token; // karakter tömb splitelésekor lesz felhasználva
    for(int i=0;i<strlen(a);i++)
    {
        char sv=a[i];
        if(sv=='.')
            dot_cnt++;
        if(sv!='1' && sv!='2' && sv!='3' && sv!='4' && sv!='5' && sv!='6' && sv!='7' && sv!='8' && sv!='9' && sv!='0' && sv!='.')
        {
            error=1;
            fprintf(stderr,"Invalid IP address!\n");
            return error;
        }
    }
    if(dot_cnt!=3)
    {
        error=1;
        fprintf(stderr,"Invalid IP address!\n");
        
    }
    else
    {  
        
        token=strtok(a,".");
        int sv=atoi(token);
        if(sv>255)
            error++;
        token=strtok(NULL,".");
        sv=atoi(token);
        if(sv>255)
            error++;    
        token=strtok(NULL,".");
        sv=atoi(token);
        if(sv>255)
            error++;
        token=strtok(NULL,".");
        sv=atoi(token);
        if(sv>255)
            error++;
        
        if(error!=0)
        {
            fprintf(stderr,"Invalid IP address!\n");            
        }
        else
        {
            printf("IP address looks valid! The program will try to connect to that device...\n");
            error=0;
        }
    }
    return error;
        
}

int communication(int x, char *b)
{
    /************************** Declarations ********************/
    int s;                            // socket ID
    int flag;                         // transmission flag
    int bytes;                        // received/sent bytes
    int err;                          // error code
    unsigned int server_size;         // length of the sockaddr_in server
    char on;                          // sockopt option
    char buffer[BUFSIZE];             // datagram buffer area
    struct sockaddr_in server;        // address of server

    /********************** Initialization **********************/
    on   = 1;
    flag = 0;
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = inet_addr(b);
    server.sin_port        = htons(x);
    server_size = sizeof server;

    //********************** Creating socket **********************/
    s = socket(AF_INET, SOCK_STREAM, 0 );
    if ( s < 0 ) {
        fprintf(stderr, "Socket creation error.\n");
        exit(12);
    }
    else
        printf("Socket creation done.\n");
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
    setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

    /********************** Connecting ***************************/
    err = connect( s, (struct sockaddr *) &server, server_size);
    if ( err < 0 ) {
        fprintf(stderr, "Connection error.\n");
        exit(13);
    }
    else
        printf("Connection done.\n");

    /********************** Sending data *************************/

    bytes = send(s, buffer, strlen(buffer)+1, flag);
    if ( bytes <= 0 ) {
        fprintf(stderr, "Sending error.\n");
        exit(14);
        }
    else
        printf("Sending done.\n");
    
    /******************** Receiving data *************************/

    bytes = recv(s, buffer, BUFSIZE, flag);
    if ( bytes <= 0 ) {
        fprintf(stderr, "Receive error.\n");
        exit(15);
        }
    else
        printf("Receive done.\n");
        close(s);
        return 0;


       
}
    

int main(int argc, char *argv[])
{
    
    //variables//
    
    int connection_type=0;
    int run_input=1; // beolvasáskor mikor kéri a számot annak a futásának az irányítására
    int run_ipchecking=1; //ip cím ellenőrzés céljából
    char ip_address[30]; //ip cím itt van eltárolva ellenőrzés
    char check_ip_address[30];
    int port=0; // portnak a száma melyen a kommunikációt fogja végezni
    
    //end of variables//
    
    
    printf("//////////////\n");
    printf("/ Program v0 /\n");
    printf("//////////////\n");
    
    
    printf("1 - Telnet\n");
    printf("2 - SSH\n");
    printf("3 - Serial\n");
        
    while(run_input)
    {
            
        printf("For choosing connection type the number from listed above: ");
        scanf("%d",&connection_type);           
        
        if(connection_type !=1 && connection_type !=2 && connection_type !=3)
        {
            fprintf(stderr,"Invalid input!\n");
        }
        else
            run_input=0;        
    }    
    switch(connection_type)
    {
        case 1:
            printf("Your chosen connection type is Telnet!\n");
            port=23;
        break;
        case 2:
            printf("Your chosen connection type is SSH!\n");
        break;
        case 3:
            printf("Your chosen connection type is Console!\n");
        break;
      
      default :
         fprintf(stderr,"Invalid input!\n");
    }
    while(run_ipchecking)
    {
        printf("Enter the target IP address example(192.168.10.69): ");
        scanf("%s",ip_address);
        printf("Checking IP address...\n");
        strcpy(check_ip_address,ip_address);
        int sv=checkipaddress(check_ip_address);        
        if(sv==0)
            run_ipchecking=0;
    }
    communication(port,ip_address);
    
    
    return 0;
}
