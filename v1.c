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
    int dns=0; //dns vagy sem 1 igen 0 nem
    int onlychar=0; // 0 -> számok és speciális karakterből áll || 1 -> betűkből és spec karakterekből áll || 2 -> van benne szám is meg betű is 
    
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i]>96 && a[i]<123)
            onlychar=1;
        
        if(a[i]>47 && a[i]<58 && onlychar==1)
            onlychar=2;
    }
    
    switch(onlychar)
    {
        case 0:
            for(int i=0;i<strlen(a);i++)
            {
                if(a[i]=='.')
                    dot_cnt++;
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
                
                if(sv>255 || sv==127)
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
        break;
        
        case 1:
            error=0;
            printf("Hostname looks valid! The program will try to connect to that device...\n");
        break;
        
        default:
            fprintf(stderr,"Invalid target try again!\n");
            error=1;
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
        printf("Enter the target IPv4 address or the hostname: ");
        scanf("%s",ip_address);
        printf("Checking...\n");
        strcpy(check_ip_address,ip_address);
        int sv=checkipaddress(check_ip_address);          
        if(sv==0)
        {
            run_ipchecking=0;
        }
            
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
            strcpy(text,"ssh ");
            strcat(text,login_name_ssh);
            strcat(text,"@");
            strcat(text,ip_address);
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
