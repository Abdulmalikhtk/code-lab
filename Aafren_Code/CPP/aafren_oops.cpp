/*
====================================================================

1. Inheritance
2. Polymorphism
    A. Compile-time
        - Function Overloading
        - Operator Overloading
    B. Run-time
        - Function Overriding
3. Abstract Class
4. Virtual Function
5. Pure Virtual Function
6. Diamond Problem & Fix
7. Smart Pointers
====================================================================
*/

#include <iostream>
#include <memory>
using namespace std;

class AbstractClass {
public:
    AbstractClass() {
        cout << "AbstractClass Default Constructor Called." << endl;
    }
    virtual ~AbstractClass() {
        cout << "AbstractClass Virtual Destructor Called." << endl;
    }

    virtual void getPromotion() = 0;
};

class Employee : public AbstractClass {
private:
    string emp_company_name;
    int emp_salary;
protected:
    int emp_age;
public:
    string emp_name;

    Employee(string name, int age, string comp_name, int salary)
        : emp_name(name), emp_age(age), emp_company_name(comp_name), emp_salary(salary) {
        cout << "Employee Constructor Called" << endl;
    }

    virtual ~Employee() override {
        cout << "Employee Destructor Called" << endl;
    }

    friend void showSalary(Employee e);
    friend class HR;

    virtual void showDetails() const {
        cout << "Employee Details: Name-" << emp_name
             << " Age-" << emp_age
             << " Company-" << emp_company_name << endl;
    }

    // Getters and Setters
    string getName() const { return emp_name; }
    string getCompName() const { return emp_company_name; }
    void setName(const string& name) { emp_name = name; }
    void setAge(int age) { emp_age = age; }
    void setCompName(const string& comp_name) { emp_company_name = comp_name; }

    int addthree(int a, int b, int c) {
        cout << "int three:" << a + b + c << endl;
        return a + b + c;
    }
    int addthree(float a, float b, float c) {
        cout << "float three:" << a + b + c << endl;
        return a + b + c;
    }
    void addtwo(int a, int b) { cout << a + b << endl; }

    int operator+(const Employee& other) {
        return this->emp_salary + other.emp_salary;
    }

    void getPromotion() override {
        if (emp_age >= 30)
            cout << emp_name << " is promoted" << endl;
        else
            cout << emp_name << " is not promoted" << endl;
    }

    virtual void work() {
        cout << emp_name << " is working as a full Stack" << endl;
    }
};

void showSalary(Employee e) {
    cout << "Salary: " << e.emp_salary << endl;
}

class Developer : public Employee {
public:
    string emp_work;

    Developer(string work, string name, int age, string comp_name, int salary)
        : Employee(name, age, comp_name, salary) {
        cout << "Developer Constructor Called" << endl;
        emp_work = work;
    }
    ~Developer() override {
        cout << "Developer Destructor Called" << endl;
    }

    void showDetails() const override {
        cout << "Developer Details developer: Name-" << emp_name << endl;
    }
};
/*
Imagine a grandparent class Scanner with a method powerOn(). If Printer and FaxMachine both inherit from Scanner, they each get their own copy of powerOn().
When a MultifunctionDevice inherits from both Printer and FaxMachine, it receives two duplicate copies of powerOn().
If you try to run device.powerOn(), the compiler will crash because it cannot decide whether to run the printer's or the fax machine's version of the power logic.
*/
class TechLead : virtual public Employee {
public:
    TechLead(string name, int age, string comp_name, int salary)
        : Employee(name, age, comp_name, salary) {
        cout << "TechLead Constructor Called" << endl;
    }
};

class Manager : virtual public Employee {
public:
    Manager(string name, int age, string comp_name, int salary)
        : Employee(name, age, comp_name, salary) {
        cout << "Manager Constructor Called" << endl;
    }
};

class Director : public TechLead, public Manager {
public:
    Director(string name, int age, string comp_name, int salary)
        : Employee(name, age, comp_name, salary),
          TechLead(name, age, comp_name, salary),
          Manager(name, age, comp_name, salary) {
        cout << "Director Constructor Called" << endl;
    }
};

class HR {
public:
    HR() { cout << "HR Constructor Called" << endl; }
    ~HR() { cout << "HR Destructor" << endl; }
    void showSalary(Employee e) {
        cout << "Salary: " << e.emp_salary << endl;
    }
};

int main() {
    // cout << "--- 1. Creating Dynamic Employee Pointer from Abstract Pointer ---" << endl;
    // AbstractClass* abstractPtr = new Employee("Alice", 31, "Amazon", 300000);
/*
AbstractClass obj; \(\rightarrow \) ❌ Illegal (Compiler will throw an error because you cannot instantiate it).

AbstractClass* abstractPtr \(\rightarrow \)  Legal.
You are creating a pointer, which is just a 8-byte memory address block.
The actual object initialized in heap memory using new is an Employee object. This is called upcasting.
*/

    // abstractPtr->getPromotion();
    // delete abstractPtr;

    cout << "\n--- 2. Testing Original Smart Pointers & Variables ---" << endl;
    Employee e("Alice", 31, "Amazon", 300000);
    // Developer d("developer", "charlie", 31, "Amazon", 400000);

    // Employee* e2 = new Developer("developer", "Daneil", 31, "Meta", 600000);
    // unique_ptr<Employee> e1 = make_unique<Employee>("Elizebath", 30, "Meta", 700000);

    // e1->showDetails();
    // showSalary(e);
    // e2->showDetails();

    HR h;
    h.showSalary(e);

    // delete e2;
    // e2 = nullptr;

    // cout << "\n--- 3. Testing Operator Overloading ---" << endl;
    // cout << "Total Salary Combined: " << (e + d) << endl;

    // cout << "\n--- 4. Testing Diamond Problem Solution ---" << endl;
    // Director dir("Boss Man", 45, "Apple", 1500000);
    // dir.showDetails();


    // cout << "=== CASE 1: Employee Pointer pointing to an Employee object ===" << endl;
    // // FIXED: Passed valid dummy values into the constructor arguments
    // Employee* empPtr = new Employee("Alice", 30, "Amazon", 300000);
    // empPtr->showDetails(); // Looks at Employee vtable -> Runs Employee version
    // delete empPtr;

    // cout << "\n=== CASE 2: Employee Pointer pointing to a Developer object ===" << endl;
    // // FIXED: Passed valid dummy values into the constructor arguments
    // Employee* devPtr = new Developer("developer", "Daniel", 28, "Meta", 400000);
    // devPtr->showDetails(); // Looks at Developer vtable -> Runs Developer version!
    // delete devPtr;

    // cout << "\n=== BONUS: Forcing a Developer object to run the Base function ===" << endl;
    // Employee* bonusPtr = new Developer("developer", "Charlie", 32, "Apple", 500000);
    // // Bypasses the child's vtable lookup path entirely using the '::' scope operator
    // bonusPtr->Employee::showDetails();
    // delete bonusPtr;


    return 0;
}
