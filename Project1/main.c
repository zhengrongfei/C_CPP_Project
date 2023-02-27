#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define SIGNIFICANTDIGITS  20
struct NUMBER{
    int x ; //10以内的数字
    int exp; 
    int mantissa[SIGNIFICANTDIGITS-1]; //位数：significantDigits-1
};
//把字符串转化为int array
 struct NUMBER parseNumber(char num[],struct NUMBER res,int size){
    int begin=0;
    res.exp=0;
    while(num[begin]=='0'){
        begin++;
        res.exp--;
    }
    printf("exp:%d",res.exp);
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
                printf("num[%d]=%d:",i+1,num[i+1]-'0');
            }
            i++;
            while(i<size-1){
                exp=exp*10+num[i+1]-'0';
                printf("num[%d]=%d:",i+1,num[i+1]-'0');
                i++;
            }
            exp=exp*sign;
            res.exp=res.exp+exp;
            printf("exp:%d",exp);
            printf("exp:%d",res.exp);
            break;
        }
        else if(num[i]=='.'){
            hasDot=true;
        }
    }

    res.exp=res.exp+e;
    printf("exp:%d",res.exp);
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


int main(int argc, char* argv[]) {
    // 创建一个字符串数组
    char num[SIGNIFICANTDIGITS+2] = {0};
// 创建一个指针，并指向静态区存放的一个字符串“ABC”
    char* tmp = argv[1];
    printf("length:%d\n",get_length(argv[1]));
    // 利用字符串拷贝函数进行拷贝
    strcpy(num, tmp);
    printf("arr%s\n",num);
// 例如内存拷贝函数进行拷贝
    memcpy(num, tmp, sizeof(num));
    int length=get_length(argv[1]);
    struct NUMBER num1;
    num1=parseNumber(num,num1,length);
    printf("x%d\n", num1.x);
    for(int i=0;i<10;i++){
        printf("%d\n",num1.mantissa[i]);
    }
    printf("exp: %d\n",num1.exp);
}
