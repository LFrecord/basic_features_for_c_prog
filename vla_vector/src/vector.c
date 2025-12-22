#include "vector.h"

struct __vector_type__
{
    void *data;
    size_t capacity;
    size_t elems_amount;
    size_t size;
};

static int increase_data(vector container)
{
    int rc = (container == NO_VECTOR) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE)
    {
        void *help_ptr = realloc(container->data, (container->capacity += VECTOR_INCREASER + 1) * container->size);
        if (help_ptr == NULL)
            rc = VECTOR_REALLOC_ERR;
        else
            container->data = help_ptr;
    }
    return rc;
}

static int decrease_data(vector container)
{
    int rc = (container == NO_VECTOR) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE)
    {
        void *help_ptr = realloc(container->data, (container->capacity -= VECTOR_INCREASER + 1) * container->size);
        if (help_ptr == NULL)
            rc = VECTOR_REALLOC_ERR;
        else
            container->data = help_ptr;
    }
    return rc;
}

int init_vector(vector *container, size_t elem_size)
{
    int rc = (container == NULL || elem_size == 0) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE)
    {
        *container = malloc(sizeof(struct __vector_type__));
        if (*container == NULL)
            rc = VECTOR_MALLOC_ERR;
    }
    if (rc == VECTOR_POS_CASE)
    {
        (*container)->data = malloc(elem_size * BASE_VECTOR_SIZE);
        if ((*container)->data == NULL)
            rc = VECTOR_DATA_MALLOC_ERR;
        else
        {
            (*container)->capacity = BASE_VECTOR_SIZE;
            (*container)->size = elem_size;
            (*container)->elems_amount = 0;
        }
    }
    return rc;
}

int free_vector(vector *container)
{
    int rc = (container == NULL) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE)
    {
        free((*container)->data);
        free(*container);
        *container = NO_VECTOR;
    }
    return rc;
}

int push_back_vector(vector container, void *p_elem)
{
    int rc = (container == NO_VECTOR || p_elem == NULL) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE && container->capacity == container->elems_amount)
        rc = increase_data(container);
    if (rc == VECTOR_POS_CASE)
        memcpy((void*)((char*)container->data + container->size * (container->elems_amount)++), p_elem, container->size);
    return rc;
}

int pop_back_vector(vector container)
{
    int rc = (container == NO_VECTOR) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE && container->elems_amount != 0)
    {
        (container->elems_amount)--;
        if (container->capacity - container->elems_amount > VECTOR_INCREASER)
            rc = decrease_data(container);
    }
    return rc;
}

int insert_vector(vector container, void *p_elem, size_t index)
{
    int rc = (container == NO_VECTOR || p_elem == NULL) ? VECTOR_POS_CASE : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE && container->elems_amount == container->capacity)
        rc = increase_data(container);
    if (rc == VECTOR_POS_CASE)
    {
        if (index >= container->elems_amount)
            rc = push_back_vector(container, p_elem);
        else
        {
            for (size_t i = ++(container->elems_amount), size = container->size; i > index; i--)
                memcpy((char*)container->data + size * i, (char*)container->data + size * (i - 1), size);
            memcpy((char*)container->data + container->size * index, p_elem, container->size);
        }
    }
    return rc;
}

int change_elem_vector(vector container, size_t index, void *p_elem)
{
    int rc = (container == NO_VECTOR || p_elem == NULL) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE && index >= container->elems_amount)
        rc = VECTOR_INDX_OUT_OF_RANGE_ERR;
    if (rc == VECTOR_POS_CASE)
        memcpy((void*)((char*)container->data + container->size * index), p_elem, container->size);
    return rc;
}

void *at_vector(vector container, int index)
{
    void *rp = NULL;
    if (container != NO_VECTOR)
    {
        if (index >= 0 && (size_t)(index) < container->elems_amount)
            rp = (void*)((char*)container->data + container->size * index);
        else if (index < 0 && (size_t)(-1 * index) <= container->elems_amount)
            rp = (void*)((char*)container->data + container->size * (container->elems_amount + index));
    }
    return rp;
}

int size_vector(vector container)
{
    return (container == NO_VECTOR) ? 0 : container->elems_amount;
}
