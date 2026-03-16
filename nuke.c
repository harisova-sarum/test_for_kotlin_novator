#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Проверяем, ввел ли пользователь аргументы
    if (argc != 3) {
        printf("Нужно ввести имя файла и радиус!\n");
        return 1;
    }

    // Открываем файл
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Не удалось открыть файл\n");
        return 1;
    }

    // Читаем радиус из второго аргумента
    int r = atoi(argv[2]);

    // Создаем два массива для координат X и Y (максимум 100*100 целей)
    int targetX[10000];
    int targetY[10000];
    int totalTargets = 0;

    // Читаем файл построчно, пока не кончатся данные
    while (fscanf(f, "%d,%d", &targetX[totalTargets], &targetY[totalTargets]) != EOF) {
        totalTargets++;
    }
    fclose(f);

    int bestX = 0;
    int bestY = 0;
    int maxKilled = -1;

    // Проверяем каждую возможную клеточку на поле от 0 до 99
    for (int x = 0; x <= 99; x++) {
        for (int y = 0; y <= 99; y++) {
            
            int currentKilled = 0;

            // Для каждой клеточки смотрим, сколько целей в нее попало
            for (int i = 0; i < totalTargets; i++) {
                int dx = x - targetX[i];
                int dy = y - targetY[i];
                
                // Считаем расстояние по теореме Пифагора: a*a + b*b = c*c
                // Если расстояние до цели меньше или равно радиусу, она уничтожена
                if (dx * dx + dy * dy <= r * r) {
                    currentKilled = currentKilled + 1;
                }
            }

            // Если в этой точке убили больше, чем раньше — запоминаем её
            if (currentKilled > maxKilled) {
                maxKilled = currentKilled;
                bestX = x;
                bestY = y;
            }
        }
    }

    // Выводим результат на экран
    printf("Координаты запуска: %d, %d\n", bestX, bestY);
    printf("Количество пораженных целей: %d\n", maxKilled);

    return 0;
}