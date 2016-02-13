 // Returns a pointer to a newly created 2d array the array2D has size [height x width]
#include "data_processing.h"
#include "MadgwickAHRS.h"
#include <cstdio>

    double** create2DArray(unsigned height, unsigned width)
    {
      double** array2D = 0;
      printf("Creating a 2D array2D\n");

      array2D = new double*[height];

      for (int h = 0; h < height; h++)
      {
            array2D[h] = new double[width];
            for (int w = 0; w < width; w++)
            {     // fill in some initial values
                  // (filling in zeros would be more logic, but this is just for the example)
                  array2D[h][w] = w + width * h;
            }
      }
      printf("Array sized [%i,%i] created.\n\n", height, width);
      return array2D;
    }

    void printmat(double** mat, unsigned height, unsigned width){
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                  printf("%f,", mat[h][w]);
            }
            printf("\n");
      }
    }

    double** modify2DArray(double** array2D, unsigned height, unsigned width,unsigned height_trun, unsigned width_trun)
    {
      double** newarray2D = 0;
      newarray2D = new double*[height_trun];
      //init
      for (int h = 0; h < height; h++)
      {
          newarray2D[h] = new double[width_trun];
      }
      //modify
     for (int h = 0; h < height_trun; h++)
      {
            for (int w = 0; w < width_trun; w++)
            {
               newarray2D[h][w] = array2D[h][w];
            }
      }

      return newarray2D;
    }


    void delete2DArray(double** my2DArray, unsigned height, unsigned width){
          printf("\n");
          printf("Cleaning up memory...\n");
          for (int h = 0; h < height; h++)
          {
            delete [] my2DArray[h];
          }
          delete [] my2DArray;
          my2DArray = 0;
          printf("Done.\n");
    }

    float * val;

    void quaternion_transformation(double** raw, double** newarray, unsigned height){
      //input: T x 10 raw data (time, 9 axis) 
      //output: T x 5 transformed data (time, 4 axis)
      
      for(int i=0; i<height; i++){
           newarray[i][0] = raw[i][0]; //keep time 
           val = MadgwickAHRSupdate(raw[i][1],raw[i][2],raw[i][3],
                                    raw[i][4],raw[i][5],raw[i][6],
                                    raw[i][7],raw[i][8],raw[i][9]);
           newarray[i][1] = val[0]; 
           newarray[i][2] = val[1]; 
           newarray[i][3] = val[2];
           newarray[i][4] = val[3];
       }
       return;
    }


/*
   int main(){
      double ** testmat = create2DArray(3,5);
      printmat(testmat,3,5);

      return 1;}
      */