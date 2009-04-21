/*
 * liuxiangj@gmail.com
 *
 * 2009.4.7
 *
 * */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLENGTH 255

union wordcontent{
    char T1[MAXLENGTH];
    int T2;
    char T3;
};
typedef struct word{
    int code;
    int con;
    union wordcontent value;
}word;

int count=0;
word sym[MAXLENGTH];

int main(int argc, char *argv[])
{
    void getsym(FILE *, char);
    void fileout(FILE *);

    FILE *fp;
    char c;
    if((fp=fopen(*++argv, "r"))==NULL){
        printf("can't open %s\n",*argv);
        return 1;
    } else {
        c=getc(fp);
        getsym(fp, c);
        fclose(fp);
    }
    fp=fopen("answer", "w");
    fileout(fp);
    fclose(fp);   
    return 0;
}

void getsym(FILE *ifp, char ch)
{
    int issymbol(char);

    int k, i, iskey, ccc;
    char a[MAXLENGTH], *id, sss;
    char *keyword[]={"main","int","char","if","else","for","while"};

    while(ch!=EOF){
        iskey=0;   
        if(isspace(ch)){        /* whether ch is \0\t\n */
            ch=getc(ifp);
        }else if (isalpha(ch)){           /* whether ch is letter */
            k=0;
            do{
                if(k<10){
                    a[k]=ch;
                    k++;
                }
                ch=getc(ifp);
            }while(isalnum(ch));    /* whether ch is letter or digit */
            a[k]='\0';              /* the last bit puts \0 */
            id=a;
            for(i=0;i<7;i++){
                if(!strcmp(id,keyword[i])){
                    strcpy(sym[count].value.T1,id);
                    sym[count].code = i+1;
                    sym[count].con = 1;
                    count++;
                    iskey=1;   
                }
            }
            if(iskey==0){
                strcpy(sym[count].value.T1,id);
                sym[count].code = 10;
                sym[count].con = 1;
                count++;
            }
        }
        else if(isdigit(ch)){
            int x=0,d=1;
            for(i=0;isdigit(ch);i++){
                a[i]=(int)ch-48;
                ch=getc(ifp);
            }
            for(;i>0;i--,d*=10){
                x=x+a[i-1]*d;
            }
            sym[count].value.T2 = x;
            sym[count].code = 20;
            sym[count].con = 2;
            count++;
        }
        else if((ccc=issymbol(ch))){ /* is symbol */
            sss=ch; 
            if(issymbol(ch=getc(ifp))){           
                switch(sss){
                case '=':
                    a[0]=sss;
                    if(ch=='='){
                        a[1]=ch;
                        a[2]='\0';
                        strcpy(sym[count].value.T1,a);
                        sym[count].code = 39;
                        sym[count].con = 1;
                        count++;
                        ch=getc(ifp);
                    }else{
                        printf("error:\'%c%c\' is unidentifying!\n",sss,ch);
                        ch=getc(ifp);
                        break;
                    }
                    break;
                case '>':
                    a[0]=sss;
                    if(ch=='='){
                        a[1]=ch;
                        a[2]='\0';
                        strcpy(sym[count].value.T1,a);
                        sym[count].code = 37;
                        sym[count].con = 1;
                        count++;
                        ch=getc(ifp);
                    }else {
                        printf("error:\'%c%c\' is unidentifying!\n",sss,ch);
                        ch=getc(ifp);
                        break;
                    }
                    break;
                case '<':
                    a[0]=sss;
                    if(ch=='='){
                        a[1]=ch;
                        a[2]='\0';
                        strcpy(sym[count].value.T1,a);
                        sym[count].code = 38;
                        sym[count].con = 1;
                        count++;
                        ch=getc(ifp);
                    }else {
                        printf("error:\'%c%c\' is unidentifying!\n",sss,ch);
                        ch=getc(ifp);
                        break;
                    }
                    break;
                case '!':
                    a[0]=sss;
                    if(ch=='='){
                        a[1]=ch;
                        a[2]='\0';
                        strcpy(sym[count].value.T1,a);
                        sym[count].code = 40;
                        sym[count].con = 1;
                        count++;
                        ch=getc(ifp);
                    }else {
                        printf("error:\'%c%c\' is unidentifying!\n",sss,ch);
                        ch=getc(ifp);
                        break;
                    }
                    break;
                case '&':
                    a[0]=sss;
                    if(ch=='&'){
                        a[1]=ch;
                        a[2]='\0';
                        strcpy(sym[count].value.T1,a);
                        sym[count].code = 42;
                        sym[count].con = 1;
                        count++;
                        ch=getc(ifp);
                    }else {
                        printf("error:\'%c%c\' is unidentifying!\n",sss,ch);
                        ch=getc(ifp);
                        break;
                    }
                    break;
                case '|':
                    a[0]=sss;
                    if(ch=='|'){
                        a[1]=ch;
                        a[2]='\0';
                        strcpy(sym[count].value.T1,a);
                        sym[count].code = 43;
                        sym[count].con = 1;
                        count++;
                        ch=getc(ifp);
                    }else {
                        printf("error:\'%c%c\' is unidentifying!\n",sss,ch);
                        ch=getc(ifp);
                        break;
                    }
                    break;
                default:
                    ungetc(ch,ifp);
                    sym[count].value.T3 =sss;
                    sym[count].code = ccc;
                    sym[count].con = 3;
                    count++;
                    ch=getc(ifp);
                    break;
                }
            } else {
                ungetc(ch,ifp);
                sym[count].value.T3 =sss;
                sym[count].code = ccc;
                sym[count].con = 3;
                count++;
                ch=getc(ifp);
            }
        }
    }
}
int issymbol(char c)
{
    char s[23] = "=+-*/()[]{},:;><000!&0|";
    int i;
    for(i=0;i<23;i++){
        if(c==s[i])
            return (i+21);
    }
    return 0;
}
void fileout(FILE *ofp)
{
    int code,t2,i,con;
    char *t1,t3;
    for(i=0;i<count;i++){
        con=sym[i].con;
        code=sym[i].code;
        t1=sym[i].value.T1;
        t2=sym[i].value.T2;
        t3=sym[i].value.T3;
        switch(con){
        case 1:
            fprintf(ofp,"(%d,%s) ",code,t1);            break;
        case 2:
            fprintf(ofp,"(%d,%d) ",code,t2);            break;
        case 3:
            if(t3!='|' && t3!='!')
                fprintf(ofp,"(%d,%c) ",code,t3);            break;
        default:            break;
        }
        if(((i+1)%4)==0)
            fprintf(ofp,"\n");
    }
}
