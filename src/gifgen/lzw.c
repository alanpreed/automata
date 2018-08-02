#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw.h"
#include "code_table.h"

static void add_output_code(uint16_t code, size_t bitlength, uint8_t *output,
                             uint16_t *output_position, uint8_t *bit_position);

static void print_bits(uint8_t byte, uint8_t bitlength);

uint64_t lzw_compress_data(uint8_t *input, uint8_t **output, uint64_t length, uint8_t num_values)
{
  uint8_t *long_output = calloc(length, sizeof(uint8_t));
  code_table_t code_table;
  code_t input_buffer;
  uint16_t output_position = 0;
  uint16_t next_output_code = 0;
  uint8_t output_bit_pos = 0;

  code_table_setup(&code_table, num_values);
  code_alloc(&input_buffer, MAX_CODE_LEN);
  input_buffer.code_len = 0;

  // Start with clear code:
  add_output_code(code_table.cc_index, code_table.code_bitlength, long_output, &output_position, &output_bit_pos);

  for(int i = 0; i < length; i++)
  {
    // Read input byte into buffer, and save previous buffer state so that it can be output if needed
    input_buffer.code[input_buffer.code_len] = input[i];
    input_buffer.code_len++;
    bool code_match = false;

    // Check each entry in code table to see if it matches input buffer
    for(int j = 0; j < code_table.table_len; j++)
    {
      code_t *test_code = &(code_table.data[j]);

      // Only check for a match if the code is the same length as the input buffer
      if(test_code->code_len == input_buffer.code_len)
      {
        code_match = true;
        for(size_t k = 0; k < input_buffer.code_len; k++)
        {
          if(test_code->code[k] != input_buffer.code[k])
          {
            code_match = false;
            break;
          }
        }
      }
      // If we've found a matching code, no need to keep searching the code table
      if(code_match)
      {
        next_output_code = j;
        break;
      }
    }
    // If no match found, add to code table and output code for buffer excluding this character
    if(!code_match)
    {
      add_output_code(next_output_code, code_table.code_bitlength, long_output, &output_position, &output_bit_pos);
      
      if(code_table.table_len < MAX_NUM_CODES)
      {
        code_table_add(&code_table, &input_buffer);
      }
      else
      {
        // Output a clear code and reset the code table if we are out of space
        add_output_code(code_table.cc_index, code_table.code_bitlength, long_output, &output_position, &output_bit_pos);
        code_table_free(&code_table);
        code_table_setup(&code_table, num_values);
      }
      
      input_buffer.code_len = 0;
      // Last character isn't included in output code, so we need to go over it again
      i--;
    }
    // If match was found, return its code if there are no more bytes. Otherwise continue reading
    if(i == length - 1)
    {
      add_output_code(next_output_code, code_table.code_bitlength, long_output, &output_position, &output_bit_pos);
    }
  }
  // Add end-of-info code when we're out of bytes
  add_output_code(code_table.eoi_index, code_table.code_bitlength, long_output, &output_position, &output_bit_pos);

  // Include any half-filled bytes in the output
  if(output_bit_pos != 0)
  {
    output_position++;
  }

  *output = calloc(output_position, sizeof(uint8_t));
  memcpy(*output, long_output, output_position);

  code_table_free(&code_table);
  free(long_output);
  return output_position;
}

static void add_output_code(uint16_t code, size_t bitlength, uint8_t *output, 
                            uint16_t *output_position, uint8_t *bit_position)
{
  while(bitlength != 0)
  {
    // Fit what we can in the current output byte
    output[*output_position] |= code << *bit_position;

    if(*bit_position + bitlength < 8)
    {
      // If everything fitted then there's nothing more to do
      (*bit_position) += bitlength;
      bitlength = 0;
    }
    else
    {
      uint8_t bits_fitted = 8 - (*bit_position);

      // If there's stuff left over, move to the next byte and update positions
      (*output_position)++;
      
      *bit_position = 0;
      code >>= bits_fitted;
      bitlength -= bits_fitted;
    }
  }
}

static void print_bits(uint8_t byte, uint8_t bitlength)
{
  for (int i = bitlength - 1; i >= 0; i--)
  {
      uint8_t bit = (byte >> i) & 1;
      printf("%u", bit);
  }
}
