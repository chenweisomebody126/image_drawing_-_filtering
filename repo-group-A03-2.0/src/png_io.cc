/*******************************************************************************
* Name            : png_io.cc
* Project         : FlashPhoto
* Module          : io_manager
* Description     : Header file for FileReader class.
* Copyright       : 2016 CSCI3081W. All rights reserved.
* Creation Date   : 11/10/16
* Original Author : Natnael Seifu
*
******************************************************************************/

#include "include/png_io.h"
#include <iostream>
#include <cstring>
#include "include/file_io.h"
#include "include/pixel_buffer.h"
#include "include/png.h"

namespace image_tools {
  PngIO::PngIO() {}
  PngIO::~PngIO() {}

  PixelBuffer* PngIO::readFile(const std::string& file_name) {
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    float alpha = 0.0;
    int width = 0;
    int height = 0;
    ColorData* temp_pixel = nullptr;
    PixelBuffer* new_canvas = nullptr;

    png_image image;
    png_bytep read_buffer;

    memset(&image, 0, sizeof(image));
    image.version = PNG_IMAGE_VERSION;

    int read_begin_status = png_image_begin_read_from_file(&image,
                                                    file_name.c_str());
    if (read_begin_status != 0) {
      // Initialize new Canvas with white back ground
      width = image.width;
      height = image.height;
      ColorData init_color(0, 1, 0, 0);
      new_canvas = new PixelBuffer(width, height, init_color);

      image.format = PNG_FORMAT_RGBA;

      // read buffer allocation
      read_buffer = (png_bytep)malloc(PNG_IMAGE_SIZE(image));

      if (read_buffer != nullptr) {
        if (png_image_finish_read(&image, NULL, read_buffer, 0, NULL) != 0) {
          // for index calculation convenience
          int index;
          for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
              // Each pixel is 4 bytes long
              // since we are iterting by pixels
              // we account for that by multiplying by 4
              index = ((i*width) + j) * 4;

              // Color Data Read from png image
              // divide by 255.0 to convert to float
              // ranging from 0 to 1
              red = read_buffer[index + 0] / 255.0;
              green = read_buffer[index + 1] / 255.0;
              blue = read_buffer[index + 2] / 255.0;
              alpha = read_buffer[index + 3] / 255.0;

              // Temporary pixel(ColorData) to populate canvas
              temp_pixel = new ColorData(red, green, blue, alpha);
              new_canvas->set_pixel(j, (height-(i+1)), *temp_pixel);
            }
          }
        }
      }
    }

    return new_canvas;
  }

  void PngIO::saveToFile(const std::string& file_name,
                         const PixelBuffer* curr_canvas) {
    png_structp write_ptr;
    png_infop info_ptr;
    // png_colorp clr_prt;

    FILE* dest_file;
    png_bytep row;
    int row_size;

    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    int width = 0;
    int height = 0;
    ColorData color;

    write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                        NULL,
                                        NULL,
                                        NULL);
    if (write_ptr == NULL) {
      fprintf(stderr, "Could not allocate write struct\n");
      return;
    }

    info_ptr = png_create_info_struct(write_ptr);
    if (info_ptr == NULL) {
      fprintf(stderr, "Could not allocate info struct\n");
      return;
    }

    dest_file = fopen(file_name.c_str(), "w");
    if (dest_file == NULL) {
      fprintf(stderr, "Error Opening file: %s\n", file_name);
      return;
    }

    width = curr_canvas->width();
    height = curr_canvas->height();

    png_init_io(write_ptr, dest_file);

    png_set_IHDR(write_ptr, info_ptr, width, height,
         8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
         PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(write_ptr, info_ptr);

    row_size = width * 4;
    row = (png_bytep) malloc (row_size * sizeof(png_byte));
    for (int j = (height-1); j >= 0; j--) {
      for (int i = 0; i < width ; i++) {
        color = curr_canvas->get_pixel(i, j);
        red = static_cast<unsigned char>(color.red()*255);
        green = static_cast<unsigned char>(color.green()*255);
        blue = static_cast<unsigned char>(color.blue()*255);
        alpha = static_cast<unsigned char>(color.alpha()*255);

        row[i*4] = red;
        row[i*4+1] = green;
        row[i*4+2] = blue;
        row[i*4+3] = alpha;

        // fprintf(stderr, "[%d,%d,%d,%d] ", row[j],
                                         //  row[j+1],
                                         //  row[j+2],
                                         //  row[j+3]);
      }
      png_write_row(write_ptr, row);
      // fprintf(stderr, "\n");
      // exit(0);
    }

    png_write_end(write_ptr, info_ptr);
    png_free(write_ptr, NULL);
    png_destroy_write_struct(&write_ptr, &info_ptr);
    free(row);
    fclose(dest_file);


    std::cout << "Saving To File: " << file_name << std::endl;
  }
}  // namespace image_tools
