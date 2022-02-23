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


    

int main(int argc, char *argv[])
{
    
    //variables//
    
    int connection_type=0; // 1- telnet 2- ssh 3- serial
    int run_input=1; // beolvasáskor mikor kéri a számot annak a futásának az irányítására
    int run_ipchecking=1; //ip cím ellenőrzés céljából
    char ip_address[30]=""; //ip cím itt van eltárolva ellenőrzés
    char check_ip_address[30]="";
    char login_name_ssh[40]="";
    char domain_name[100]="";
    char text[100]="";
    
    
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
    
    while(run_ipchecking)
    {
        printf("Enter the target IPv4 address example(192.168.10.69): ");
        scanf("%s",ip_address);
        printf("Checking IP address...\n");
        strcpy(check_ip_address,ip_address);
        int sv=checkipaddress(check_ip_address);        
        if(sv==0)
            run_ipchecking=0;
    }
    
    switch(connection_type)
    {
        case 1:
            printf("Your chosen connection type is Telnet!\n");
            strcpy(text,"telnet ");
            strcat(text,ip_address);  
            system(text);
        break;
        case 2:
            printf("Your chosen connection type is SSH!\n");
            printf("Login name for ssh: ");
            scanf("%s",login_name_ssh);
            printf("SSH domain name (if you don't know type 0): ");
            scanf("%s",domain_name);
            printf("%d",strlen(domain_name));
            strcpy(text,"ssh ");
            strcat(text,login_name_ssh);
            strcat(text,"@");
            if(strcmp(domain_name,"0")==0)
                strcat(text,ip_address);
            else
                strcat(text,domain_name);
            system(text);    
            
            
        break;
        case 3:
            printf("Your chosen connection type is Serial!\n");
        break;
      
      default :
         fprintf(stderr,"Invalid input!\n");
    }
    
    
    
    
    
    
    
    
    return 0;
}
