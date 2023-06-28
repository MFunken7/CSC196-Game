#include <iostream>
#include "../../Engine/Core/Random.h"
#include "../../Engine/Core/FileIO.h"
#include "../../Engine/Core/memory.h"
using namespace std;




int main()
{
	int* p = new int;
	
	delete p;







	cout << kiko::getFilePath() << endl;
	kiko::setFilePath("Assets");
	cout << kiko::getFilePath() << endl;
	size_t size;
	kiko::getFileSize("game.txt", size);
	cout << size << endl;

	std::string s;
	kiko::readFile("game.txt", s);
	cout << s << endl;


	/*kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {
		cout << kiko::random(10, 20) << endl;
	}*/
}