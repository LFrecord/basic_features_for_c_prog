#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <string.h>

/**
 * Тип данных, реализующий массив динамической длины (вектор)
 * 
 */
#define vector vector_t
#define BASE_VECTOR_SIZE 20
#define VECTOR_INCREASER 5
#define NO_VECTOR NULL

enum vector_return_codes
{
    VECTOR_POS_CASE,
    VECTOR_VAR_ERR,
    VECTOR_MALLOC_ERR,
    VECTOR_DATA_MALLOC_ERR,
    VECTOR_REALLOC_ERR
};

typedef struct __vector_type__ *vector_t;

/**
 * Инициализирует вектор
 * \param[in,out] container - Описатель вектора
 * \param[in] elem_size - Размер сохраняемого элемента
 * 
 * \return - VECTOR_POS_CASE или код ошибки
 */
int init_vector(vector *container, size_t elem_size);

/**
 * Освобождает вектор
 * \param[in,out] container - Описатель вектора
 * 
 * \note - После освобождения памяти определитель становится равен NO_VECTOR
 * 
 * \return - VECTOR_POS_CASE или код ошибки
 */
int free_vector(vector *container);


/**
 * Добавляет элемент в конец вектора
 * \param[in,out] container - Описатель вектора
 * \param[in] p_elem - Указатель на объект
 * 
 * \return - VECTOR_POS_CASE или код ошибки
 */
int push_back_vector(vector container, void *p_elem);

/**
 * Удаляет элемент из конца вектора
 * \param[in,out] container - Описатель вектора
 * 
 * \note Если вектор пуст, ничего не делает. Случай не возвращает кода ошибки.
 * 
 * \return - VECTOR_POS_CASE или код ошибки
 */
int pop_back_vector(vector container);

/**
 * Добавляет элемент в позицию вектора по индексу
 * \param[in,out] container - Описатель вектора
 * \param[in] p_elem - Указатель на элемент
 * \param[in] index - Индекс позиции, на которую будет записан элемент
 * 
 * \note Если индекс окажется больше длины вектора, то элемент будет записан в конец
 * 
 * \return - VECTOR_POS_CASE или код ошибки
 */
int insert_vector(vector container, void *p_elem, size_t index);


/**
 * Возвращает указатель на элемент по индексу
 * \param[in,out] container - Описатель вектора
 * \param[in] index - Индекс элемента, указатель на который будет возвращён
 * 
 * \note Индекс имеет тип int, те он может быть как положительным, так и отрицательным. Отрицательные индексы возвращают указатели с последнего при -1 итд в
 * обратном порядке. Ошибочной являются ситуации, когда переданный индекс больше индекса последнего элемента или когда модуль переданного индекса больше
 * количество записанных элементов.
 * 
 * \return - VECTOR_POS_CASE или код ошибки
 */
void *at_vector(vector container, int index);

/**
 * Возвращает длину вектора (количество записанных элементов)
 * \param[in,out] container - Описатель вектора
 * 
 * \note Если вектор не проинициализирован, функция возвращает 0.
 * 
 * \return - VECTOR_POS_CASE или код ошибки
 */
int size_vector(vector container);

#endif
