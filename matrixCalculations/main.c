#include <stdio.h>
#include <math.h>

/*
  Takes 2 inputs:
  
    matrixToTranspose - this holds the value of the matrix we want to transpose 
    transposeMatrix - this holds the matrix in which we want this transpose to be stored 
*/
void tranposeMatrix(double (*matrixToTranspose)[2], double (*transposeMatrix)[4]) {
  for(int index = 0; index < 4; index++) {
    transposeMatrix[0][index] = matrixToTranspose[index][0];
    transposeMatrix[1][index] = matrixToTranspose[index][1];
  }
}

/*
  Takes 2 inputs:

    matrixToInverse - holds the the value of the matrix we want to inverse 
    inverseMatrix - holds the matrix in which we want this inverse to be stored
*/
void calculateInverseMatrix(double (*matrixToInverse)[2], double (*inverseMatrix)[2]) {
  double determinantPartA = matrixToInverse[0][0] * matrixToInverse[1][1];
  double determinantPartB = matrixToInverse[0][1] * matrixToInverse[1][0];

  double determinant = 1 / ((determinantPartA) - (determinantPartB));

  double temp = 0;

  for(int row = 0; row < 2; row++) {
    for(int column = 0; column < 2; column++) {
      if(row == 0 && column == 0) {
        temp = matrixToInverse[0][0];
        inverseMatrix[0][0] = matrixToInverse[1][1];
      } else if(row == 1 && column == 1) {
        inverseMatrix[1][1] = temp;
      } else {
        inverseMatrix[row][column] = matrixToInverse[row][column] * -1;
      }
    }
  }

  for(int row = 0; row < 2; row++) {
    for(int column = 0; column < 2; column++) {
      inverseMatrix[row][column] = inverseMatrix[row][column] * determinant;
    }
  }
}

