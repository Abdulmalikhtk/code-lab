#include<iostream>
#include<utility> //provideds pair
using namespace std; // allows writing pair instead of std::pair

//1,000,000,007 is popular because it is the smallest prime number greater than one billion.

// Close to (10^9), so residues have a large range.
// Prime, enabling modular inverses and Fermat’s little theorem.
// Values fit in a signed 32-bit integer.
// Multiplying two residues fits in signed 64-bit long long.
// Easy to remember and standardized across programming contests.


#include <iostream>
#include <utility>
using namespace std;

const long long MOD = 1'000'000'007;

pair<long long, long long> fibonacci(long long n)
{
    // F(0) = 0 and F(1) = 1
    if (n == 0)
        return {0, 1};

    // Calculate F(k) and F(k + 1), where k = n / 2
    auto [a, b] = fibonacci(n / 2);

    // c = F(2k)
    long long c =
        (a * ((2 * b % MOD - a + MOD) % MOD)) % MOD;

    // d = F(2k + 1)
    long long d =
        (a * a % MOD + b * b % MOD) % MOD;

    if (n % 2 == 0)
    {
        // n = 2k
        return {c, d};
    }
    else
    {
        // n = 2k + 1
        return {d, (c + d) % MOD};
    }
}

int main()
{
    long long n;
    cin >> n;

    cout << fibonacci(n).first << endl;
}
