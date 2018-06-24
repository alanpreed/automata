#include "gifgen.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lzw.h"
// http://www.matthewflickinger.com/lab/whatsinagif/bits_and_bytes.asp

static bool started = false;
FILE *gif_file = NULL;

static void lzw_compress_image(grid_t *frame, uint8_t num_colours);

void gifgen_start(char *filename, uint16_t width, uint16_t height)
{
  gif_file = fopen(filename, "wb+");

  if(gif_file != NULL)
  {
    char version_header[7] = "GIF89a";
    char logical_screen_desc[7] = { (uint8_t)(width & 0xFF), (uint8_t)(width >> 8),
                                    (uint8_t)(height & 0xFF), (uint8_t)(height >> 8),
                                    0b10010001, 0x00, 0x00};
    char global_colour_table[12] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00};

    fwrite(version_header, sizeof(uint8_t), 6, gif_file);
    fwrite(logical_screen_desc, sizeof(uint8_t), 7, gif_file);
    fwrite(global_colour_table, sizeof(uint8_t), 12, gif_file);
    started = true;
  }
  else
  {
    printf("gifgen error: couldn't open file\r\n");
  }
}

void gifgen_add_frame(uint8_t *data, uint16_t width, uint16_t height) //grid_t *frame)
{
  if(started)
  {
    uint8_t image_descriptor[10] = { 0x2C,
                                    0x00, 0x00,
                                    0x00, 0x00,
                                    (uint8_t)(width & 0xFF), (uint8_t)(width >> 8),
                                    (uint8_t)(height & 0xFF), (uint8_t)(height >> 8),
                                    0x00};

    uint8_t *output = calloc(100, sizeof(uint8_t));
    uint16_t output_length = lzw_compress_data(data, output, width * height, 4);

    printf("Final output code stream: ");
    for(size_t i = 0; i < output_length; i++)
    {
      printf("%x, ", output[i]);
    }
    printf("\r\n");

    // Image descriptor
    fwrite(image_descriptor, sizeof(uint8_t), 10, gif_file);

    // LZW minimum code size
    fputc(0x02, gif_file);

    // Data block size
    fputc((uint8_t)output_length, gif_file);

    // LZW data
    fwrite(output, sizeof(uint8_t), output_length, gif_file);

    // Block terminator
    fputc(0x00, gif_file);

    free(output);
  }
  else
  {
    printf("gifgen error: can't add frame before file is started\r\n");
  }
}

void gifgen_finish(void)
{
  fputc(0x3B, gif_file);
  fclose(gif_file);
  started = false;
}

