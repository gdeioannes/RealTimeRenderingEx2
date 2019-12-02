//============================================================================
// Name        : RandomPointCloud.cpp
// Author      : Gabriel De Ioannes
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int num=1000000;
	cout << num << " # set of "<< num << " points" << endl;
	for(int i=0;i<num;i++){
		cout << -100+rand()%200 << " " << -100+rand()%200 << endl;
	}
	return 0;
}
