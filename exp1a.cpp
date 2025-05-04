#include <bits/stdc++.h>
using namespace std;

double fact(double n) {
    if(n<=1) return 1;
    return n*fact(n-1);
}

int main() {
    const char separator = ' ';
    const int nameWidth = 10;
    const int numWidth  = 10;
    int start = 0, end1 = 100;
    cout<<"Tabular plot"<<endl;
    cout<<left<<setw(nameWidth-4)<<setfill(separator)<<"n"<<setw(nameWidth)<<setfill(separator)<<"log(i)"<<setw(nameWidth)<<setfill(separator)<<"ln(i)"<<setw(nameWidth)<<setfill(separator)<<"n^3"<<setw(nameWidth)<<setfill(separator)<<"log^2(i)"<<setw(nameWidth)<<setfill(separator)<<"ln(ln(n))"<<setw(nameWidth)<<setfill(separator)<<"2^log(i)"<<setw(nameWidth)<<setfill(separator)<<"log(log(n))"<<setw(nameWidth+2)<<setfill(separator)<<"(logn)^logn"<<setw(nameWidth)<<setfill(separator)<<"nlog(n)"<<setw(nameWidth+2)<<setfill(separator)<<"n^log(logn)"<<setw(nameWidth)<<setfill(separator)<<"sqrt(logn)"<<setw(nameWidth)<<setfill(separator)<<"log(n!)"<<setw(nameWidth)<<setfill(separator)<<"log(n)!"<<setw(nameWidth)<<setfill(separator)<<"sqrt(2)^logn"<<endl;
    for(int i = start; i<end1; i++) {
        cout<<left<<setw(numWidth-4)<<setfill(separator)<<i<<setw(numWidth)<<setfill(separator)<<setw(numWidth)<<setfill(separator)<<log2(i)<<setw(numWidth)<<setfill(separator)<<log(i)<<setw(numWidth)<<setfill(separator)<<pow(i,3)<<setw(numWidth)<<setfill(separator)<<pow(log2(i),2)<<setw(numWidth)<<setfill(separator)<<log(log(i))<<setw(numWidth)<<setfill(separator)<<pow(2,log2(i))<<setw(numWidth)<<setfill(separator)<<log2(log2(i))<<setw(numWidth)<<setfill(separator)<<pow(log2(i),log2(i))<<setw(numWidth)<<setfill(separator)<<i*log2(i)<<setw(numWidth+2)<<setfill(separator)<<pow(i,log2(log2(i)))<<setw(numWidth)<<setfill(separator)<<sqrt(log2(i))<<setw(numWidth+2)<<setfill(separator)<<log2(fact(i))<<setw(numWidth)<<setfill(separator)<<fact(log2(i))<<setw(numWidth)<<setfill(separator)<<pow(sqrt(2),log2(i))<<endl;
    }
    return 0;
}