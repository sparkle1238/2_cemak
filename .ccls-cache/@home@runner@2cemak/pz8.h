// https://prog-cpp.ru/data-stack/ - стек
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define NMAX 1023

// структура стека 
struct stack {
  char elem[NMAX];
  int top;
};

// создание стека
void init(struct stack *stk) {
  stk->top = 0;
}

//кладем на верх и делаем сдвиг 
void push(struct stack *stk, char f) {
  if(stk->top < NMAX) {
    stk->elem[stk->top] = f;
    stk->top++;
  } else
    printf("Стек полон, количество элементов: %d !\n", stk->top);
}

//забираем верхний элемент
char pop(struct stack *stk) {
  char elem;
  if((stk->top) > 0)
  {
    stk->top--;
    elem = stk->elem[stk->top];
    return elem;
  }
  else
  {
    return 0;
  }
}


int isempty(struct stack *stk) {
  if(stk->top == 0)   
    return 1;
  else 
    return 0;
}

int CheckFile(FILE *fin)
{ 
  // стек
  struct stack *stk;
  stk = (struct stack*)malloc(sizeof(struct stack));
  init(stk);
  //идем по файлу 
  char sign;
  while((sign=fgetc(fin)) != EOF) 
  {
    // запись скобочек в стек
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
  if(isempty(stk)!=1) 
  { 
    return 1; 
  }
  fseek( fin , 0 , SEEK_SET );  
  return 0 ;
}