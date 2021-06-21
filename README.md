# Переводчик азбуки Морзе

Графическое приложение, созданное с помощью Qt/C++.

### Как начать тестировать у себя?
- Скачиваем себе репозиторий
- Открываем **Qt Creator** не ниже версии 4.15
- Выбираем файл `MorseTranslator.pro`
- Выполняем сборку и запускаем

### Особенности
1) Вводить текст можно только в левое окно.
2) Кодируются только буквы латинского алфавита (заглавные и маленькие) и знаки препинания из множества `{ ',' '.' ';' }`, остальные символы будут потеряны при кодировке! Соответственно, декодировать можно только те же самые символы.
3) Левое поле ввода считается азбукой Морзе до тех пор, пока в нём есть только символы из множества `{ '-' '.' ' ' }`.
4) Один пробел в азбуке Морзе используется для отделения символов слова, два - для отделения слов.
5) Открытие файла вставляет содержимое в левое окно ввода.
6) В результирующий файл будет сохраняться только азбука Морзе (нужное окно с данными определяется автоматически).
7) Под левым окном подсчитывается общее количество введённых символов.
8) Текст из правого окна можно скопировать в буфер обмена.
9) Работа выполнена с использованием Qt Widgets.
10) Реализовано сохранение положения и размеров окна с предыдущей сессии.
11) В окне "О программе" есть мои контактные данные.

К данной работе прилагается видео с демонстрацией работы, однако, процесс выбора/сохранения файлов в нём не виден.