#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;
#define print(x) std::cout << x << std::endl;

class Animal
{
  protected:
	int legCount;
	float size;
	Animal(int legCount, float hairs) : legCount(legCount), size(size) {}

};

class Dog : public Animal
{
  public:
	string name;

	// constructor
	Dog(string name , int lC) : name(name), Animal(lC,3)
	{
		print("Dog " + name + " created!");
	}

	// copy constructor
	Dog(const Dog &other, int lC) : name(other.name + "_copy"), Animal(lC,3)
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
		print(legCount);
		print(name);
		print(size);
	}
};



int main()
{

	vector<Dog> v;
	Dog d1("alex",1);
	d1.info();
	// Dog d2("tim");
	// Dog d2 = d1;

	// this copies the dog
	// v.push_back(Dog("charles"));

	return 0;
}