struct Result
{
    int a;
    int b;
    int c;
};

Result getValues()
{
    return {10,20,30};
}

int main()
{
    Result result = getValues();

    cout<< result.first ;

}

// #include <vector>

// vector<int> getValues()
// {
//     return {10, 20, 30};
// }
// Access the values:




// vector<int> values = getValues();

// cout << values[0] << " "
//      << values[1] << " "
//      << values[2];
