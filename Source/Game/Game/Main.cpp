#include <iostream>
#include "../../Engine/Core/Random.h"
#include "../../Engine/Core/FileIO.h"
#include "../../Engine/Core/memory.h"
#include "../../Engine/Core/Time.h"
#include "../../Engine/Renderer/Renderer.h"
#include <chrono>

using namespace std;




int main()
{
	kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 1000000; i++) {}
	cout << timer.GetElapsedNanoseconds() << endl;

	//auto start = chrono::high_resolution_clock::now();
	//for(int i = 0; i < 1000000; i++){}
	//auto end = chrono::high_resolution_clock::now();

	//cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;



	//cout << kiko::getFilePath() << endl;
	//kiko::setFilePath("Assets");
	//cout << kiko::getFilePath() << endl;
	//size_t size;
	//kiko::getFileSize("game.txt", size);
	//cout << size << endl;

	//std::string s;
	//kiko::readFile("game.txt", s);
	//cout << s << endl;


	///*kiko::seedRandom((unsigned int)time(nullptr));
	//for (int i = 0; i < 10; i++) {
	//	cout << kiko::random(10, 20) << endl;
	//}*/
}