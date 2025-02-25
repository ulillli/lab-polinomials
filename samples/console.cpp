#include "polynoms.h"
#include "translator.h"
#include <string>
int main() {
	try {
		std::cout << "What do you want to do?\n";
		std::cout << std::endl;
		std::cout << "1.Polynom+Polynom\n";
		std::cout << "2.Polynom*=const\n";
		std::cout << "3.Polynom*=Polynom\n";
		std::cout << "4.-Polynom\n";
		std::string str;
		std::cin >> str;
		std::cout << std::endl;
		int i = stoi(str);

		std::string s1, s2;
		double c;
		Polynom P1, P2;
		switch (i) {
		case 1:
			std::cout << "Input the first polynom\n";
			std::cin >> s1;
			std::cout << "Input the second polynom\n";
			std::cin >> s2;
			P1= Polynom(translator(s1).getPolynom());
			P2= Polynom(translator(s2).getPolynom());
			P1 += P2;
			std::cout << std::endl;
			P1.print();
			break;
		case 2:
			std::cout << "Input the polynom\n";
			std::cin >> s1;
			std::cout << "Input the const\n";
			std::cin >> c;
			P1 = Polynom(translator(s1).getPolynom());
			P1 *= c;
			std::cout << std::endl;
			P1.print();
			break;
		case 3:
			std::cout << "Input the first polynom\n";
			std::cin >> s1;
			std::cout << "Input the second polynom\n";
			std::cin >> s2;
			P1 = Polynom(translator(s1).getPolynom());
			P2 = Polynom(translator(s2).getPolynom());
			P1 *= P2;
			std::cout << std::endl;
			P1.print();
			break;
		case 4:
			std::cout << "Input the polynom\n";
			std::cin >> s1;
			P1 = Polynom(translator(s1).getPolynom());
			std::cout << std::endl;
			(-P1).print();
			break;
		}
	}
	catch (char * str) {
		std::cout << str;
	}
}