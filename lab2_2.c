//Импорт библиотек
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CARS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    char color[MAX_NAME_LENGTH];
    char bodyType[MAX_NAME_LENGTH];
} Car;

Car cars[MAX_CARS];
int carCount = 0;

int car_exists(const Car *newCar) {
    for (int i = 0; i < carCount; i++) {
        if (strcmp(cars[i].name, newCar->name) == 0 &&
            strcmp(cars[i].color, newCar->color) == 0 &&
            strcmp(cars[i].bodyType, newCar->bodyType) == 0) {
            return 1;
        }
    }
    return 0;
}

Car* find_car_by_name_color_bodytype(const char *name, const char *color, const char *bodyType) {
    for (int i = 0; i < carCount; i++) {
        if (strcmp(cars[i].name, name) == 0 &&
            strcmp(cars[i].color, color) == 0 &&
            strcmp(cars[i].bodyType, bodyType) == 0) {
            return &cars[i];
        }
    }
    return NULL;
}

void read_input(char *buffer, size_t size, const char *prompt) {
    do {
        printf("%s", prompt);
        fflush(stdout); // Очистка буфера вывода
        if (fgets(buffer, size, stdin) == NULL) {
            // Обработка ошибки чтения
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        // Удаляем символ новой строки, если он присутствует
        buffer[strcspn(buffer, "\n")] = 0;
    } while (strlen(buffer) == 0);
}

void addCar() {
    if (carCount >= MAX_CARS) {
        printf("Невозможно добавить больше машин.\n");
        return;
    }

    Car newCar;
    read_input(newCar.name, MAX_NAME_LENGTH, "Введите название машины: ");
    read_input(newCar.color, MAX_NAME_LENGTH, "Введите цвет машины: ");
    read_input(newCar.bodyType, MAX_NAME_LENGTH, "Введите тип кузова машины: ");

    if (car_exists(&newCar)) {
        printf("Данная машина уже добавлена.\n");
        return;
    }

    cars[carCount++] = newCar;
    printf("Машина добавлена.\n");
}

void deleteCar() {
    char name[MAX_NAME_LENGTH];
    char color[MAX_NAME_LENGTH];
    char bodyType[MAX_NAME_LENGTH];
    read_input(name, MAX_NAME_LENGTH, "Введите название машины для удаления: ");
    read_input(color, MAX_NAME_LENGTH, "Введите цвет машины для удаления: ");
    read_input(bodyType, MAX_NAME_LENGTH, "Введите тип кузова машины для удаления: ");

    Car *car = find_car_by_name_color_bodytype(name, color, bodyType);
    if (car) {
        for (int i = 0; i < carCount; i++) {
            if (&cars[i] == car) {
                for (int j = i; j < carCount - 1; j++) {
                    cars[j] = cars[j + 1];
                }
                carCount--;
                printf("Машина удалена.\n");
                return;
            }
        }
    } else {
        printf("Машина не найдена.\n");
    }
}

int color_exists_for_name_bodytype(const char *name, const char *color, const char *bodyType) {
    for (int i = 0; i < carCount; i++) {
        if (strcmp(cars[i].name, name) == 0 &&
            strcmp(cars[i].bodyType, bodyType) == 0 &&
            strcmp(cars[i].color, color) == 0) {
            return 1;
        }
    }
    return 0;
}

int editCar(const char *name, const char *color, const char *bodyType, const char *newColor) {
    Car *car = find_car_by_name_color_bodytype(name, color, bodyType);
    if (car) {
        if (color_exists_for_name_bodytype(name, newColor, bodyType)) {
            printf("Характеристики совпадают с машиной в базе, невозможно присвоить цвет.\n");
            return 0; // Редактирование не удалось
        }
        strcpy(car->color, newColor);
        // Тип кузова не редактируется
        printf("Тип кузова нельзя редактировать.\n");
        printf("Машина отредактирована.\n");
        return 1; // Редактирование удалось
    } else {
        printf("Машина не найдена.\n");
        return 0; // Редактирование не удалось
    }
}

void searchCar() {
    char name[MAX_NAME_LENGTH];
    char color[MAX_NAME_LENGTH];
    char bodyType[MAX_NAME_LENGTH];
    read_input(name, MAX_NAME_LENGTH, "Введите название машины для поиска: ");
    read_input(color, MAX_NAME_LENGTH, "Введите цвет машины для поиска: ");
    read_input(bodyType, MAX_NAME_LENGTH, "Введите тип кузова машины для поиска: ");

    Car *car = find_car_by_name_color_bodytype(name, color, bodyType);
    if (car) {
        printf("Машина найдена:\nНазвание: %s\nЦвет: %s\nТип кузова: %s\n", car->name, car->color, car->bodyType);
    } else {
        printf("Машина не найдена.\n");
    }
}

void listCars() {
    if (carCount == 0) {
        printf("Список машин пуст.\n");
        return;
    }

    printf("Список всех машин:\n");
    for (int i = 0; i < carCount; i++) {
        printf("Название: %s, Цвет: %s, Тип кузова: %s\n", cars[i].name, cars[i].color, cars[i].bodyType);
    }
}

int main() {
    int choice;
    char input[10];
    do {
        printf("\nМеню:\n");
        printf("1. Добавить машину\n");
        printf("2. Удалить машину\n");
        printf("3. Редактировать машину\n");
        printf("4. Поиск машины\n");
        printf("5. Вывести список всех машин\n");
        printf("0. Выйти\n");
        printf("Выберите опцию: ");
        fflush(stdout); // Очистка буфера вывода

        while (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, "%d", &choice) != 1 || choice < 0 || choice > 5) {
            printf("Неверный выбор. Пожалуйста, выберите команду из меню: ");
            fflush(stdout); // Очистка буфера вывода
        }

        switch (choice) {
            case 1:
                addCar();
                break;
            case 2:
                deleteCar();
                break;
            case 3:
                char name[MAX_NAME_LENGTH];
                char color[MAX_NAME_LENGTH];
                char bodyType[MAX_NAME_LENGTH];
                read_input(name, MAX_NAME_LENGTH, "Введите название машины для редактирования: ");
                read_input(color, MAX_NAME_LENGTH, "Введите цвет машины для редактирования: ");
                read_input(bodyType, MAX_NAME_LENGTH, "Введите тип кузова машины для редактирования: ");
                char newColor[MAX_NAME_LENGTH];
                read_input(newColor, MAX_NAME_LENGTH, "Введите новый цвет машины: ");
                editCar(name, color, bodyType, newColor);
                break;
            case 4:
                searchCar();
                break;
            case 5:
                listCars();
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
