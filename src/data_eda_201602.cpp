//============================================================================
// Name        : data_eda.cpp
// Author      : Sean Chang
// Version     :
// Copyright   : 
// Description : Tiba motion tracking
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
#include "MadgwickAHRS.h"

    int main()
    {
      
			//array data
      const int height = 15; //number of time
      const int width = 10;  //9 sensors + 1 time 
      int i=0, j=0;

      double** my2DArray = create2DArray(height, width);
      
      
      //random variables
          	std::default_random_engine generator;
          	std::normal_distribution<double> distribution(0.0, 0.2);
            float tmp;
          	//declare variables
          	//create simulation data
          	for(j = 1; j<10; j++){
          		 for(i=0; i< height; i++){
            			my2DArray[i][j] = sin( 2.0*PI*i/height) + distribution(generator);
            		}
               cout <<endl;
          	}
       printmat(my2DArray, height, width);
       printf("\n");
        /*
         //printmat(my2DArray, height, width);
       float * val;
       val = MadgwickAHRSupdate(dat[0][0],dat[0][1],dat[0][2],
                                dat[0][3],dat[0][4],dat[0][5],
                                dat[0][6],dat[0][7],dat[0][8]);
                         
       printf("\n the quaternion is: %f %f %f %f \n \n ", val[0], val[1], val[2], val[3]);
        */

      //quaternion
      

      double** newdat = create2DArray(height, 5);
      quaternion_transformation(my2DArray, newdat, height);
      printmat(newdat, height, 5);

       //printmat(dat, 10, 10);
      
      /*
      //truncated array
      int height_trun = 5;
      int width_trun = 10;
      double** new2DArray = modify2DArray(my2DArray, height, width, height_trun, width_trun);
      printf("Array modified");
      printmat(new2DArray, height_trun, width_trun);

      //clean up another matrix

        printf("Cleaning up memory...\n");
        for (int h = 0; h < height_trun; h++)
        {
          delete [] new2DArray[h];
        }
        delete [] new2DArray;
        new2DArray = 0;
        printf("Ready.\n");

      */

        delete2DArray(my2DArray, height, width);
	      delete2DArray(newdat, height, width);
 

     
       



      return 0;
    }


