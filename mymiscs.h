#ifndef _mymiscs
#define _mymiscs 1

//checker függvény ide kerül ki a jobbátláthatóság érdekében
//

//forrás ehhez a fv-hez https://www.geeksforgeeks.org/print-in-place-of-characters-for-reading-passwords-in-c/
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int getche(void) // * irat ki
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}



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


#endif /* mymiscs.h */
