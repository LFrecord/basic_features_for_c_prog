#include "check_vector.h"

#define SUCCESS 0
#define FAILURE 1

int main(void)
{
    Suite *vector_suite = suite_to_test_vector_lib();

    SRunner *runner = srunner_create(vector_suite);

    srunner_run_all(runner, CK_VERBOSE);

    int failed_tests = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (failed_tests == 0) ? SUCCESS : FAILURE;
}
