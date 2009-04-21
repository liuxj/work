/**
 * (C) Copyright 2009
 * Author: xiangjun liu <liuxiangj@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <ctype.h>
#define MAX 255

int stack[MAX], sp = 0, count = 0, con = 0; 
/* count use to  line number
 * con is a sign to stop or not */
int main(int argc, char *argv[])
{
    void push (int);
    int pop (void);
    int getop (void);
    int *identify_string(void);
	
    int yy_pushtab[13][4] = {
        {257,1,258,0},
        {256,0},
        {0},
        {260,259,0},
        {0},
        {260,259,2,0},
        {0},
        {262,261,0},
        {262,261,3,0},
        {0},
        {5,258,4,0},
        {6,0},
        {256,0}
    };
    int yy_d[8][7] = {
        {-1, 0, -1, -1, 0,-1, 0},
        {2, 1, -1, -1, 1, -1, 1},
        {-1,4,-1,-1,3,4,3},
        {-1,-1,-1,-1,7,-1,7},
        {-1,6,5,-1,-1,6,-1},
        {-1,-1,-1,-1,10,-1,11},
        {-1,9,9,8,-1,9,-1},
        {-1,12,-1,-1,12,-1,12}
    };
	int what, *p, c, i;  
    /* p point to value of string
     * c store top vlaue of stack */
    p=identify_string();
    if(con==0) {
        push(263);              /* initilize */
        printf("No.   stack\t\twhat_to_do\n------------\n");
        while (sp > 0)          /* stack is not empty */
        {
            if ((c=getop()) >= 0 && c <=6){ /* c is a terminal symbol */
                if (c != *p) {  /* c dont equal its value */
                    printf("error: grammar error 1\n", c);
                    break;
                } else {
                    printf("%2d    ", ++count);
                    for(i=0;i<sp;i++) /* print stack */
                        printf("%d ",stack[i]); 
                    printf("\n");
                    pop();
                    p++;        /* point to  next value of string */
                }
            } else {
                what = yy_d[(getop()-256)][*p];
                if (what == -1) {
                    printf("error: grammar error 2\n");
                    break;
                } else {
                    printf("%2d    ", ++count); /* print line numbers */
                    for(i=0;i<sp;i++) /* print stack */
                        printf("%d ",stack[i]); 
                    printf("\t\t%d", what); /* print what_to_do */
                    printf("\n");
                    pop();
					i=0;
                    while(yy_pushtab[what][i] != 0){ /* push all contents of yy_pushtab */
                        push(yy_pushtab[what][i++]);
                    }
                }
            }
        } 
    }
    return 0;
}

void push(int val)
{
    if (sp < MAX)               /* stack is not full */
        stack[sp++] = val;      /* push value */
    else
        printf("error:push stack full, can't push %d\n", val);
}

int pop(void)
{
    if (sp > 0)                 /* stack is not empty */
        return stack[--sp];     /* pop value */
    else {
        printf("error:pop stack empty\n");
        return 0;
    }
}

int getop(void)
{
    if (sp > 0)                 /* stack is not empty */
        return stack[sp-1];     /* just fetch top value */
    else {
        printf("error:getop stack empty\n");
        return 0;
    }
}

int *identify_string(void)
{
    char ch, buf[MAX], *pbuf;
    /* "buf" is buffer of input string
     * "pbuf" point to "buf"*/
    int in[MAX], *pin, k=0, kk,i;
    /* "in" store input string
     * "pin" point to "in" */
    printf("input string: "); 
    while((buf[k++]=getchar()) != '\n')
        ;
    buf[k] = '\0';              /* string is end of \0 */
    buf[--k] = '#';             /* put # first */
    pbuf = buf;
    k = 0;
    while(*pbuf != '\0') {      /* whether reach the end of sting */
        if(isdigit(*pbuf)) {    /* whether is a number */
            while(isdigit(*++pbuf)) /* skip numbers */
                ;
            pbuf--;             /* back a character */
            in[k++] = 6;        /* 6 is num's value */
        } else if(*pbuf==')')
            in[k++] = 5;        /* 5 is )'s value */
        else if(*pbuf=='(')
            in[k++] = 4;        /* 4 is ('s value */
        else if(*pbuf=='*')
            in[k++] = 3;        /* 3 is *'s value */
        else if(*pbuf=='+')
            in[k++] = 2;        /* 2 is +'s value */
        else if(*pbuf==';')
            in[k++] = 1;        /* 1 is ;'s value */
        else if(*pbuf=='#')
            in[k++] = 0;        /* 0 is #'s value */
        else if(*pbuf=='\n')
            ;                   /* skip '\n' */
        else {
            printf("error: %c is unknown.\n", *pbuf);
            con = 1;            /* unknown character, stop program */
        }
        pbuf++;
    }
    for(kk=0;kk<k && con==0;kk++) /* print the values of the string */
        printf("in[%d]=%d\n",kk,in[kk]);
    pin = in;
    return pin;                 /* return pin */
}
