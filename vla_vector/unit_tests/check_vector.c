#include "check_vector.h"

// POSSITIVE TESTS OF VECTOR FUNCTIONS

START_TEST(ptest1_init_free_ok)
{
    int rc = 0;
    vector container = NO_VECTOR;

    rc = init_vector(&container, sizeof(int));
    if (rc == VECTOR_POS_CASE)
        rc = free_vector(&container);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(ptest2_push_back_at_pos_ok)
{
    vector container = NO_VECTOR;
    int rc = init_vector(&container, sizeof(int));

    for (int i = 1; rc == VECTOR_POS_CASE && i <= 5; i++)
        rc = push_back_vector(container, &i);
    
    for (int i = 5; rc == VECTOR_POS_CASE && i > 0; i--)
        if (*(int*)at_vector(container, i - 1) != i)
            rc = i;
    
    if (container != NO_VECTOR)
        free_vector(&container);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(ptest3_at_neg_ok)
{
    vector container = NO_VECTOR;
    int rc = init_vector(&container, sizeof(int));

    for (int i = 1; rc == VECTOR_POS_CASE && i <= 5; i++)
        rc = push_back_vector(container, &i);
    
    for (int i = -1; rc == VECTOR_POS_CASE && i >= -5; i--)
    {
        int elem = *(int*)at_vector(container, i);
        if (elem != 6 + i)
            rc = i;
    }

    if (container != NO_VECTOR)
        free_vector(&container);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(ptest4_pop_back_ok)
{
    vector container = NO_VECTOR;
    int rc = init_vector(&container, sizeof(int));

    for (int i = 1; rc == VECTOR_POS_CASE && i <= 5; i++)
        rc = push_back_vector(container, &i);
    
    for (int iter = 5, indx = -1; rc == VECTOR_POS_CASE && iter > 0; iter--)
    {
        int elem = *(int*)at_vector(container, indx);
        if (elem != iter)
            rc = elem;
        if (rc == VECTOR_POS_CASE)
            rc = pop_back_vector(container);
    }

    if (container != NO_VECTOR)
        free_vector(&container);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(ptest5_size_vector_ok)
{
    vector container = NO_VECTOR;
    int rc = init_vector(&container, sizeof(int));

    for (int i = 1; rc == VECTOR_POS_CASE && i <= 5; i++)
        rc = push_back_vector(container, &i);
    
    for (int i = size_vector(container); rc == VECTOR_POS_CASE && i > 0; i--)
        if (*(int*)at_vector(container, i - 1) != i)
            rc = i;
    
    if (container != NO_VECTOR)
        free_vector(&container);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(ptest6_change_elem_ok)
{
    vector container = NO_VECTOR;
    int rc = init_vector(&container, sizeof(int));

    for (int i = 1, elem = 0; rc == VECTOR_POS_CASE && i <= 5; i++)
        rc = push_back_vector(container, &elem);
    
    for (int i = 1; rc == VECTOR_POS_CASE && i <= 5; i++)
        rc = change_elem_vector(container, (size_t)(i - 1), &i);
    
    for (int i = 5; rc == VECTOR_POS_CASE && i > 0; i--)
        if (*(int*)at_vector(container, i - 1) != i)
            rc = i;
    
    if (container != NO_VECTOR)
        free_vector(&container);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(ptest7_insert_elem_ok)
{
    vector container = NO_VECTOR;
    int rc = init_vector(&container, sizeof(int));

    for (int i = 1, elem = 1; rc == VECTOR_POS_CASE && i <= 3; i++, elem += 2)
        rc = push_back_vector(container, &elem);
    
    for (int iter = 1, elem = 2; rc == VECTOR_POS_CASE && iter <= 3; iter += 2, elem += 2)
        rc = insert_vector(container, &elem, (size_t)(iter));
    if (rc == VECTOR_POS_CASE)
    {
        int over_indx_elem = 6;
        rc = insert_vector(container, &over_indx_elem, 15);
    }
    
    for (int i = 6; rc == VECTOR_POS_CASE && i > 0; i--)
        if (*(int*)at_vector(container, i - 1) != i)
            rc = i;
    
    if (container != NO_VECTOR)
        free_vector(&container);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

// NEGATIVE TESTS OF VECTOR FUNCTIONS

START_TEST(ntest1_init_free_err)
{
    vector c1 = NO_VECTOR;

    int rc1 = init_vector(NULL, sizeof(int));
    int rc2 = init_vector(&c1, 0);
    int rc3 = free_vector(NULL);
    int rc4 = free_vector(&c1);

    ck_assert_int_eq(rc1, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc2, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc3, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc4, VECTOR_VAR_ERR);
}
END_TEST

START_TEST(ntest2_push_back_pop_back_err)
{
    vector c1 = NO_VECTOR;
    int el1 = 1;
    int rc1 = push_back_vector(NO_VECTOR, &el1);
    int rc2 = push_back_vector(c1, &el1);

    init_vector(&c1, sizeof(int));

    int rc3 = push_back_vector(c1, NULL);
    int rc4 = pop_back_vector(NO_VECTOR);

    free_vector(&c1);

    int rc5 = pop_back_vector(c1);

    ck_assert_int_eq(rc1, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc2, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc3, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc4, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc5, VECTOR_VAR_ERR);
}

START_TEST(ntest3_insert_size_err)
{
    vector c1 = NO_VECTOR;
    int el1 = 1;
    int rc1 = insert_vector(NO_VECTOR, &el1, 0);
    
    init_vector(&c1, sizeof(int));

    int rc2 = insert_vector(c1, NULL, 0);
    int rc3 = size_vector(NO_VECTOR);

    free_vector(&c1);

    ck_assert_int_eq(rc1, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc2, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc3, 0);
}
END_TEST

START_TEST(ntest4_change_elem_err)
{
    vector c1 = NO_VECTOR;
    int el1 = 1;

    int rc1 = change_elem_vector(c1, 15, &el1);

    init_vector(&c1, sizeof(int));

    int rc2 = change_elem_vector(c1, 15, NULL);

    free_vector(&c1);

    ck_assert_int_eq(rc1, VECTOR_VAR_ERR);
    ck_assert_int_eq(rc2, VECTOR_VAR_ERR);
}
END_TEST

// Testing suite

Suite *suite_to_test_vector_lib(void)
{
    Suite *s = suite_create("suite for testing vector data type and functions");

    TCase *possitive = tcase_create("possitives"), *negative = tcase_create("negatives");

    tcase_add_test(possitive, ptest1_init_free_ok);
    tcase_add_test(possitive, ptest2_push_back_at_pos_ok);
    tcase_add_test(possitive, ptest3_at_neg_ok);
    tcase_add_test(possitive, ptest4_pop_back_ok);
    tcase_add_test(possitive, ptest5_size_vector_ok);
    tcase_add_test(possitive, ptest6_change_elem_ok);
    tcase_add_test(possitive, ptest7_insert_elem_ok);

    tcase_add_test(negative, ntest1_init_free_err);
    tcase_add_test(negative, ntest2_push_back_pop_back_err);
    tcase_add_test(negative, ntest3_insert_size_err);
    tcase_add_test(negative, ntest4_change_elem_err);

    suite_add_tcase(s, possitive);
    suite_add_tcase(s, negative);
    return s;
}
