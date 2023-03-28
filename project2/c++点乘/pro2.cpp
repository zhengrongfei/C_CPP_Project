#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace chrono;
#include <fstream>
enum TYPE
{
    INT = 0,
    FLOAT
};

template <typename T>
T *generate_random_array(int n)
{
    T *arr = new T[n]; // 动态分配内存
    srand(time(NULL)); // 初始化随机数种子
    // 生成随机数并赋值给数组元素
    for (int i = 0; i < n; i++)
    {
        arr[i] = static_cast<T>(rand());
    }
    return arr; // 返回数组指针
}


template <typename T>
T dot_product(const T* arr1, const T* arr2, const size_t n) {
    T result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += arr1[i] * arr2[i];
    }
    return result;
}

int main()
{
    //输入
    int n=1000000;
    string str;
    cout << "请输入数据类型：" << endl;
    cin >> str;
    TYPE type;
    if (str == "int")
    {
        type = INT;
    }
    else if (str == "float")
    {
        type = FLOAT;
    }
    else
    {
        cout << "请输入正确的数据类型！" << endl;
        return 0;
    }

    ofstream fout("outputc.csv");

    high_resolution_clock::time_point start, end;
    if (type == INT)
    {
        //把1-n的数据个数都跑一遍
        int i=1;
        while(i<=n)
        {
            int *int_array0 = generate_random_array<int>(i);
            int *int_array1 = generate_random_array<int>(i);
            start = high_resolution_clock::now();
            dot_product(int_array0, int_array1, i);
            end = high_resolution_clock::now();
            delete[] int_array0;
            delete[] int_array1;
            fout << i << ",";
            fout << duration_cast<nanoseconds>(end - start).count() << "\r\n";
            i=i+1000;
        }
    }
    if (type == FLOAT)
    {
        int i=1;
        while(i<=n)
        {
        float *float_array0 = generate_random_array<float>(i);
        float *float_array1 = generate_random_array<float>(i);
        start = high_resolution_clock::now();
        dot_product(float_array0,float_array1,i);
        end = high_resolution_clock::now(); 
        delete[] float_array0;
        delete[] float_array1;
        fout << i << ",";
        fout << duration_cast<nanoseconds>(end - start).count() << "\r\n";
        i=i+1000;
        }
    }
    fout.close();
}
