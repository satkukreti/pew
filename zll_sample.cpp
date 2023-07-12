#include <iostream> 
using namespace std;

#include "zany.h"
#include "ZLL.h"
#include "Thinker.h"

template <typename T>
void reportZany(const T &param) {
	cout << param << " is ";
	if (!isZany(param)) cout << "not ";
	cout << "zany" << endl;
}

int main() {
        int one = 1;
	int two = 2;
	string one_str = "one";
	string two_str = "Two";
	reportZany(one);
	reportZany(two);
	reportZany(one_str);
	reportZany(two_str);
	Thinker genius(8, "210");
	Thinker notgenius(40, "100");
	reportZany(genius);
	reportZany(notgenius);
	
	ZLL<int> zll1;
	ZLL<string> zll2;
	ZLL<Thinker> zll3;

	zll1.back(1);
	zll2.back("two");
	zll3.back(genius);
}
