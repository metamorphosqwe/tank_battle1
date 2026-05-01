cmake_minimum_required(VERSION 3.10)
project(TankBattle VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Исходные файлы игры
set(SOURCES
    main.cpp
    menu.cpp
    game_state.cpp
    field.cpp
    player.cpp
    enemy.cpp
    projectile.cpp
    collision.cpp
    io_requests.cpp
)

# Заголовочные файлы
set(HEADERS
    game_constants.h
    menu.h
    game_state.h
    field.h
    player.h
    enemy.h
    projectile.h
    collision.h
    io_requests.h
)

# Создание исполняемого файла
add_executable(tank_battle ${SOURCES} ${HEADERS})

# Настройки компиляции
target_compile_options(tank_battle PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Wall -Wextra -pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /permissive->
)

# Для Windows подключаем дополнительные библиотеки
if(WIN32)
    target_link_libraries(tank_battle PRIVATE winmm)
endif()

# Установка целевой директории
set_target_properties(tank_battle PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
