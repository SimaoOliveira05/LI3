#include "./utils/cmp.h"

gint cmp_int(gconstpointer a, gconstpointer b) {
    int int_a = atoi((const char*)a);
    int int_b = atoi((const char*)b);

    return (int_a > int_b) - (int_a < int_b);
}

gint cmp_int_pointer_with_data(gconstpointer a, gconstpointer b, gpointer user_data) {
    (void)user_data;
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;

    return (int_a > int_b) - (int_a < int_b);
}

gint strcmp_wrapper(gconstpointer a, gconstpointer b, gpointer user_data) {
    (void) user_data;
    return g_strcmp0((const char *)a, (const char *)b);
}