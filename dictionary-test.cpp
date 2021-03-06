/*Author: Piotr Sawicki*/
#include "dictionary-test.h"
void DictionaryTest::sizeAndCapacityTest(){
	Dictionary<int, double> dict;
	messageSize(dict, "Testing size reporting for key: int, value: double\nBefore: ");
	for(int i = 0; i < 20; ++i)
		dict.add(i + 1, (i + 1) * 3.14);
	assert(dict.getSize() == 20);
	messageSize(dict, "After adding 20 elements: ");
	std::cout << std::endl;
}
void DictionaryTest::sizeAndCapacityTest2(){
	Dictionary<std::string, Vector> dict;
	messageSize(dict, "Testing size reporting for key: string, value: vector\nBefore: ");
	Vector vect(2);
	vect.setNthValue(0, 5.55);
	vect.setNthValue(1, 6.66);
	for(int i = 0; i < 40; ++i)
		dict.add(std::string(i, 'a'), vect); 
	assert(dict.getSize() == 40);
	messageSize(dict, "After adding 40 elements: ");
	std::cout << std::endl;
}
void DictionaryTest::addExistingPairTest(){
	Dictionary<int, double> dict;
	for(int i = 0; i < 3; ++i)
		dict.add(i + 1, (i + 1) * 6.28);
	printSize(dict, "Testing behavior when trying to add a key already in the dictionary. Before:\n");
	dict.add(1, 6.28);
	assert(dict.getSize() == 3);
	printSize(dict, "After adding 1/6.28:\n");
	std::cout << std::endl;
}
void DictionaryTest::addExistingPairTest2(){
	Dictionary<std::string, Vector> dict;
	Vector vect(3), vect2(3);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j)
			vect.setNthValue(j, i * j);
		dict.add(std::string(1, 'x' - i), vect);
	}
	printSize(dict, "Testing behavior when trying to add a key already in the dictionary. Before:\n");
	dict.add(std::string(1, 'v'), vect2);
	assert(dict.getSize() == 3);
	printSize(dict, "After adding 'v'/[0, 0, 0]:\n");
	std::cout << std::endl;
}
void DictionaryTest::removeTest(){
	Dictionary<long long, char> dict;
	for(char i = 'a'; i < 'd'; ++i)
		dict.add(i, i);
	printSize(dict, "Testing removal. Before:\n");
	dict.remove((long long)'a', 'a');
	assert(dict.getSize() == 2);
	printSize(dict, "After removing 97/'a':\n");
	std::cout << "Removing 97/'a' again\n";
	dict.remove((long long)'a', 'a');
	assert(dict.getSize() == 2);
	std::cout << std::endl;
}
void DictionaryTest::removeTest2(){
	Dictionary<std::string, Vector> dict;
	Vector vect(3);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j)
			vect.setNthValue(j, i);
		dict.add(std::string(1, 'a' + i), vect);
	}
	printSize(dict, "Testing removal. Before:\n");
	dict.remove(std::string(1, 'c'), vect);
	assert(dict.getSize() == 2);
	printSize(dict, "After removing 'c'/[2,2,2]:\n");
	std::cout << "Removing 'b'/[2,2,2]:\n";
	dict.remove(std::string(1, 'b'), vect);
	assert(dict.getSize() == 2);
	std::cout << std::endl;
}
void DictionaryTest::changeTest(){
	Dictionary<int, double> dict;
	for(int i = 0; i < 3; ++i)
		dict.add(i + 1, (i + 1) * (i + 2));
	printSize(dict, "Testing changing. Before:\n");
	dict.change(1, 3.14);
	printSize(dict, "After changing key: 1 to value: 3.14\n");
	std::cout << "Trying to change element with key 4\n";
	bool f = dict.change(4, 3.14);
	assert(!f);
	std::cout << "Confirming change happened\n";
	double confirm = 0;
	bool b = dict.find(1, confirm);
	assert(confirm == 3.14);
	assert(b);
	std::cout << "Test successful\n\n";
}
void DictionaryTest::changeTest2(){
	Dictionary<std::string, Vector> dict;
	Vector vect(3);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j)
			vect.setNthValue(j, i + j);
		dict.add(std::string(1, 'n' - i), vect);
	}
	printSize(dict, "Testing changing. Before:\n");
	for(int i = 0; i < 3; ++i)
		vect.setNthValue(i, 2 * (i + 1));
	dict.change(std::string(1, 'm'), vect);
	printSize(dict, "After changing key: 'm' to value: [2,4,6]\n");
	Vector vect2(3);
	assert(dict.find(std::string(1, 'm'), vect2));
	assert(vect2 == vect);
	std::cout << "Change successful\n\n";
}
void DictionaryTest::comparisonTest(){
	std::cout << "Testing comparison\n";
	Dictionary<int, double> dict1, dict2;
	for(int i = 0; i < 3; ++i){
		dict1.add(i, i);
		dict2.add(i, i);
	}
	assert(dict1 == dict2);
	std::cout << "Equal dictionaries: " << std::boolalpha << (dict1 == dict2) << std::endl;
	dict2.change(0, 3.14);
	assert(!(dict1 == dict2));
	std::cout << "Different dictionaries: " << (dict1 == dict2) << std::endl;
	Dictionary<int, double> dict3;
	assert(!(dict3 == dict1));
	std::cout << "Different sizes: " << (dict3 == dict1) << "\n\n";
}	
void DictionaryTest::comparisonTest2(){
	std::cout << "Testing comparison with string/vector\n";
	Dictionary<std::string, Vector> dict1, dict2;
	Vector vect(3);
	for(int i = 0; i < 3; ++i){
		dict1.add(std::string(1, 'a' + i), vect);
		dict2.add(std::string(1, 'a' + i), vect);
	}
	assert(dict1 == dict2);
	std::cout << "Equal dictionaries: " << std::boolalpha << (dict1 == dict2) << std::endl;
	vect.setNthValue(1, 2);
	dict2.change(std::string(1, 'b'), vect);
	assert(!(dict1 == dict2));
	std::cout << "Different dictionaries: " << (dict1 == dict2) << "\n\n";
}
void DictionaryTest::sortTest(){
	std::cout << "Testing sorting with int/double\n";
	Dictionary<int, double> dict;
	dict.add(5, 5.5);
	dict.add(3, 3.3);
	dict.add(4, 8);
	dict.add(10, 15);
	dict.add(1, 8);
	dict.add(6, 9.9);
	dict.add(-42, 0);
	dict.remove(4, 8);
	dict.remove(1, 8);
	dict.add(-13, 18);
	dict.add(2, 3);
	dict.add(1, 9);
	printSize(dict, "Added keys: 5, 3, 4, 10, 1, 6, -42. Removed: 4, 1. Added: -13, 2, 1. Result:\n");
	double confirm = 0;
	dict.find(10, confirm);
	assert(confirm == 15);
}
void DictionaryTest::emptyTest(){
	std::cout << "Testing behavior when removing a value from an empty dictionary.\n";
	Dictionary<std::string, Vector> dict;
	bool ifSuccess = dict.remove(std::string(1, 'a'), Vector(1));
	assert(!ifSuccess);
	std::cout << std::endl;
}
