#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum
{
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA
};

const int INF = 1e8;

int N, M;
int longMinima, longMaxima;
vector<string> tablero;
vector<vector<bool>> recorridos;

void backTracking(int i, int j, int longitud, int ultDireccion)
{
    if (i < 0 || i >= N || j < 0 || j >= M)
        return;

    if (recorridos[i][j] || tablero[i][j] == '#')
        return;

    if (i == N - 1 && j == M - 1)
    {
        if (longitud > longMaxima)
            longMaxima = longitud;

        if (longitud < longMinima)
            longMinima = longitud;

        return;
    }

    recorridos[i][j] = true;

    switch (tablero[i][j])
    {
        case '+':
            backTracking(i, j + 1, longitud + 1, IZQUIERDA);
            backTracking(i + 1, j, longitud + 1, ARRIBA);
            backTracking(i, j - 1, longitud + 1, DERECHA);
            backTracking(i - 1, j, longitud + 1, ABAJO);
            break;
        case 'I':
            if (ultDireccion > -1)
            {
                switch (ultDireccion)
                {
                    case DERECHA:
                        backTracking(i, j - 1, longitud + 1, DERECHA);
                        break;
                    case IZQUIERDA:
                        backTracking(i, j + 1, longitud + 1, IZQUIERDA);
                        break;
                    case ARRIBA:
                        backTracking(i + 1, j, longitud + 1, ARRIBA);
                        break;
                    case ABAJO:
                        backTracking(i - 1, j, longitud + 1, ABAJO);
                        break;
                }
            }
            else
            {
                backTracking(i + 1, j, longitud + 1, ARRIBA);
                backTracking(i, j + 1, longitud + 1, IZQUIERDA);
            }
            break;
        case 'L':
            if (ultDireccion > -1)
            {
                switch (ultDireccion)
                {
                    case IZQUIERDA:
                    case DERECHA:
                        backTracking(i + 1, j, longitud + 1, ARRIBA);
                        backTracking(i - 1, j, longitud + 1, ABAJO);
                        break;
                    case ARRIBA:
                    case ABAJO:
                        backTracking(i, j + 1, longitud + 1, IZQUIERDA);
                        backTracking(i, j - 1, longitud + 1, DERECHA);
                        break;
                }
            }
            else
            {
                backTracking(i + 1, j, longitud + 1, ARRIBA);
                backTracking(i, j + 1, longitud + 1, IZQUIERDA);
            }
            break;
    }
    
    recorridos[i][j] = false;
}

int main()
{
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++)
    {
        longMinima = INF;
        longMaxima = -INF;
        tablero.clear();

        cin >> N >> M;
        recorridos.clear();
        recorridos.resize(N, vector<bool>(M, false));

        for (int j = 0; j < N; j++)
        {
            string input;
            cin >> input;

            tablero.push_back(input);
        }
        
        backTracking(0, 0, 0, -1);

        if (longMinima == INF)
            cout << "IMPOSIBLE" << endl;
        else
            cout << "POSIBLE " << longMinima << " " << longMaxima << endl;
    }

    return 0;
}