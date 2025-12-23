/**
 * @file main.c
 * @brief Tests the dynamic array-based List implementation.
 * @details Demonstrates append, insert, pop, and conversion to array.
 * @author Pranveer
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * @brief Prints a NULL-terminated array of strings.
 * @param array Pointer to the array of strings.
 */
void print_string_array(char** array)
{
    for (size_t i = 0; array[i]; i++) printf("%s", array[i]);
    printf("\n");
}

/**
 * @brief Self-test implementation for List.
 */
static void test_list()
{
    // Initialize a new list
    List* list1 = list_init();
    assert(list1 != NULL);
    assert(list_length(list1) == 0);

    // Append elements
    assert(list_append(list1, "Hai ") == 0);
    assert(list_append(list1, "Hoang ") == 0);
    assert(list_append(list1, "Dang ") == 0);
    assert(list_length(list1) == 3);

    // Convert to array and check order
    void** array1 = list_to_array(list1);
    assert(strcmp(array1[0], "Hai ") == 0);
    assert(strcmp(array1[1], "Hoang ") == 0);
    assert(strcmp(array1[2], "Dang ") == 0);
    assert(array1[3] == NULL);
    free(array1);

    // Insert element at index 1
    assert(list_insert(list1, 1, "Inserted ") == 0);
    assert(list_length(list1) == 4);
    void** array2 = list_to_array(list1);
    assert(strcmp(array2[1], "Inserted ") == 0);
    free(array2);

    // Pop element
    void* popped = list_pop(list1);
    assert(strcmp((char*)popped, "Dang ") == 0);
    assert(list_length(list1) == 3);

    // Create a list from variadic arguments
    List* list2 = list_from_args("Mentor ", "Graphics ", "Siemens", NULL);
    assert(list2 != NULL);
    assert(list_length(list2) == 3);

    // Append list2 into list1 manually
    for (size_t i = 0; i < list_length(list2); i++)
        assert(list_append(list1, list2->items[i]) == 0);
    assert(list_length(list1) == 6);

    // Convert to array and print
    char** final_array = (char**)list_to_array(list1);
    printf("Final list: ");
    print_string_array(final_array);
    free(final_array);

    // Free lists
    list_free(list1);
    list_free(list2);

    printf("All list tests passed successfully!\n");
}

/**
 * @brief Main function.
 */
int main()
{
    test_list();
    return 0;
}
