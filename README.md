# Useful Classes — коллекция полезных классов на C++

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![PostgreSQL](https://img.shields.io/badge/PostgreSQL-16-336791.svg)](https://www.postgresql.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

## 📋 О проекте

Проект представляет собой коллекцию переиспользуемых классов на C++ для различных задач:

- **Математические структуры**: длинная арифметика, матрицы
- **Структуры данных**: бинарное дерево поиска, графы
- **Сетевые приложения**: эхо-сервер, чат, HTTP-сервер, прокси-сервер, файловый сервер
- **Базы данных**: классы-обёртки для работы с PostgreSQL
- **Криптография**: MD5, SHA-256, RSA, факторизация Ферма
- **Тестирование**: модульные тесты для всех компонентов

## 🏗️ Структура проекта
Useful-classes/
├── include/
│ ├── algoritms/ # Криптографические алгоритмы
│ │ ├── md5.hpp
│ │ ├── sha256.hpp
│ │ ├── rsa.hpp
│ │ └── fermat_factorization.hpp
│ ├── structs/ # Структуры данных
│ │ ├── LongNumber.hpp
│ │ ├── Matrix.hpp
│ │ ├── Graph.hpp
│ │ └── BinarySearchTree.hpp
│ ├── networks/ # Сетевые классы
│ │ ├── database/
│ │ │ ├── Database.hpp
│ │ │ ├── EchoDatabase.hpp
│ │ │ ├── ChatDatabase.hpp
│ │ │ ├── FileDatabase.hpp
│ │ │ ├── HttpDatabase.hpp
│ │ │ └── ProxyDatabase.hpp
│ │ ├── EchoServer.hpp
│ │ ├── ChatServer.hpp
│ │ ├── FileServer.hpp
│ │ ├── HttpServer.hpp
│ │ └── ProxyServer.hpp
│ ├── Generator.hpp # Генераторы тестовых данных
│ └── tests.hpp # Заголовки тестов
├── src/
│ ├── algoritms/ # Реализации алгоритмов
│ ├── structs/ # Реализации структур
│ ├── networks/
│ │ ├── database/ # Реализации классов БД
│ │ └── server/ # Реализации серверов
│ ├── tests.cpp # Модульные тесты
│ └── main.cpp # Точка входа
└── CMakeLists.txt # Конфигурация сборки

## 🚀 Быстрый старт

### Требования

- C++17 совместимый компилятор (g++ 9+, clang 10+, MSVC 2019+)
- CMake 3.10+
- PostgreSQL 14+ (для работы с базами данных)
- libpq-dev (клиентская библиотека PostgreSQL)

### Установка PostgreSQL (Ubuntu)

```bash
sudo apt update
sudo apt install postgresql postgresql-contrib libpq-dev
Сборка проекта
bash
git clone https://github.com/3qupo/Useful-classes.git
cd Useful-classes
mkdir build && cd build
cmake ..
make
```


### Настройка базы данных
```sql
-- Создание баз данных для проектов
CREATE DATABASE echo_db;
CREATE DATABASE chat_db;
CREATE DATABASE file_db;
CREATE DATABASE http_db;
CREATE DATABASE proxy_db;

-- Создание таблиц для EchoDatabase
\c echo_db
CREATE TABLE clients (
    id SERIAL PRIMARY KEY,
    ip_address VARCHAR(45) NOT NULL UNIQUE,
    first_seen TIMESTAMP DEFAULT NOW(),
    last_seen TIMESTAMP DEFAULT NOW(),
    request_count INT DEFAULT 0
);

CREATE TABLE logs (
    id SERIAL PRIMARY KEY,
    client_id INT NOT NULL REFERENCES clients(id) ON DELETE CASCADE,
    message TEXT NOT NULL,
    message_length INT,
    created_at TIMESTAMP DEFAULT NOW()
);

-- Аналогично для остальных БД (см. документацию)
```

### Запуск тестов
```bash
cd build
./tests           # Запуск всех тестов
./main            # Запуск основной программы
```

### 📚 Классы и их назначение
#### Математические структуры
##### LongNumber
Длинная арифметика с поддержкой:

- Сложение, вычитание, умножение, деление, остаток
- Сравнение чисел
- Преобразование из строки

```cpp
LongNumber a("12345678901234567890");
LongNumber b("98765432109876543210");
LongNumber c = a + b;
```

##### Matrix
Матрица целых чисел с операциями:

- Сложение, вычитание, умножение матриц
- Умножение на число
- Транспонирование

```cpp
Matrix m1(3, 3);
Matrix m2(3, 3);
Matrix result = m1 * m2;
``` 

#### Криптографические алгоритмы
##### MD5
128-битное хеширование (для контрольных сумм, не для безопасности!)

```cpp
MD5 md5;
md5.update("Hello, World!");
std::cout << md5.hexdigest() << std::endl;  // 32 hex символа
```

##### RSA
Асимметричное шифрование (генерация ключей, шифрование/дешифрование)

```cpp
RSA rsa(512);
LongNumber encrypted = rsa.encrypt(LongNumber("42"));
LongNumber decrypted = rsa.decrypt(encrypted);
```

#### Сетевые классы и базы данных
##### Database
Базовый класс для работы с PostgreSQL:

- Подключение к БД
- Выполнение SQL-запросов
- Экранирование строк (защита от SQL-инъекций)

``` cpp
Database db;
db.connect("localhost", "5432", "my_db", "postgres", "1234");
db.executeQuery("INSERT INTO users (name) VALUES ('Alice')");
```

##### EchoDatabasey
Логирование запросов эхо-сервера:

- Сохранение IP и сообщения
- Получение последних сообщений

```cpp
EchoDatabase db;
db.logMessage("127.0.0.1", "Hello, Server!");
auto messages = db.getRecentMessage(10);
```

##### ChatDatabase
Хранение сообщений чата:

- Пользователи, комнаты
- Отправка и получение сообщений
- Управление участниками комнат

### 🔧 Конфигурация
#### Настройка подключения к БД
В файле main.cpp укажите параметры подключения:

```cpp
db.connect("localhost", "5433", "my_own_db", "postgres", "1234");
``` 

Параметры:

- host — адрес сервера БД
- port — порт (обычно 5432 или 5433)
- dbname — имя базы данных
- user — имя пользователя
- password — пароль

#### Настройка компиляции
В CMakeLists.txt указаны основные флаги:

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
target_link_libraries(main pq)  # libpq для PostgreSQL
```

### 🧪 Тестирование
Запуск всех тестов:

```bash
cd build && ctest
```

Или вручную:

```bash
./tests
```

Тесты покрывают:

- Корректность математических операций
- Работу с БД
- Криптографические алгоритмы
- Граничные случаи


### 👨‍💻 Автор
Andrei (3qupo)