#include<stdio.h>
#include <stdlib.h>
#include <memory.h>

#define N 3

struct Matrix{
    int x,y;
    double *array;
};

struct Matrix Create_Matrix(int x,int y){
    struct Matrix res;
    res.x=x,res.y=y;
    res.array=(double*)malloc(x*y*sizeof(double));
    memset(res.array,0,x*y*sizeof(double));
    return res;
}

void Transpose(struct Matrix* a){
    int temp[(a->x)*(a->y)];
    for(int i=0;i<a->x;i++){
        for(int j=0;j<a->y;j++)
            temp[i*(a->x)+j]=a->array[i*(a->x)+j];
    }
    for(int i=0;i<a->x;i++){
        for(int j=0;j<a->y;j++)
            a->array[j*(a->y)+i]=temp[i*(a->x)+j];
    }
}

struct Matrix Add(struct Matrix a,struct Matrix b){
    for(int i=0;i<(a.x)*(a.y);i++)
        a.array[i]+=b.array[i];
    return a;
}

struct Matrix Multiply(struct Matrix a,struct Matrix b){
    struct Matrix res=Create_Matrix(a.x,b.y);
    for(int i=0;i<a.x;i++)
        for(int j=0;j<b.y;j++)
            for(int k=0;k<b.x;k++)
                res.array[i*(a.x)+j] += a.array[i*(a.x)+k] * b.array[k*(b.x)+j];
    return res;
}

void Print(struct Matrix a){
    for(int i=0;i<a.x;i++){
        for(int j=0;j<a.y;j++)
            printf("%llf ",a.array[i*a.x+j]);
        printf("\n");
    }
    printf("\n");
}

int main(){
    struct Matrix x=Create_Matrix(3,3);
    //初始化賦值
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            x.array[i*x.x+j]=j;
    }

    Transpose(&x);
    Print(x);
    x=Add(x,x);
    Print(x);
    x=Multiply(x,x);
    Print(x);
}