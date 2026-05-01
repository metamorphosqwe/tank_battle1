# Makefile для игры "Танковый бой"
# Компиляция: make
# Очистка: make clean
# Запуск: ./tank_battle

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = tank_battle

# Исходные файлы
SRCS = main.cpp menu.cpp game_state.cpp field.cpp player.cpp enemy.cpp projectile.cpp collision.cpp io_requests.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Компиляция исходных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

# Зависимости
main.o: main.cpp menu.h game_state.h
menu.o: menu.cpp menu.h game_state.h
game_state.o: game_state.cpp game_state.h field.h player.h enemy.h projectile.h collision.h
field.o: field.cpp field.h game_constants.h
player.o: player.cpp player.h projectile.h enemy.h
enemy.o: enemy.cpp enemy.h projectile.h
projectile.o: projectile.cpp projectile.h
collision.o: collision.cpp collision.h projectile.h enemy.h player.h
io_requests.o: io_requests.cpp io_requests.h

.PHONY: all clean
