[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

[![GitHub forks](https://img.shields.io/github/forks/NikolayNetreba/Task2)](https://github.com/NikolayNetreba/Task2/network/members)
[![GitHub stars](https://img.shields.io/github/stars/NikolayNetreba/Task2)](https://github.com/NikolayNetreba/Task2/stargazers)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/NikolayNetreba/Task2)](https://github.com/NikolayNetreba/Task2/pulls)
[![GitHub last commit](https://img.shields.io/github/last-commit/NikolayNetreba/Task2)](https://github.com/NikolayNetreba/Task2/commits/main)
# Task Onegin
![alt text](image-1.png)

# Постановка задачи:
1. Считать текс из файла максимально эффективным способом
2. Отсортировать текст в алфавитном порядке без учета небуквенных символов (пробелы, знаки препинания, цифры, спецсимволы)
   1. Слева на право
   2. Справа на лево
3. Вывести отсортированный текст + исходник

# Общая архитектура
Основная логика алгоритма находится в ```onegin.cpp```. ```uSort.cpp``` - собственная реализация qsort, которая полностью повторяет логику библиотечной функции. ```TXLibe.cpp``` - Нужен для прекомпилированния библиотеки. [TXLibe.h](http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/) - маленькая, да удаленькая библиотечка, которую я использую для отлова ошибок во время компиляции.
```text
.
├── preparatory_tasks
|
├── colors.h
├── onegin.h
├── uSort.h
|
├── onegin.cpp
├── uSort.cpp
└── TXLibe.cpp
```

# Алгоритм решения
1. Узнаем размер файла при помощи ```fstat()```, выделяя под него буфер.
2. Считываем из файла одним запросом при помощи ```read()```
3. Индексируем массив для сортировки
4. Сортируем алгоритмом QuickSort с использованием собственных компараторов и собственной реализации этого алгоритма. Первая сортировка происходит собственно реализованным алгоритмом, вторая сортировка происходит с помощью библиотечной функции qsort.
5. Выводим в ```stdout```

# Компиляция и запуск
Сначала необходимо скомпилировать ```TXLibe.cpp```:

```g++ TXLibe.cpp -c TXLibe.o```

Потом скомпилировать саму программу:

```g++ onegin.cpp uSort.cpp TXLibe.o```

И наконец запустить с выводом в файл:

```.\a.exe > output.txt```

Также можно указать файл из которого будут считывать на моменте компиляции: ```.\a.exe onegi.txt > output.txt```

# Фичи
1. Если файла не существует, то программа не упадет, а попросит еще раз ввести имя файла.
2. ```free_struct_text``` - функцию очистки структуры
3. ```fill_str_count``` - функция для подсчета строк по разделителю
4. ```colors.h``` - моя библиотечка для красивого вывода.

# colors.h
### Возможные цвета:
```cpp
MAKE_RED(A)
MAKE_GREEN(A)
MAKE_YELLOW(A)
MAKE_BLUE(A)
MAKE_MAGENTA(A)
MAKE_CYAN(A)
```
Пример использования:
```cpp
fprintf(stderr, MAKE_YELLOW("Enter the file name:"));
```

# Благодарности
[Mrksist](https://github.com/Mrksist) - за пример хорошей README

[Деду](https://wiki.mipt.tech/index.php/%D0%94%D0%B5%D0%B4%D0%B8%D0%BD%D1%81%D0%BA%D0%B8%D0%B9_%D0%98%D0%BB%D1%8C%D1%8F_%D0%A0%D1%83%D0%B4%D0%BE%D0%BB%D1%8C%D1%84%D0%BE%D0%B2%D0%B8%D1%87) - за работу


