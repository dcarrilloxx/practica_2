#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 512  // Constant de dimensió

float Mat[N][N], MatDD[N][N];
float V1[N], V2[N], V3[N], V4_res[N];

// Inicialització de matrius i vectors amb valors pseudo-aleatoris
void InitData(float Mat[N][N], float MatDD[N][N], float V1[N], float V2[N], float V3[N]){
    int i,j;
    srand(334411);
    for( i = 0; i < N; i++ ){
        for( j = 0; j < N; j++ ){
            Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
            if ( (abs(i - j) <= 3) && (i != j))
            MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
            else if ( i == j )
            MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
            else MatDD[i][j] = 0.0;
        }
    }
    for( i = 0; i < N; i++ ){
        V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
        V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
        V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
    }
}

// Imprimir elements d'un vector
void PrintVect(float vect[N], int from, int numel){
    for (int i = from; i < from+numel; i++){
        if (i < (from+numel)-1)
            printf("%f",vect[i]);
        else
            printf("%f\n",vect[i]);
    }
}

// Imprimir elements d'una fila d'una matriu
void PrintRow(float mat[N][N], int row, int from, int numel){
    for (int i = from; i < from+numel; i++){
        if (i < (from+numel)-1)
            printf("%f",mat[row][i]);
        else
            printf("%f\n",mat[row][i]);
    }
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

// Determinar la magnitud
float Magnitude(float vect[N]) {
    return sqrt(Scalar(vect, vect));
}

// Determinar si dos vectors són ortogonals
int Ortogonal(float vect1[N], float vect2[N]) {
    return Scalar(vect1, vect2) == 0;
}

// Projecció d’un vector sobre un altre
void Projection(float vect1[N], float vect2[N], float vectres[N]){
    float alfa = Scalar(vect1,vect2)/Magnitude(vect2);
    MultEscalar(vect2, vectres, alfa);
}

// Infini-norma d’una matriu
float Infininorm(float M[N][N]) {
    float sumMax = 0;
    float sum = 0;
    for (int i = 0; i < N; i++) {
        sum = 0;
        for (int j = 0; j < N; j++)
            sum += fabsf(M[i][j]);
        if (sum > sumMax) {
            sumMax = sum;
        }
    }
    return sumMax;
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
        for (int j = 0; j < N; j++) {
            sum += M[i][j] * M[i][j];
        }
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
        if (diag_val < row_sum) return 0; // No és dominant
    }
    return 1; // És diagonalment dominant
}


//Multiplicació d’una matriu per un vector
void Matriu_x_Vector(float M[N][N], float vect[N], float vectres[N]) {
    for (int i = 0; i < N; i++) {
        float sum = 0.0;
        for (int j = 0; j < N; j++) {
            sum += M[i][j] * vect[j];
        }
        vectres[i] = sum;
    }
}



// Implementació del mètode de Jacobi
int Jacobi(float M[N][N], float vect[N], float vectres[N], unsigned iter) {
    int aplicable = 1;
    float X[N], newX[N];
    float suma, error;
    const float tolerancia = 1e-6;

    // Inicialitzar X i newX a zero
    for (int i = 0; i < N; i++) {
        X[i] = 0.0;
        newX[i] = 0.0;
    }

    // Comprovar si la matriu és diagonalment dominant
    if (DiagonalDom(M) == 1) {
        // Iteracions del mètode de Jacobi
        for (int pasos = 0; pasos < iter; pasos++) {
            error = 0.0; // Reinicialitzar error en cada iteració

            // Actualització de cada element de la solució
            for (int i = 0; i < N; i++) {
                suma = vect[i]; // Inicialitzar amb el terme independent
                for (int j = 0; j < N; j++) {
                    if (j != i)
                        suma -= M[i][j] * X[j]; // Restar altres termes
                }
                newX[i] = suma / M[i][i]; // Dividir pel coeficient diagonal

                // Calcular error d'aquesta iteració
                error += fabs(newX[i] - X[i]);
            }

            // Copiar els nous valors al vector X
            for (int i = 0; i < N; i++) {
                X[i] = newX[i];
            }

            // Verificar si l'error és menor que la tolerància
            if (error < tolerancia) {
                break; // Convergència assolida
            }
        }

        // Copiar el resultat a vectres
        for (int i = 0; i < N; i++) {
            vectres[i] = X[i];
        }
    } else {
        aplicable = 0; // La matriu no és diagonalment dominant
    }

    return aplicable;
}


