#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> dp;
vector<vector<tuple<bool, int, int>>> path; 
int bagCapacity, stuffNum;

int solve(vector<pair<int, int>>& stuffList){
    for(int item=1; item<=stuffNum; ++item){
        for(int capacity=0; capacity<=bagCapacity; ++capacity){
            if(stuffList[item-1].second>bagCapacity){
                continue;
            }

            int maxValWithoutCurrItem=dp[item-1][capacity];
            int maxValWithCurrItem=0;
            int currWeight=stuffList[item-1].second;
            int remainingSlot=0;

            if(capacity>=currWeight){
                remainingSlot=capacity-currWeight;
                maxValWithCurrItem=stuffList[item-1].first+dp[item-1][remainingSlot];
            }

            if(maxValWithCurrItem>maxValWithoutCurrItem){
                dp[item][capacity]=maxValWithCurrItem;
                get<0>(path[item][capacity])=1;
                get<1>(path[item][capacity])=item-1;
                get<2>(path[item][capacity])=remainingSlot;
            }
            else{
                dp[item][capacity]=maxValWithoutCurrItem;
                get<0>(path[item][capacity])=0;
                get<1>(path[item][capacity])=item-1;
                get<2>(path[item][capacity])=capacity;
            }
        }
    }

    return dp[stuffNum][bagCapacity];
}

void printCombination(){
    int m=stuffNum, n=bagCapacity, tmp;

    while(get<1>(path[m][n])){
        if(get<0>(path[m][n])){
            cout << m << '\n';
        }
        tmp=m;
        m=get<1>(path[m][n]);
        n=get<2>(path[tmp][n]);
    }
}

int main(){
    vector<pair<int, int>> stuffList={ {50, 11},{30, 2},{20, 6},{30, 1} };
    bagCapacity=11; stuffNum=stuffList.size();

    dp.resize(stuffNum+1, vector<int>(bagCapacity+1));
    path.resize(stuffNum+1, vector<tuple<bool, int, int>>(bagCapacity+1));

    for(int i=0; i<=bagCapacity; ++i){
        dp[0][i]=0;
    }
    for(int i=0; i<=stuffNum; ++i){
        dp[i][0]=0;
    }

    cout << solve(stuffList) << '\n';
    printCombination();

    return 0;
}