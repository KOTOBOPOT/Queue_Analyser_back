# Queue Analyser 
Queue Analyser- программа, анализирующая количество человек в очереди в различных местах(в частности в столовых)
## Конфигурация проекта под ОС Ubuntu
Проект использует систему сборки CMake
> Данный проект использует библиотеки: Boost/Beast и Boost/Asio, opencv2/opencv и работу с базой данных. Они должны быть предустановлены. Для успешной компиляции и запуска проекта необходимо установить эти библиотеки

### Для тестирования используются GTest. Установка
```
sudo apt-get install libgtest-dev cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```
### Сборка проекта
```
mkdir build
cd ./build 
cmake .. 
make
```
### Запуск программы
> Вы находитесь в директории build
```
./queueAnalyser
```
### Запуск тестов 
> Вы находитесь в директории build
```
ctest
```

