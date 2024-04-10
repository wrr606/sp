#include<bits/stdc++.h>
using namespace std;

constexpr int N=1e5;

class Person{
private:
    int money=1e3;
public:
    void Deposit(int num){
        money+=num;
    }

    void Withdraw(int num){
        money-=num;
    }

    int Query(){
        return money;
    }
} Sam;

void ATM1(){
    for(int i=0;i<N;i++)
        Sam.Deposit(10);
}

void ATM2(){
    for(int i=0;i<N;i++)
        Sam.Withdraw(10);
}

int main() {
    cout<<"money:\t"<<Sam.Query()<<endl;

    thread thread1(ATM1);
    thread thread2(ATM2);

    thread1.join();
    thread2.join();

    cout<<"money\t"<<Sam.Query()<<endl;

    return 0;
}