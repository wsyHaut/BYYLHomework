//
//  main.cpp
//  编译原理实验一
//
//  Created by 石佳欢 on 2019/4/21.
//  Copyright © 2019 石佳欢. All rights reserved.
//

/*cifa fenxi chengxu*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NULL 0

FILE *fp;
char cbuffer;
char *key[9]={"if","else","for","while","do","return","break","continue","int"};
char *border[6]={",",";","{","}","(",")"};
char *arithmetic[4]={"+","-","*","/"};
char *relation[6]={"<","<=","=",">",">=","<>"};
char *consts[20];
char *label[20];
int constnum=0,labelnum=0;

int search(char searchchar[],int wordtype)
{
    int i=0;
    switch (wordtype) {
        case 1:for (i=0;i<=8;i++)
        {
            if (strcmp(key[i],searchchar)==0)
                return(i+1);
        }
        case 2:{for (i=0;i<=5;i++)
        {
            if (strcmp(border[i],searchchar)==0)
                return(i+1);
        }           return(0);
        }
            
        case 3:{for (i=0;i<=3;i++)
        {
            if (strcmp(arithmetic[i],searchchar)==0)
            {
                return(i+1);
            }
        }
            return(0);
        }
            
        case 4:{for (i=0;i<=5;i++)
        {
            if (strcmp(relation[i],searchchar)==0)
            {
                return(i+1);
            }
        }
            return(0);
        }
            
        case 5:{for (i=0;i<=constnum;i++)
        {
            if (strcmp(consts[i],searchchar)==0)
            {
                return(i+1);
            }
        }
            consts[i-1]=(char *)malloc(sizeof(searchchar));
            strcpy(consts[i-1],searchchar);
            constnum++;
            return(i);
        }
            
        case 6:{for (i=0;i<=labelnum;i++)
        {
            if (strcmp(label[i],searchchar)==0)
            {
                return(i+1);
            }
        }
            label[i-1]=(char *)malloc(sizeof(searchchar));
            strcpy(label[i-1],searchchar);
            labelnum++;
            return(i);
        }
            
    }
    return 0;
}


char alphaprocess(char buffer)
{
    int atype;
    int i=-1;
    char alphatp[20];
    while ((isalpha(buffer))||(isdigit(buffer)))
    {
        alphatp[++i]=buffer;
        buffer=fgetc(fp);
    }
    alphatp[i+1]='\0';
    if (atype=search(alphatp,1))
        printf("(1, \"%s\")\n",alphatp);
    else
    {
        atype=search(alphatp,6);
        printf("(2, \"%s\")\n",alphatp);
    }
    return(buffer);
}

char digitprocess(char buffer)
{
    int i=-1;
    char digittp[20];
    int dtype;
    while ((isdigit(buffer)))
    {
        digittp[++i]=buffer;
        buffer=fgetc(fp);
    }
    digittp[i+1]='\0';
    dtype=search(digittp,5);
    printf("(3, \"%s\")\n",digittp);
    return(buffer);
}

char otherprocess(char buffer)
{
    
    int i=-1;
    char othertp[20];
    int otype,otypetp;
    othertp[0]=buffer;
    othertp[1]='\0';
    if (otype=search(othertp,3))
    {
        printf("(4, \"%s\")\n",othertp);
        buffer=fgetc(fp);
        goto out;
    }
    
    if (otype=search(othertp,4))
    {
        buffer=fgetc(fp);
        othertp[1]=buffer;
        othertp[2]='\0';
        if (otypetp=search(othertp,4))
        {
            printf("(4, \"%s\")\n",othertp);
            goto out;
        }
        else
            othertp[1]='\0';
        printf("(4, \"%s\")\n",othertp);
        goto out;
    }
    
    if (buffer==':')
    {
        buffer=fgetc(fp);
        if (buffer=='=')
            printf(":= (2,2)\n");
        buffer=fgetc(fp);
        goto out;
    }
    else
    {
        if (otype=search(othertp,2))
        {
            printf("(5, \"%s\")\n",othertp);
            buffer=fgetc(fp);
            goto out;
        }
    }
    
    if ((buffer!='\n')&&(buffer!=' '))
        printf("%c error,not a word\n",buffer);
    buffer=fgetc(fp);
out:      return(buffer);
}


int main()
{
    
    int i;
    char filename[100] = "/Users/jiahuanshi/Desktop/test.txt";
    char str[20] = "hello";
    
    
    for (i=0;i<=20;i++)
    {
        label[i]=str;
        consts[i]=str;
    };
    printf("初始化完成！");
    if ((fp=fopen(filename,"r"))==NULL)
    {
        printf("打开文件失败");
        printf("error");
    }
    else
    {
        printf("打开文件成功！\n");
        cbuffer = fgetc(fp);
        while (cbuffer!=EOF)
        {
            if (isalpha(cbuffer))
                cbuffer=alphaprocess(cbuffer);
            else if (isdigit(cbuffer))
                cbuffer=digitprocess(cbuffer);
            else cbuffer=otherprocess(cbuffer);
        }
        printf("over\n");
        getchar();
    }
}
