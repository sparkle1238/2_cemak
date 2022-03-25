// #include <stdio.h>
// #include <malloc.h>
// #include <limits.h>
// #include <string.h>
// #include <ctype.h>

// char *bit(char *res,unsigned int x)
// {
//   do
//   {
//     res--; //переход к следующему символу в строке
//     if( x & 1 )
//       *res = '1'; 
//     else 
//       *res = '0'; //проверка бита
//     x >>= 1; //переход к следующему биту 
//   } while(x != 0); //если число кончилось - ведущие нули игнорируем
//   return res;
// }

// void cout(char *res,char *str1)
// {
//   printf("Битовое представление -");
//   for(int i=0;res[i]!='\0';i++)
//     i % 8 == 0 ?
//       printf(" %c",res[i]) :
//       printf("%c",res[i]);
  
//   printf(" \nБайтовое представление - ");
//   for(int i=0;str1[i]!='\0';i++)
//     i % 2 == 0 ?
//       printf(" 0x%c",str1[i]) : 
//       printf("%c",str1[i]);
// }

// void F(unsigned int x)
// {
//   unsigned int hex = x;
//   char *str = (char*)malloc(1024*8*sizeof(x)+1); 
//   char *res;
//   res = str+sizeof(str); 
//   *res = 0; 
//   char *str1=(char*)malloc(1024*sizeof(char));  
//   hex = x;
//   res = bit(res,x);
//   sprintf(str1,"%x",hex);
//   int k = strlen(str1);
//   for (int i = 0; i < k; i++)
//   {
//     str1[i] = toupper(str1[i]);//перевод в верхний регистр
//   }
//   cout(res,str1);
//   free(str1);
// }


// int main()
// { 
//   unsigned int x = UINT_MAX;   
  
//   printf("\nПроизвольное значение - ");
//   scanf("%i",&x);
//   F(x); 

  
//   printf("\n\nMAX \nМаксимальное значение - %u\n",UINT_MAX);
//   F(UINT_MAX);  

  
//   printf("\n\nMIN \nМинимальное значение - %u\n",NULL);
//   F(0);  
  
//   return 0;
// }
