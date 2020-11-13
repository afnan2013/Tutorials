#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int max(int x, int y){
    return (x>y)?1:0;
}

int main(){
    int x,y;
    cin>> x>> y;
    bool z = max(x,y);
    cout<< z <<endl;
    return 0;

}