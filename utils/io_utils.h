#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <stddef.h>

/* Lê uma linha do stdin para buf (removendo o '\n' se existir). */
void ler_linha(const char* prompt, char* buf, size_t buf_sz);

/* Lê um inteiro do stdin. Retorna 1 em sucesso, 0 em falha. */
int ler_int(const char* prompt, int* out);

#endif /* IO_UTILS_H */
