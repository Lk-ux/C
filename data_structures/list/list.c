#include "list.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/** Initial capacity for new lists */
#define LIST_INITIAL_CAPACITY 8

/**
 * @brief Resize the internal array to a new capacity.
 * @param list Pointer to the List.
 * @param new_capacity New capacity.
 * @return 0 on success, -1 on failure.
 */
static int list_resize(List* list, size_t new_capacity)
{
    void** new_items = realloc(list->items, new_capacity * sizeof(void*));
    if (!new_items)
        return -1;
    list->items = new_items;
    list->capacity = new_capacity;
    return 0;
}

List* list_init(void)
{
    List* list = malloc(sizeof(List));
    if (!list)
        return NULL;

    list->items = malloc(LIST_INITIAL_CAPACITY * sizeof(void*));
    if (!list->items)
    {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = LIST_INITIAL_CAPACITY;
    return list;
}

int list_append(List* list, void* val)
{
    if (list->size >= list->capacity)
    {
        if (list_resize(list, list->capacity * 2) != 0)
            return -1;
    }
    list->items[list->size++] = val;
    return 0;
}

int list_insert(List* list, size_t index, void* val)
{
    if (index > list->size)
        return -1;

    if (list->size >= list->capacity)
    {
        if (list_resize(list, list->capacity * 2) != 0)
            return -1;
    }

    memmove(&list->items[index + 1], &list->items[index],
            (list->size - index) * sizeof(void*));
    list->items[index] = val;
    list->size++;
    return 0;
}

void* list_pop(List* list)
{
    if (list->size == 0)
        return NULL;

    return list->items[--list->size];
}

size_t list_length(const List* list) { return list->size; }

void** list_to_array(const List* list)
{
    void** array = malloc((list->size + 1) * sizeof(void*));
    if (!array)
        return NULL;

    memcpy(array, list->items, list->size * sizeof(void*));
    array[list->size] = NULL;
    return array;
}

List* list_from_args(void* first, ...)
{
    va_list ap;
    List* list = list_init();
    if (!list)
        return NULL;

    va_start(ap, first);
    void* val = first;
    while (val != NULL)
    {
        if (list_append(list, val) != 0)
        {
            list_free(list);
            va_end(ap);
            return NULL;
        }
        val = va_arg(ap, void*);
    }
    va_end(ap);

    return list;
}

void list_free(List* list)
{
    if (!list)
        return;
    free(list->items);
    free(list);
}
