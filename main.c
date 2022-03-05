// https://prog-cpp.ru/c-files/                   - строки

// http://cppstudio.com/post/1628/                - курсор

// https://prog-cpp.ru/c-struct/                  - структура

// http://all-ht.ru/inf/prog/c/func/atoi.html    - строка в число

// https://ru.wikibooks.org/wiki/%D0%AF%D0%B7%D1%8B%D0%BA_%D0%A1%D0%B8_%D0%B2_%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D0%B0%D1%85/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0    - qsort
 

// https://ru.stackoverflow.com/questions/524051/%D0%92%D0%BE%D0%B7%D0%BC%D0%BE%D0%B6%D0%BD%D0%BE-%D0%BB%D0%B8-%D1%81-%D0%BF%D0%BE%D0%BC%D0%BE%D1%89%D1%8C%D1%8E-qsort-%D0%BE%D1%82%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-%D0%BC%D0%B0%D1%81%D1%81%D0%B8%D0%B2-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80-%D0%BF%D0%BE-%D0%BF%D0%BE%D0%BB%D1%8E-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B   - qsort

//  http://cppstudio.com/post/812/ из строки в double

#include <stdio.h>
#include <stdlib.h> //qsort,atoi
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

void Clear(char *arr)
{
  for(int i=0;i<11;i++)
    arr[i]='0';
}

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
  printf("___________________________________\n|  name  | age   | height  | mark |\n|--------+-------+---------+------|\n");
  for (int i = 0; i < spisoc; i++)
    printf("| %6s |  %3.d  | %.2lf  | %s  |\n|--------+-------+---------+------|\n",student[i].name, student[i].age, student[i].height, student[i].mark); 
}

void Filter(int age,struct Student *student,int spisoc)
{ 
  printf("\n3) фильтр все старше %i \n",age);
  printf("___________________________________\n|  name  | age   | height  | mark |\n|--------+-------+---------+------|\n");
  for (int i = 0; i < spisoc; i++)
    if(student[i].age>age)
      printf("| %6s |  %3.d  | %.2lf  | %s  |\n|--------+-------+---------+------|\n",student[i].name, student[i].age, student[i].height, student[i].mark); 
}

// заполнение структуры студента 
int Teble(FILE *test,struct Student *student,int spisoc)
{  
   
  char title[11]={};
  char symbol, symbol2;
  int size=0;
  //идем до конца файла 
  while ((symbol2 = fgetc(test)) != EOF) 
  {
    
    if (title[0] == 'a' && title[1] == 'g' && title[2] == 'e') 
    {
      char str[7]={}; //создаем временное хранилище
      fgets(str, 4, test); //(куда записываем ,сколько символов, поток)
      student[spisoc].age = atoi(str); //перевод из строки в int
      Clear(title);      
    }
    
    if (title[0]=='h' && title[1]=='e' && title[2]=='i' && title[3]=='g'  && title[4] == 'h' && title[5] == 't') 
    {
      char arr[8]={};
      fgets(arr, 8, test);
      student[spisoc].height = strtod(arr, NULL); // перевод из строки в дабл
      Clear(title);
    }
    
    if (title[0]=='m' && title[1]=='a' && title[2]=='r' && title[3]=='k') 
    {
      char arr[10]={};
      ArrJson(symbol2,test,arr);
      strcpy(student[spisoc].mark, arr);
      Clear(title);
    }
    
    if (title[0]=='n' && title[1]=='a' && title[2]=='m' && title[3]=='e') 
    {
      char arr[10]={};
      ArrJson(symbol2,test,arr);
      strcpy(student[spisoc].name, arr);
      Clear(title);
    }
    
    if (symbol == '}') spisoc++; // увеличиваем количество студентов 
    if(symbol=='"' && symbol2!=':')  size=0; // узнаем длину слова
    size++;
    // считываем слова в ковычках 
    if(symbol=='"' && symbol2==':')
    {
      fseek(test, -size, SEEK_CUR);
      for(int i = 0 ; title[i-1]!='"' ;i++)
      {
        title[i]=fgetc(test);
      }
    }
    symbol = symbol2; 
  }
  return spisoc;
}


int main() 
{
  FILE* test = NULL;
  test=fopen("test.json","r");
  //проверка что файл открылся 

  if (test==NULL || CheckFile(test)!=0)
  {
    perror("opening file (r)");
    return 0; 
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
  Filter(16,student,spisoc);
  fclose(test);//закрытие файла
  return 0;
}