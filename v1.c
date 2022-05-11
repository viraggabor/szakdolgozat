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
#include <termios.h>

#include "mymiscs.h" //ellenőrző fv-ek, titkosítás, 
                    

#define N 1000
#define BUFSIZE 1024                 // Max length of buffer


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
    FILE *f= fopen("login.txt","r");
    int i=0;
    int j=0;
    int key[5]={1,-4,9,14,-1};
    char sv='0';
    int cnt=0;
    int success=1;
    
    //end of variables//
    
    
    printf("//////////////\n");
    printf("/Program v0.5/\n");
    printf("//////////////\n");
    
    
    while(success)
    {
        cnt=0;
        char login_name[30]=""; 
        char login_pw[30]="";   
        printf("Login: ");
        while(cnt!=2)
        {
            if(cnt==0)
            {
                sv = getch();
                if(sv!='\n'){
                    login_name[i]=sv;
                    i++;  
                }
                else
                {
                    cnt++;
                    i=0;
                    if(cnt==1)
                        printf("\nPassword: ");
                }
            }
            if(cnt==1)
            {
                sv = getch();
                if(sv!='\n')
                {
                    login_pw[i]=sv;
                    i++;
                }
                else
                {   
                    i=0;
                    cnt++;
                }
            }
        }
        char line[60]="";
        char *token;
        char name_sv[30]="";
        char pw_sv[30]="";
        while(fgets(line,60,f))
        {
            j=0;
            char changed_line[60]="";
            if(line[strlen(line)-1]=='\n')
                line[strlen(line)-1]='\0';
            for(int i=0;i<strlen(line);i++)
            {
                if(j==5)
                    j=0;
                changed_line[i]=line[i]-key[j];  
                j++;        
            }
            token=strtok(changed_line," ");
            strcpy(name_sv,token);
            token=strtok(NULL,"\n");
            strcpy(pw_sv,token);
            if((strcmp(login_name,name_sv)==0)&& (strcmp(login_pw,pw_sv)==0)) 
            {
                success=0;            
            }
            
        }
        if(success==1)
                fprintf(stderr,"\nFailed login attempt! Try again!\n");
        rewind(f);
    }
    printf("\nSuccessful login!\n");
    fclose(f);
    printf("-----------------------\n\n");
    
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
