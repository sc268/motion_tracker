//============================================================================
// Name        : data_eda.cpp
// Author      : Sean Chang
// Version     :
// Copyright   : 
// Description : Tiba motion tracking
//============================================================================
// data format: (time, ax, ay, az, gx, gy, gz, mx, my, mz)
// data array: N by 10 matrix 

#include <iostream>
#include <vector>
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
      //printmat(my2DArray, height, width);
      
      //random variables
          	std::default_random_engine generator;
          	std::normal_distribution<double> distribution(0.0, 0.2);
          
          	//declare variables
          	//create simulation data
            double tmp[10]; 
           for(int t=0; t< height; t++){
            	 for(j = 1; j<10; j++){
                  tmp[j] = sin( 2.0*PI*t/height) + distribution(generator);
            			my2DArray[t][j] = tmp[j];
            		}
                //time
                my2DArray[t][0] = t; 
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

    //online selection example
      //double arr[10];
      //for(i=0; i<10; i++){arr[i]= my2DArray[0][i];};
      double threshold = 0.9;
      // keep if L2 norm of accelration > threshold
      //double L2_acc = pow(pow(arr[1], 2) + pow(arr[1], 2) + pow(arr[1], 2), 0.5);
     

      printf("demo: selecting data when accelration > threshold\n");
      double** array_selection = create2DArray(height, width);
      int idx = 0;
      for(int t=0; t< height; t++){
          for(j = 1; j<10; j++){
              tmp[j] = sin( 2.0*PI*t/height) + distribution(generator);
              }
              tmp[0] = t; //time 

          if (keep_obs(tmp[1], tmp[2], tmp[3], threshold)){
              for(j=0; j<10; j++){array_selection[idx][j] = tmp[j];}
              idx += 1;         
              }
           cout <<endl;
          }
       printmat(array_selection, height, width);
       printf("\n");
        



      double** quat = create2DArray(height, 5);
      quaternion_transformation(my2DArray, quat, height);
      printmat(quat, height, 5);

      double** newdat = create2DArray(height, 4);
      euler_transformation(quat, newdat, height);
      printmat(newdat, height, 4);
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
        delete2DArray(array_selection, height, width);
	      delete2DArray(quat, height, width);
        delete2DArray(newdat, height, width);
 

     
       



      return 0;
    }


