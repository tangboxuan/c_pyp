#include "binaryheap.h"
#include <string.h>

int main(int argc, char **argv){
    
    node_heap *heap[20];
    int len = strlen(argv[1]);
    initial_heap(heap, argv[1]);
    print_elem_heap(heap, len);
    build_max_heap(heap, len);
    print_elem_heap(heap, len);
    myheapsort(heap, len);
    print_elem_heap(heap, len);
}
