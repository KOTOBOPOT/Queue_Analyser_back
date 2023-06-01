# Подготовка к работе с SQLite C++ API

В библиотеку включена директория ```database/sqlite-autoconf-3410200```

Перед первой компиляцией библиотеки требуется установить SQLite и подготовить его к работе с C++

Для загрузки SQLite вызовите следующие команды из корневой папки проекта:
```shell
cd lib/database_handler/database/
curl --output sqlite-autoconf.tar.gz https://www.sqlite.org/2023/sqlite-autoconf-3410200.tar.gz
tar -xzf sqlite-autoconf.tar.gz 
cd sqlite-autoconf-3410200
```

Для установки SQLite вызовите эти команды из папки ```sqlite-autoconf-3410200```:
```shell
./configure
make
sudo make install
```

Наконец, для удаления промежуточных файлов вызовите:
```shell
make distclean
rm sqlite-autoconf.tar.gz
```

> **Примечание**: последние 7 цифр в названии загружаемого пакета – это версия библиотеки. Она может меняться, поэтому
если команда загрузки не запускается, смотрите актуальную версию на [сайте SQLite](https://www.sqlite.org/download.html). 

После этого программа должна корректно компилироваться.