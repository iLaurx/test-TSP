// GROK

#include <bits/stdc++.h>
using namespace std;
/*
const int N = 15;
const int INF = 1e9;

// Matriz de distancias 15x15 (simétrica, ejemplo realista)
int dist[N][N] = {
    {0, 29, 20, 21, 16, 31, 10, 25, 24, 28, 18, 22, 15, 30, 27},
    {29, 0, 15, 29, 28, 40, 35, 20, 18, 22, 25, 19, 31, 17, 23},
    {20, 15, 0, 12, 25, 18, 22, 30, 27, 19, 21, 28, 16, 24, 26},
    {21, 29, 12, 0, 14, 23, 19, 17, 31, 26, 15, 20, 29, 22, 18},
    {16, 28, 25, 14, 0, 21, 24, 28, 15, 30, 27, 17, 20, 19, 22},
    {31, 40, 18, 23, 21, 0, 16, 29, 25, 14, 30, 22, 18, 27, 21},
    {10, 35, 22, 19, 24, 16, 0, 15, 28, 20, 17, 26, 23, 31, 19},
    {25, 20, 30, 17, 28, 29, 15, 0, 22, 18, 24, 15, 30, 21, 28},
    {24, 18, 27, 31, 15, 25, 28, 22, 0, 16, 19, 29, 14, 25, 20},
    {28, 22, 19, 26, 30, 14, 20, 18, 16, 0, 23, 17, 27, 15, 29},
    {18, 25, 21, 15, 27, 30, 17, 24, 19, 23, 0, 28, 22, 20, 16},
    {22, 19, 28, 20, 17, 22, 26, 15, 29, 17, 28, 0, 25, 18, 24},
    {15, 31, 16, 29, 20, 18, 23, 30, 14, 27, 22, 25, 0, 21, 19},
    {30, 17, 24, 22, 19, 27, 31, 21, 25, 15, 20, 18, 21, 0, 28},
    {27, 23, 26, 18, 22, 21, 19, 28, 20, 29, 16, 24, 19, 28, 0}
};
*/


// ? CASO DE PRUEBA

const int N = 4;   // ← Modificado
const int INF = 1e9;

int dist[4][4] = {
    {0,  10, 15, 20},
    {10, 0,  35, 25},
    {15, 35, 0,  30},
    {20, 25, 30, 0}
};


int dp[1 << N][N];           // dp[mask][i] = costo mínimo para visitar mask terminando en i
int prevCity[1 << N][N];     // Para reconstruir el camino
int prevMask[1 << N][N];     // Máscara anterior

void tspHeldKarp() {
    // Inicialización
    for (int mask = 0; mask < (1 << N); ++mask) {
        for (int i = 0; i < N; ++i) {
            dp[mask][i] = INF;
            prevCity[mask][i] = -1;
            prevMask[mask][i] = -1;
        }
    }

    // Base: solo ciudad 0
    dp[1][0] = 0;

    // Bottom-up
    for (int mask = 0; mask < (1 << N); ++mask) {
        for (int u = 0; u < N; ++u) {
            if (dp[mask][u] == INF) continue;

            for (int v = 0; v < N; ++v) {
                if (mask & (1 << v)) continue; // ya visitada

                int newMask = mask | (1 << v);
                int newCost = dp[mask][u] + dist[u][v];

                if (newCost < dp[newMask][v]) {
                    dp[newMask][v] = newCost;
                    prevCity[newMask][v] = u;
                    prevMask[newMask][v] = mask;
                }
            }
        }
    }

    // Encontrar el mínimo costo cerrando el ciclo
    int fullMask = (1 << N) - 1;
    int minCost = INF;
    int lastCity = -1;

    for (int i = 1; i < N; ++i) {
        if (dp[fullMask][i] + dist[i][0] < minCost) {
            minCost = dp[fullMask][i] + dist[i][0];
            lastCity = i;
        }
    }

    // Reconstrucción del camino
    vector<int> path;
    int mask = fullMask;
    int cur = lastCity;

    while (cur != -1) {
        path.push_back(cur);
        int pCity = prevCity[mask][cur];
        int pMask = prevMask[mask][cur];
        cur = pCity;
        mask = pMask;
    }
    path.push_back(0);           // cerrar ciclo
    reverse(path.begin(), path.end());

    // Salida
    cout << "=== SOLUCIÓN ÓPTIMA TSP (15 ciudades) ===\n";
    cout << "Costo mínimo total: " << minCost << "\n\n";
    cout << "Recorrido óptimo: ";
    for (int city : path) {
        cout << city << " ";
    }
    cout << "\n";
}

int main() {
    tspHeldKarp();
    return 0;
}