#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "gifgen/lzw.h"

#define LZW_INPUT_SIZE 100
#define NUM_DATA_VALUES 4
#define LZW_OUTPUT_SIZE 22

uint8_t input_data[100] = { 1,1,1,1,1,2,2,2,2,2,
                            1,1,1,1,1,2,2,2,2,2,
                            1,1,1,1,1,2,2,2,2,2,
                            1,1,1,0,0,0,0,2,2,2,
                            1,1,1,0,0,0,0,2,2,2,
                            2,2,2,0,0,0,0,1,1,1,
                            2,2,2,0,0,0,0,1,1,1,
                            2,2,2,2,2,1,1,1,1,1,
                            2,2,2,2,2,1,1,1,1,1,
                            2,2,2,2,2,1,1,1,1,1,
                          };

uint8_t output_expected[LZW_OUTPUT_SIZE] = { 0x8C, 0x2D, 0x99, 0x87, 0x2A,
                                0x1C, 0xDC, 0x33, 0xA0, 0x02,
                                0x75, 0xEC, 0x95, 0xFA, 0xA8, 
                                0xDE, 0x60, 0x8C, 0x04, 0x91, 
                                0x4C, 0x01
                              };

uint8_t *output_received;

int setup(void **state)
{
  return 0;
}

int teardown(void **state)
{
  free(output_received);
  return 0;
}

void test_lzw(void **state)
{
  uint16_t output_length = lzw_compress_data(input_data, &output_received, LZW_INPUT_SIZE, NUM_DATA_VALUES);

  assert_true(output_length == LZW_OUTPUT_SIZE);

  printf("Expected:  ");
  for(size_t i = 0; i < output_length; i++)
  {
    printf("%x ", output_expected[i]);
  }
  printf("\r\n");

  printf("Generated: ");
  for(size_t i = 0; i < output_length; i++)
  {
    printf("%x ", output_received[i]);
  }
  printf("\r\n");

  for(size_t i = 0; i < output_length; i++)
  {
    assert_int_equal(output_expected[i], output_received[i]);
  }
}

int main(void)
{
  const struct CMUnitTest tests[] =
  {
    cmocka_unit_test(test_lzw),
  };

  int count_failed_tests = cmocka_run_group_tests(tests, setup, teardown);

  return count_failed_tests;
}