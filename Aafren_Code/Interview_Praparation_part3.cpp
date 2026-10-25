Your programs demonstrate the correct interview topics, but there are a few important corrections.

1. Shallow Copy, Deep Copy and Operator Overloading
Shallow Copy
name = t.name;
Both objects store the same memory address:

t2.name ----\
             ---> "Daniel"
t4.name ----/
Therefore, changing t4.name also changes t2.name. Shallow copying raw owning pointers is dangerous because deleting one pointer can leave the other dangling or cause a double deletion.

Deep Copy
name = new string(*t.name);
A new string is allocated and only the value is copied:

t1.name ---> "Charlie"
t3.name ---> "Charlie"
The objects are independent, so changing t3.name to "alice" does not modify t1.name.

Operator Overloading
bool operator==(const Test& other) const {
    return age == other.age;
}
This defines how == behaves for two Test objects. Your implementation considers objects equal when their ages match, regardless of their names.

Important Problem
Your class allocates memory with new but never calls delete, causing memory leaks. Adding a destructor while retaining the shallow copy would cause double deletion.

For production code, store the string directly:

class Test {
public:
    string name;
    int age;
};
This avoids manual memory management. If a class owns a raw resource, follow the Rule of Three/Five: destructor, copy constructor, copy assignment, move constructor and move assignment.

2. Lvalue, Rvalue and std::move
An lvalue is an expression that identifies an existing object, usually with a name:

string name = "Kiccha";
string& reference = name;
An rvalue is generally a temporary value or an object whose resources may be moved:

string temporary = string("Hema");
string&& reference = string("Hema");
An lvalue reference is an alias:

string name = "Kiccha";
string& reference = name;

reference = "Kiccha Kicchu";

cout << name; // Kiccha Kicchu
std::move
std::move does not move anything by itself. It converts an object into an rvalue so its move constructor or move assignment operator can be selected.

string source = "Hema";
string destination = std::move(source);
After moving:

destination normally owns the original string data.
source remains valid but has an unspecified value.
It is commonly empty, but the C++ standard does not guarantee that.
Therefore, this statement is incorrect:

cout << source << " is guaranteed empty";
The correct interview explanation is:

“The moved-from object remains valid and can be assigned a new value or destroyed, but its previous value should not be assumed.”

Also, your expected output has one mistake: after assigning nameRef = "kiccha kicchu", name1 prints "kiccha kicchu", not "kiccha".

3. Smart Pointers
unique_ptr
unique_ptr provides exclusive ownership. It cannot be copied, but ownership can be transferred using std::move.

unique_ptr<Rectangle> first =
    make_unique<Rectangle>(10, 9);

unique_ptr<Rectangle> second = std::move(first);

if (first == nullptr) {
    cout << "Ownership moved to second\n";
}

second->area();
After moving, first becomes null. Calling first->area() would cause undefined behavior.

shared_ptr
shared_ptr allows multiple pointers to own the same object. The object is destroyed when the final owner disappears.

shared_ptr<Rectangle> first =
    make_shared<Rectangle>(10, 9);

{
    shared_ptr<Rectangle> second = first;

    cout << first.use_count() << '\n'; // 2
}

cout << first.use_count() << '\n'; // 1
weak_ptr
weak_ptr observes an object managed by shared_ptr but does not own it or increase its reference count. It prevents ownership cycles.

weak_ptr<Rectangle> observer = first;

if (shared_ptr<Rectangle> object = observer.lock()) {
    object->area();
}
Always call lock() before accessing the object because the original shared_ptr may already have destroyed it.

Interview summary: unique_ptr means one owner, shared_ptr means multiple owners, and weak_ptr means a non-owning observer. Prefer smart pointers and direct value members over manually managing memory with new and delete.

Suggested actions
