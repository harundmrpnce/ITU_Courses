// e07_16a.cpp
// Repeated Base Classes (The Diamond Problem)

#include<iostream>
using std::cout;
using std::endl;

class Common
{
protected:
	int common_data{};
};

class Base1 : public Common			// virtual base
{};

class Base2 : public Common        // virtual base
{};

// The Derived class contains two common_data
class Derived : public Base1, public Base2
{
public:
	void setCommonData(int in)
	{
		// common_data = in;        // Error ambigious
		Base1::common_data = in;	// OK but confusing
	}
	int getCommonData() const
	{
		// return common_data;      // Error ambigious
		return Base2::common_data;  // OK but confusing different from Base1::common_data
	}
};

int main()
{
	Derived d;
	d.setCommonData(2);									// Set the common_data to 2.				
	cout << "Common Data = " << d.getCommonData() << endl; // get function returns 0 !
	return 0;
}
