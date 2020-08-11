/*
 * calibration_matrix.hpp
 *
 *  Created on: Aug 1, 2020
 *      Author: jeslava
 */

#ifndef CALIBRATION_MATRIX_HPP_
#define CALIBRATION_MATRIX_HPP_

/*
float calib_elem[9] = { 846.16923116, 0, 401.32045045, 0, 843.5034920988, 293.0509457892, 0, 0, 1 };
cv::Mat A_calib = cv::Mat(3, 3, CV_32F, calib_elem);

float distortion_elem[14] = { -50.189981, 928.85485, 0.0033421127, -0.0027987138, 1163.3371223, -50.2374148, 930.5739643, 1098.623809, 0, 0, 0, 0, 0, 0};
cv::Mat D_calib = cv::Mat(1, 14, CV_32F, distortion_elem);
*/


/*Calibration Kitty 3*/

float calib_elem[9] = { 721.5377, 0, 609.5593, 0, 721.5377, 172.854, 0, 0, 1 };
cv::Mat A_calib = cv::Mat(3, 3, CV_32F, calib_elem);

float distortion_elem[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
cv::Mat D_calib = cv::Mat(1, 14, CV_32F, distortion_elem);


#endif /* CALIBRATION_MATRIX_HPP_ */
