#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
char Filename[30];  //文件名
FILE *fpin;   //声明一个函数指针
char ch,prog[1000],token[8];
char *keyword[8]={"if","then","else","repeat","until","read","write"};
int p=0,symbol=0;
/*  symbol表
    0->  字母  -> 1 -> 其他 -> 2
         if   -> 3
         then -> 4
         else -> 5
         end  -> 6
         repeat -> 7
         until -> 8
         read -> 9
         write -> 10
         数字  -> 11 -> 其他 -> 12
         + -> 13
         - -> 14
         * -> 15
         / -> 16
         = -> 17
         < -> 18
         ; -> 19
*/
void GetToken(char* prog)   //词法分析
{
    int n;
    for(n=0;n<8;n++){
        token[n]='\0';
    }
    n=0;
    ch=prog[p++];
    while(ch==' '||ch=='\n'||ch=='\t'){ch=prog[p++];}  //跳过空格，换行符，制表符
    if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
        symbol=1;
        do{  //在token中记录单词
            token[n++]=ch;
            ch=prog[p++];
        }while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'));

        symbol=2;
        for(n=0;n<8;n++){
            if(strcmp(token,keyword[n])==0){  //判断token是否为保留字
                symbol=n+3;
            }
        }
        p--;
    }
    else if(ch=='{'){
        do{
            ch=prog[p++];
        }while(ch!='}');
        symbol=-1;
        return;
    }
    else if(ch>='0'&&ch<='9'){
        symbol=11;
        do{
            token[n++]=ch;
            ch=prog[p++];
        }while(ch>='0'&&ch<='9');

        symbol=12;
        p--;
        return;
    }
    else{
        switch(ch)
        {
            case '+':symbol=13;token[0]=ch;break;
            case '-':symbol=14;token[0]=ch;break;
            case '*':symbol=15;token[0]=ch;break;
            case '/':symbol=16;token[0]=ch;break;
            case '=':symbol=17;token[0]=ch;break;
            case '<':symbol=18;token[0]=ch;break;
            case ';':symbol=19;token[0]=ch;break;
            default: symbol=-2;cout<<"词法分析出错，请检查是否输入非法字符！\n";break;
        }
    }
}

int main(void){
    /*读入文件*/
    cout<<"请输入源文件名：";
    for(;;){
        cin>>Filename;
        if((fpin=fopen(Filename,"r"))!=NULL)
            break;
        else 
            cout<<"文件路径错误！请重新输入源文件名：";
    }
    /*将文件内容存入字符串prog*/
    p=0;
    do{
        ch=fgetc(fpin);
        prog[p++]=ch;
    }while(ch!=EOF);

    p=0;  
    do{
        GetToken(prog);   //词法分析
        switch(symbol)
        {
            case -1:
            case -2:break;
            default:cout<<"("<<symbol<<","<<token<<")"<<endl;  break;
        }
    }while(ch!=EOF);
}
