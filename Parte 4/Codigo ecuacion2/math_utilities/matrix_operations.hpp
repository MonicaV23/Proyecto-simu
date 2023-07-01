#include <cmath>

#include "vector.hpp"
#include "matrix.hpp"

void product_scalar_by_matrix(float scalar, Matrix* M, int n, int m, Matrix* R){
    for(int r = 0; r < n; r++)
        for(int c = 0; c < m; c++)
            R->set(scalar*M->get(r,c),r,c);
}

void product_matrix_by_vector(Matrix* M, Vector* V, int n, int m, Vector* R){
    for(int r = 0; r < n; r++){
        float acc = 0;
        for(int c = 0; c < n; c++)
            acc += M->get(r,c)*V->get(c);
        R->set(acc,r);
        
    }
    R->show();
}

/**
 * A continuación vamos a recibir las matrices A, B y R, de la cual
 * el resultado la vamos a guardar en la matriz R
 */
void  product_matrix_by_matrix(Matrix* A, Matrix* B, Matrix* R){
    /**
     * n y m son las dimensiones de la A
     * p y q son las dimesiones de la B 
    */
    int n = A->get_nrows(), m = A->get_ncols(), p = B->get_nrows(), q = B->get_ncols();
    if(m == p){ //debe cumplirse para realizar la multiplicación (siempre se va a cumplir. )
        R->set_size(n,q);//seteamos el tamaño de la matriz R
        R->init();//similar al ensamblaje inicializamos la matriz en cero. 
        

        /**
         * Este triple for no supone una preocupación.
         * Podemos garantizar que nunca los valores que se toman en este for no serán grandes, es más
         * hasta los concemos, no pasarán de 2 o 3.
        */
        for(int r = 0; r < n; r++)
            for(int c = 0; c < q; c++)
                for(int i = 0; i < m; i++)//este for se encarga de realizar la acumulación. 
                    /**
                     * Donde agarramos de la matriz A el dato que está en la fila en la que estoy en la primera columna, 
                     * multiplicado por la columna donde voy en la primera fila y así sucesivamente. 
                    */
                    R->add(A->get(r,i)*B->get(i,c),r,c);
    }else{
        cout << "Incompatibilidad de dimensiones al multiplicar matrices.\n\nAbortando...\n";
        exit(EXIT_FAILURE);
    }
}

float determinant(Matrix* M);

float determinant_auxiliar(Matrix* M){
    int n = M->get_ncols();
    float acc = 0;

    for(int c = 0; c < n; c++){
        Matrix clon(n,n);
        M->clone(&clon);
        clon.remove_row(0);
        clon.remove_column(c);
        acc += pow(-1,c)*M->get(0,c)*determinant(&clon);
    }

    return acc;
}

float determinant(Matrix* M){
    float ans;
    switch(M->get_ncols()){
        case 1: ans = M->get(0,0); break;
        case 2: ans = M->get(0,0)*M->get(1,1) - M->get(0,1)*M->get(1,0); break;
        case 3: ans = M->get(0,0)*M->get(1,1)*M->get(2,2)-M->get(0,0)*M->get(1,2)*M->get(2,1)-M->get(0,1)*M->get(1,0)*M->get(2,2)+M->get(0,1)*M->get(1,2)*M->get(2,0)+M->get(0,2)*M->get(1,0)*M->get(2,1)-M->get(0,2)*M->get(1,1)*M->get(2,0); break;
        default: ans = determinant_auxiliar(M);
    }
    return ans;
}

float get_minor(Matrix* M, int n, int r, int c){
    Matrix clon(n,n);
    M->clone(&clon);

    //M.show(); clon.show();

    clon.remove_row(r);
    clon.remove_column(c);

    //clon.show();

    return determinant(&clon);
}

void conjugate_matrix(Matrix* M, int n, Matrix* C){
    for(int r = 0; r < n; r++)
        for(int c = 0; c < n; c++)
            C->set(pow(-1,r+c)*get_minor(M,n,r,c),r,c);
}

void transpose(Matrix* M, int n, int m, Matrix* T){
    for(int r = 0; r < n; r++)
        for(int c = 0; c < m; c++)
            T->set(M->get(r,c),c,r);
}

void calculate_inverse(Matrix* A, int n, Matrix* X){
    Matrix L(n,n), Y(n,n);
    float acum;

    for(int i= 0; i < n; i++){
        for(int j= 0; j < n; j++){
            if(i == j){
                acum = 0;
                for(int k = 0; k < j; k++){
                    acum += pow(L.get(j,k),2);
                }
                L.set(sqrt(A->get(j,j) - acum),j,j);
            }
            else{
                if(i > j){
                    acum = 0;
                    for(int k = 0; k < j; k++){
                        acum += L.get(i,k)*L.get(j,k);
                    }
                    L.set((1/L.get(j,j))*(A->get(i,j) - acum),i,j);
                } 
                else{
                    L.set(0,i,j);
                }
            }
        }
    }

    for(int i= 0; i < n; i++){
        for(int j= 0; j < n; j++){
            if(i == j){
                Y.set(1/L.get(i,i),i,i);
            }
            else{
                if(i > j){
                    acum = 0;
                    for(int k = j; k < i; k++){
                        acum += L.get(i,k)*Y.get(k,j);
                    }
                    Y.set(-(1/L.get(i,i))*acum,i,j);
                }
                else{
                    Y.set(0,i,j);
                }
            }
        }
    }

    for(int i= n-1; i >= 0; i--){
        for(int j= 0; j < n; j++){
            acum = 0;
            for(int k = i+1; k < n; k++){
                acum += L.get(k,i)*X->get(k,j);
            }
            X->set((1/L.get(i,i))*( Y.get(i,j) - acum ),i,j);
        }
    }
}