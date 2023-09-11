#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Parcial {
    ulong minutos;
    ulong descontento;
};

ulong N;
vector<Parcial> parciales;

bool ordenarParciales(const Parcial &p1, const Parcial &p2) {
    return p1.minutos * p2.descontento < p2.minutos * p1.descontento;
}

ulong correccionesPendientes() {
    sort(parciales.begin(), parciales.end(), ordenarParciales);

    unsigned long long descontento = 0, tiempo = 0;
    for (ulong i = 0; i < N; i++) {
        tiempo += parciales[i].minutos;
        descontento = (descontento + tiempo * parciales[i].descontento) % (ulong)(1e9 + 7);
    }

    return descontento;
}

int main() {
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> N;
        parciales.resize(N);

        for (ulong j = 0; j < N; j++)
            cin >> parciales[j].minutos;

        for (ulong j = 0; j < N; j++)
            cin >> parciales[j].descontento;

        cout << correccionesPendientes() << endl;
    }

    return 0;
}