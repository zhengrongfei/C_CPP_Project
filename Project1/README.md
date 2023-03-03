# Project1 Report

## Project Background and Purpose

This project aims to implement a calculator for addition, subtraction, multiplication and division between two numbers.And the main focus of my project is to realize high-precision calculation with C.

## Data Structure

- Predefined constants
```
 #define  SIGNIFICANTDIGITS  100
```
This means that inputs with 100 significant digits can be handled, e.g. 3.14 has 3 significant digits and 3.14e100 has 3 significant digits.And you can change the valid digits of the calculator at the top of the code.


- Data storage mode

Inspired by the way floating point numbers are stored in the underlying computer, all numbers in this project are stored as follows:
``` C
struct NUMBER{
    int x ;                 //integer in (0,10) 
    int exp; 
    int mantissa[SIGNIFICANTDIGITS-1]; 
    int countNumber;        //real digits of mantissa
};
```
Convert to scientific notation， the number represented by the struct is 
***`x.mantissa*10^exp`***.

## Methodology 

### Add
- Firstly,Aligns the decimal points of two numbers

for example:

    num1={1,2,3,4};
    num2={1,2}
    //Aligning decimal points by completing zeros,and then, num2 should be {0,0,1,2}
- Then,add one by one from low to high bit, paying attention to rounding, and store the result in a new array.

for example:

```
987.1+24:

   9 8 7 . 1
 + 0 2 4 . 0
-------------
 1 0 1 1 . 1

```

    
### Subtract

- Similar to addition, change the addition of each to subtraction
- Notice：The first operand must be greater than or equal to the second operand

### Multiply

- Unlike addition, multiplication does not require the alignment of decimal points, we just need to remember the exponents of the two numbers, then multiply and round them from the lower to the higher, and perform the calculation at the end to obtain the decimal point position of the result

```
1.28 * 1.16e100

exp1=0
exp2=100

    1 2 8
 *  1 1 6
-------------
    7 6 8
  1 2 8
1 2 8
-------------
1 4 8 4 8

No rounding in the highest bit, so the exp of the result is exp1+exp2 =100
So the final result is
 1.4848 * 10^100 

```

### Division
- The double data type and division operations within C, without other optimizations.
### Sample Inputs and Outputs

```
./Calculator 1 + a
请输入正确的数字！0
```

```
./Calculator 1.63e100 + 1
16300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001
```

```
./Calculator 10 + 3.14
13.14
```

```
./Calculator 1.63e100 - 1
16299999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
```
```
./Calculator 2 - 1       
1
```
```
./Calculator 12 '*' 6.78910   
81.46920
```
```
./Calculator 123456 '*' 6.78910e20
838155129600000000000000000
```

```
./Calculator 12 / 2
6.000000
```

### Advantages
- Supports high-precision addition, subtraction and multiplication

- Support scientific notation input

### Disadvantages
- Not support high-precision subtraction
- Not support negative numbers in operations
- \* must be entered as '*' to parse
