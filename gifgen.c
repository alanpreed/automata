#include "gifgen.h"
#include <stdio.h>
#include <stdbool.h>
// http://www.matthewflickinger.com/lab/whatsinagif/bits_and_bytes.asp

static bool started = false;
FILE *gif_file = NULL;
uint8_t bin = 0b11111111;

static void lzw_compress_image(grid_t *frame, uint8_t num_colours);

void gifgen_start(char *filename, uint16_t width, uint16_t height)
{
  gif_file = fopen(filename, "wb");

  if(gif_file != NULL)
  {
    char version_header[7] = "GIF89a";
    char logical_screen_desc[8] = { (uint8_t)(width & 0xFF), (uint8_t)(width >> 8),
                                    (uint8_t)(height & 0xFF), (uint8_t)(height >> 8),
                                    0b10010000, 0x00, 0x00};
    char global_colour_table[6] = {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF};

    fwrite(version_header, sizeof(uint8_t), 6, gif_file);
    fwrite(logical_screen_desc, sizeof(uint8_t), 8, gif_file);
    fwrite(global_colour_table, sizeof(uint8_t), 6, gif_file);
    started = true;
  }
  else
  {
    printf("gifgen error: couldn't open file\r\n");
  }
}

void gifgen_add_frame(grid_t *frame)
{
  if(started)
  {
    uint8_t image_descriptor[10] = { 0x2C,
                                    0x00, 0x00,
                                    0x00, 0x00,
                                    (uint8_t)(frame->width & 0xFF), (uint8_t)(frame->width >> 8),
                                    (uint8_t)(frame->height & 0xFF), (uint8_t)(frame->height >> 8),
                                    0x00};
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

