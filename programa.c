                                                                                                                                                                                                                                                                                                        programa.c *#include <stdio.h>#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 512  // Constant de dimensió

float Mat[N][N], MatDD[N][N];
float V1[N], V2[N], V3[N],V4_res[N];

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
	if(i<(from+numel)-1
        	printf("%f ", vect[i]);
	else
		printf("%f\n",vect[i]
    }
}

// Imprimir elements d'una fila d'una matriu
void PrintRow(float mat[N][N], int row, int from, int numel) {
    for (int i = from; i < from + numel; i++) {
	 if(i<(from+numel)-1
                printf("%f ", mat[row][i]);
        else
                printf("%f\n",mat[row][i]

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
    return result
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

void Matriu_x_Vector(float M[N][N], float vect[N], float vectres[N]){
    float sum = 0;
    for(int i = 0; i < N; i++){
        sum = 0;
        for(int j = 0; j < N; j++){
            sum += M[i][j] * vect[j];
        }
        vectres[i] = sum;
    }
}

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


//Jacobi
int Jacobi(float M[N][N], float vect[N], float vectres[N], unsigned iter) {
    int aplicable = 1;
    float X[N], newX[N];
    float suma, error, tolerancia = 1e-6;

    // Inicializar X i newX a zero
    for(int i = 0; i < N; i++) {
        X[i] = 0;
        newX[i] = 0;
    }

    // Comprovar si la matriu es diagonal dominant
    if(DiagonalDom(M) == 1) {
        for(int pasos = 0; pasos < iter; pasos++) {
            error = 0.0; // Inicializar error en cada iteració
            for(int i = 0; i < N; i++) {
                suma = vect[i];
                for(int j = 0; j < N; j++) {
                    if(j != i)
                        suma -= M[i][j] * X[j];
                }
                newX[i] = suma / M[i][i];
                error += fabs(newX[i] - X[i]); // Calcular error d'aquesta iteració
            }

            // Actualizar X amb els nous valor de newX
            for (int i = 0; i < N; i++) {
                X[i] = newX[i];
            }

            // Verificar l'error es menor que la tolerancia
            if (error < tolerancia) {
                break; 
            }
        }

        // Copiar el resultadt a vectres
        for(int i = 0; i < N; i++) {
            vectres[i] = X[i];
        }
    } else {
        aplicable = 0; // La matriu no es diagonal dominante
    }

    return aplicable;
}



int main() {
    // A. Inicialitzar les matrius i vectors
    InitData();
    
    // A.a Mostrar els elements 0 a 9 i 256 a 265 dels vectors V1, V2 i V3
    printf("V1 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V1, 0, 10);         // 0 a 9
    PrintVect(V1, 256, 10);       // 256 a 265
    printf("\n");
    printf("V2 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V2, 0, 10);         // 0 a 9
    PrintVect(V2, 256, 10);       // 256 a 265
    printf("\n");
    printf("V3 del 0 al 9 i del 256 al 265:\n");
    PrintVect(V3, 0, 10);         // 0 a 9
    PrintVect(V3, 256, 10);       // 256 a 265
    printf("\n");
    // B. Mostrar els elements 0 a 9 de les files 0 i 100 de la matriu Mat
    printf("Mat fila 0 del 0 al 9:\n");
    PrintRow(Mat, 0, 0, 10);
    printf("\n");
    printf("Mat fila 100 del 0 al 9:\n");
    PrintRow(Mat, 100, 0, 10);
    printf("\n");
	
    // C. Mostrar els elements 0 a 9 de la fila 0 i del 90 al 99 de la fila 100 a la matriu MatDD
    printf("MatDD fila 0 del 0 al 9:\n");
    PrintRow(MatDD, 0, 0, 10);
    printf("\n");
    printf("MatDD fila 100 del 90 al 99:\n");
    PrintRow(MatDD, 100, 90, 10);
    printf("\n");

    // D. Calcular i mostrar les normes i si és diagonal dominant per a Mat i MatDD
    printf("Per a la matriu Mat:\n");
    printf("Infininorma de Mat = %f\n", Infininorm(Mat));
    printf("Norma 1 = %f\n", Onenorm(Mat));
    printf("Norma de Frobenius = %f\n", NormFrobenius(Mat));
    if DiagonalDom(Mat)==1
	printf("La matriu Mat es diagonal dominant");
    else
	printf("La matriu Mat no es diagonal dominant");
    printf("\n\n");
    printf("Per a la matriu MatDD:\n");
    printf("Infininorma de MatDD = %f\n", Infininorm(MatDD));
    printf("Norma u de Mat = %f\n", Onenorm(MatDD));
    printf("Norma de Frobenius de Mat = %f\n", NormFrobenius(MatDD));
    if DiagonalDom(MatDD)==1
	printf("La matriu MatDD es diagonal dominant");
    else
	printf("La matriu MatDD no es diagonal dominant");
    print("\n\n")
    
    //E. Calcular i visualitzar els productes escalars
    printf("Producte escalar V1 · V2 = %f\n", Scalar(V1, V2));
    printf("Producte escalar V1 · V3 = %f\n", Scalar(V1, V3));
    	printf("Producte escalar V2 · V3 = %f\n", Scalar(V2, V3));

    //F. Calcular i visualitzar la magnitud de V1, V2 i V3
    printf("Magnitud de V1 = %f\n", Magnitude(V1));
    printf("Magnitud de V2 = %f\n", Magnitude(V2));
    printf("Magnitud de V3 = %f\n", Magnitude(V3));

    // G. Calcular i visualitzar totes les combinacions possibles si V1 és o no ortogonal amb V2 i V3 i si V2 i V3  
    if(Ortogonal(V1, V2) == 1)
        printf("V1 i V2 son ortogonals");
    else
        printf("V1 i V2 no son ortogonals");
    printf("\n");
    if(Ortogonal(V1, V3) == 1)
        printf("V1 i V3 son ortogonals");
    else
        printf("V1 i V3 no son ortogonals");
    printf("\n");
    if(Ortogonal(V2, V3) == 1)
        printf("V2 i V3 son ortogonals");
    else
        printf("V2 i V3 no son ortogonals");
    printf("\n\n");

    //H.Calcular la multiplicació del vector V3 amb l’escalar 2.0 i visualitzar els elements 0 al 9 i 256 al 265 del vector resultant.
    MultEscalar(V3, V4_res, 2.0);
    printf("Els elements 0 al 9 i 256 al 265 del resultat de multiplicar V3x2.0 son:\n");
    PrintVect(V4_res, 0, 10);
    PrintVect(V4_res, 256, 10);
    printf("\n\n");

    //I. Calcular la projecció del V2 sobre V3 i visualitzar els 10 primers elements del vector resultant. Repetiu per la projecció de V1 sobre V2. 
    Projection(V2, V3, V4_res);
    printf("Els elements 0 a 9 del resultat de la projeccio de V2 sobre V3 son:\n");
    PrintVect(V4_res, 0, 10);
    Projection(V1,V2,V4_res);
    printf("Els elements 0 a 9 del resultat de la projeccio de V1 sobre V2 son:\n");
    PrintVect(V4_res, 0, 10);
    printf("\n\n");
    
    //J. Calcular la multiplicació de la matriu Mat amb el vector v2 i visualitzar els 10 primers elements del vector resultant
    Matriu_x_Vector(Mat , V2, V4_res);
    printf("Els elements 0 a 9 del resultat de la multiplicacio de Mat per V2 son:\n");
    PrintVect(V4_res, 0, 10);
    printf("\n\n");


    // K. Calcular la solució del sistema d’equacions MatDD*X = V3
    if (Jacobi(MatDD, V3, V4_res, 1)==1){
        Jacobi(MatDD, V3, V4_res, 1);
        printf("Els elements 0 a 9 de la solucio (1 iter) del sistema d'equacions son:\n");
        PrintVect(Vres, 0, 10);
        Jacobi(MatDD, V3, V4_res, 1000);
        printf("Els elements 0 a 9 de la solucio (1000 iter) del sistema d'equacions son:\n");
        PrintVect(Vres, 0, 10);
    }
    else
        printf("La matriu MatDD no es diagonal dominant, no es pot aplicar Jacobi");
    if (Jacobi(Mat, V3, V4_res, 1)==0)
        printf("La matriu Mat no es diagonal dominant, no es pot aplicar Jacobi");
    else{
        Jacobi(Mat, V3, V4_res, 1);
        PrintVect(V4_res, 0, 10);
    }
}
