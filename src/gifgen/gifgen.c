#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lzw.h"
#include "gifgen.h"
#include "colour_table.h"
#include <math.h>
// http://www.matthewflickinger.com/lab/whatsinagif/bits_and_bytes.asp

static bool started = false;
static FILE *gif_file = NULL;
static uint8_t num_colours;

void gifgen_start(char *filename, uint16_t width, uint16_t height, colour_t *palette, size_t palette_size)
{
  gif_file = fopen(filename, "wb+");

  if(gif_file != NULL)
  {
    char version_header[7] = "GIF89a";
    fwrite(version_header, sizeof(uint8_t), sizeof(version_header)/sizeof(version_header[0]) - 1, gif_file);

    colour_table_t table;
    uint8_t *global_colour_table;
    colour_table_init(palette, palette_size, &table);
    num_colours = table.size;
    size_t output_size = colour_table_convert(&table, &global_colour_table);
    uint8_t logical_screen_desc[7] = { (uint8_t)(width & 0xFF), (uint8_t)(width >> 8),
                                    (uint8_t)(height & 0xFF), (uint8_t)(height >> 8),
                                    0b10010000 + (table.N & 0b00000111), 0x00, 0x00};

    fwrite(logical_screen_desc, sizeof(uint8_t), sizeof(logical_screen_desc)/sizeof(logical_screen_desc[0]), gif_file);
    fwrite(global_colour_table, sizeof(uint8_t), output_size, gif_file);

    // Extension block to enable unlimited looping of the gif
    uint8_t application_extension[19] = { 0x21, 0xFF, 0x0B, 
                                          'N', 'E', 'T', 'S', 'C', 'A', 'P', 'E', '2', '.', '0',
                                          0x03, 0x01, 0x00, 0x00, 0x00 };

    fwrite(application_extension,sizeof(uint8_t), sizeof(application_extension) / sizeof(application_extension[0]), gif_file);

    colour_table_free(&table);
    free(global_colour_table);
    started = true;
  }
  else
  {
    printf("gifgen error: couldn't open file\r\n");
  }
}

void gifgen_add_frame(uint8_t *data, uint16_t width, uint16_t height, uint16_t delay)
{
  if(started)
  {
    uint8_t graphic_control_extension[8] = {0x21, 0xF9, 0x04, 0x04, 
                                            (uint8_t)(delay & 0xFF), (uint8_t)(delay >> 8),
                                            0x00, 0x00};

    fwrite(graphic_control_extension, sizeof(uint8_t), 
            sizeof(graphic_control_extension) / sizeof(graphic_control_extension[0]), gif_file);

    uint8_t image_descriptor[10] = { 0x2C,
                                    0x00, 0x00,
                                    0x00, 0x00,
                                    (uint8_t)(width & 0xFF), (uint8_t)(width >> 8),
                                    (uint8_t)(height & 0xFF), (uint8_t)(height >> 8),
                                    0x00};

    // Image descriptor
    fwrite(image_descriptor, sizeof(uint8_t),  sizeof(image_descriptor) / sizeof(image_descriptor[0]), gif_file);

    uint8_t *output;
    uint16_t output_length = lzw_compress_data(data, &output, width * height, num_colours);

    // LZW minimum code size
    uint8_t lzw_min_code_size = log((double)num_colours) / log(2.0);
    fputc(lzw_min_code_size, gif_file);

    // Write out LZW data in subblocks of up to 255 bytes
    size_t output_position = 0;

    while(output_length > 255)
    {
      // Data subblock size
      fputc(255, gif_file);

      // LZW data
      fwrite(&(output[output_position]), sizeof(uint8_t), 255, gif_file);

      output_position += 255;
      output_length -= 255;
    }
    
    // Write any remaining data and ensure that 0x00 terminates the data section
    fputc((uint8_t)output_length, gif_file);
    if(output_length > 0)
    {
      fwrite(&(output[output_position]), sizeof(uint8_t), output_length, gif_file);
      fputc(0x00, gif_file);
    }

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
