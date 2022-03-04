// https://prog-cpp.ru/data-stack/ - стек
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define NMAX 1023

struct stack {
  float elem[NMAX];
  int top;
};

void init(struct stack *stk) {
  stk->top = 0;
}

void push(struct stack *stk, float f) {
  if(stk->top < NMAX) {
    stk->elem[stk->top] = f;
    stk->top++;
  } else
    printf("Стек полон, количество элементов: %d !\n", stk->top);
}

float pop(struct stack *stk) {
  float elem;
  if((stk->top) > 0)
  {
    stk->top--;
    elem = stk->elem[stk->top];
    return elem;
  }
  else
  {
    printf("Стек пуст!\n");
    return 0;
  }
}

int isempty(struct stack *stk) {
  if(stk->top == 0)    return 1;
  else return 0;
}

int CheckFile()
{ //строчка
  // char *arr = (char*)malloc(1024 * sizeof(char));
  // fgets(arr,1023,stdin);
  // стек
  struct stack *stk;
  stk = (struct stack*)malloc(sizeof(struct stack));
  init(stk);
   FILE* fin = NULL;
   fin=fopen("test.json","r");
  if (fin==NULL)
  {
      perror("opening file (r)");
      return 1;
  }
  char sign;
  while((sign=fgetc(fin)) != EOF) 
  {
    // запись скобочек
    if (sign=='[' || sign=='(' || sign=='{') 
      push(stk,sign);  
    // проверка на то что у нас верхняя скобочка закрывается раньше всех 
    if ( sign=='}' && pop(stk) != '{' ) 
    { 
      perror("error"); 
      return 1;
    } //{ 
    if ( sign==']' && pop(stk) != '[' )
    {
      perror("error"); 
      return 1;
    } //[
    if ( sign==')' && pop(stk) != '(' )
    {
      perror("error"); 
      return 1;
    } //(    
  }
  if(isempty(stk)!=1) return 1; 
  return 0 ;
}