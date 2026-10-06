// General recommendation:

// Use struct when each value has a specific meaning.
// Use array when all three values have the same type.
// Use tuple when the values can have different types.
// Use vector when the number of values can change.
// Use references when you intentionally want the function to modify existing variables.

// Most are related to the C++ Standard Library, but they belong to different categories.

// std::vector — STL container; dynamic size.
// std::array — STL-style container; fixed size.
// std::pair — Standard Library utility that groups two values.
// std::tuple — Standard Library utility that groups multiple values.
// struct — core C++ language feature, not STL.
// Reference parameters (int&) — core C++ language feature, not STL.

// vector<int> values;            // Container
// sort(values.begin(), values.end()); // Algorithm
// auto it = values.begin();      // Iterator
