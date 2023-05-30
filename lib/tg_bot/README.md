### Установка библиотек
1. Установка и компиляция telegram-api для С++
```  
sudo apt-get install libboost-all-dev libssl-dev nlohmann-json3-dev
git clone https://github.com/reo7sp/tgbot-cpp.git ./lib/tg_bot/lib/tg_bot_api
cd ./lib/tg_bot/lib/tg_bot_api
cmake .  
make -j4
sudo make install
```

### Запуск бота
Для запуска бота в `configs` требуктся добавить файл `tg_bot_token.json` вида
```
{ "token": "<Токен телеграм бота>" }
```