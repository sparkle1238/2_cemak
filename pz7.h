#include <stdio.h>
#include <malloc.h>
#include <limits.h>

char *bit(char *res,unsigned int x)
{
do{
    res--; //переход к следующему символу в строке
    if( x & 1 )
      *res = '1'; 
    else 
      *res = '0'; //проверка бита
    x>>=1; //переход к следующему биту 
  }while(x != 0); //если число кончилось - ведущие нули игнорируем
  return res;
}

void cout(char *res,char *str1)
{
  printf("Битовое представление -");
  for(int i=0;res[i]!='\0';i++)
    i % 8 == 0 ?  printf(" %c",res[i]) : printf("%c",res[i]);
  printf(" \nБайтовое представление - ");
  for(int i=0;str1[i]!='\0';i++)
    i % 2 == 0 ?  printf(" 0x%c",str1[i]) : printf("%c",str1[i]);
}

int main()
{
  
  unsigned int x = UINT_MAX;
  unsigned int hex = x;
  char *str = (char *)malloc(1024*8*sizeof(x)+1); 
  char *res;//* указатель на первый элемент 
  res = str+sizeof(str); //заполнение строки идет с конца (с младшего бита)
  *res = 0; //конец строки
  char *str1=(char *)malloc(1024*sizeof(char));          
  
  printf("\nпроизвольное\n");
  scanf("%i",&x);
  hex = x;
  res = bit(res,x);
  sprintf(str1,"%x",hex);
  cout(res,str1);
  memset(str1,0,1024);
  memset(str,0,1024*8);
  
  printf("\nMAX\n");
  x = UINT_MAX;
  hex = x;
  res = bit(res,x);
  sprintf(str1,"%x",hex);
  cout(res,str1);
  
  
  
  
  return 0;
  
}
