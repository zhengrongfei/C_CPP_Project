package org.example;

import java.util.Scanner;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;


public class Main {
    enum TYPE {
        INT, FLOAT;
    }


    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        int n = 1000000;
        System.out.println("请输入数据类型：");
        String str = scanner.next();
        TYPE type;
        if (str.equals("int")) {
            type = TYPE.INT;
        } else if (str.equals("float")) {
            type = TYPE.FLOAT;
        } else {
            System.out.println("请输入正确的数据类型！");
            return;
        }

        String csvFilePath = "outputf.csv";
        FileWriter writer = new FileWriter(csvFilePath);
        BufferedWriter bufferWriter = new BufferedWriter(writer);

        long start, end;
        if (type == TYPE.INT) {

            Integer i=1;
            while(i<=n) {
                int[] intArray0 = generateRandomArrayInt(i);
                int[] intArray1 = generateRandomArrayInt(i);
                start = System.nanoTime();
                dotProduct(intArray0, intArray1);
                end = System.nanoTime();
                bufferWriter.write(Integer.toString(i));
                bufferWriter.write(",");
                bufferWriter.write(Long.toString(end - start));
                bufferWriter.newLine();
                i=i+1000;
            }
        } else {
            Integer i=1;
            while(i<=n) {
                float[] floatArray0 = generateRandomArrayFloat(i);
                float[] floatArray1 = generateRandomArrayFloat(i);
                start = System.nanoTime();
                dotProduct(floatArray0, floatArray1);
                end = System.nanoTime();
                bufferWriter.write(Integer.toString(i));
                bufferWriter.write(",");
                bufferWriter.write(Long.toString(end - start));
                bufferWriter.newLine();
                i=i+1000;
            }
        }
        bufferWriter.close();
    }

    public static int[] generateRandomArrayInt(int n) {
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = (int) (Math.random() * Integer.MAX_VALUE);
        }
        return arr;
    }

    public static float[] generateRandomArrayFloat(int n) {
        float[] arr = new float[n];
        for (int i = 0; i < n; i++) {
            arr[i] = (float) Math.random() * Float.MAX_VALUE;
        }
        return arr;
    }

    public static int dotProduct(int[] arr1, int[] arr2) {
        int result = 0;
        for (int i = 0; i < arr1.length; i++) {
            result += arr1[i] * arr2[i];
        }
        return result;
    }

    public static float dotProduct(float[] arr1, float[] arr2) {
        float result = 0.0f;
        for (int i = 0; i < arr1.length; i++) {
            result += arr1[i] * arr2[i];
        }
        return result;
    }
}
