#include <stdio.h>     // Per entrada/sortida
#include <stdlib.h>    // Per gestió de memòria i nombres aleatoris
#include <math.h>      // Per funcions matemàtiques com sqrt() i fabs()

#define N 512          // Definició de mida de vectors i matrius

// Variables globals
float Mat[N][N], MatDD[N][N];
float V1[N], V2[N], V3[N];

// Funció d'inicialització de dades
void InitData() {
    int i, j;
    srand(334411); // Llavor per generar nombres pseudo-aleatoris
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            Mat[i][j] = (((i * j) % 3) ? -1 : 1) * (100.0 * (rand() / (1.0 * RAND_MAX)));
            if ((abs(i - j) <= 3) && (i != j))
                MatDD[i][j] = (((i * j) % 3) ? -1 : 1) * (rand() / (1.0 * RAND_MAX));
            else if (i == j)
                MatDD[i][j] = (((i * j) % 3) ? -1 : 1) * (10000.0 * (rand() / (1.0 * RAND_MAX)));
            else MatDD[i][j] = 0.0;
        }
        V1[i] = (i < N / 2) ? (((i * j) % 3) ? -1 : 1) * (100.0 * (rand() / (1.0 * RAND_MAX))) : 0.0;
        V2[i] = (i >= N / 2) ? (((i * j) % 3) ? -1 : 1) * (100.0 * (rand() / (1.0 * RAND_MAX))) : 0.0;
        V3[i] = (((i * j) % 5) ? -1 : 1) * (100.0 * (rand() / (1.0 * RAND_MAX)));
    }
}

// Funció per mostrar elements d’un vector
void PrintVect(float vect[N], int from, int numel) {
    for (int i = from; i < from + numel && i < N; i++) {
        printf("%f ", vect[i]);
    }
    printf("\n");
}

// Funció per mostrar elements d’una fila d’una matriu
void PrintRow(float mat[N][N], int row, int from, int numel) {
    for (int i = from; i < from + numel && i < N; i++) {
        printf("%f ", mat[row][i]);
    }
    printf("\n");
}

// Multiplicació escalar d'un vector
void MultEscalar(float vect[N], float vectres[N], float alpha) {
    for (int i = 0; i < N; i++) {
        vectres[i] = vect[i] * alpha;
    }
}

// Producte escalar entre dos vectors
float Scalar(float vect1[N], float vect2[N]) {
    float result = 0;
    for (int i = 0; i < N; i++) {
        result += vect1[i] * vect2[i];
    }
    return result;
}

// Magnitud d'un vector
float Magnitude(float vect[N]) {
    float sum = 0;
    for (int i = 0; i < N; i++) {
        sum += vect[i] * vect[i];
    }
    return sqrt(sum);
}

// Determinació de vectors ortogonals
int Ortogonal(float vect1[N], float vect2[N]) {
    return Scalar(vect1, vect2) == 0.0;
}

// Projecció d'un vector sobre un altre
void Projection(float vect1[N], float vect2[N], float vectres[N]) {
    float dot_product = Scalar(vect1, vect2);
    float magnitude_squared = Scalar(vect2, vect2);
    for (int i = 0; i < N; i++) {
        vectres[i] = (dot_product / magnitude_squared) * vect2[i];
    }
}

// Norma infinita d'una matriu
float Infininorm(float M[N][N]) {
    float max = 0;
    for (int i = 0; i < N; i++) {
        float rowSum = 0;
        for (int j = 0; j < N; j++) {
            rowSum += fabs(M[i][j]);
        }
        if (rowSum > max) max = rowSum;
    }
    return max;
}

// Norma ú d'una matriu
float Onenorm(float M[N][N]) {
    float max = 0;
    for (int j = 0; j < N; j++) {
        float colSum = 0;
        for (int i = 0; i < N; i++) {
            colSum += fabs(M[i][j]);
        }
        if (colSum > max) max = colSum;
    }
    return max;
}

// Norma de Frobenius d'una matriu
float NormFrobenius(float M[N][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += M[i][j] * M[i][j];
        }
    }
    return sqrt(sum);
}

// Funció principal per realitzar proves
int main() {
    InitData();

    // Proves de funcions
    float Vres[N];
    MultEscalar(V3, Vres, 2.0);
    printf("Multiplicació escalar de V3 amb 2.0:\n");
    PrintVect(Vres, 0, 10);

    printf("Producte escalar V1·V2: %f\n", Scalar(V1, V2));
    printf("Magnitud de V1: %f\n", Magnitude(V1));

    printf("Infininorm de Mat: %f\n", Infininorm(Mat));
    printf("Norma ú de Mat: %f\n", Onenorm(Mat));
    printf("Norma de Frobenius de Mat: %f\n", NormFrobenius(Mat));

    return 0;
}

