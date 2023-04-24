# Подготовка к работе с SQLite C++ API

В библиотеку включена директория ```database/sqlite-autoconf-3410200```

Перед первой компиляцией библиотеки требуется установить SQLite и подготовить его к работе с C++

Для этого запустите следующие команды в командной строке:
```shell
cd /lib/database_handler/database/sqlite-autoconf-3410200
./configure
make
sudo make install
make distclean
```

После этого программа должна корректно компилироваться.