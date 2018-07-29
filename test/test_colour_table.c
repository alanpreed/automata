#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "gifgen/colour_table.h"

#define PALETTE_SIZE 5
#define EXPECTED_OUTPUT_SIZE 24

colour_table_t table;

int setup(void **state)
{
  return colour_table_init((colour_t[PALETTE_SIZE]) {
                      (colour_t){0,0,0},
                      (colour_t){1,1,1},
                      (colour_t){2,2,2},
                      (colour_t){3,4,5},
                      (colour_t){6,7,8},}, PALETTE_SIZE, &table);
}

int teardown(void **state)
{
  colour_table_free(&table);
  return 0;
}

void test_colour_table(void **state)
{
  uint8_t *received_output;
  size_t output_size = colour_table_convert(&table, &received_output);

  assert_true(output_size == EXPECTED_OUTPUT_SIZE);

  if(received_output == NULL)
  {
    printf("NULL!\r\n");
  }

  for(size_t i = 0; i < PALETTE_SIZE; i++)
  {
    assert_int_equal(received_output[(3 * i)], table.colours[i].red);
    assert_int_equal(received_output[(3 * i) + 1], table.colours[i].green);
    assert_int_equal(received_output[(3 * i) + 2], table.colours[i].blue);
  }

  free(received_output);
}

int main(void)
{
  const struct CMUnitTest tests[] =
  {
    cmocka_unit_test(test_colour_table),
  };

  return cmocka_run_group_tests(tests, setup, teardown);
}