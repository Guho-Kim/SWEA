// [SWEA] No 13736. 사탕 분배
/*
    A + B = C
    0.
        A % C
    1. 
        (1) 2A
            2A % C
        (2) A-B = 2A-C
            (2A-C) % C = 2A % C
    2. 
        (1) 2(2A % C)
            2^2*A % C
        (2) 2(2A % C) - C)
            2^2*A % C
    ...
    n.
        2^n*A % C
*/

#include <iostream>
using namespace std;

typedef unsigned long long ull;
ull C; // A + B = C

ull powerOfTwo(ull n)
{
	if (n == 0) return 1;
    ull temp = powerOfTwo(n / 2);
	ull result = (temp*temp)%C;
    
	if (n % 2 == 1) result =(result*2)%C;

	return result;
}

int solve(){
	ull A, B, K;
    cin >> A>> B >> K;
    C = A + B;
    
	ull result = (powerOfTwo(K) * A) % C;
	return min(result, C - result);
}

int main()
{
	int T;cin >> T;
	for (int tc = 1; tc <= T; tc++){cout << "#" << tc << ' ' <<solve()<< "\n";}
	return 0;
}