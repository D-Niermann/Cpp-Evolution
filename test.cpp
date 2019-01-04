#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "utils.hpp"

using namespace std;
#define print(x) std::cout << x << std::endl;

class Animal
{
  protected:
	int legCount;
	float size;
	Animal(int legCount, float size) : legCount(legCount), size(size) {}
  public:
	virtual void info(){};
};

class Dog : public Animal
{
  public:
	string name;

	// constructor
	Dog(string name , int lC, float size) : name(name), Animal(lC, size)
	{
		print("Dog " + name + " created!");
	}

	// copy constructor
	Dog(const Dog &other) : name(other.name + "_copy"), Animal(other.legCount, other.size)
	{
		print("Dog " + name + " Copied!")
	}

	// deconstructor
	~Dog()
	{
		print("Dog " + name + " destroyed!")
	}

	void info(){
		print("info:");
		cout << "legCount:" ; print(legCount);
		cout << "name:" ; print(name);
		cout << "size:" ; print(size);
		print("\n");
	}
};



int main()
{
	// Dog* ptr;
	//polymorphic
	// vector<Dog> v;

	// for (int i = 0; i< 3; i++)
	// {
	// 	//polymorphic: Dog added but storage is animal
	// 	// ptr = new Dog(std::to_string(i),1, 2);
	// 	// print(ptr);
	// 	print(std::to_string(i)+"------");
	// 	v.emplace_back(
	// 			Dog(std::to_string(i),1, 2)
	// 		);
	// }
	// //polymorphic info function used from Dog class
	// print(v.size());
	// print("=========")
	// for (int i= 0; i<v.size(); i++){
	// 	v[i].info();
	// }
	// // delete &v[0];
	// v.erase(v.begin()+2);
	// print(v.size());
	// print("=========")
	// for (int i= 0; i<v.size(); i++){
	// 	v[i].info();
	// }

	position p1(1,2);
	position p2(3,4);
	p1 = p2;
	p1.display();
	p2.display();

	return 0;
}