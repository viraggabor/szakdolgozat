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
        return error;
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
            return error; 
        }
        else
            return error;
    }
        
}

int communication(int x, char *b)
{
    
    
    
}

int main(int argc, char *argv[])
{
    
    //variables//
    
    int connection_type=0;
    int run_input=1; // beolvasáskor mikor kéri a számot annak a futásának az irányítására
    int run_ipchecking=1; //ip cím ellenőrzés céljából
    char ip_address[30]; //ip cím itt van eltárolva ellenőrzés
    
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
            printf("Your chosen connection type is Telnet!");
        break;
        case 2:
            printf("Your chosen connection type is SSH!");
        break;
        case 3:
            printf("Your chosen connection type is Console!");
        break;
      
      default :
         fprintf(stderr,"Invalid input!\n");
    }
    while(run_ipchecking)
    {
        printf("Enter the target IP address example(192.168.10.69): ");
        scanf("%s",ip_address);
        printf("Checking IP address...\n");
        int sv=checkipaddress(ip_address);
        if(sv==0)
            run_ipchecking=0;
    }
    
    
    
    
    return 0;
}
