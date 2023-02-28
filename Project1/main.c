#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define  SIGNIFICANTDIGITS  100
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
     bool hasDot=false;
    int begin=0;
    res.exp=0;
    if(num[0]=='0'){
        hasDot=true;
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
    int countNumber=num1.countNumber+num2.countNumber;
    if(ans[num1.countNumber+num2.countNumber+1]!=0){
        exp++;
        countNumber++;
    }
    if(exp<0){
        //前面补0
        printf("0.");
        for(int k=-1;k>exp;k--){
            printf("0");
        }
        //正常输出
        for(int k=countNumber;k>=0;k--){
            printf("%d",ans[k]);
        }
    }
    if(exp<countNumber-1&&exp>=0){
        //补小数点
        for(int k=countNumber;k>=0;k--){
            printf("%d",ans[k]);
            if(countNumber-k==exp){
                printf(".");
            }
        }
    }
    if(exp>=countNumber-1){
        //正常输出
        for(int k=countNumber;k>=0;k--){
            printf("%d",ans[k]);
        }
        //末尾补0
        for(int k=1;k<=exp-countNumber+1;k++){
            printf("%d",0);
        }
    }
    printf("\n");

}

int absCompare(int a,int b){
    int a0=abs(a);
    int b0=abs(b);
    if (a0>b0){
        return a0;
    }
    return b0;
}


void add(struct NUMBER num1,struct NUMBER num2){
    //大数加法
    //小数点对齐
    int addExp=absCompare(num1.exp,num2.exp);
    int countNumberA;
    int countNumberB;
    char numA[SIGNIFICANTDIGITS+addExp];
    char numB[SIGNIFICANTDIGITS+addExp];
    char ans[SIGNIFICANTDIGITS+addExp+1];
    ans[SIGNIFICANTDIGITS+addExp+1]=0;
    for(int i=0;i<SIGNIFICANTDIGITS+addExp-1;i++){
        numA[i]=0;
        numB[i]=0;
        ans[i]=0;
    }

    
    int exp;
    
    int flag=1;
    if(num1.exp<num2.exp){
        flag=0;
    }

    if(flag==1){
        countNumberA=num1.countNumber+1;
        countNumberB=num2.countNumber+1+num1.exp-num2.exp;
        exp=num1.exp;
        //给num2补0
        numA[0]=num1.x;
        numB[num1.exp-num2.exp]=num2.x;
        for(int i=0;i<num1.countNumber;i++){
            numA[i+1]=num1.mantissa[i];
        }
        int k=0;
        for(int i=num1.exp-num2.exp+1;i<countNumberB;i++){
            numB[i]=num2.mantissa[k];
            k++;
        }
    }
    else{
        countNumberB=num2.countNumber+1;
        countNumberA=num1.countNumber+1+num2.exp-num1.exp;
        exp=num2.exp;
        //给num1补0
        numB[0]=num2.x;
        numA[num2.exp-num1.exp]=num1.x;
        for(int i=0;i<num2.countNumber;i++){
            numB[i+1]=num2.mantissa[i];
        }
        int k0=0;
        for(int i=num2.exp-num1.exp+1;i<countNumberA;i++){
            numA[i]=num1.mantissa[k0];
            
            k0++;
        }
    }

    int countNumber=absCompare(countNumberA,countNumberB);



    //初始化完成，开始加法运算
    for(int i=countNumber-1;i>=0;i--){
        int tmp = numA[i]+numB[i];
        
        ans[countNumber-i-1]+=tmp;
        //进位处理
        ans[countNumber-i]+=ans[countNumber-i-1]/10;
        ans[countNumber-i-1]=ans[countNumber-i-1]%10;
    }

    //运算完成 输出
    if(ans[countNumber+1]!=0){
        exp++;
        countNumber++;
    }

    if(exp<0){
        //前面补0
        printf("0.");
        for(int k=-1;k>exp;k--){
            printf("0");
        }
        //正常输出
        for(int k=countNumber-1;k>=0;k--){
            printf("%d",ans[k]);
        }
    }

    if(exp<countNumber-1&&exp>=0){
        //补小数点
        for(int k=countNumber-1;k>=0;k--){
            printf("%d",ans[k]);
            if(countNumber-k-1==exp){
                printf(".");
            }
        }
    }
    if(exp>=countNumber-1){
        //正常输出
        for(int k=countNumber-1;k>=0;k--){
            printf("%d",ans[k]);
        }
        //末尾补0
        for(int k=1;k<=exp-countNumber+1;k++){
            printf("%d",0);
        }
    }
    printf("\n");
}

