#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define NMAX 1023


// структура стека 
struct stack
{
  char elem[NMAX];
  int top;
};

void push(struct stack *stk, char element) 
{
  if(stk->top < NMAX) {
    stk->elem[stk->top] = element;
    stk->top++;
  } else
    printf("Стек полон, количество элементов: %d !\n", stk->top);
}

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
    printf("Стек пуст!\n");
    return 0;
  }
}

int isempty(struct stack *stk) {
  if(stk->top == 0)    
    return 1;
  else return 0;
}
void init(struct stack *stk)
{
  stk-> top = 0;
}


int main(){
  struct stack str[100];
  char arr[100];
  fgets(arr,99,stdin);
  init(str);

  for(int i = 0; arr[i]!= '\0'; i++)
    {
      if (arr[i] == '{' ||  arr[i]=='[' || arr[i] == '(' )
        push(str,arr[i]);
      
      if ((arr[i] == '}' && pop(str)!= '{')||( arr[i]==']' && pop(str)!= '[') || (arr[i] == ')' && pop(str)!= '(' ))
      {
        printf("Error\n");
        return 0;
        }
    }

  if (isempty(str) != 1)
  {
    printf("Error\n");
    return 0;
    }
  printf("Success");
  return 0;
  

  
}