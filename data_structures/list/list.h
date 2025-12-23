#ifndef __LIST__
#define __LIST__

#include <stddef.h>

/**
 * @file list.h
 * @brief Dynamic array of generic pointers, similar to Python lists.
 */

/**
 * @struct List
 * @brief Represents a dynamic array of void pointers.
 */
typedef struct
{
    void **items;    /**< Pointer to array of elements */
    size_t size;     /**< Current number of elements */
    size_t capacity; /**< Allocated capacity */
} List;

/**
 * @brief Initialize a new empty list.
 * @return Pointer to the newly created List.
 */
List *list_init(void);

/**
 * @brief Append an element to the end of the list.
 * @param list Pointer to the List.
 * @param val Pointer to the value to append.
 * @return 0 on success, -1 on allocation failure.
 */
int list_append(List *list, void *val);

/**
 * @brief Insert an element at a given index.
 * @param list Pointer to the List.
 * @param index Position to insert.
 * @param val Pointer to the value to insert.
 * @return 0 on success, -1 on error.
 */
int list_insert(List *list, size_t index, void *val);

/**
 * @brief Remove and return the last element from the list.
 * @param list Pointer to the List.
 * @return Pointer to the removed element, NULL if list is empty.
 */
void *list_pop(List *list);

/**
 * @brief Get the number of elements in the list.
 * @param list Pointer to the List.
 * @return Number of elements.
 */
size_t list_length(const List *list);

/**
 * @brief Convert the list to a NULL-terminated array.
 * @param list Pointer to the List.
 * @return Pointer to a newly allocated array. Caller must free it.
 */
void **list_to_array(const List *list);

/**
 * @brief Create a list from variable arguments, ending with NULL.
 * @param first Pointer to the first element.
 * @param ... Subsequent elements ending with NULL.
 * @return Pointer to the newly created List.
 */
List *list_from_args(void *first, ...);

/**
 * @brief Free the list structure (does not free individual elements).
 * @param list Pointer to the List.
 */
void list_free(List *list);

#endif
