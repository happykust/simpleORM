# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM gcc:latest as build

WORKDIR /orm-test

RUN apt-get update && apt-get install -y libboost-dev default-libmysqlclient-dev libmysqlcppconn-dev libgtest-dev cmake

# Скопируем директорию /src в контейнер
ADD . /app/src

# Установим рабочую директорию для сборки
WORKDIR /app/build

RUN g++ -Wall -I/usr/include/cppconn -o main ../src/main.cpp -L/usr/lib -lmysqlcppconn

# Выполним сборку и запуск
CMD ["./main"]
