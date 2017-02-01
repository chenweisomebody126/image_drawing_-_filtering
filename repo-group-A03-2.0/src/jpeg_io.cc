/*******************************************************************************
* Name            : jpeg_io.h
* Project         : FlashPhoto
* Module          : io_manager
* Description     : Header file for FileReader class.
* Copyright       : 2016 CSCI3081W. All rights reserved.
* Creation Date   : 11/10/16
* Original Author : Natnael Seifu
*
******************************************************************************/

#include "include/jpeg_io.h"
#include <iostream>
#include "include/jpeglib.h"
#include "include/file_io.h"
#include "include/pixel_buffer.h"

namespace image_tools {
  JpegIO::JpegIO() {}
  JpegIO::~JpegIO() {}

  PixelBuffer* JpegIO::readFile(const std::string& file_name) {
    int row_pos = 0;
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    int image_width = 0;
    int image_height = 0;
    PixelBuffer* new_canvas = nullptr;
    ColorData* temp_pixel = nullptr;

    // Working space for jpeg library
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE* source_file;
    // JSAMPARRAY is a pointer to JSAMPROW
    // JSAMPROW is a pointer to JSAMPLE
    // JSAMPLE represents a single Color Component (R,G,B)
    // JSAMPLE is an unsigned char(1byte) color range 0-255
    JSAMPARRAY buffer;
    int row_stride;

    // Opening Image file
    if ((source_file = fopen(file_name.c_str(), "rb")) == NULL) {
      fprintf(stderr, "Error Open File: %s\n", file_name.c_str());
      return nullptr;
    }

    // Initializing JPEG work space
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, source_file);
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);

    // Init new canvas
    image_width = cinfo.output_width;
    image_height = cinfo.output_height;
    ColorData init_color(1, 1, 1, 1);
    new_canvas = new PixelBuffer(image_width, image_height, init_color);

    // Number of Color Components(JSAMPLEs) in one row of image
    row_stride = cinfo.output_width * cinfo.output_components;

    // Allocates JSAMPARRAY bacause jpeg_read_scanlines only takes JSAMPARRAY
    // as a JSAMPLE buffer
    buffer = (JSAMPARRAY) malloc(cinfo.output_height * sizeof(JSAMPROW));
    buffer[0] = (JSAMPROW) malloc(row_stride * sizeof(JSAMPLE));

    while (cinfo.output_scanline < image_height) {
      // Just for readability
      row_pos = cinfo.output_scanline;
      // Holds Color component of a row each iteration
      // buffer[0] = (JSAMPROW) malloc(row_stride * sizeof(JSAMPLE));
      // Reads one line and stores it in buffer[0]
      (void) jpeg_read_scanlines(&cinfo, buffer, 1);

      // Storing Row to new_canvas
      for (int i = 0; i < image_width; i++) {
        red = buffer[0][i*3] / 255.0;
        green = buffer[0][i*3+1] / 255.0;
        blue = buffer[0][i*3+2] / 255.0;
        temp_pixel = new ColorData(red, green, blue);
        new_canvas->set_pixel(i, (image_height-(row_pos+1)), *temp_pixel);
        // fprintf(stderr, "[%d,%d,%d]", buffer[0][i],
        //                                  buffer[0][i+1],
        //                                  buffer[0][i+2]);
      }
      // fprintf(stderr, "\n");
    }

    // Freeing our buffer
    free(buffer[0]);
    free(buffer);

    // clean up
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(source_file);

    return new_canvas;
  }

  void JpegIO::saveToFile(const std::string& file_name,
                          const PixelBuffer* curr_canvas) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    FILE* dest_file;
    JSAMPROW row[1];
    int row_size;
    int width;
    int height;
    // int quality;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    if ((dest_file = fopen(file_name.c_str(), "wb")) == NULL) {
      fprintf(stderr, "Saving Unsuccessful\n");
      fprintf(stderr, "Error Opening/Creating file: %s\n", file_name.c_str());
      return;
    }

    width = curr_canvas->width();
    height = curr_canvas->height();
    row_size = width * 3;
    row[0] = (JSAMPROW) malloc(row_size * sizeof(unsigned char));

    jpeg_stdio_dest(&cinfo, dest_file);
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    // jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    for (int i = (height-1); i >= 0; i--) {
      for (int j = (width-1); j >= 0; j--) {
        ColorData color = curr_canvas->get_pixel(j, i);
        red = static_cast<unsigned char>(color.red()*255);
        green = static_cast<unsigned char>(color.green()*255);
        blue = static_cast<unsigned char>(color.blue()*255);
        // fprintf(stderr, "[%d,%d,%d] ", red, green, blue);
        row[0][j*3] = red;
        row[0][j*3+1] = green;
        row[0][j*3+2] = blue;
      }
      (void) jpeg_write_scanlines(&cinfo, row, 1);
      // fprintf(stderr, "\n");
      // exit(0);
    }

    jpeg_finish_compress(&cinfo);
    fclose(dest_file);
    jpeg_destroy_compress(&cinfo);

    free(row[0]);
    std::cout << "Saving To File: " << file_name << std::endl;
  }
}  // namespace image_tools
