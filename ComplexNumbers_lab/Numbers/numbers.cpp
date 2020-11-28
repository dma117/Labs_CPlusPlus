#include "complex.h"
#include "rational.h"


int main() {
	Complex c1(133, -89);
	Complex c2(-899.3, 144.0);

	std::cout << c1 << ' ' << c2 << std::endl;
	std::cout << c1 + c2 << std::endl;
	std::cout << c1 + 10 << std::endl;
	std::cout << c1 + 45.4 << std::endl;

	return 0;
}
