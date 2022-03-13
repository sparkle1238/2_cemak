#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>


char * LittleEndian(unsigned int values)
{
    size_t bytes = sizeof(values);
    char *n = (unsigned char*)malloc(1024*sizeof(unsigned char*));
    for (size_t i = 0; i < bytes; i++)
    {
        n[i] = *((unsigned char*)& values << i);
    }
    return n;
}

int main()
{
  unsigned int max = UINT_MAX;
  unsigned int min = 0 ;
  printf("max = %u \nmin = %u \nмаксимальный байтовый вид = %s \nминимальный байтовый вид = %s", max, min, LittleEndian(max), LittleEndian(min));
  
  return 0;
}