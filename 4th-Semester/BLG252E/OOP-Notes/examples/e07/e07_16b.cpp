// e07_16b.cpp
// Repeated Base Classes (The Diamond Problem)
// Solution virtual base classes 

#include<iostream>
using std::cout;
using std::endl;

class Common
{
protected:
	int common_data{};
};

class Base1 : virtual public Common			// virtual base
{};

class Base2 : virtual public Common        // virtual base
{};

// The Derived class contains only one common_data
class Derived : public Base1, public Base2
{
public:
	void setCommonData(int in)
	{
		common_data = in;
	 // Base1::common_data = in;		// OK!
	}
	int getCommonData() const
	{
		return common_data;
	 // return Base2::common_data;   // OK! Same as Base1::comon_data
	}
};

int main()
{
	Derived d;
	d.setCommonData(2);
	cout << "Common Data = " << d.getCommonData() << endl;
	return 0;
}
