#include <iostream>

#include "Thinker.h"

Thinker::Thinker() {
	iq = "";
	age = 0;
}

Thinker::Thinker(const int &i, const std::string &c) {
	age = i;
	iq = c;
}

bool Thinker::operator==(const Thinker &other) const {
	return ((age == other.age) &&
		(iq == other.iq));
}

bool isZany(const Thinker &t) {
	return (t.iq == "100");
}

std::ostream &operator<<(std::ostream &out, const Thinker &c) {
	out << c.iq << " [" << c.age << "]";
	return out;
}
