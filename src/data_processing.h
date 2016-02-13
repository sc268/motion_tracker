/*
 * data_processing.h
 *
 *  Created on: Dec 17, 2015
 *      Author: pingpong3mike
 */

#ifndef DATA_PROCESSING_H_
#define DATA_PROCESSING_H_

	double** create2DArray(unsigned height, unsigned width);

    void printmat(double** mat, unsigned height, unsigned width);

    double** modify2DArray(double** array2D, unsigned height, unsigned width,unsigned height_trun, unsigned width_trun);
    void delete2DArray(double** my2DArray, unsigned height, unsigned width);
    void quaternion_transformation(double** raw, double** newarray, unsigned height);
#endif /* DATA_PROCESSING_H_ */
