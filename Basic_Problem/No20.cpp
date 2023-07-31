/*
    3304. 최장 공통 부분 수열
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 1001

using namespace std;

int dp[MAX_N][MAX_N];

void init(){
    for(int i=0; i<MAX_N; i++)
        for(int j=0; j<MAX_N; j++)
            dp[i][j]=0;

}


void Make_LCS_DP(string str1, string str2){
    for(int i=1; i<=str1.length(); i++){
        for(int j=1; j<=str2.length(); j++){
            if(str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
        
    }
}


string longestCommonSubsequence(string str1, string str2) {
    int i = str1.length();
    int j = str2.length();
    string result = "";

    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            result = str1[i - 1] + result;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return result;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        init();
        string str1, str2;
        cin >> str1;
        cin >> str2;
        Make_LCS_DP(str1, str2);
        int LCS = dp[str1.length()][str2.length()];

        cout<<"#"<<test_case<<" "<<LCS<<endl;
	}
	return 0;
}