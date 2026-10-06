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
