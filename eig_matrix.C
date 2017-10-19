#include <iostream>
#include"lapacke.h"

using namespace std;


int* f(int i,int N){

  int nb[4];


  if(i>0&&i<N-1){
    nb[0]=i+1;
    nb[1]=i-1;
    nb[2]=i+N;
    nb[3]=0;//This values doesn't matter
  }
  else if(i>int((N-1)*N)&&i<int(N*N-1)){
    nb[0]=i+1;
    nb[1]=i+1;
    nb[2]=i-N;
    nb[3]=0;
  }
  else if(i%N==0){
    nb[0]=i+1;
    nb[1]=i-N;
    nb[2]=i+N;
    nb[3]=0;
  }
  else if((i+1)%N==0){
    nb[0]=i-1;
    nb[1]=i-N;
    nb[2]=i+N;
    nb[3]=0;
  }
  else if(i==0){
    nb[0]=i+1;
    nb[1]=i+N;
    nb[2]=0;
    nb[3]=0;
  }
  else if(i==N-1){
    nb[0]=i-1;
    nb[1]=i+N;
    nb[2]=0;
    nb[3]=0;
  }
  else if(i==int((N-1)*N)){
    nb[0]=i+1;
    nb[1]=i-N;
    nb[2]=0;
    nb[3]=0;
  }
  else if(i==int(N*N-1)){
    nb[0]=i-1;
    nb[1]=i-N;
    nb[2]=0;
    nb[3]=0;
  }
  else{
    nb[0]=i-1;
    nb[1]=i+1;
    nb[2]=i-N;
    nb[3]=i+N;
  }

  return nb;

}



int length(int i, int N){

  int l;

  if((i>0&&i<N-1) || (i>int((N-1)*N)&&i<int(N*N-1)) || i%N==0  ||(i+1)%N==0)
    l=3;
  else if(i==0||i==N-1||i==int((N-1)*N)||i==int(N*N-1))
    l=2;
  else 
    l=4;

  return l;

}
 
int main()
{
    // note, to understand this part take a look in the MAN pages, at section of parameters.
  static int n=3;

    char    JOBVL = 'N';
    char    JOBVR = 'V';
    int     N = n*n;
    int     LDA=n*n;
    double WR[n*n];
    double WI[n*n];
    double VL[n*n][n*n];
    int LDVL=n*n;
    double VR[n*n][n*n];
    int LDVR=n*n;
    double  WORK[4*n*n];
    int LWORK=4*n*n;
    int INFO=0;
 
    double A[n*n][n*n];

    for(int i=0;i<int(n*n);i++)
      for(int j=0;j<int(n*n);j++)
	A[i][j]=0;

    double t=0.1;
    for(int i=0;i<n*n;i++){

      for(int j=0;j<length(i,N);j++)
	A[i][f(i,N)[j]]=-t;

      A[i][i]=1;

    }
    

    for(int i=0;i<n*n;i++){
      for(int j=0;j<n*n;j++){
	cout << A[i][j] << "     ";
      }
      cout << endl;
    }

    
    //double A[3][3]={{1,4,7},{4,5,8},{7,8,9}}; 
   
    
    cout << "solving..."<< endl << endl;
    //Tenho de transpor a matriz para a enviar para o FORTRAN. Se a matriz for simetrica a transposta e igual a normal. Os vetores proprios estao em linhas e nao em colunas. Na descricao da funcao diz colunas mas isso e se virmos em FORTRAN
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
