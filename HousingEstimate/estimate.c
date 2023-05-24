#include <stdio.h>
#include <stdlib.h>


void clear2DArray(double** mat, int r) {
	for (int i = 0; i < r; ++i) {
		free(mat[i]);
		mat[i] = NULL;
	}

	free(mat);
	mat = NULL;
} 

//------------------------------------------------------------
double** inverseFunc(double** matrix, int x){
	double** sol = malloc(x * sizeof(double*));
  double** inversed = malloc(x * sizeof(double*));
	for(int i = 0; i < x; i++) {
		sol[i] = malloc(x * sizeof(double*));
	}
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < x; j++) {
			if(i == j) {
				sol[i][j] = 1;
			} else {
				sol[i][j] = 0;
			}
		} 
	}
  //^^^^^^AUGMENTED MATRIX
  
	for(int i = 0; i < x; i++) {
		inversed[i] = malloc(x * sizeof(double));
	}
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < x; j++) {
			double y = matrix[i][j];
			inversed[i][j] = y;
		}
	}
	for(int t = 0; t < x; t++) {
		double someM = inversed[t][t];
		for (int u = 0; u < x; u++) {
			double looseInversed = inversed[t][u] / someM;
			inversed[t][u] = looseInversed;
			double looseSol = sol[t][u] / someM;
			sol[t][u] = looseSol;
		}
		for (int a = t + 1; a < x; a++) {
			someM = inversed[a][t];
			for (int b = 0; b < x; b++) {
				double looseInversed = inversed[a][b] - (someM * inversed[t][b]);
				double looseSol = sol[a][b] - (someM * sol[t][b]);
				inversed[a][b] = looseInversed;
				sol[a][b] = looseSol;
			}
		}
	}

	for (int a = x - 1; a >= 0; a--) {
		for (int b = a - 1; b >= 0; b--) {
			double someM = inversed[b][a];
			for (int c = 0; c < x; c++) {
				double looseInverted = inversed[b][c] - (someM * inversed[a][c]);
				double looseSol = sol[b][c] - (someM * sol[a][c]);
				inversed[b][c] = looseInverted;
				sol[b][c] = looseSol;
			}
		}
	}
  clear2DArray(inversed, x);
	return sol;
}

//-----------------------------------------------------------


double** multiplyFunc(double** first, double** second, int r1, int c1, int r2, int c2){
  if(c1 != r2){
    return NULL;
  }else{
    double** multiply = (double**)malloc(r1* sizeof(double*));
    int i;

    for(i = 0; i< r1;i++){
      multiply[i] = (double*)malloc(c2* sizeof(double));
    }
    int j;
    for(i = 0; i<r1;i++){
      for ( j = 0; j <c2 ; j++) {
        multiply[i][j] = 0;
      }
    }
    int k;
    for(i = 0; i< r1;i++){
      for(j = 0;j<c2;j++){
        for(k = 0; k< c1;k++){
          multiply[i][j] += first[i][k] * second[k][j];
        }
      }
    }	
    	
        return multiply;
  }
}

//------------------------------------------------------------


double** transposeFunc(double** arr2d, int r, int c){
	double** transposed = malloc(c * sizeof(double*));

	for(int k = 0; k < c; k++) {
		transposed[k] = malloc(r * sizeof(double));
	}

	for(int i = 0; i < c; i++) {
		for(int j = 0; j < r; j++) {
			double tmp = arr2d[j][i];
			transposed[i][j] = tmp;
		}
	}
	return transposed;
}


//------------------------------------------------------------

int main(int argc, char** argv){
  if (argc < 3)   exit(EXIT_FAILURE);

  char* name = argv[1];
  FILE* file = fopen(name,"r");

  if(file ==  NULL){
        exit(0);
    }
    int r;
    int c;

  fscanf(file, "%*[^\n]\n");
  fscanf(file, "%d \n", &c);
  fscanf(file, "%d \n", &r);
  c++;
    
  double** arr = (double**)malloc(r* sizeof(double*));

  int i,j;
    
  for(i = 0; i<r;i++){
    arr[i] = (double*)malloc(c*sizeof(double));
  }
    
  for(i = 0; i<r; i++){
    for(j = 0; j<c; j++){
      fscanf(file,"%lf ", &arr[i][j]);
    }
        fscanf(file,"\n");
  }
  fclose(file);
  //-------------------------------------------------------------------
  //next txt file
  
    name = argv[2];
    FILE* datatext = fopen(name,"r");

    if(datatext ==  NULL){
        exit(0);
    }
    int r2;
    int c2;
    
    fscanf(datatext, "%*[^\n]\n");
    fscanf(datatext, "%d \n", &c2);
    fscanf(datatext, "%d \n", &r2);

    double** dataArr = (double**)malloc(r2* sizeof(double*));

    for(i = 0; i<r2;i++){
        dataArr[i] = (double*)malloc((c-1)*sizeof(double));
    }

    for(i = 0; i<r2; i++){
        for(j = 0; j<(c-1); j++){
            fscanf(datatext,"%lf ", &dataArr[i][j]);
        }
        fscanf(datatext,"\n");
    }
    fclose(datatext);
    
  //--------------------------------------------------------  
    double** xArr = (double**)malloc(r* sizeof(double*));
    for(i = 0; i<r;i++){
        xArr[i] = (double*)malloc(c*sizeof(double));
    }
    for(i = 0; i<r;i++){
        xArr[i][0] = 1;
        for(j = 1; j<c;j++){
            xArr[i][j] = arr[i][j-1];
        }
    }
  
    double** yArr = (double**)malloc(r* sizeof(double*));
    for(i = 0; i<r;i++){
        yArr[i] = (double*)malloc(sizeof(double));
    }
    for(i = 0; i<r;i++){
        yArr[i][0] = arr[i][c-1];
    }
  
    double** wArr = (double**)malloc((c-1)* sizeof(double*));
    for(i = 0; i<(c-1);i++){
        wArr[i] = (double*)malloc(sizeof(double));
    }
  //-----------------------------------------------------
    clear2DArray(arr, r);

  
    double** transposedArr = transposeFunc(xArr,r,c);
    double** multipliedArr = multiplyFunc(transposedArr,xArr,c,r,r,c);
    double** inversedArr = inverseFunc(multipliedArr,c);
    double** CalculatedArr = multiplyFunc(inversedArr,transposedArr,c,c,c,r);
    double** weightOfAttributes = multiplyFunc(CalculatedArr,yArr,c,r,r,1);

    int p;
    double count = 0;
    for(i = 0; i<r2;i++){
        for(j=-1;j<(c-1);j++){
            if(j <0){
                count += weightOfAttributes[0][0];
            }
            else{
                count += weightOfAttributes[j+1][0]*dataArr[i][j];
            }
        }
        count+=.5;
        p = count;
        printf("%d\n",p);
        count = 0;
    }
    clear2DArray(xArr,r);
    clear2DArray(yArr,r);
    clear2DArray(wArr,c-1);
    clear2DArray(weightOfAttributes,c);
    clear2DArray(transposedArr, c);
    clear2DArray(multipliedArr,c);
    clear2DArray(inversedArr, c);
    clear2DArray(CalculatedArr,c);
    clear2DArray(dataArr, r2);
    
    return 0;
}
