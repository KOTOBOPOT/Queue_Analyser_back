## Конфигурация проекта под ОС Ubuntu
> Данный проект использует библиотеки Boost/Beast и Boost/Asio для работы с сетевыми протоколами. Для успешной компиляции и запуска проекта необходимо установить эти библиотеки.

### Установка библиотек
#### Установка Boost/Beast и Boost/Asio для Ubuntu
Вы можете установить библиотеки Boost/Beast и Boost/Asio из официального репозитория Ubuntu с помощью следующей команды в терминале:
```shell
sudo apt-get install libboost-all-dev
```

#### Установка Boost/Beast и Boost/Asio для MacOS
Для установки библиотек с помощью командной строки на MacOS потребуется менеджер пакетов Brew.
```shell
brew install boost
```

#### Сборка и установка Boost/Beast и Boost/Asio из исходного кода
Вы можете также собрать и установить библиотеки Boost/Beast и Boost/Asio из исходного кода. Для этого необходимо выполнить следующие шаги:

1. Скачайте исходный код библиотек с официального сайта Boost (https://www.boost.org/users/download/).

2. Распакуйте архив с исходным кодом библиотек.

3. Перейдите в директорию с распакованным исходным кодом и выполните следующие команды:
```
./bootstrap.sh --prefix=/usr/local
./b2
sudo ./b2 install
```
Эти команды соберут и установят библиотеки Boost/Beast и Boost/Asio в систему.Эти команды соберут и установят библиотеки Boost/Beast и Boost/Asio в систему.