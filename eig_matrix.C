#include <iostream>
#include"lapacke.h"

using namespace std;
 
int main()
{
    // note, to understand this part take a look in the MAN pages, at section of parameters.
  static int n=3;

    char    JOBVL = 'N';
    char    JOBVR = 'V';
    int     N = n;
    int     LDA=n;
    double WR[n];
    double WI[n];
    double VL[n][n];
    int LDVL=n;
    double VR[n][n];
    int LDVR=n;
    double  WORK[4*n];
    int LWORK=4*n;
    int INFO=0;
 

    //double AB[n][n];
    //double ABaux[n][n];


    double A[3][3]={{1,2,3},{4,5,6},{7,8,9}}; 
   

    cout << "solving..."<< endl << endl;
    LAPACK_dgeev(&JOBVL,&JOBVR,&N,A[0],&LDA,WR,WI,VL[0],&LDVL,VR[0],&LDVR,WORK,&LWORK,&INFO);
    if(INFO){
	// checks INFO, if INFO != 0 something goes wrong, for more information see the MAN page of dgetrs.
	cout << "an error occured : "<< INFO << endl << endl;
      }else{
        cout << "print the result : {";

	for (int i=0;i<N;i++)
	  {
	    cout << WR[i] << " ";
	  }
	cout << "}" << endl << endl;

        for(int i=0;i<N;i++){
	   cout << " {";
	   for (int j=0;j<N;j++){
	       cout << VR[i][j] << " ";
	   }
	cout << "}" << endl << endl;
	}
    }


    cout << "program terminated." << endl << endl;
    return 0;
}
