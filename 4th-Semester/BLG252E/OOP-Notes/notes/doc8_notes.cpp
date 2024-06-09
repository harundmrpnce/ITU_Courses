/*
    class Professor {
        .......
        public:
            void print() {
                cout << "Professor" << endl;
            }
    }

    class Dean : Professor {
        .......
        public:
            void print() {
                cout << "Dean" << endl;
            }
    }

    class Rector {
        ......
        public:
            void meetVisitor(Professor* visitor) {
                visitor->print();
            }
    }

    int main() {
        Professor* ptr;
        if (ptr == &prof)
            rector.meetVisitor(&prof);
        else (ptr == &dean)
            rector.meetVisitor(&dean);
    }

    ! In this example, the print function is not polymorphic, when the rector calls the meetVisitor function, the professor class' print function will run for both dean and professor object. It is determined at compiling time.
    ! The virtual keyword must be added to the base class polymorphic function to make it polymorphic. It is not obligatory to add virtual keyword to the derived classes.
    ! In polymorphic example, the print function will called according to the sending pointer variable. If the pointer type is Dean, then its print function will be called. This decision is made at during runtime.

    ? If we derive the professor or dean class again, or we discard a class from the system, we do not need to redefine the meetVisitor function again.

    ? The static type of pointer visitor is Professor, and the dynamic type is determined at runtime. 
    ? Connecting functions during compilation is static (early) binding, at runtime is dynamic (late) binding.

    ? Override keyword should be used in derived polymorphic functions to avoid possible errors. It is not must. The virtual and override keywords appears in only class declarations, we do not need to add them to the definitions.

    ! Overloading, Name-Hiding, Polymorphism
    ! Overloading occurs in same class or same namespace, at least one of the signature (return type, parameter, etc.) of the functions must be different. "ad hoc polymorphism"
    ! Name-Hiding occurs when derived class redefines the base class' method. The redefined method may have same or different siganture. 

    ? We must define at least 1 pure virtual function to make the class abstract.
    ** virtual method(parameter) = 0; (it doesn't have definition) (pure virtual function)
    ! Each derived class must implement the body of its pure virtual function, if it is not, then it is an abstract class, too.

    ! We cannot create an object from an abstract class. We cannot pass or return the object by value, either. The reference or address to the abstract is allowed.

    ! Constructors cannot be virtual. Destructors will be virtual if dynamic objects are used in the program.
*/