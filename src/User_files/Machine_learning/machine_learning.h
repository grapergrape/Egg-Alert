#pragma once

/* Includes ---------------------------------------------------------------- */
#include <Arduino_OV767X.h> //Click here to get the library: http://librarymanager/All#Arduino_OV767X

#include <stdint.h>
#include <stdlib.h>






/* Function definitions ------------------------------------------------------- */
// bool ei_camera_init(void);
// void ei_camera_deinit(void);
// bool ei_camera_capture(uint32_t img_width, uint32_t img_height, uint8_t *out_buf) ;
// int calculate_resize_dimensions(uint32_t out_width, uint32_t out_height, uint32_t *resize_col_sz, uint32_t *resize_row_sz, bool *do_resize);
// void resizeImage(int srcWidth, int srcHeight, uint8_t *srcImage, int dstWidth, int dstHeight, uint8_t *dstImage, int iBpp);
void cropImage(int srcWidth, int srcHeight, uint8_t *srcImage, int startX, int startY, int dstWidth, int dstHeight, uint8_t *dstImage, int iBpp);
// int ei_camera_cutout_get_data(size_t offset, size_t length, float *out_ptr) ;
void predict(float* result_pred);