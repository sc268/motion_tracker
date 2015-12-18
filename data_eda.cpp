//============================================================================
// Name        : data_eda.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
//#include <deque>
//#include <list>
#include <random>
#include <math.h>
using namespace std;

#define PI 3.14159265


//return when index = odd number
#include <cstdio>
#include "data_processing.h"


    int main()
    {
      printf("Creating a 2D array2D\n");
      printf("\n");
      //array data
      int height = 10;
      int width = 20;
      double** my2DArray = create2DArray(height, width);
      printf("Array sized [%i,%i] created.\n\n", height, width);
      printmat(my2DArray, height, width);

      //truncated array
      int height_trun = 5;
      int width_trun = 10;
      double** new2DArray = modify2DArray(my2DArray, height, width, height_trun, width_trun);
      printf("Array modified");
      printmat(new2DArray, height_trun, width_trun);


          // important: clean up memory
          printf("\n");
          printf("Cleaning up memory...\n");
          for (int h = 0; h < height; h++)
          {
            delete [] my2DArray[h];
          }
          delete [] my2DArray;
          my2DArray = 0;
          printf("Ready.\n");

          //clean up another matrix

          printf("Cleaning up memory...\n");
          for (int h = 0; h < height_trun; h++)
          {
            delete [] new2DArray[h];
          }
          delete [] new2DArray;
          new2DArray = 0;
          printf("Ready.\n");

          //random variables
          	std::default_random_engine generator;
          	std::normal_distribution<double> distribution(0.0, 0.2);

          	//declare variables
          	const int dim_time = 10;
          	double dat[10][dim_time];
          	int i=0, j=0;

          	//create fake data
          	for(i = 0; i<10; i++){
          		for(j=0; j<dim_time; j++){
          			dat[i][j] = distribution(generator);
          			cout << sin( 2.0*PI*j/dim_time) + dat[i][j];
          		}
               cout <<endl;
          	}
          	return 0;

      return 0;
    }


