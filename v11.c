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
#include "mymiscs.h"


int main()
{
    //variables
    int line1=line_empty(1); //1-> szabad 0->foglalt
    int line2=line_empty(2);
    int line3=line_empty(3);
    int line4=line_empty(4);
    int line5=line_empty(5); //1-> szabad 0->foglalt
    int line6=line_empty(6);
    int line7=line_empty(7);
    int line8=line_empty(8);
    //printf("%d %d %d %d\n",line1, line2, line3, line4);
    
    int input=0;
    int valid=1; //
    int run=1;
    int emptyline=2;
    char line[100]="";
    char *token;
    
    FILE *f= fopen("login.txt","r");
    FILE *g= fopen("connections.txt","r");
    char text[100]="";
    char login[30]="";
    int i=0;
    int j=0;
    int key[5]={1,-4,9,14,-1};
    char sv='0';
    int cnt=0;
    int success=1;
    printf("///////////////////////\n");
    printf("/Terminal Server Login/\n");
    printf("///////////////////////\n");
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
                        if(sv==8 || sv==127)
                        {
                            if(i!=0){
                            i--;
                            login_name[i]=' ';
                            }
                        }
                        else
                        {
                            login_name[i]=sv;
                            i++;
                        }
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
                        if(sv==8 || sv==127) // 127 oka: https://stackoverflow.com/questions/4363309/how-to-check-for-the-backspace-character-in-c
                        {
                            if(i!=0){
                            i--;
                            login_pw[i]=' ';
                            }
                        }
                        else
                        {
                            login_pw[i]=sv;
                            i++;
                        }
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
                    strcpy(login,login_name);
                }
                
            }
            if(success==1)
            {
                fprintf(stderr,"\nFailed login attempt! Try again!\n");
                logs(login_name,"-",2);
            }
            rewind(f);
        }
        fclose(f);
    system("clear");
    printlines();
    while(run){
        
        while(valid)
        {
            printf("Enter your input: ");
            scanf("%d",&input);
            if(input!=1 && input!=2 && input!=3 && input!=4 && input!=5 && input!=6 && input!=7 && input!=8 &&input!=100 && input!=101 && input!=102 && input!=103 && input!=104)
            {
                fprintf(stderr,"Invalid input try again!\n");
            }
            else
                valid=0;
        }
        valid=1;
        switch(input)
        {
            
            case 1: //line1
                emptyline=line_empty(1);
                if(emptyline==1)
                {
                logs(login,"line1",0);
                system("sudo minicom line1");
                logs(login,"line1",1);
                }
                else
                    fprintf(stderr,"This line is taken try another one");
                    
                break;
            case 2: //line2
                emptyline=line_empty(2);
                if(emptyline==1)
                {
                logs(login,"line2",0);
                system("sudo minicom line2");
                logs(login,"line2",1);
                }
                else
                    fprintf(stderr,"This line is taken try another one");
                    
                break;
            case 3: //line3
                emptyline=line_empty(3);
                if(emptyline==1)
                {
                    logs(login,"line3",0);
                    system("sudo minicom line3");
                    logs(login,"line3",1);
                }
                else
                    fprintf(stderr,"This line is taken try another one");
                
                break;
            case 4: //line4
                emptyline=line_empty(4);
                if(emptyline==1)
                {
                    logs(login,"line4",0);
                    system("sudo minicom line4");
                    logs(login,"line4",1);
                }
                else
                    fprintf(stderr,"This line is taken try another one");
                
                break;
            case 5: //line5
                emptyline=line_empty(5);
                if(emptyline==1)
                {
                    logs(login,"line5",0);
                    system("sudo minicom line5");
                    logs(login,"line5",1);
                }
                else
                    fprintf(stderr,"This line is taken try another one");
                
                break;
            case 6: //line6
                emptyline=line_empty(6);
                if(emptyline==1)
                {
                    logs(login,"line6",0);
                    system("sudo minicom line6");
                    logs(login,"line6",1);
                }
                else
                    fprintf(stderr,"This line is taken try another one");
                
                break;
            case 7: //line5
                emptyline=line_empty(7);
                if(emptyline==1)
                {
                    logs(login,"line7",0);
                    system("sudo minicom line7");
                    logs(login,"line7",1);
                }
                else
                    fprintf(stderr,"This line is taken try another one");
                
                break;
            case 8: //line5
                emptyline=line_empty(8);
                if(emptyline==1)
                {
                    logs(login,"line8",0);
                    system("sudo minicom line8");
                    logs(login,"line8",1);
                }
                else
                    fprintf(stderr,"This line is taken try another one");
                
                break;
            case 100: //empty lines
                
                line1=line_empty(1);
                line2=line_empty(2);
                line3=line_empty(3);
                line4=line_empty(4);
                line5=line_empty(5);
                line6=line_empty(6);
                line7=line_empty(7);
                line8=line_empty(8);
                system("clear");
                printf("-----------------------\n");
                printf("-     Empty lines     -\n");
                printf("-----------------------\n\n");
                if(line1==1)
                    printf("line 1 is empty\n");
                if(line2==1)
                    printf("line 2 is empty\n");
                if(line3==1)
                    printf("line 3 is empty\n");
                if(line4==1)
                    printf("line 4 is empty\n");
                if(line5==1)
                    printf("line 5 is empty\n");
                if(line6==1)
                    printf("line 6 is empty\n");
                if(line7==1)
                    printf("line 7 is empty\n");
                if(line8==1)
                    printf("line 8 is empty\n");
                
                if(line1==0 && line2==0 && line3==0 &&line4==0 && line5==0 && line6==0 && line7==0 && line8==0)
                    printf("There is no empty line at the moment try again later!");
                printf("\n");
                sleep(5);
                system("clear");
                printlines();            
                
                
                break;
            
            case 101: //power outlet manager  
                
                system("clear");
                printf("------------\n");
                printf("-APC config-\n");
                printf("------------\n");
                int outlet_value=0;
                int outlet_checker_run=1;
                int outlet_command=0;
                int outlet_event_run=1;
                //int outlet_event=0;
                int apc_run=1;
                
                while(apc_run)
                {
                    while(outlet_checker_run)
                    {
                        printf("Choose outlet <1-8>\n");
                        printf("9 - Outlet status\n");
                        printf("10 - Back\n");
                        scanf("%d",&outlet_value);
                        if(outlet_value<0 || outlet_value>10)
                            fprintf(stderr,"Invalid input!\n");
                        else
                        {
                            if(outlet_value==10)
                            {
                                outlet_checker_run=0;
                                apc_run=0;
                                outlet_event_run=0;
                            }
                            else if(outlet_value==9)
                                system("apc --status");
                            else
                                outlet_checker_run=0;
                        }
                        
                    }
                    while(outlet_event_run)
                    {
                        printf("------------------------\n");
                        printf("Your chosen outlet: %d \n",outlet_value);
                        printf("------------------------\n");
                        printf("1 - Power on\n");
                        printf("2 - Power off\n");
                        printf("3 - Reboot device\n");
                        printf("4 - Back\n");
                        scanf("%d",&outlet_command);
                        if(outlet_command==4) //back
                        {
                            outlet_event_run=0;
                            outlet_checker_run=1;
                            
                        }
                        else if(outlet_command==3) //reboot
                        {
                            if(outlet_value==1)
                                system("apc --reboot 1");
                            else if(outlet_value==2)
                                system("apc --reboot 2");
                            else if(outlet_value==3)
                                system("apc --reboot 3");
                            else if(outlet_value==4)
                                system("apc --reboot 4");
                            else if(outlet_value==5)
                                system("apc --reboot 5");
                            else if(outlet_value==6)
                                system("apc --reboot 6");
                            else if(outlet_value==7)
                                system("apc --reboot 7");
                            else if(outlet_value==8)
                                system("apc --reboot 8");                            
                        }
                        else if(outlet_command==2) //off
                        {
                            if(outlet_value==1)
                                system("apc --off 1");
                            else if(outlet_value==2)
                                system("apc --off 2");
                            else if(outlet_value==3)
                                system("apc --off 3");
                            else if(outlet_value==4)
                                system("apc --off 4");
                            else if(outlet_value==5)
                                system("apc --off 5");
                            else if(outlet_value==6)
                                system("apc --off 6");
                            else if(outlet_value==7)
                                system("apc --off 7");
                            else if(outlet_value==8)
                                system("apc --off 8");
                        }
                        else if(outlet_command==1) //on
                        {
                            if(outlet_value==1)
                                system("apc --on 1");
                            else if(outlet_value==2)
                                system("apc --on 2");
                            else if(outlet_value==3)
                                system("apc --on 3");
                            else if(outlet_value==4)
                                system("apc --on 4");
                            else if(outlet_value==5)
                                system("apc --on 5");
                            else if(outlet_value==6)
                                system("apc --on 6");
                            else if(outlet_value==7)
                                system("apc --on 7");
                            else if(outlet_value==8)
                                system("apc --on 8");
                        }
                    }
                    
                    
                }
                system("clear");
                printlines();
                break;
                
            case 102: //history
                rewind(g);
                printf("\n");
                while(fgets(line,100,g))
                {
                    token=strtok(line,"\t");
                    if(strcmp(token,"LOGIN")==0)
                    {
                        token=strtok(NULL,"\t");
                        if(strcmp(login,token)==0)
                        {
                            token=strtok(NULL,"\t");
                            printf("%s",token);
                            token=strtok(NULL,"\t");
                            printf("\t%s",token);
                        }
                            
                    }
                }
                printf("\n");
                sleep(5);
                system("clear");
                printlines();
                
                break;
                
            case 103: //clean screen
                system("clear");
                printlines();
                break;
                
            case 104: //quit
                run=0;
                break; 
        }
        
    }
    fclose(g);    
    
    return 0;
    
}
