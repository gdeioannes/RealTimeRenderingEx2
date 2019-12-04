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
	int min=-10;
	int max=10;
	cout << num << " # set of "<< num << " points" << endl;
	for(int i=0;i<num;i++){
		cout << min+rand()%max << " " << min+rand()%max << endl;
	}
	return 0;
}
