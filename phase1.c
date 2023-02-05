#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>



int mkdir(const char *pathname);



char inp[1000];
char inpfirst[100];
char inpaddress[100];
char strinsert[1000];
char whatend[100];
FILE* filep;
int posleft = 0, posright = 0;
void inputf(){
    scanf("%[^\n]", inp);
    getchar();
}

void inpfirstf(){
    char* firstl = strchr(inp, ' ');
    strncpy(inpfirst, inp, firstl-inp);
    inpfirst[firstl-inp] = '\0';

    //Errors:
}


int findadress(){
    char inptmp[1000];
    strcpy(inptmp, inp);
    if(!strstr(inptmp,"--file")){return 0;} //Errors!
    char *dashdashfile;
    char *dashdashfileend;
    dashdashfile = strstr(inptmp,"--file");

    if(strstr(dashdashfile+2, whatend)){dashdashfileend = strstr(dashdashfile+2, whatend);}

    else{dashdashfileend = strchr(dashdashfile, '\0');}

    char* inp1 ;
    inp1 = dashdashfile;
    inp1[dashdashfileend-dashdashfile]='\0';

    char* inpaddfirst;
    char* inpaddfinal;
    if(!strchr(inp1,'/')){printf("NOT ALLOWED!\n");return 0;}
    inpaddfirst = strchr(inp1,'/');
    if(!strrchr(inp1, '"')){inpaddfinal = strchr(inp1, '\0');}
    else{inpaddfinal = strrchr(inp1, '"') - 1 ;}
    strncpy(inpaddress, inpaddfirst +1, inpaddfinal-inpaddfirst); //+1 !!
    inpaddress[inpaddfinal-inpaddfirst] = '\0';
    //printf("%s#", inpaddress);
    //Errors:
    //printf("##%s##\n", inpaddress);
    if(strncmp(inpaddress, "root/", 5)!=0){printf("NOT ALLOWED!\n");return 0;}
    return 1;
}

int findstr(){
    char inptmp[1000];
    strcpy(inptmp, inp);
    if(!strstr(inptmp,"--str")){return 0;} //Errors!
    char *dashdashfile;
    char *dashdashfileend;
    dashdashfile = strstr(inptmp,"--str");
    if(strstr(dashdashfile+2, " --pos")){dashdashfileend = strstr(dashdashfile+2, " --pos");}
    else{dashdashfileend = strchr(dashdashfile, '\0');}
    char* inp1 ;
    inp1 = dashdashfile;
    inp1[dashdashfileend-dashdashfile]='\0';
    inp1 += 6;
    if(*inp1=='"'){
        inp1+=1;
        inp1[dashdashfileend-dashdashfile-8]='\0';
    }
    //printf("str: %s\n", inp1);
    strcpy(strinsert, inp1);

    //Errors:
    return 1;
}

int findpos(){
    char inptmp[1000];
    strcpy(inptmp, inp); 
    if(!strstr(inptmp,"--pos")){return 0;} //Errors!
    char *dashdashfile;
    char *dashdashfileend;
    dashdashfile = strstr(inptmp,"--pos");

    if(strstr(dashdashfile+2, " --pos")){dashdashfileend = strstr(dashdashfile+2, " --pos");}
    else{dashdashfileend = strchr(dashdashfile, '\0');}

    char* inp1 ;
    inp1 = dashdashfile;
    inp1[dashdashfileend-dashdashfile]='\0';
    inp1 += 6;
    sscanf(inp1, "%d:%d", &posleft, &posright);

    //Errors:
    return 1;
}
// int inpaddf(int inp1){
//     char* inpaddfirst;
//     char* inpaddfinal;
//     inpaddfirst = strchr(inp1,'/');
//     inpaddfinal = strrchr(inp1, '"');
//     if(!inpaddfinal){inpaddfinal = strchr(inp1, '\0');}
//     strncpy(inpaddress, inpaddfirst +1, inpaddfinal-inpaddfirst); //+1 !!
//     inpaddress[inpaddfinal-inpaddfirst] = '\0';
//     //Errors:
//     if(strncmp(inpaddress, "root/", 5)){printf("NOT ALLOWED!\n");return 0;}
//     return 1;
// }

int makedirsf(){
    char* tmpinpadress;
    char* ltmp;
    char* rtmp;
    char* dirname;
    char* firstltmp;
    strcpy(tmpinpadress, inpaddress);
    //printf("%s\n", tmpinpadress);
    strcpy(dirname, "salam\0");
    if(!strchr(tmpinpadress, '/')){return 1;}
    ltmp = tmpinpadress;
    rtmp = strchr(tmpinpadress, '/')+1;
    firstltmp = ltmp;
    while(1){
        if(!strchr(rtmp, '/')){break;}
        ltmp = rtmp;
        rtmp = strchr(rtmp, '/')+1;     

    
        //printf("%s\n%s\n##\n", ltmp, rtmp);
        strncpy(dirname, firstltmp, rtmp-firstltmp-1);
        dirname[rtmp-firstltmp-1]='\0';
        // printf("%s\n", dirname);
        mkdir(dirname);
    }

    return 1;
}

