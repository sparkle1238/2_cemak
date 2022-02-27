// https://prog-cpp.ru/c-files/                   - строки

// http://cppstudio.com/post/1628/                - курсор

// https://prog-cpp.ru/c-struct/                  - структура

// http://all-ht.ru/inf/prog/c/func/atoi.html    - строка в число

// https://ru.wikibooks.org/wiki/%D0%AF%D0%B7%D1%8B%D0%BA_%D0%A1%D0%B8_%D0%B2_%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D0%B0%D1%85/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0    - qsort
 

// https://ru.stackoverflow.com/questions/524051/%D0%92%D0%BE%D0%B7%D0%BC%D0%BE%D0%B6%D0%BD%D0%BE-%D0%BB%D0%B8-%D1%81-%D0%BF%D0%BE%D0%BC%D0%BE%D1%89%D1%8C%D1%8E-qsort-%D0%BE%D1%82%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-%D0%BC%D0%B0%D1%81%D1%81%D0%B8%D0%B2-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80-%D0%BF%D0%BE-%D0%BF%D0%BE%D0%BB%D1%8E-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B   - qsort

//  http://cppstudio.com/post/812/ из строки в double

#include <stdio.h>
#include <stdlib.h> //qsort,atoi

#define PRINT_TABLE  printf("| %6s |  %3.d  | %.2lf  | %s  |\n|--------+-------+---------+------|\n",student[i].name, student[i].age, student[i].height, student[i].mark); 
#define PRINT_HEAD  printf("___________________________________\n|  name  | age   | height  | mark |\n|--------+-------+---------+------|\n");
 
//функции, которая умеет сравнивать два элемента массива
int Comp(const int *i, const int *j) 
{
  return *i - *j; 
}

//структура
struct Student 
{
  int age;
  char mark[3];
  double height;
  char name[6]
};

//вытаскиваем элементы массива из json
void ArrJson(char symbol2, FILE *test, char *arr)
{
  int index = 0;
  char symbol = symbol2;
  while ( symbol != '\n') 
  {
    symbol = symbol2;
    symbol2 = fgetc(test);
    if ((symbol == ',' || symbol == '[') && symbol2 == '"') 
    {
      arr[index] = fgetc(test);
      index++;
    }
  }
}

//красивый вывод
void Cout(struct Student *student,int spisoc)
{
  PRINT_HEAD;
  for (int i = 0; i < spisoc; i++)
    PRINT_TABLE;
}

// заполнение структуры студента 
int Teble(FILE *test,struct Student *student,int spisoc)
{  
  char symbol, symbol2;
  //идем до конца файла
  while ((symbol2 = fgetc(test)) != EOF) 
  {
    if (symbol == 'g' && symbol2 == 'e') 
    {
      char str[7]; //создаем временное хранилище
      fseek(test, 3, SEEK_CUR); //курсор  : (поток,количество символов которые пропустим,откуда начинать  )
      fgets(str, 4, test); //(куда записываем ,сколько символов, поток)
      student[spisoc].age = atoi(str); //перевод из строки в int
    }
    
    if (symbol == 'h' && symbol2 == 't') 
    {
      char arr[8]={};
      fseek(test, 3, SEEK_CUR);
      fgets(arr, 7, test);
      student[spisoc].height = strtod(arr, NULL); // перевод из строки в дабл
    }
    
    if (symbol == 'r' && symbol2 == 'k') 
    {
      char arr[10] ={};
      ArrJson(symbol2,test,arr);
      strcpy(student[spisoc].mark, arr);
    }
    
    if (symbol == 'm' && symbol2 == 'e') 
    {
      char arr[10]={};
      ArrJson(symbol2,test,arr);
      strcpy(student[spisoc].name, arr);
    }
    
    if (symbol == '}') spisoc++; // увеличиваем количество студентов 
    symbol = symbol2;
  }
return spisoc;
}


int main() 
{
  FILE* test = NULL;
  test=fopen("test.json","r");
  //проверка что файл открылся 
  if (test==NULL)
  {
    perror("opening file (r)");
    return 1;
  }
  
  struct Student student[100];
  int spisoc = Teble(test,student,0);
  //вывод
  printf("\n1) вывод\n");
  Cout(student,spisoc);
  //сортировка
  printf("\n2) сортировка\n");
  qsort(student, spisoc, sizeof(student[0]),Comp); // qsort или можно написать пузырек
  Cout(student,spisoc);
  //фильтр
  printf("\n3) фильтр все старше 16 \n");
  PRINT_HEAD;
  for (int i = 0; i < spisoc; i++)
    if(student[i].age>16)
      PRINT_TABLE; 
  fclose(test);//закрытие файла
  return 0;
}