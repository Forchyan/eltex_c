#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct Node{
    char surname[20];
    char faculty[20];
    int nomer;
    int group;
};

void insert(struct Node* node){
    printf("Введите фамилию: ");
    scanf("%s", node->surname);
    printf("Введите номер зачетной книжки: ");
    scanf("%d", &(node->nomer));
    printf("Введите факультет: ");
    scanf("%s", node->faculty);
    printf("Введите группу: ");
    scanf("%d", &(node->group));
}

void output(struct Node table[], int *size){
    if (*size == 0){
        printf("Таблица пустая!\n");
        return;
    }
    printf("Фамилия\tНомер зачетной книжки\tФакультет\tГруппа\n");
    for (int i=0; i < *size; i++){
        printf("%s\t%d\t\t\t%s\t%d\n", table[i].surname,table[i].nomer, table[i].faculty,table[i].group);
    }
}

void delete(struct Node table[],int index, int *size){
    if (index < 0 || index >= *size){
        printf("Неверный индекс!\n");
        return;
    }
    for (int i = index; i <= *size; i++){
        table[i] = table[i+1];
    }
    (*size)--;
    printf("Удалена запись с индексом: %d\n",index);
}

int read_from_file(struct Node table[], const char* filename){
    FILE* file;
    file = fopen(filename,"r");
    if (file == NULL){
        printf("Ошибка при открытии файла\n");
        return 0;
    }
    int counter = 0;
    while(fscanf(file, "%s %d %s %d",table[counter].surname, &table[counter].nomer, table[counter].faculty, &table[counter].group) == 4)
    {
        counter++;
    }
    fclose(file);
    return counter;
}

void write_to_file(struct Node table[], int *size)
{
    FILE* file = fopen("table.txt","w");
    if (file == NULL){
        printf("Ошибка при открытии файла\n");
        return;
    }
    int counter = 0;
    while (counter < *size ){
        fprintf(file,"%s %d %s %d\n",table[counter].surname, table[counter].nomer, table[counter].faculty, table[counter].group);
        counter++;
    }   
    fclose(file);
    printf("Таблица сохранена в файл!\n");
}

void search_nomer(struct Node table[], int *size, int nomer_zachetki)
{
    int exist = 0;
    for (int i = 0; i < *size; i++){
        if (table[i].nomer == nomer_zachetki){
            printf("Данные студента с заданным номером: \n");
            exist = 1;
            printf("----------------\nФамилия: %s\nНомер зачетной книжки: %d\nФакультет: %s\nНомер группы: %d\n", table[i].surname, table[i].nomer, table[i].faculty, table[i].group);
        }
    }
    if (exist == 0) printf("Ничего не найдено!\n");
}

void sorting(struct Node table[], int *size) // сортировка пузырьком (возрастание) по номеру зачётки 
{
    for (int i = 0; i < *size - 1; i++){
        for (int j = 0; j < *size - 1 - i; j++){
            if (table[j].nomer > table[j+1].nomer){
                struct Node temp = table[j];
                table[j] = table[j+1];
                table[j+1] = temp;
            }
        }
    }
}

void change(struct Node table[], int index, int *size, int *group){ // изменить группу студента
    if (index < 0 || index >= *size){
        printf("Неверный индекс!\n");
        return;
    }
    table[index].group = *group;
    printf("У студента %s изменена группа на %d\n", table[index].surname, table[index].group);
}

void count_groupsize(struct Node table[], int* size, int *group){ 
    int counter = 0, sum = 0;
    for (int i = 0; i < *size; i++){
        if (table[i].group == *group){
            counter++;
            sum += table[i].nomer; 
        }
    }
    if (counter == 0) {
        printf("Нет записей для указанной группы!\n");
    }
    else printf("Не знаю зачем, но средний номер зачётной книжки для указанной группы: %d %.2f\n", *group, (float)sum/counter);
}



void menu(){
    int exit = 0, size = 0, nomber, index, group;
    struct Node table[MAX_SIZE];
	int symbol;
    while (exit != 1){
        printf("\nМеню:\n");
        printf("1. Ввод записи таблицы с клавиатуры\n");
        printf("2. Загрузка таблицы из файла\n");
        printf("3. Сохранение таблицы в файл\n");
        printf("4. Просмотр таблицы\n");
        printf("5. Сортировка таблицы по номеру зачётки\n");
        printf("6. Поиск в таблице\n");
        printf("7. Удаление записи\n");
        printf("8. Изменение (редактирование) группы студента\n");
        printf("9. Вычисление с проверкой и использованием всех записей по заданному условию\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &symbol);
        switch (symbol) {
            case 1:
                system("clear");
                if (size < MAX_SIZE) {
                    insert(&(table[size]));
                    size++;
                    printf("Запись добавлена.\n");
                } else {
                    printf("Достигнуто максимальное количество записей.\n");
                }
                //system("pause > null");
                break;
            
            case 2:
                system("clear");
                printf("Введите имя файла для загрузки: ");
                char filename[50];
                scanf("%s", filename);
                size = read_from_file(table, filename);
                if (size > 0) {
                    printf("Таблица загружена из файла.\n");
                }
                
                //system("pause > null");
                break;
            
            case 3:
                system("clear");
                write_to_file(table, &size);
                //system("pause > null");
                break;
            
            case 4:
                system("clear");
                output(table, &size);
                //system("pause > null");
                break;
            
            case 5:
                system("clear");
                sorting(table, &size);
                printf("Таблица отсортирована по возрастанию номера зачётки!\n");
                //system("pause > null");
                break;
            
            case 6:
                system("clear");
                printf("Введите значение номера зачётки для поиска: ");
                scanf("%d", &nomber);
                search_nomer(table, &size, nomber);
                //system("pause > null");
                break;
            
            case 7:
                system("clear");
                printf("Введите индекс записи для удаления: ");
                scanf("%d", &index);
                delete(table, index, &size);
                //system("pause > null");
                break;
            
            case 8:
                system("clear");
                printf("Введите индекс записи и саму группу для редактирования группы студента : ");
                scanf("%d %d", &index, &group);
                change(table, index, &size, &group);
                //system("pause > null");
                break;
            
            case 9:
                system("clear");
                printf("Введите номер группы для вычисления: ");
                scanf("%d", &group);
                count_groupsize(table, &size, &group);
                //system("pause > null");
                break;
            
            case 0:
                system("clear");
                exit = 1;
                printf("Программа завершена.\n");
                //system("pause > null");
                break;
            
            default:
                system("clear");
                printf("Некорректный выбор.\n");
                //system("pause > null");
                break;
         }
    }
 }   

int main(){
    menu();
    return 0;
}
