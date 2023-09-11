#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N, W, sumaTotal;
vector<int> cuentas;
vector<vector<int>> dp;
string res;

bool saldosSospechosos(int i, int w) {
    if (i == N)
        return w == W;

    if (dp[i][w + sumaTotal] != -1)
        return dp[i][w + sumaTotal];
    
    bool esVenta = saldosSospechosos(i + 1, w + cuentas[i]);
    bool esGasto = saldosSospechosos(i + 1, w - cuentas[i]);
    dp[i][w + sumaTotal] = esVenta || esGasto;

    if ((esVenta && esGasto) || (esVenta && res[i] == '-') || (esGasto && res[i] == '+'))
        res[i] = '?';
    else if (esVenta && res[i] == 'x')
        res[i] = '+';
    else if (esGasto && res[i] == 'x')
        res[i] = '-';

    return dp[i][w + sumaTotal];
}

int main() {
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> N >> W;
        cuentas.assign(N, 0);
        res.assign(N, 'x');
        sumaTotal = 0;

        for (int j = 0; j < N; j++) {
            cin >> cuentas[j];
            cuentas[j] /= 100;
            sumaTotal += cuentas[j];
        }

        W /= 100;

        dp.assign(N, vector<int>(2 * sumaTotal + 1, -1));

        saldosSospechosos(0, 0);
        cout << res << endl;
    }

    return 0;
}