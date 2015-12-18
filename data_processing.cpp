 // Returns a pointer to a newly created 2d array the array2D has size [height x width]
#include "data_processing.h"
#include <cstdio>

    double** create2DArray(unsigned height, unsigned width)
    {
      double** array2D = 0;
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
      return array2D;
    }

    void printmat(double** mat, unsigned height, unsigned width){
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                  printf("%i,", mat[h][w]);
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
