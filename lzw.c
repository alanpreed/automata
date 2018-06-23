#include "lzw.h"
#include "code_table.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t lzw_compress_data(uint8_t *input, uint8_t *output, uint16_t length, uint8_t num_values)
{
  code_table_t code_table;
  code_t input_buffer;

  size_t output_len = 100;

  //uint8_t *output_codes = calloc(output_len, sizeof(uint8_t));
  uint8_t output_position = 0;
  uint8_t next_output_code = 0;

  code_table_setup(&code_table, num_values);

  // Start with clear code:
  output[0] = code_table.cc_index;
  output_position++;

  for(int i = 0; i < length; i++)
  {
    // Read input byte into buffer, and save previous buffer state so that it can be output if needed
    input_buffer.code[input_buffer.code_len] = input[i];
    input_buffer.code_len++;
    bool code_match = false;

    // Check each entry in code table to see if it matches input buffer
    for(int j = 0; j < code_table.table_len; j++)
    {
      code_t test_code = code_table.data[j];

      // Only check for a match if the code is the same length as the input buffer
      if(test_code.code_len == input_buffer.code_len)
      {
        code_match = true;
        for(size_t k = 0; k < input_buffer.code_len; k++)
        {
          if(test_code.code[k] != input_buffer.code[k])
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
      code_table_add(&code_table, input_buffer);
      input_buffer = (code_t){0};
      output[output_position] = next_output_code;
      output_position++;
      // Last character isn't included in output code, so we need to go over it again
      i--;
    }
    // If match was found, return its code if there are no more bytes. Otherwise continue reading
    if(i == length - 1)
    {
      output[output_position] = next_output_code;
      output_position++;
    }
  }
  // Add end-of-info code when we're out of bytes
  output[output_position] = code_table.eoi_index;
  output_position++;

  return output_position;
}
