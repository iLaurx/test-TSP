#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Cambiar esta constante según el tamaño de la matriz
const int N = 4; 
const int VISITED_ALL = (1 << N) - 1;

// Matriz de adyacencia de prueba
int graph[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

// Tabla DP: dp[estado_mascara][ciudad_actual]
vector<vector<int>> dp(1 << N, vector<int>(N, -1));
// Tabla de rastreo para reconstruir el camino
vector<vector<int>> parent(1 << N, vector<int>(N, -1));

int tsp(int mask, int pos) {
    // Caso base: todas las ciudades visitadas, regresar al origen
    if (mask == VISITED_ALL) {
        return graph[pos][0];
    }
    
    // Si ya se calculó el estado, usar memorización
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INT_MAX;
    
    // Probar ir a todas las ciudades no visitadas
    for (int city = 0; city < N; city++) {
        if ((mask & (1 << city)) == 0) {
            int newCost = graph[pos][city] + tsp(mask | (1 << city), city);
            
            if (newCost < ans) {
                ans = newCost;
                parent[mask][pos] = city;
            }
        }
    }
    return dp[mask][pos] = ans;
}

void printPath() {
    int mask = 1; // Bit 0 encendido (Ciudad 0 visitada)
    int pos = 0;
    
    cout << "Recorrido optimo detallado: 0";
    
    while (true) {
        int nextCity = parent[mask][pos];
        if (nextCity == -1) break;
        
        cout << " -> " << nextCity;
        mask |= (1 << nextCity);
        pos = nextCity;
    }
    // Cierre del ciclo Hamiltoniano
    cout << " -> 0" << endl;
}

int main() {
    cout << "=========================================" << endl;
    cout << "      SOLUCIÓN EXACTA AL TSP" << endl;
    cout << "=========================================" << endl;
    
    // Iniciar desde la ciudad 0 con la máscara 1 (0001)
    int minCost = tsp(1, 0);
    
    cout << "Costo minimo total de la ruta: " << minCost << endl;
    printPath();
    cout << "=========================================" << endl;

    return 0;
}