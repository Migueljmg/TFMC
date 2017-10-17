#include <iostream>
#include"lapacke.h"

using namespace std;
 
int main()
{
    // note, to understand this part take a look in the MAN pages, at section of parameters.
    char    JOBZ = 'N';
    char    UPLO= 'U';
    int     N = 3;
    int     KD = 2; //nr of diagonals above the main one
    int     LDAB = 3;
    double  W[3];
    double  Z[3][3] ;
    int     LDZ=3;
    double  WORK[7];
    int INFO=0;
 
    double  AB[3][3] =
    {
      {0, 0, 8},
      {0, 7, 6},
      {3, 4, 2}
    };//The 0's correspond in this case to numbers that don't have to be stored. AB is equivalent to the following matrix:

    /*
      3 7 8
      7 4 6
      8 6 2
    */

    //symmetric with respect to the diagonal
 
// end of declarations
 
    cout << "compute the LU factorization..." << endl << endl;

    // checks INFO, if INFO != 0 something goes wrong, for more information see the MAN page of dgetrf.
    if(INFO)
    {
        cout << "an error occured : "<< INFO << endl << endl;
    }else{
        cout << "solving the system..."<< endl << endl;
        // void LAPACK_dgetrs( char* trans, lapack_int* n, lapack_int* nrhs, const double* a, lapack_int* lda, const lapack_int* ipiv,double* b, lapack_int* ldb, lapack_int *info );
        LAPACK_dsbev(&JOBZ,&UPLO,&N,&KD,AB[0],&LDAB,W,Z[0],&LDZ,WORK,&INFO);
        if(INFO)
        {
            // checks INFO, if INFO != 0 something goes wrong, for more information see the MAN page of dgetrs.
            cout << "an error occured : "<< INFO << endl << endl;
        }else{
            cout << "print the result : {";
            int i;
            for (i=0;i<N;i++)
            {
                cout << W[i] << " ";
            }
            cout << "}" << endl << endl;
        }
    }
 
    cout << "program terminated." << endl << endl;
    return 0;
}
