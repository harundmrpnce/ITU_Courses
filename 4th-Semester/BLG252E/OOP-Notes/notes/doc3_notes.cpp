/*
? If the body of a function is written in the class definition, then this function is defined as an inline function.

! The difference between inline function and standard function is: 
! The machine language code corresponds to inline function directly implemented to the executable file where it is used. When the standard function is called the parameters are moved to the function via stack, then the function is executed. 

? Inline functions are suggested to use if a function is very short.

? Any class method is defined just once, it is not created for all objects, separately. All objects use the same function.

? The default mode of the class is private, we do not have to determine the private mode of the class.
? By convention, it is better to write public part of the class first.

? The friend function is written into the relevant class, but it is not a member of that class. It can access any of the members of a class object, regardless of their access specification.

! An example to friend function
    class Point{
        public:
            friend void display(Point&);
        other methods and attributes
    };

    void display(Point &point) {
        std::cout  << "x= " << point.m_x << " y= " << point.m_y;
    }

    int main() {
        Point point1(10, 20);
        display(point1);
    }

? An entire class can be declared to be a friend of another class. All methods of a friend class have unrestricted access to its friend class methods and attributes.
? The friendship between classes is not a bidirectional and transitive.
! Friend declarations may undermine the principle of data hiding, so they should be used sparingly.

! An example to friend class
    class Point{
        public:
            friend class GraphicTools;
        private:
            int m_x, m_y;
        other methods and attributes
    };

    class GraphicTools{
        public:
            void moveToZero(Point& point) {
                point.m_x = 0;
                point.m_y = 0;
            }
            Another methods of GraphicTools class can manipulate the Point class members.
    };

    int main() {
        Point point1(10, 20);
        GraphicTools tool;
        tool.moveToZero(point1);
    }
*/