void sub(struct NUMBER num1,struct NUMBER num2){
    //大数减法
    //小数点对齐
    int addExp=absCompare(num1.exp,num2.exp);
    int countNumberA;
    int countNumberB;
    char numA[SIGNIFICANTDIGITS+addExp];
    char numB[SIGNIFICANTDIGITS+addExp];
    char ans[SIGNIFICANTDIGITS+addExp+1];
    ans[SIGNIFICANTDIGITS+addExp+1]=0;
    for(int i=0;i<SIGNIFICANTDIGITS+addExp-1;i++){
        numA[i]=0;
        numB[i]=0;
        ans[i]=0;
    }

    
    int exp;
    
    int flag=1;
    if(num1.exp<num2.exp){
        flag=0;
    }

    if(flag==1){
        countNumberA=num1.countNumber+1;
        countNumberB=num2.countNumber+1+num1.exp-num2.exp;
        exp=num1.exp;
        //给num2补0
        numA[0]=num1.x;
        numB[num1.exp-num2.exp]=num2.x;
        for(int i=0;i<num1.countNumber;i++){
            numA[i+1]=num1.mantissa[i];
        }
        int k=0;
        for(int i=num1.exp-num2.exp+1;i<countNumberB;i++){
            numB[i]=num2.mantissa[k];
            k++;
        }
    }
    else{
        countNumberB=num2.countNumber+1;
        countNumberA=num1.countNumber+1+num2.exp-num1.exp;
        exp=num2.exp;
        //给num1补0
        numB[0]=num2.x;
        numA[num2.exp-num1.exp]=num1.x;
        for(int i=0;i<num2.countNumber;i++){
            numB[i+1]=num2.mantissa[i];
        }
        int k0=0;
        for(int i=num2.exp-num1.exp+1;i<countNumberA;i++){
            numA[i]=num1.mantissa[k0];
            
            k0++;
        }
    }

    int countNumber=absCompare(countNumberA,countNumberB);



    //初始化完成，开始减法运算
    if (numA[0] >= numB[0])
    {
        for (int i = countNumber - 1; i >= 0; i--)
        {
            int tmp = numA[i] - numB[i];

            ans[countNumber - i - 1] += tmp;
            //退位处理
            if (ans[countNumber - i - 1] < 0)
            {
                ans[countNumber - i] -= 1;
                ans[countNumber - i - 1] = ans[countNumber - i - 1] + 10;
            }

        }
    }

    if (numA[0] < numB[0])
    {
        for (int i = countNumber - 1; i >= 0; i--)
        {
            int tmp = numB[i] - numA[i];

            ans[countNumber - i - 1] -= tmp;
            //退位处理
            if (ans[countNumber - i - 1] < 0)
            {
                ans[countNumber - i] -= 1;
                ans[countNumber - i - 1] = ans[countNumber - i - 1] + 10;
            }
        }
        printf("-");
    }


    //运算完成 输出

    for(int i=countNumber-1;i>=0;i--){
        if(ans[i]==0){
            exp--;
            countNumber--;
        }
    }

    if(exp<0){
        //前面补0
        printf("0.");
        for(int k=-1;k>exp;k--){
            printf("0");
        }
        //正常输出
        for(int k=countNumber-1;k>=0;k--){
            printf("%d",ans[k]);
        }
    }

    if(exp<countNumber-1&&exp>=0){
        //补小数点
        for(int k=countNumber-1;k>=0;k--){
            printf("%d",ans[k]);
            if(countNumber-k-1==exp){
                printf(".");
            }
        }
    }
    if(exp>=countNumber-1){
        //正常输出
        for(int k=countNumber-1;k>=0;k--){
            printf("%d",ans[k]);
        }
        //末尾补0
        for(int k=1;k<=exp-countNumber+1;k++){
            printf("%d",0);
        }
    }
    printf("\n");

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
    case ADD:
        add(num1,num2);
        break;
    case SUBSTRUCT:
        sub(num1,num2);
        break;
    default:
        break;
    }
    return 0;
}
