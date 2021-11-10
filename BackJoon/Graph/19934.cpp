//함수 구현 문제

#include "supertrees.h"
#include <vector>

using namespace std;

int construct(vector<vector<int>> p) {
	int n = p.size();
    vector<vector<int>> answer;
	for (int i = 0; i < n; i++) {
		vector<int> row;
		row.resize(n);
		answer.push_back(row);
	}
	build(answer);
	return 1;
}