// Funció principal
int main() {
    // A. Inicialitzar les matrius i vectors
    InitData(Mat, MatDD, V1, V2, V3);

    // A.a Mostrar elements dels vectors V1, V2 i V3
    printf("V1 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V1, 0, 10);
    PrintVect(V1, 256, 10);
    printf("\n");
    printf("V2 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V2, 0, 10);
    PrintVect(V2, 256, 10);
    printf("\n");
    printf("V3 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V3, 0, 10);
    PrintVect(V3, 256, 10);
    printf("\n");

    // B. Mostrar elements de files de la matriu Mat
    printf("Mat fila 0 del 0 al 9:\n");
    PrintRow(Mat, 0, 0, 10);
    printf("\n");

    printf("Mat fila 100 del 0 al 9:\n");
    PrintRow(Mat, 100, 0, 10);
    printf("\n");

    // C. Mostrar elements de la matriu MatDD
    printf("MatDD fila 0 del 0 al 9:\n");
    PrintRow(MatDD, 0, 0, 10);
    printf("\n");

    printf("MatDD fila 100 del 90 al 99:\n");
    PrintRow(MatDD, 100, 90, 10);
    printf("\n");

    // D. Calcular i mostrar les normes
    printf("Per a la matriu Mat:\n");
    printf("Infininorma = %f\n", Infininorm(Mat));
    printf("Norma 1 = %f\n", Onenorm(Mat));
    printf("Norma de Frobenius = %f\n", NormFrobenius(Mat));
    printf("Mat diagonal dominant: %s\n", DiagonalDom(Mat) ? "Sí" : "No");
    printf("\n");

    printf("Per a la matriu MatDD:\n");
    printf("Infininorma = %f\n", Infininorm(MatDD));
    printf("Norma 1 = %f\n", Onenorm(MatDD));
    printf("Norma de Frobenius = %f\n", NormFrobenius(MatDD));
    printf("MatDD diagonal dominant: %s\n", DiagonalDom(MatDD) ? "Sí" : "No");
    printf("\n");

// E. Calcular i visualitzar els productes escalars
printf("Producte escalar V1 · V2 = %f\n", Scalar(V1, V2));
printf("Producte escalar V1 · V3 = %f\n", Scalar(V1, V3));
printf("Producte escalar V2 · V3 = %f\n", Scalar(V2, V3));

// F. Calcular i visualitzar la magnitud de V1, V2 i V3
printf("Magnitud de V1 = %f\n", Magnitude(V1));
printf("Magnitud de V2 = %f\n", Magnitude(V2));
printf("Magnitud de V3 = %f\n", Magnitude(V3));

// G. Calcular i visualitzar l'ortogonalitat entre vectors
if (Ortogonal(V1, V2))
    printf("V1 i V2 son ortogonals\n");
else
    printf("V1 i V2 no son ortogonals\n");

if (Ortogonal(V1, V3))
    printf("V1 i V3 son ortogonals\n");
else
    printf("V1 i V3 no son ortogonals\n");

if (Ortogonal(V2, V3))
    printf("V2 i V3 son ortogonals\n");
else
    printf("V2 i V3 no son ortogonals\n");

// H. Multiplicació del vector V3 amb l'escalar 2.0
MultEscalar(V3, V4_res, 2.0);
printf("Els elements 0 al 9 i 256 al 265 del resultat de multiplicar V3x2.0 són:\n");
PrintVect(V4_res, 0, 10);
PrintVect(V4_res, 256, 10);

// I. Projecció de V2 sobre V3 i de V1 sobre V2
Projection(V2, V3, V4_res);
printf("Els elements 0 a 9 del resultat de la projecció de V2 sobre V3 són:\n");
PrintVect(V4_res, 0, 10);

Projection(V1, V2, V4_res);
printf("Els elements 0 a 9 del resultat de la projecció de V1 sobre V2 són:\n");
PrintVect(V4_res, 0, 10);

// J. Multiplicació de la matriu Mat amb el vector V2
Matriu_x_Vector(Mat, V2, V4_res);
printf("Els elements 0 a 9 del resultat de la multiplicació de Mat per V2 són:\n");
PrintVect(V4_res, 0, 10);

// K. Resolució del sistema d'equacions MatDD * X = V3 utilitzant Jacobi
if (Jacobi(MatDD, V3, V4_res, 1) == 1) {
    printf("Els elements 0 a 9 de la solució (1 iteració) del sistema d'equacions són:\n");
    PrintVect(V4_res, 0, 10);
    Jacobi(MatDD, V3, V4_res, 1000);
    printf("Els elements 0 a 9 de la solució (1000 iteracions) del sistema d'equacions són:\n");
    PrintVect(V4_res, 0, 10);
} else {
    printf("La matriu MatDD no és diagonal dominant, no es pot aplicar Jacobi\n");
}

// Intentar amb la matriu Mat
if (Jacobi(Mat, V3, V4_res, 1) == 0) {
    printf("La matriu Mat no és diagonal dominant, no es pot aplicar Jacobi\n");
} else {
    printf("Els elements 0 a 9 del resultat amb Jacobi i Mat són:\n");
    PrintVect(V4_res, 0, 10);
}

return 0;
}
