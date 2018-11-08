#include <iostream>
#include "tdm.hpp"

using namespace std;


int main() {
	Array1D u, l, d, b;
	u = {3., -1., -1.};
	l = {2., 4., 1.};
	d = {1., 2., 2., 0.};
	b = {7., 3., 8., -2.};
	TDM tdm(u, d, l, b);
	tdm.Print();

	return 0;
}
