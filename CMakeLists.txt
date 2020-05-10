cmake_minimum_required(VERSION 3.15)
project(JoJo_Run)

set(CMAKE_CXX_STANDARD 11)
add_executable(JoJo_Run ../../../../Desktop/JoJo_Run/main.cpp ../../../../Desktop/JoJo_Run/Hero.h ../../../../Desktop/JoJo_Run/Hero.cpp ../../../../Desktop/JoJo_Run/Observer.h ../../../../Desktop/JoJo_Run/Subject.h ../../../../Desktop/JoJo_Run/Block.h ../../../../Desktop/JoJo_Run/Block.cpp ../../../../Desktop/JoJo_Run/FireWall.h ../../../../Desktop/JoJo_Run/FireWall.cpp ../../../../Desktop/JoJo_Run/ScoreHUD.h ../../../../Desktop/JoJo_Run/ScoreHUD.cpp ../../../../Desktop/JoJo_Run/Map.h ../../../../Desktop/JoJo_Run/Map.cpp ../../../../Desktop/JoJo_Run/Factory.h ../../../../Desktop/JoJo_Run/Factory.cpp ../../../../Desktop/JoJo_Run/Enemy.h ../../../../Desktop/JoJo_Run/Enemy.cpp ../../../../Desktop/JoJo_Run/EmeraldEnemy.h ../../../../Desktop/JoJo_Run/EmeraldEnemy.cpp ../../../../Desktop/JoJo_Run/HamonEnemy.h ../../../../Desktop/JoJo_Run/HamonEnemy.cpp ../../../../Desktop/JoJo_Run/FireEnemy.h ../../../../Desktop/JoJo_Run/FireEnemy.cpp ../../../../Desktop/JoJo_Run/Shield.h ../../../../Desktop/JoJo_Run/Shield.cpp ../../../../Desktop/JoJo_Run/Knife.h ../../../../Desktop/JoJo_Run/Knife.cpp ../../../../Desktop/JoJo_Run/PowerUp.cpp ../../../../Desktop/JoJo_Run/PowerUp.h)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()