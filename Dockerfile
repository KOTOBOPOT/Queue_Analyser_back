# Base image
FROM ubuntu:latest
FROM reo7sp/tgbot-cpp

# Устанавливаем зависимости
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    git \
    cmake \
    libsqlite3-dev \
    libboost-all-dev \
    libgtest-dev \
    libgtk2.0-dev \
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    python3-opencv \
    libopencv-dev \
    nlohmann-json3-dev

# Копируем файлы проекта внутрь образа
COPY . /app

# Устанавливаем рабочую директорию
WORKDIR /app

# Собираем и устанавливаем проект
RUN mkdir build && cd build && cmake .. && make

# Запускаем приложение при запуске контейнера
CMD echo "./build/tgBot &\n./build/queueAnalyser\n./build/start_server" | bash

