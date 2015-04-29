// CoinOptionality.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

float allval[100][100];

float calc_option_value(int tossed,int heads){
	float intrinsic = (tossed == 0) ? 0: (float)heads / tossed;
	if (heads > tossed){
		return -1;
	}
	else if (tossed == 100) {
		return intrinsic;
	}
	else if (allval[tossed][heads] > 0.001) {
		return std::max(intrinsic, allval[tossed][heads]);
	}
	else {
		float optionality = calc_option_value(tossed + 1, heads + 1) / 2 + calc_option_value(tossed + 1, heads) / 2;
		allval[tossed][heads] = std::max(intrinsic, optionality);
		return std::max(intrinsic, optionality);
	}
	return 0;
}
int main()
{
	float a = calc_option_value(0, 0);
	for (int i = 0; i < 100; i++)
	{
		int j = (i + 1) / 2;
		float intrinsic  = (i == 0) ? 0 : (float)j / i;
		cout << "tossed:" << i << "  heads:" << j << "  dec:" << (( intrinsic == allval[i][j]) ? "exercise" : "continue") << "  intrinsic value:" << intrinsic << "  optionality: " << allval[i][j] - intrinsic<< endl;
	}
	for (int j = 0; j < 50; j++) {
		int i = j * 2;
		float intrinsic = (i == 0) ? 0 : (float)j / i;
		cout << allval[i][j] - intrinsic << ";";
	}
	cout << a << endl;
	//cout << a<< endl;
	while (1) {
		int i;int j;
		cout << " number of tosses:";
		//getline(cin, i);
		cin >> i;
		cout << " number of heads:";
		//getline(cin, j);
		cin >> j;
		float intrinsic = (i == 0) ? 0 : (float)j / i;
		cout << "tossed:" << i << "  heads:" << j << "  dec:" << ((intrinsic == allval[i][j]) ? "exercise" : "continue") << "  intrinsic value:" << intrinsic << "  optionality: " << allval[i][j] - intrinsic << endl;
	}
	return 0;
}

