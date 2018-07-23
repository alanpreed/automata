#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <cmocka.h>


void test_fail(void **state)
{
  assert_true(true);
}

int main(void)
{
  const struct CMUnitTest tests[] =
  {
    cmocka_unit_test(test_fail),
  };

  int count_failed_tests = cmocka_run_group_tests(tests, NULL, NULL);

  return count_failed_tests;
}