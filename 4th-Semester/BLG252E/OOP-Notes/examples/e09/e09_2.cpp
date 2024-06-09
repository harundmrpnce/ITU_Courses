// e09_2.cpp
//    Objects as template arguments

#include <iostream>
using std::cout;
using std::endl;

class ComplexT{								//A class to define complex numbers 
public:
  ComplexT(double in_r, double in_im) :m_re{ in_r }, m_im{ in_im }{}  // Constructor
  bool operator>(const ComplexT&) const;					// overloading operator >, compares the sizes of two complex numbers
  double getRe()const {return m_re;}
  double getIm()const {return m_im;}
private:
	double m_re{}, m_im{};
};

// The Body of the function for operator > 
// The function compares the sizes of two complex numbers
bool ComplexT::operator>(const ComplexT& in_complex) const
{
   double size = m_re * m_re + m_im * m_im;
   double in_size = in_complex.m_re * in_complex.m_re + in_complex.m_im * in_complex.m_im;
   return size > in_size;
}

// Overloading the operator << for Complex numbers
std::ostream& operator <<(std::ostream& out, const ComplexT& z)            
{
	out << "( " << z.getRe() << " , " << z.getIm() << " )" << endl;
    return out;
};

// template function 
// The function returns the larger of two arguments
template <typename T> 
const T& maxOf(const T& n1, const T& n2)
{ 
    return n1 > n2 ? n1 : n2;
} 

int main()
{
	char c1{ 'D' }, c2{ 'N' };
	int i1{ 5 }, i2{ -3 };
    double d1{ 3.05 }, d2{ 12.47 };
    ComplexT z1(1.4,0.6), z2(4.6,-3.8);

    cout << maxOf(c1, c2) << endl;
    cout << maxOf(i1,i2) << endl;
    cout << maxOf(d1,d2) << endl;
    cout << maxOf(z1,z2) << endl;  // operator << must be overloaded for ComplexT

	return 0;
}
