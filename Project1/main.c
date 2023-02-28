#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define SIGNIFICANTDIGITS  100
enum OPERATOR
{
      ADD=1, SUBSTRUCT, MUL, DIV
};


struct NUMBER{
    int x ; //10以内的数字
    int exp; 
    int mantissa[SIGNIFICANTDIGITS-1]; //位数：significantDigits-1
    int countNumber;
};
//把字符串转化为int array
 struct NUMBER parseNumber(char num[],struct NUMBER res,int size){
    int begin=0;
    res.exp=0;
    if(num[0]=='0'){
        begin=2;
        res.exp=-1;
        while(num[begin]=='0'){
            begin++;
            res.exp--;
        }
    }
    for(int i=0;i<SIGNIFICANTDIGITS-1;i++){
        res.mantissa[i]=0;
    }
    //指尾数的个数
    int coutNumber=0;
    int e=0;
    bool hasDot=false;
    //第一个数字
    res.x=num[begin]-'0';
    for(int i = begin+1 ;i < size ;i++ ){

        if(isdigit(num[i])){
            res.mantissa[coutNumber]=num[i]-'0';
            coutNumber++;
            if(!hasDot){
                e++;
            }
        }
        else if(num[i]=='e'||num[i]=='E'){
            int exp=0;
            int sign=1;
            if(num[i+1]=='-'){
                sign=-1;
            }
            else{
                exp=num[i+1]-'0';
            }
            i++;
            while(i<size-1){
                exp=exp*10+num[i+1]-'0';
                i++;
            }
            exp=exp*sign;
            res.exp=res.exp+exp;
            break;
        }
        else if(num[i]=='.'){
            hasDot=true;
        }
    }

    res.exp=res.exp+e;
    res.countNumber=coutNumber;
    return res;
}

int get_length(char str[])
{
	char *p = str;
	int count = 0;
	while (*p++ != '\0')
	{
		count++;
	}
	return count;
}
int chooseOperator(char symble[]){
    switch (symble[0])
    {
    case '+':
        return 1;
    case '-':
        return 2;
    case '/':
        return 4;
    default:
        return 3;
    }
    return 0;
}


void mul(struct NUMBER num1,struct NUMBER num2){
    //乘法不用对齐

    char ans[SIGNIFICANTDIGITS*2]={0};
    for(int i=num2.countNumber-1;i>=-1;i--){
        for(int j=num1.countNumber-1;j>=-1;j--){
            int b=num1.mantissa[j];
            int a=num2.mantissa[i];
            if(j==-1){
                b=num1.x;
            }
            if(i==-1){
                a=num2.x;
            }

            int tmp=a*b;
            ans[num2.countNumber+num1.countNumber-2-i-j]+=tmp;
            //进位处理
            ans[num2.countNumber+num1.countNumber-1-i-j]+=(ans[num2.countNumber+num1.countNumber-2-i-j]/10);
            ans[num2.countNumber+num1.countNumber-2-i-j]=ans[num2.countNumber+num1.countNumber-2-i-j]%10;
        }
    }
    int exp=num1.exp+num2.exp;
    //判断x有没有变成两位
    if(ans[num1.countNumber+num2.countNumber+1]!=0){
        exp=exp+1;
    }
    //输出结果
    for(int i=num1.countNumber+num2.countNumber+1;i>=0;i--){
        if((num1.x==0||num2.x==0)){
            return;
        }
        else if(i==num1.countNumber+num2.countNumber+1&&ans[num1.countNumber+num2.countNumber+1]==0){
            continue;
        }
        printf("%d",ans[i]);
        if(i==num1.countNumber+num2.countNumber+1 && ans[i]!=0){
            printf(".");
        }
        if(i==num1.countNumber+num2.countNumber && ans[i+1]==0){
            printf(".");
        }
    }
    printf("e%d\n",exp);
}

int main(int argc, char* argv[]) {


    char* o=argv[2];
    char opt[1];
    char* tmp1 = argv[2];
    memcpy(opt, tmp1, 1);
    int operator=chooseOperator(opt);

    char numA[SIGNIFICANTDIGITS+2] = {0};
    char* tmpA = argv[1];
    strcpy(numA, tmpA);
    memcpy(numA, tmpA, sizeof(numA));
    int lengthA=get_length(argv[1]);

    struct NUMBER num1;
    num1=parseNumber(numA,num1,lengthA);

    char numB[SIGNIFICANTDIGITS+2] = {0};
    char* tmpB = argv[3];

    strcpy(numB, tmpB);
    memcpy(numB, tmpB, sizeof(numB));
    int lengthB=get_length(argv[3]);

    struct NUMBER num2;
    num2=parseNumber(numB,num2,lengthB);




    switch (operator)
    {
    case MUL:
        /* code */
        mul(num1,num2);
        break;
    default:
        break;
    }
    return 0;
}



