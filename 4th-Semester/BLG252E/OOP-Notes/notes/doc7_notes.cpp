/*
! Multiple inheritance can introduce ambiguity and complexity in the code. It must be used judiciously and only when necessary

! Private members can be accessed only in the defined class or friend class (function).
! Protected members can be accessed in the defined class and in the derived class.
! Public members can be accessed in the defined class, in the derived class, and from the objects of the defined class. 
! Since the derived class can directly access the protected members of the base class, it may cause undesired changes.

! Base class access specifier does not affect how the derived class members can access the base class members. It affects the objects and subclasses of derived class. 
? For example, when we specify a base class as private to a derived class, the derived class members can still access the base class members. However, the objects and subclasses of the derived class cannot access the base class members. 

    class ColoredPoint : private Point {
        private:
            using Point::move;  ! Suppose that the point function inherited as public. This block makes move function private in the ColoredPoint class.
        public:
            using Point::print;  ! It makes the print() function public in the ColoredPoint class. (print already is a public function in the Point class)
    }

! Redefined methods cannot be accessed from the objects of derived class directly. It can be accessed like this: object.Base::method_name(); (only the method is public in the base class)

? The order of constructors and destructors in composition with inheritance:
? Part for parent constructor - Parent constructor - Part for child constructor - Child constructor
? Child destructor - Part for child destructor - Parent destructor - Part for parent destructor

? A pointer to the base class can point to the derived class object implicitly if the base class inherited as public. However, a pointer to the derived class can point to the base class object explicitly. 

    Derived d_obj;
    Base* bp = &d_obj;                   implicit conversion
    Derived* dp = bp;                    ERROR! Base is not Derived
    dp = static_cast<Derived*>(bp);     explicit conversion

! The base class pointer can access only the derived class members that are inherited from the base class.

    ColoredPoint objColoredPoint{ 10, 20, Color::Blue }; 
    Point* ptrPoint = &objColoredPoint;      Point* ptr ← &ColoredPoint
    ptrPoint->move(30, 40);                  OK. Moving is Points behavior
    ptrPoint->setColor(Color::Green);        ERROR! Setting the color is not points behavior
    ColoredPoint* ptrColoredPoint = &objColoredPoint;  ColoredPoint* ptr
    ptrColoredPoint->move(100, 200);            OK. ColoredPoint is a Point
    ptrColoredPoint->setColor(Color::Green);    OK. ColoredPoints behavior

*/