/*
  Entry point.
*/
int main(void) {
  
  /*
    Beacon locations that we are looking at
    
    DOES THIS NEED TO BE INSIDE THE WHILE LOOP? SINCE THIS WILL CONSTANTLY CHANGE BASED ON WHERE WE ARE IN THE ROOM?
  */
  int beaconLocations[4][2] = {
    {0, 0},
    {10, 0},
    {15, 10},
    {0, 12}
  };

  /*
    Holds the value of the measured distances from the 4 beacons
    
    THIS WOULD ALSO BE UPDATING ON BEACON LOCATIONS.
  */
  double distanceMeasure[4][1] = {
    2.92,
    8.14,
    15.46,
    9.89
  };

  /* 
    Arbitrary estimation of the location.  
  */
  double locationEstimate[2][1] = {
    20, 
    20
  };
  
 
  /* 
    'correctionFactor' matrix initialised to some arbitrary value as we want to keep going until this correction factor is very small. Therefore, we start with something big initially.
  */
  double correctionFactor[2][1] = {
    1000, 
    1000
  };

  /*
    Keep the while loop going until both x and y correction factors are greater than 0.01 units away from the actual location. At this point there's no reason in carrying on with this loop as we won't get any closer.
  */
  while((!(correctionFactor[0][0] < 0.01)) && (!(correctionFactor[1][0] < 0.01))) {
    /*
      Following are declarations for all matrices that will be used in the program. Currently they're all hardcoded, but can be improved by using dynamic arrays.

      alpha[4][1] - 4x1 matrix that holds the value of alpha, the factors that provide the distance of the current location estimate to the different beacons.

      a[4][2] - 4x2 matrix that holds the value of A, which is a part of the equation Ax = b.

      aTranspose[2][4] - 2x4 matrix that holds the value of the 'a' matrix transposed.

      b[4][1] - 4x1 matrix that holds the value of b in the equation Ax = b.

      c[2][2] - 2x2 matrix that holds the value of aTranspose matrix (dot product with) a matrix

      d[2][1] - 2x1 matrix that holds the value of aTranspose matrix (dot product with) b matrix 

      inverseMatrix[2][2] - 2x2 matrix that holds the value of the inverse of c matrix 

      e[2][1] - 2x1 matrix that holds the temporary value of the correctionFactor before it can be assigned to the correctionFactor matrix 
    */
    double alpha[4][1] = {0};
    double a[4][2] = {0};
    double aTranspose[2][4] = {0};
    double b[4][1] = {0};
    double c[2][2] = {0};
    double d[2][1] = {0};
    double inverseMatrix[2][2] = {0};
    double e[2][1] = {0};
    
    /*
      Calculate 'alpha' using following equation:
        
        alpha(i) = sqrt[(x(i) - x)^2 + (y(i) - y)^2]

        where i = beacon 1, 2, 3 ....
              x(i) = x coordinate of beacon 
              y(i) = y coordinate of beacon 
              x = x coordinate of current location estimate 
              y = y coordinate of current location estimate 
    */
    for(int row = 0; row < 4; row++) {
      double temp = pow((beaconLocations[row][0] - locationEstimate[0][0]),2) + pow((beaconLocations[row][1] - locationEstimate[1][0]), 2);

      alpha[row][0] = sqrt(temp);
    }

    /*
      Calculate 'alpha' using following equation:
        
        A(i) = [-(x(i) - x)/alpha(i) , -(y(i) - y)/alpha(i)]

        where i = beacon 1, 2, 3 ....
              x(i) = x coordiante of beacon 
              y(i) = y coordinate of beacon 
              x = x coordinate of current location estimate 
              y = y coordinate of current location estimate 
              alpha(i) = alpha value of the current beacon
    */ 
    for(int row = 0; row < 4; row++) {
      double columnOne = (-1*(beaconLocations[row][0] - locationEstimate[0][0]))/alpha[row][0];
      double columnTwo = (-1*(beaconLocations[row][1] - locationEstimate[1][0]))/alpha[row][0];

      a[row][0] = columnOne;
      a[row][1] = columnTwo;
    }

    /*
      Calculate transpose of the 'a' matrix
    */
    tranposeMatrix(a, aTranspose);

    /* 
      Calculate b using following equation:

        b(i) = d(i) - alpha(i)

        where i = beacon 1, 2, 3 ....
              d(i) = measured distance from current beacon
              alpha(i) = alpha value of the current beacon
    */
    for(int row = 0; row < 4; row++) {
      b[row][0] = distanceMeasure[row][0] - alpha[row][0];
    }

    /*
      'aTranspose' matrix (dot product) 'a' matrix and store it in 'c' matrix 
    */
    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < 2; j++) {
        for(int k = 0; k < 4; k++) {
          c[i][j] += aTranspose[i][k] * a[k][j];
        }
      }
    }

    /*
      Calculate inverse of 'c' matrix and store it in 'inverseMatrix' matrix
    */
    calculateInverseMatrix(c, inverseMatrix);

    /* 
      'aTranspose' matrix (dot product) 'b' matrix and store it in 'd' matrix
    */
    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < 1; j++) {
        for(int k = 0; k < 4; k++) {
          d[i][j] += aTranspose[i][k] * b[k][j];
        }
      }
    }

    /*
      'inverseMatrix' matrix (dot product) 'd' matrix and store it in 'e' matrix
    */
    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < 1; j++) {
        for(int k = 0; k < 2; k++) {
          e[i][j] += inverseMatrix[i][k] * d[k][j];
        }
      }
    }

    /*
      Assign values from temporary matrix 'e' into the 'correctionFactor' matrix
    */
    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < 1; j++) {
        correctionFactor[i][j] = e[i][j];
      }
    }

    /* 
      Add the 'correctionFactor' matrix coordinates to our current location estimate
    */
    locationEstimate[0][0] += correctionFactor[0][0];
    locationEstimate[1][0] += correctionFactor[1][0];

    /* 
      Change the 'correctionFactor' matrix coordinates to be positive so they can be evaluated by our while loop
    */
    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < 1; j++) {
        if(correctionFactor[i][j] < 0) {
          correctionFactor[i][j] *= -1;
        }
      }
    }

    /* 
      Print out the correctionFactor coordinates or the locationEstimate coordinates
    */
    printf("%f %f\n", locationEstimate[0][0], locationEstimate[1][0]);
  }
}