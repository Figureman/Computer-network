#include <stdio.h>
#include "DataLink.h"
#include "IpV4.h"
#include "Transport.h"

struct FileName{
    char  data1[10];
    unsigned short status1;
    char  data2[10];
    unsigned short status2;
    char  data3[10];
    unsigned short status3;
    char  data4[10];
    unsigned short status4;
    char  data5[10];
    unsigned short status5;
    unsigned short num;//共有多少个文件
};
struct FileName setFilename(struct FileName one,unsigned int choice,char *data){
    if(choice==1){
        strcpy(one.data1,data);
        one.status1=1;
    }
    else if (choice ==2){
        strcpy(one.data2,data);
        one.status2=1;
    }
    else if(choice==3){
        strcpy(one.data3,data);
        one.status3=1;
    }
    else if (choice==4){
        strcpy(one.data4,data);
        one.status4=1;
    }
    else{
        strcpy(one.data5,data);
        one.status5=1;
    }
    one.num=one.num+1;
    return one;
}
struct FileName  RemoveFilename(struct FileName one,unsigned int choice){
    if(choice==1){
        one.status1=0;
    }
    else if (choice ==2){
        one.status2=0;
    }
    else if(choice==3){
        one.status3=0;
    }
    else if (choice==4){
        one.status4=0;
    }
    else{
        one.status5=0;
    }
    one.num=one.num-1;
    return one;
}
char * getFilename(struct FileName one,unsigned int choice){
    char * reason;
    if(choice==1){
        if(one.status1==0){
            return NULL;
        }
        else{
             reason=one.data1;
        }
    }
    else if(choice==2){
        if(one.status2==0){
            return NULL;
        }
        else{
            reason= one.data2;
        }
    }
    else if(choice==3){
        if(one.status3==0){
            return NULL;
        }
        else{
            reason=one.data3;
        }
    }
    else if(choice==4){
        if(one.status4==0){
            return NULL;
        }
        else{
            reason=one.data4;
        }
    }
    else if(choice==5){
        if(one.status5==0){
            return NULL;
        }
        else{
            reason=one.data5;
        }
    }
    return reason;
}
int write(struct PPP  ppp,char * data)
{
    FILE *fp;
    fp = fopen(data, "w+");
    if (!fp)
    {
        printf("errror!\n");
        exit(-1);
    }
    else{
        fwrite(&ppp, sizeof(ppp), 1, fp);
        fclose(fp);
        printf("Write to File Successfully!\n");
    }
    return 0;
}

struct PPP read(char *data){
    printf("请等待正在查看");
    struct  PPP ppp;
    FILE * fp;
    fp=fopen(data,"r");
    if(!fp)
    {
        printf("errror!\n");
        exit(-1);
    }else{
        printf("Read to File Successfully!\n");
        fread(&ppp,sizeof(ppp),1,fp);
        return ppp;
    }
}
//初始化文件管理状态
struct FileName init(){
    struct FileName one;
    one.status1=0;
    one.status2=0;
    one.status3=0;
    one.status4=0;
    one.status5=0;
    one.num=0;
    return one;
}

