#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 512  // Constant de dimensió

float Mat[N][N], MatDD[N][N];
float V1[N], V2[N], V3[N];

// Inicialització de matrius i vectors amb valors pseudo-aleatoris
void InitData(){
int i,j;
srand(334411);
for( i = 0; i < N; i++ )
 for( j = 0; j < N; j++ ){
 Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
 if ( (abs(i - j) <= 3) && (i != j))
 MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
 else if ( i == j )
 MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
 else MatDD[i][j] = 0.0;
 }
for( i = 0; i < N; i++ ){
 V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
 V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
 V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
}
}


// Imprimir elements d'un vector
void PrintVect(float vect[N], int from, int numel) {
    for (int i = from; i < from + numel; i++) {
        printf("%f ", vect[i]);
    }
    printf("\n");
}

// Imprimir elements d'una fila d'una matriu
void PrintRow(float mat[N][N], int row, int from, int numel) {
    for (int i = from; i < from + numel; i++) {
        printf("%f ", mat[row][i]);
    }
    printf("\n");
}

// Multiplicació escalar
void MultEscalar(float vect[N], float vectres[N], float alfa) {
    for (int i = 0; i < N; i++) {
        vectres[i] = alfa * vect[i];
    }
}

// Producte escalar
float Scalar(float vect1[N], float vect2[N]) {
    float result = 0.0;
    for (int i = 0; i < N; i++) {
        result += vect1[i] * vect2[i];
    }
    return result;
}

// Magnitud d’un vector (reutilitza Scalar)
float Magnitude(float vect[N]) {
    return sqrt(Scalar(vect, vect));
}

// Determinar si dos vectors són ortogonals (reutilitza Scalar)
int Ortogonal(float vect1[N], float vect2[N]) {
    return Scalar(vect1, vect2)==0;
}

// Projecció d’un vector sobre un altre (reutilitza Scalar)
void Projection(float vect1[N], float vect2[N], float vectres[N]) {
    float scalar = Scalar(vect1, vect2) / Scalar(vect2, vect2);
    MultEscalar(vect2, vectres, scalar);
}

// Infini-norma d’una matriu
float Infininorm(float M[N][N]) {
    float max_sum = 0.0;
    for (int i = 0; i < N; i++) {
        float row_sum = 0.0;
        for (int j = 0; j < N; j++) {
            row_sum += fabs(M[i][j]);
        }
        if (row_sum > max_sum) max_sum = row_sum;
    }
    return max_sum;
}

// Norma-u d’una matriu
float Onenorm(float M[N][N]) {
    float max_sum = 0.0;
    for (int j = 0; j < N; j++) {
        float summ = 0.0;
        for (int i = 0; i < N; i++) {
            summ += fabs(M[i][j]);
        }
        if (summ > max_sum) max_sum = summ;
    }
    return max_sum;
}

// Norma de Frobenius d’una matriu
float NormFrobenius(float M[N][N]) {
    float sum = 0.0;
    for (int i = 0; i < N; i++) {
        sum += Scalar(M[i], M[i]);
    }
    return sqrt(sum);
}

// Determinar si una matriu és Diagonal Dominant
int DiagonalDom(float M[N][N]) {
    for (int i = 0; i < N; i++) {
        float diag_val = fabs(M[i][i]);
        float row_sum = 0.0;
        for (int j = 0; j < N; j++) {
            if (i != j) row_sum += fabs(M[i][j]);
        }
        if (diag_val < row_sum) return 0;
    }
    return 1;
}

// Multiplicació d’una matriu per un vector
void Matriu_x_Vector(float M[N][N], float vect[N], float vectres[N]) {
    for (int i = 0; i < N; i++) {
        vectres[i] = Scalar(M[i], vect);
    }
}

int main() {
    // A. Inicialitzar les matrius i vectors
    InitData();
    
    // A.a Mostrar els elements 0 a 9 i 256 a 265 dels vectors V1, V2 i V3
    printf("V1 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V1, 0, 10);         // 0 a 9
    PrintVect(V1, 256, 10);       // 256 a 265
    printf("V2 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V2, 0, 10);         // 0 a 9
    PrintVect(V2, 256, 10);       // 256 a 265
    printf("V3 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V3, 0, 10);         // 0 a 9
    PrintVect(V3, 256, 10);       // 256 a 265

    // B. Mostrar els elements 0 a 9 de les files 0 i 100 de la matriu Mat
    printf("Mat fila 0 del 0 al 9:\n");
    PrintRow(Mat, 0, 0, 10);
    printf("Mat fila 100 del 0 al 9:\n");
    PrintRow(Mat, 100, 0, 10);

    // C. Mostrar els elements 0 a 9 de la fila 0 i del 90 al 99 de la fila 100 a la matriu MatDD
    printf("MatDD fila 0 del 0 al 9:\n");
    PrintRow(MatDD, 0, 0, 10);
    printf("MatDD fila 100 del 90 al 99:\n");
    PrintRow(MatDD, 100, 90, 10);

    // D. Calcular i mostrar les normes i si és diagonal dominant per a Mat i MatDD
    printf("Per a la matriu Mat:\n");
    printf("Infininorma = %f\n", Infininorm(Mat));
    printf("Norma 1 = %f\n", Onenorm(Mat));
    printf("Norma de Frobenius = %f\n", NormFrobenius(Mat));
    printf("És diagonal dominant? %s\n", DiagonalDom(Mat) ? "Sí" : "No");

    printf("Per a la matriu MatDD:\n");
    printf("Infininorma = %f\n", Infininorm(MatDD));
    printf("Norma 1 = %f\n", Onenorm(MatDD));
    printf("Norma de Frobenius = %f\n", NormFrobenius(MatDD));
    printf("És diagonal dominant? %s\n", DiagonalDom(MatDD) ? "Sí" : "No");

    return 0;
}
