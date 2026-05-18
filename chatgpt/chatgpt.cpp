// CHATGPT

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;
/*
const int N = 4;                 // EXACTAMENTE 15 ciudades

const int VISITED_ALL = (1 << N) - 1;
*/
// ------------------------------------------------------------
// MATRIZ DE ADYACENCIA (GRAFO PONDERADO)
// ------------------------------------------------------------
/*
int graph[N][N] = {

    //0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
    { 0, 29, 20, 21, 16, 31,100, 12,  4, 31, 18, 23, 27, 35, 40}, //0
    {29,  0, 15, 29, 28, 40, 72, 21, 29, 41, 12, 19, 33, 24, 36}, //1
    {20, 15,  0, 15, 14, 25, 81,  9, 23, 27, 16, 28, 30, 31, 29}, //2
    {21, 29, 15,  0,  4, 12, 92, 12, 25, 13, 22, 18, 26, 37, 41}, //3
    {16, 28, 14,  4,  0, 16, 94,  9, 20, 16, 24, 21, 25, 32, 38}, //4
    {31, 40, 25, 12, 16,  0, 95, 24, 36,  3, 28, 17, 29, 33, 44}, //5
    {100,72, 81, 92, 94, 95,  0, 90,101, 99, 88, 76, 84, 91, 93}, //6
    {12, 21,  9, 12,  9, 24, 90,  0, 15, 25, 11, 20, 22, 30, 35}, //7
    { 4, 29, 23, 25, 20, 36,101, 15,  0, 35, 19, 24, 31, 38, 42}, //8
    {31, 41, 27, 13, 16,  3, 99, 25, 35,  0, 30, 18, 26, 34, 45}, //9
    {18, 12, 16, 22, 24, 28, 88, 11, 19, 30,  0, 14, 20, 22, 31}, //10
    {23, 19, 28, 18, 21, 17, 76, 20, 24, 18, 14,  0, 11, 15, 20}, //11
    {27, 33, 30, 26, 25, 29, 84, 22, 31, 26, 20, 11,  0, 10, 18}, //12
    {35, 24, 31, 37, 32, 33, 91, 30, 38, 34, 22, 15, 10,  0, 14}, //13
    {40, 36, 29, 41, 38, 44, 93, 35, 42, 45, 31, 20, 18, 14,  0}  //14
};
*/


const int N = 4;                 // EXACTAMENTE 15 ciudades

const int VISITED_ALL = (1 << N) - 1;

int graph[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

// ------------------------------------------------------------
// DP[mask][pos]
// mask = subconjunto de ciudades visitadas
// pos  = ciudad actual
// ------------------------------------------------------------
vector<vector<int>> dp(1 << N, vector<int>(N, -1));

// Para reconstruir el camino óptimo
vector<vector<int>> parent(1 << N, vector<int>(N, -1));

// ------------------------------------------------------------
// FUNCIÓN TSP CON PROGRAMACIÓN DINÁMICA + BITMASK
// ------------------------------------------------------------
int tsp(int mask, int pos)
{
    // Caso base:
    // Si todas las ciudades fueron visitadas,
    // regresar a la ciudad inicial (0)
    if (mask == VISITED_ALL)
    {
        return graph[pos][0];
    }

    // Si ya fue calculado
    if (dp[mask][pos] != -1)
    {
        return dp[mask][pos];
    }

    int ans = INT_MAX;

    // Intentar visitar cada ciudad no visitada
    for (int city = 0; city < N; city++)
    {
        // Verificar si city NO ha sido visitada
        if ((mask & (1 << city)) == 0)
        {
            int newCost =
                graph[pos][city] +
                tsp(mask | (1 << city), city);

            // Actualizar mínimo
            if (newCost < ans)
            {
                ans = newCost;
                parent[mask][pos] = city;
            }
        }
    }

    return dp[mask][pos] = ans;
}

// ------------------------------------------------------------
// RECONSTRUCCIÓN DEL CAMINO ÓPTIMO
// ------------------------------------------------------------
void printPath()
{
    int mask = 1; // Solo ciudad 0 visitada
    int pos = 0;

    cout << "\nRecorrido optimo:\n";
    cout << "0 ";

    while (true)
    {
        int nextCity = parent[mask][pos];

        if (nextCity == -1)
            break;

        cout << "-> " << nextCity << " ";

        mask |= (1 << nextCity);
        pos = nextCity;
    }

    // Regresar al origen
    cout << "-> 0\n";
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------
int main()
{
    cout << "=========================================\n";
    cout << "PROBLEMA DEL VIAJANTE (TSP)\n";
    cout << "Programacion Dinamica + Bitmask DP\n";
    cout << "15 ciudades\n";
    cout << "=========================================\n";

    int minCost = tsp(1, 0);

    cout << "\nCosto minimo total: " << minCost << endl;

    printPath();

    return 0;
}