int gotopos(int linepos, int wordpos, FILE* filepp){
    rewind(filepp);
    char tmpc = ' ';
    int ii=0;
    int checking = 0;
    for(int i=0; i<posleft;i++){
        tmpc=' ';
        while(tmpc!='\n'){
            if(checking == 1 ){fputc('\n', filepp);break;}
            else{tmpc = fgetc(filepp);}

            if(tmpc == EOF){checking = 1;}
            ii++;
        }
        ii++;   // \n 2tas!!!
    }
    int checking2 = 0;
    for(int i=0;i<wordpos;i++){
        if(checking){fputc('#', filepp);}
        else{tmpc = fgetc(filepp);
            if(tmpc == EOF){checking = 1;}



            if(tmpc == '\n'){
                // fprintf(filepp, "%c%s", )
                printf("Cant do that!");
                return -1;
            }
        }
        ii++;
    }

    if(checking2) fputc('\n', filepp);
    if(checking){
        return -1;
    }
    return ii;

}

int copyforundo(FILE* filepp){
    rewind(filepp);
    char namew [100];
    strcpy(namew, "configs/config_");
    //rewind(filepp);
    FILE* undofile = fopen(namew, "w");
    char tmpchar = ' ';
    tmpchar = fgetc(filepp);
    while (tmpchar != EOF){
        fputc(tmpchar, undofile);
        tmpchar = fgetc(filepp);
    }
    fclose(undofile);
}
int copyforundotmp(FILE* filepp){
    rewind(filepp);
    char namew [100];
    strcpy(namew, "configs/config_tmp");
    //rewind(filepp);
    FILE* undofile = fopen(namew, "w");
    char tmpchar = ' ';
    tmpchar = fgetc(filepp);
    while (tmpchar != EOF){
        fputc(tmpchar, undofile);
        tmpchar = fgetc(filepp);
    }
    fclose(undofile);
}



int main(){
    while (1){
        inputf();
        inpfirstf();


        if(!strcmp(inpfirst,"createfile")){
            strcpy(whatend,":/\0");
            if(findadress()){
                if(makedirsf()){
                    //printf("%s\n", inpaddress);
                    filep = fopen(inpaddress, "a");
                    fclose(filep);
                }
            }
        }

        if(!strcmp(inpfirst,"insertstr")){
            strcpy(whatend," --str\0");
            if(findadress()){
                if(makedirsf()){
                    findstr();
                    findpos();
                    posleft--;
                    //printf("#%s#", inpaddress);
                    // printf("str: %s\npos: %d:%d\n", strinsert, posleft, posright);
                    filep = fopen(inpaddress, "r+");
                    copyforundo(filep);
                    FILE* tmpfilep;
                    tmpfilep = fopen("tempfile.txt", "w");
                    rewind(filep);
                    char tmpchar = ' ';
                    if(gotopos(posleft, posright, filep)!=-1){
                        fseek(filep, gotopos(posleft, posright, filep), SEEK_SET);
                        tmpchar = fgetc(filep);
                        while( tmpchar != EOF ){
                            fputc(tmpchar, tmpfilep);
                            tmpchar = fgetc(filep);
                        }
                    }
                    fclose(tmpfilep);
                    //printf("##%d##", gotopos(posleft, posright, filep));
                    fseek(filep, gotopos(posleft, posright, filep), SEEK_SET);
                    fprintf(filep, "%s", strinsert);
                    
                    tmpfilep = fopen("tempfile.txt", "r");
                    tmpchar = fgetc(tmpfilep);
                    while( tmpchar != EOF ){
                        fputc(tmpchar, filep);
                        tmpchar = fgetc(tmpfilep);
                    }
                    fclose(filep);
                    fclose(tmpfilep);
                }
            }
        }
        if(!strcmp(inpfirst,"cat")){
            strcpy(whatend,":/\0");
            if(findadress()){
                if(makedirsf()){
                    //printf("%s\n", inpaddress);
                    filep = fopen(inpaddress, "r");
                    char tmpchar = ' ';
                    while(tmpchar != EOF){
                        tmpchar = fgetc(filep);
                        printf("%c", tmpchar);
                    }
                    printf("\n");
                    fclose(filep);
                }
            }
        }
        if(!strcmp(inpfirst,"undo")){
            strcpy(whatend,":/\0");
            if(findadress()){
                if(makedirsf()){
                    //printf("%s\n", inpaddress);
                    
                    filep = fopen(inpaddress, "r+");
                    rewind(filep);
                    copyforundotmp(filep);
                    fclose(filep);

                    filep = fopen(inpaddress, "w");
                    char namew [100];
                    strcpy(namew, "configs/config_");
                    rewind(filep);
                    FILE* undofile = fopen(namew, "r");
                    char tmpchar = ' ';
                    tmpchar = fgetc(undofile);
                    while (tmpchar != EOF){
                        fputc(tmpchar, filep);
                        tmpchar = fgetc(undofile);
                    }
                    fclose(undofile);
                    fclose(filep);

                    strcpy(namew, "configs/config_tmp");
                    rewind(filep);
                    undofile = fopen(namew, "r");
                    copyforundo(undofile);
                    fclose(undofile);
                }
            }
        }




    }
}