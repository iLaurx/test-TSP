// GEMINI 

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int N = 15;
const int INF = 1e9; // Valor infinito para representar la ausencia de caminos o inicialización

// Matriz de adyacencia de 15x15 (Valores de ejemplo simulados)
// El costo de ir de una ciudad a sí misma es 0.
/*
int dist[N][N] = {
    {0, 11, 15, 23, 19, 27, 30, 12, 18, 20, 25, 22, 14, 16, 21},
    {11, 0, 12, 17, 22, 25, 14, 19, 21, 13, 29, 24, 18, 15, 10},
    {15, 12, 0, 13, 10, 18, 22, 27, 25, 31, 16, 19, 20, 23, 17},
    {23, 17, 13, 0, 14, 11, 28, 20, 16, 15, 12, 21, 26, 24, 19},
    {19, 22, 10, 14, 0, 12, 16, 21, 23, 25, 18, 14, 11, 13, 20},
    {27, 25, 18, 11, 12, 0, 15, 13, 14, 19, 22, 26, 20, 17, 16},
    {30, 14, 22, 28, 16, 15, 0, 11, 19, 17, 21, 23, 25, 12, 14},
    {12, 19, 27, 20, 21, 13, 11, 0, 10, 14, 16, 18, 15, 11, 13},
    {18, 21, 25, 16, 23, 14, 19, 10, 0, 12, 15, 17, 19, 22, 24},
    {20, 13, 31, 15, 25, 19, 17, 14, 12, 0, 11, 13, 16, 18, 15},
    {25, 29, 16, 12, 18, 22, 21, 16, 15, 11, 0, 10, 12, 14, 18},
    {22, 24, 19, 21, 14, 26, 23, 18, 17, 13, 10, 0, 11, 15, 13},
    {14, 18, 20, 26, 11, 20, 25, 15, 19, 16, 12, 11, 0, 10, 12},
    {16, 15, 23, 24, 13, 17, 12, 11, 22, 18, 14, 15, 10, 0, 11},
    {21, 10, 17, 19, 20, 16, 14, 13, 24, 15, 18, 13, 12, 11, 0}
};
*/

// Caso de prueba

int dist[4][4] = {
    {0, 10, 15, 20}, // Desde Ciudad 0 a: [0, 1, 2, 3]
    {10, 0, 35, 25}, // Desde Ciudad 1 a: [0, 1, 2, 3]
    {15, 35, 0, 30}, // Desde Ciudad 2 a: [0, 1, 2, 3]
    {20, 25, 30, 0}  // Desde Ciudad 3 a: [0, 1, 2, 3]
};


// Tabla de DP: memo[máscara_ciudades_visitadas][última_ciudad_visitada]
// El tamaño de la máscara para 15 ciudades es 2^15 = 32768
int memo[1 << N][N];

// Tabla auxiliar para reconstruir la ruta óptima
int parent[1 << N][N];

// Función recursiva con memorización (Top-Down)
int tsp(int mask, int u) {
    // Caso base: Si todas las ciudades han sido visitadas (máscara con todos los bits en 1)
    // Se debe regresar obligatoriamente a la ciudad origen (0)
    if (mask == (1 << N) - 1) {
        return dist[u][0];
    }

    // Si el estado ya fue calculado previamente, retornar el valor guardado
    if (memo[mask][u] != -1) {
        return memo[mask][u];
    }

    int ans = INF;
    int best_next_city = -1;

    // Intentar visitar cada una de las siguientes ciudades posibles
    for (int v = 0; v < N; ++v) {
        // Verificar si la ciudad 'v' NO ha sido visitada aún (el bit v está en 0)
        if ((mask & (1 << v)) == 0) {
            // Calcular el costo de transicionar a la ciudad 'v'
            int new_cost = dist[u][v] + tsp(mask | (1 << v), v);
            
            if (new_cost < ans) {
                ans = new_cost;
                best_next_city = v;
            }
        }
    }

    // Registrar la decisión óptima para la posterior reconstrucción del camino
    parent[mask][u] = best_next_city;
    
    // Memorizar y retornar el resultado óptimo para este estado
    return memo[mask][u] = ans;
}

// Función para reconstruir e imprimir la ruta exacta tomada
void recuperarRuta() {
    int mask = 1; // Comenzamos con solo la ciudad 0 visitada (000000000000001)
    int curr = 0; // Ciudad inicial
    
    cout << "Ruta optima detallada: ";
    cout << curr;

    // Recorrer las N-1 transiciones restantes
    for (int i = 1; i < N; ++i) {
        int next_city = parent[mask][curr];
        cout << " -> " << next_city;
        mask |= (1 << next_city); // Marcar la siguiente ciudad como visitada
        curr = next_city;         // Moverse a la siguiente ciudad
    }
    
    // Regresar explícitamente al origen
    cout << " -> 0" << endl;
}

int main() {
    // Inicializar la tabla de memorización con -1 (estados no visitados)
    for (int i = 0; i < (1 << N); ++i) {
        for (int j = 0; j < N; ++j) {
            memo[i][j] = -1;
            parent[i][j] = -1;
        }
    }

    // Ejecutar el TSP iniciando en la ciudad 0, con la máscara con solo el bit 0 encendido (1)
    int costo_minimo = tsp(1, 0);

    // Desplegar resultados en consola
    cout << "==================================================" << endl;
    cout << "   SOLUCIÓN EXACTA AL TSP (BITMASK DP) - N = 15" << endl;
    cout << "==================================================" << endl;
    cout << "Costo minimo total de la ruta: " << costo_minimo << endl;
    cout << "--------------------------------------------------" << endl;
    recuperarRuta();
    cout << "==================================================" << endl;

    return 0;
}