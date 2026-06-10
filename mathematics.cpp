#include <vector>
using namespace std;

vector<int> primes(int n){
    vector<int> is_prime(n+1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i*i <= n; i++)
    {
        if(is_prime[i]){
            for (int j = i*i; j <= n; j+=i)
            {
                is_prime[j] = 0;
            }
        }
    }
    vector<int> prime_nums;
    for (int i = 2; i <= n; i++)
    {
        if(is_prime[i]) prime_nums.push_back(i);
    }
    return prime_nums;
}
