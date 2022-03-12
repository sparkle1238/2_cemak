// https://prog-cpp.ru/c-files/                   - строки

// http://cppstudio.com/post/1628/                - курсор

// https://prog-cpp.ru/c-struct/                  - структура

// http://all-ht.ru/inf/prog/c/func/atoi.html    - строка в число

// https://ru.wikibooks.org/wiki/%D0%AF%D0%B7%D1%8B%D0%BA_%D0%A1%D0%B8_%D0%B2_%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D0%B0%D1%85/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0    - qsort
 

// https://ru.stackoverflow.com/questions/524051/%D0%92%D0%BE%D0%B7%D0%BC%D0%BE%D0%B6%D0%BD%D0%BE-%D0%BB%D0%B8-%D1%81-%D0%BF%D0%BE%D0%BC%D0%BE%D1%89%D1%8C%D1%8E-qsort-%D0%BE%D1%82%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-%D0%BC%D0%B0%D1%81%D1%81%D0%B8%D0%B2-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80-%D0%BF%D0%BE-%D0%BF%D0%BE%D0%BB%D1%8E-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B   - qsort

//  http://cppstudio.com/post/812/ из строки в double

#include <stdio.h>
#include <stdlib.h> //qsort,atoi
#include <string.h>
#include <time.h>

#include "pz8.h" 

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
  char name[6];
};

//вытаскиваем элементы массива из json
void ArrJson(char symbol2, FILE *test, char *arr)
{
  int index = 0;
  char symbol = symbol2;
  while ( symbol != ']') 
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
  printf("___________________________________\n|  name  | age   | height  | mark |\n|--------+-------+---------+------|\n");
  for (int i = 0; i < spisoc; i++)
    printf("| %6s |  %3.d  | %.2lf  | %s  |\n|--------+-------+---------+------|\n",student[i].name, student[i].age, student[i].height, student[i].mark); 
}

//вывод струкруры с фильтвом возраста 
void FilterAge(int age,struct Student *student,int spisoc)
{ 
  printf("\n3) фильтр все старше %i \n",age);
  printf("___________________________________\n|  name  | age   | height  | mark |\n|--------+-------+---------+------|\n");
  for (int i = 0; i < spisoc; i++)
    if(student[i].age>age)
      printf("| %6s |  %3.d  | %.2lf  | %s  |\n|--------+-------+---------+------|\n",student[i].name, student[i].age, student[i].height, student[i].mark); 
}

// очистка массива 
void ArrClaer(char *arr)
{
  for(int i=0;arr[i]!='\0';i++)
    arr[i]='\000';
}

// заполнение структуры студента из файла json
int Teble(FILE *test,struct Student *student,int spisoc)
{  
  char title[11]={},symbol, symbol2;
  int size=0;
  //идем до конца файла 
  while ((symbol2 = fgetc(test)) != EOF) 
  {   
    if (strcmp("age",title) == 0) 
    {
      char str[7]={}; //создаем временное хранилище
      for(int i=0;(symbol2 = fgetc(test)) != ',';i++)
        str[i]=symbol2;
      student[spisoc].age = atoi(str); //перевод из строки в int
      ArrClaer(title);
    }
    
    if (strcmp("height",title) == 0 ) 
    {
      char str[8]={};
      for(int i=0;(symbol2 = fgetc(test)) != ',';i++)
        str[i]=symbol2;
      student[spisoc].height = strtod(str, NULL); // перевод из строки в дабл
      ArrClaer(title);
    }
    
    if (strcmp("mark",title) == 0) 
    {
      char str[10]={};
      ArrJson(symbol2,test,str);
      strcpy(student[spisoc].mark, str);
      ArrClaer(title);
    }
    
    if (strcmp("name",title) == 0) 
    {
      char str[10]={};
      ArrJson(symbol2,test,str);
      strcpy(student[spisoc].name, str);
      ArrClaer(title);
    }
    if (symbol == '}') spisoc++; // увеличиваем количество студентов   
    if(symbol == '"' && symbol2 != ':') size=0; // узнаем длину слова
    size++;
    // считываем слова в кавычках 
    if(symbol == '"' && symbol2 == ':')
    {
      fseek(test, -size, SEEK_CUR);
      int i = 0;
      for( ; title[i-1] != '"' ;i++)
      {
        title[i]=fgetc(test);
      }
      title[i-1]='\000';
    }    
    symbol = symbol2; 
  }
  return spisoc;
}


int main() 
{
  FILE* test = NULL;
  test = fopen("test.json","r");
  //проверка что файл открылся 
  if (test==NULL || CheckFile(test)!=0)
  {
    perror("opening file (r)");
    return 0; 
  }
  
  long long int start = clock();
  struct Student student[100];
  int spisoc = Teble(test,student,0);
  //вывод
  printf("\n1) вывод\n");
  Cout(student,spisoc);
  //сортировка
  printf("\n2) сортировка\n");
  qsort(student, spisoc, sizeof(student[0]),(int (*)(const void *,const void *))Comp); // qsort или можно написать пузырек
  Cout(student,spisoc);
  //фильтр
  FilterAge(16,student,spisoc);
  
  printf(" %lli\n",clock() - start);
  fclose(test);//закрытие файла
  return 0;
}