int main() {
    unsigned status=0;  //判断是否建立连接
    unsigned choice=0;  //命令选择
    unsigned int Source_port=8080;
    unsigned int Destination_port=8081;
    const char* Source_address="192.168.0.0";
    const char* Destination_address="192.168.1.0";

    struct FileName one;//文件管理器

    printf("欢迎您来到旺旺语句笔记世界\n");
    printf("您目前的ip地址为:%s\n",Source_address);
    printf("您目前所使用的端口号为:%d\n",Source_port);
    printf("您目前可以连接的ip地址为:%s\n",Destination_address);
    printf("您目前可以连接的端口号为:%d\n",Destination_port);
    while(1) {
        printf("----------请输入您要执行的命令：-------------------\n");
        printf("---------------------1.建立连接--------------------\n");
        printf("----------------------2.查看文件列表-------------------------\n");
        printf("----------------------3.读出文件--------------------------\n");//读出后立即选择删除
        printf("-----------------------4.写入文件-------------------------\n");
        printf("-------------------------5.删除文件------------------------\n");
        printf("-------------------------0.Quit------------------------\n");
        scanf("%d", &choice);
        if (choice == 1) {
            status = 1;
            printf("连接已经建立!\n");
            one = init();
            printf("文件管理器已经初始化!\n");
        } 
        else if (choice == 2) {
            if (status == 0) {
                printf("请先建立连接\n");
                continue;
            } else {
                if (one.num == 0) {
                    printf("目前尚未写入文件\n");
                } else {
                    if (one.status1 == 1) {
                        printf("文件一已经写入,命名为%s\n", one.data1);
                    } else {
                        printf("文件一为空\n");
                    }
                    if (one.status2 == 1) {
                        printf("文件二已经写入,命名为%s\n", one.data2);
                    } else {
                        printf("文件二为空\n");
                    }
                    if (one.status3 == 1) {
                        printf("文件三已经写入,命名为%s\n", one.data3);
                    } else {
                        printf("文件三为空\n");
                    }
                    if (one.status4 == 1) {
                        printf("文件四已经写入,命名为%s\n", one.data4);
                    } else {
                        printf("文件四为空\n");
                    }
                    if (one.status5 == 1) {
                        printf("文件五已经写入,命名为%s\n", one.data5);
                    } else {
                        printf("文件五为空\n");
                    }

                }
            }
        } 
        else if (choice == 3) {
            if (status == 0) {
                printf("请先建立连接!\n");
                continue;
            } else {
                unsigned int datachoice;
                printf("请输入你要读取的文件的序号:");
                scanf("%d", &datachoice);
                char *FileName = getFilename(one, datachoice);
                printf("HHHHHHHHHH%s",FileName);
                if (FileName == NULL) {
                    printf("该文件未被写入,请重新选择");
                    continue;
                };
                struct PPP ppp = read(FileName);
                /*数据链路层解封装*/
                struct Ipv4 ip = dataLinkUnpack(ppp);
                /*********网络层开始解压*************/
                struct UDP udp = unpackIP(ip);
                /**********运输层开始解压************/
                unsigned char *ans = TransportUnpack(udp, ip.Source_address, ip.Destination_address);
                printf("应用层数据 %s\n", ans);
                
            }
        } 
        else if (choice == 4) {
            if (status == 0) {
                printf("请先建立连接!\n");
                continue;
            } else {
                unsigned int datachoice;
                printf("请输入你要写入的文件的序号:\n");
                scanf("%d", &datachoice);
                gets();
                char *data = getFilename(one, datachoice);
                char *dataName;
                if (data == NULL) {
                    char str[2][30];
                    for(unsigned int i=0;i<2;i++){
                        if(i==0){
                            char *string = str[0];  //一定要先将指针变量初始化
                            printf("请输入您要写入的文件的名字，请以.txt结尾:\n");
                            gets(string);  //也可以写成gets(str);
                            one=setFilename(one, datachoice, string);
                            dataName=string;
                        }
                        else{
                            char *string = str[1];  //一定要先将指针变量初始化
                            printf("请输入你要写入的数据：");
                            gets(string);  //也可以写成gets(str);
                            unsigned int length = strlen(string);
                            /*运输层开始封装*/
                            struct UDP udp = TransportPack(string, length, Source_address, Destination_address, Source_port,
                                                   Destination_port);
                            /*网络层开始封装*/
                            struct Ipv4 ip = packIP(udp, Source_address, Destination_address);
                            //unsigned char * ip1=(unsigned char *)(&ip);
                            /*数据链路层分装*/
                            struct PPP ppp = dataLinkPack(ip, ip.length, 0);
                            /****Write File***/
                            write(ppp,dataName);
                        }
                    }
                } else {
                    printf("该文件已经被写入,请重新查找文件或者删除某一个文件");
                }
            }
        }
        else if(choice==5){
            unsigned int datachoice;
            printf("请输入你要删除的文件的序号:\n");
            scanf("%d", &datachoice);
            char *data = getFilename(one, datachoice);
            if(data==NULL){
                printf("文件为空\n");
                continue;
            }
            one=RemoveFilename(one,datachoice);
            remove(data);
            printf("文件%s已删除\n",data);
        }
        else if (choice==0){
            printf("欢迎下次光临\n");
            break;
        }
        else{
            printf("指令错误请重新输入\n");
            continue;
        }

    }
    return 0;
};
