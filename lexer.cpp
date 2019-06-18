#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
char Filename[30];  //文件名
FILE *fpin;   //声明一个函数指针
char ch,prog[1000],token[8];
char *keyword[8]={(char*)"if",(char*)"then",(char*)"else",(char*)"end",(char*)"repeat",(char*)"until",(char*)"read",(char*)"write"};
int p=0,symbol=0,n;
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
void GetToken()   //词法分析
{
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
        int temp=0;
        
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
            // default: symbol=-2;cout<<"Error!\n";break;
        }
    }
}

int main(void){
    /*读入文件*/
    cout<<"Please input Filename:";
    for(;;){
        cin>>Filename;
        int temp=0;
        while(Filename[temp]!='\0'){
            temp++;
        }  
        if((fpin=fopen(Filename,"r"))!=NULL)
            break;
        else 
            cout<<"Filename Error! Repeat:";
    }
    /*将文件内容存入字符串prog*/
    p=0;
    do{
        ch=fgetc(fpin);
        prog[p++]=ch;
    }while(ch!=EOF);

    
    ofstream outFile;
    outFile.open("C:\\Users\\45312\\Documents\\lex.txt");

    p=0;  
    do{
        GetToken();   //词法分析
        switch(symbol)
        {
            case -1:
            case -2:break;
            default:{
                outFile<<"("<<symbol<<","<<token<<")"<<endl;
                cout<<"("<<symbol<<","<<token<<")"<<endl;  
                break;
            }
        }
    }while(ch!=EOF);

    return 0;
}
