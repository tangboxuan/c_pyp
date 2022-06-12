#include "binaryheap.h"
#include <assert.h>
#include <string.h>

/*allocate memory in the heap for a node_heap type element and returns a pointer to the new node_heap*/

node_heap *allocate_node_heap(void)
{
    // TO DO
    node_heap *pointer = calloc(1, sizeof(node_heap));
    return pointer;
}

/*initialise the heap array elements*/

void initial_heap(node_heap **heap, char *sequence)
{
    for (int i = 1; i <= strlen(sequence); i++)
    {
        heap[i] = allocate_node_heap();
        heap[i]->key = &sequence[i-1];
        heap[i]->position = i;
    }
}

char get_element(node_heap **heap, int index)
{
    return heap[index]->key[0];
}

/*print every element of the heap array*/
void print_elem_heap(node_heap **heap, int length)
{
    for (int i = 1; i <= length; i++)
    {
        printf("%c ", get_element(heap, i) );
    }
    printf("\n");
    for (int i = 1; i <= length; i++)
    {
        printf("%d ", heap[i]->position);
    }
    printf("\n");
}

/* returns the index in the heap array where the parent is allocated for the index passed as argument*/

int parent(int index)
{
    // TO DO
    return (index - 1);
}

/* returns the index in the heap array where the left child is allocated for the index passed as argument*/

int left_child(int index)
{
    // TO DO
    return 2 * index;
}

/* returns the index in the heap array where the right child is allocated for the index passed as argument*/

int right_child(int index)
{
    // TO DO
    return 2 * index + 1;
}

/* exchange node_heap node1 to node_heap node2*/

void swap(node_heap *node1, node_heap *node2)
{
    // TO DO
    // printf("SwAPPING %c %c\n", node1->key[0], node2->key[0]);
    char *temp_key = node1->key;
    node1->key = node2->key;
    node2->key = temp_key;
    int temp_pos = node1->position;
    node1->position = node2->position;
    node2->position = temp_pos;
}

/*Moves down the value of the heap[current] so the subtree rooted at index "current" satisfies with the max-heap property*/

void max_heapify(node_heap **heap, int current, int heap_size)
{
    int largest = current;
    int left = left_child(current);
    if (left <= heap_size && get_element(heap, left) > get_element(heap, largest))
    {
        largest = left;
    }
    int right = right_child(current);
    if (right <= heap_size && get_element(heap, right) > get_element(heap, largest))
    {
        largest = right;
    }
    if (get_element(heap, largest) > get_element(heap, current))
    {
        swap(heap[current], heap[largest]);
        max_heapify(heap, largest, heap_size);
    }
}

/*it orders the heap so the ordered heap complies the max-heap property*/

void build_max_heap(node_heap **heap, int heap_size)
{
    for (int i = heap_size / 2; i > 0; i--)
    {
        // printf("heapify %d\n", i);
        max_heapify(heap, i, heap_size);
    }
}

/*starting from a max-heap ordered array, it moves the largest item from the heap and it into the array position left as the heap shrinks*/

void myheapsort(node_heap **heap, int length)
{
    build_max_heap(heap, length);
    for (int i = length; i > 0; i--)
    {
        swap(heap[1], heap[i]);
        max_heapify(heap, 1, i - 1);
    }
}

/*free the memory allocated by a node_heap type element in the heap*/

void free_node(node_heap *node)
{
    // TO DO
    free(node);
}

/*free the memory allocated in the heap array*/

void free_heap(node_heap **heap, int length)
{
    // TO DO
    for (int i = 1; i <= length; i++)
    {
        free_node(heap[i]);
    }
}
