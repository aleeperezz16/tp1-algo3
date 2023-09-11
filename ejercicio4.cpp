#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = 1e9;

int N, K;
vector<int> posiciones, solucion;
vector<vector<vector<int>>> dp;

int costoMin(int inicio, int ultimo) {
    int costo = 0;
    int costoSig = INF, costoAnt = INF;
    for (int i = inicio + 1; i < ultimo; i++) {
        if (ultimo < N)
            costoSig = abs(posiciones[i] - posiciones[ultimo]);
        if (inicio > -1)
            costoAnt = abs(posiciones[i] - posiciones[inicio]);

        costo += min(costoAnt, costoSig);
    }

    return costo;
}

int choripanes(int i, int j, int k) {
    if (k < 0)
        return INF;
    
    if (i == N)
        return k > 0 ? INF : costoMin(j, i);

    if (dp[i][j + 1][k] != -1)
        return dp[i][j + 1][k];

    dp[i][j + 1][k] = min(costoMin(j, i) + choripanes(i + 1, i, k - 1), choripanes(i + 1, j, k));
    return dp[i][j + 1][k];
}

void reconstruirSolucion() {
    vector<int> solucion;
    for (int i = 0, j = -1, k = K; i < N; i++) {
        if (dp[i][j + 1][k] == costoMin(j, i) + choripanes(i + 1, i, k - 1)) {
            solucion.push_back(posiciones[i]);
            j = i;
            k--;
        }
    }
    
    for (int i = 0; i < K; i++) {
        cout << solucion[i];
        if (i < K - 1)
            cout << " ";
    }
    cout << endl;   
}

int main() {
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> N >> K;
        posiciones.assign(N, 0);

        for (int j = 0; j < N; j++)
            cin >> posiciones[j];

        dp.assign(N, vector<vector<int>>(N, vector<int>(K + 1, -1)));
        cout << choripanes(0, -1, K) << endl;
        reconstruirSolucion();
    }

    return 0;
}