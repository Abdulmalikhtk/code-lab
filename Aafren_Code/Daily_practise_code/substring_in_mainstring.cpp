#include <iostream>
#include <string>
using namespace std;

int findSubstring(string mainstring, string substring)
{
    int n = mainstring.length();
    int m = substring.length();

    for (int i = 0; i <= n - m; i++)      // note: <=, not <
    {
        int j = 0;
        while (j < m && mainstring[i+j] == substring[j])
        {
            j++;
        }
        if (j == m)                        // matched all the way through
        {
            return i;
        }
    }
    return -1;
}


int main() {
    string mainstring = "Hi this is aafren";
    string substring  = "this";


    size_t found = mainstring.find(substring);

    if (found != string::npos)
    {
        cout << "substring " << substring << " is found in mainstring "
             << mainstring << " at the position of: " << found << endl;
    }
    else
    {
        cout << "substring " << substring << " is not found in mainstring "
             << mainstring << endl;
    }

    //manual method
    int found1 = findSubstring(mainstring, substring);

    if (found1 != -1)
    {
        cout << "substring " << substring << " is found in mainstring "
             << mainstring << " at the position of: " << found << endl;
    }
    else
    {
        cout << "substring " << substring << " is not found in mainstring "
             << mainstring << endl;
    }

    return 0;
}
