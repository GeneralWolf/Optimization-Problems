#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int dp[505][60000][2];
int n, h, H;

int recur(int idx, int las, int change) {
    if (las > H)                            //verificações se é possivel
        return 0;
    if (las < h)
        return 0;
    if (idx > n)
        return 0;
    if (las == h and idx >= 3)
        return 1;
    int res = 0;

    if (dp[idx][las][change] > -1)          //se ja tiver sido computado da return desse valor, poupa poder computacional
        return dp[idx][las][change];

    if (change) {                               //se ainda estiver a subir testa tanto para continuar a subir como para começar a descer
        for (int i = 1; i <= h - 1; i++) {
            res += recur(idx + 1, las + i, change);
            res %= mod;
            res += recur(idx + 1, las - i, 1 - change);
            res %= mod;
        }
    }
    else {                                          //se estiver a descer só testa a continuação da descida
        for (int i = 1; i <= h - 1; i++) {
            res += recur(idx + 1, las - i, change);
            res %= mod;
        }
    }

    return dp[idx][las][change] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int f;
    cin >> f;


    while (f--) {
        memset(dp, -1, sizeof dp);
        cin >> n >> h >> H;
        cout << recur(1, h, 1) % mod << endl;
    }

    return 0;
}