const double EPS = 1e9;


void swap_elem(void* a, void* b, size_t size, void* pivotPtr);
void change_elem_char_copy(char* str1, char* str2, size_t dif, size_t size);
void swap_elem_uint64(char* str1, char* str2, size_t size, void** pivotPtr);
size_t partition(void* arr, size_t len, size_t size, int(*comp)(const void*, const void*));
void u_quick_sort(void* arr, size_t len, size_t size, int(*comp)(const void*, const void*));

