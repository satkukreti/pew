#include <iostream>
class Thinker {
	private:
		std::string iq = "";
		int age = 0;
	public:
		Thinker();
		Thinker(const int &i, const std::string &c);
		bool operator==(const Thinker &other) const;
		friend bool isZany(const Thinker &t);
		friend std::ostream &operator<<(std::ostream &out,
						const Thinker &c);
};
