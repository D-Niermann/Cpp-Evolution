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
	Dog(const Dog &other, int lC, float size) : name(other.name + "_copy"), Animal(lC,size)
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
	}
};



int main()
{
	Dog* ptr;
	//polymorphic
	vector<Animal*> v;
	for (int i = 0; i< 2; i++)
	{
		//polymorphic: Dog added but storage is animal
		ptr = new Dog(std::to_string(i),1, 2);
		print(ptr);
		v.push_back(ptr);
	}
	//polymorphic info function used from Dog class
	print("---");
	v[0]->info();
	print("---");
	v[1]->info();


	return 0;
}