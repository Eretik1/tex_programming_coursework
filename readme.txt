Приложение рассчитано для работы на Windows 10 или выше.
Среда разработки: Visual Studio Code.
Компилятор: GCC 14.2.0.
дополнительные библиотеки: Qt6, CMake. 
Для сборки проекта необходимо клонировать репозиторий 
"https://github.com/Eretik1/tex_programming_coursework.git"
в папку, путь к которой не содержит символов кириллицы.
После клонирования репозитория необходимо перейти в созданную директорию:
    cd tex_programming_coursework
Создать папку build:
    mkdir build && cd build
Запустить cmake:
    cmake ..
Собрать проект:
    cmake --build . --config Release
И запустить программу:
    ./coursework