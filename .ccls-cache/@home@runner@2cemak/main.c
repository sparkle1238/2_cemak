// https://prog-cpp.ru/c-files/                   - строки

// http://cppstudio.com/post/1628/                - курсор

// https://prog-cpp.ru/c-struct/                  - структура

// http://all-ht.ru/inf/prog/c/func/atoi.html    - строка в число

// https://ru.wikibooks.org/wiki/%D0%AF%D0%B7%D1%8B%D0%BA_%D0%A1%D0%B8_%D0%B2_%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D0%B0%D1%85/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0
// - qsort

// https://ru.stackoverflow.com/questions/524051/%D0%92%D0%BE%D0%B7%D0%BC%D0%BE%D0%B6%D0%BD%D0%BE-%D0%BB%D0%B8-%D1%81-%D0%BF%D0%BE%D0%BC%D0%BE%D1%89%D1%8C%D1%8E-qsort-%D0%BE%D1%82%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-%D0%BC%D0%B0%D1%81%D1%81%D0%B8%D0%B2-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80-%D0%BF%D0%BE-%D0%BF%D0%BE%D0%BB%D1%8E-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B
// - qsort http://cppstudio.com/post/812/ из строки в double
#include <stdio.h>
#include <stdlib.h> //qsort,atoi

int comp(const int *i, const int *j) { return *i - *j; }

//структура
struct Student {
  int age;
  char mark[3];
  double height;
};

int main() {
  char symbol, symbol2;
  char *ptrEnd;
  struct Student student[100];
  FILE *test = fopen("test.json", "r");
  int j = 0; //количество студентов

  //идем до конца файла
  while ((symbol2 = fgetc(test)) != EOF) {
    if (symbol == 'e' && symbol2 == '"') {
      char str[7]; //создаем временное хранилище
      fseek(test, 2, SEEK_CUR); //курсор  : (поток,количество символов которые
                                //пропустим,откуда начинать  )
      fgets(str, 4, test); //(куда записываем ,сколько символов, поток)
      student[j].age = atoi(str); //перевод из строки в int
    }
    if (symbol == 't' && symbol2 == '"') {
      char arr[8];
      fseek(test, 2, SEEK_CUR);
      fgets(arr, 7, test);
      student[j].height = strtod(arr, NULL); // перевод из строки в дабл
    }
    if (symbol == 'k' && symbol2 == '"') {
      int k = 0;
      while (symbol != '\n') {
        symbol = symbol2;
        symbol2 = fgetc(test);

        if ((symbol == ',' || symbol == '[') && symbol2 == '"') {
          student[j].mark[k] = fgetc(test);
          k++;
        }
      }
    }

    if (symbol == '}')
      j++;
    symbol = symbol2;
  }

  //вывод
  printf("1)вывод\n");
  printf("| age   | height  | mark\n");
  for (int i = 0; i < j; i++)
    printf("|  %3.d  | %.2lf  | %s\n", student[i].age, student[i].height, student[i].mark);
  printf("------------------\n");
  //сортировка
  printf("2)сортировка\n");
  qsort(student, j, sizeof(student[0]),
        (int (*)(const void *,
                 const void *))comp); // qsort или можно написать пузырек
  for (int i = 0; i < j; i++)
    printf("|  %3.d  | %.2lf  | %s\n", student[i].age, student[i].height, student[i].mark);
  printf("------------------\n");
  //фильтр
  printf("3)фильтр все старше 16 \n");
  for (int i = 0; i < j; i++)
    if (student[i].age > 16)
      printf("|  %3.d  | %.2lf  | %s\n", student[i].age, student[i].height,
             student[i].mark);
  printf("------------------\n");

  //закрытие файла
  fclose(test);

  return 0;
}