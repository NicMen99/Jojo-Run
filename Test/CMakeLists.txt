project(unittest)

message("" ${CMAKE_CURRENT_LIST_DIR})
message("" ${CMAKE_CURRENT_SOURCE_DIR})
message("" ${CMAKE_SOURCE_DIR})

set(GOOGLETEST_VERSION 1.10.1)

add_subdirectory(googletest)

add_executable(testrunner "" )

target_sources(testrunner
        PUBLIC
        runner.cpp
        # add test files here
        EntityTest.cpp
)

#
# Source code
#

target_sources(testrunner
        PRIVATE
        ${CMAKE_SOURCE_DIR}/Src
        ${CMAKE_SOURCE_DIR}/Src/AnimationManager.h
        ${CMAKE_SOURCE_DIR}/Src/AnimationManager.cpp
        ${CMAKE_SOURCE_DIR}/Src/CollisionManager.h
        ${CMAKE_SOURCE_DIR}/Src/CollisionManager.cpp
        ${CMAKE_SOURCE_DIR}/Src/InputManager.h
        ${CMAKE_SOURCE_DIR}/Src/InputManager.cpp
        ${CMAKE_SOURCE_DIR}/Src/Factory.h
        ${CMAKE_SOURCE_DIR}/Src/Factory.cpp
        ${CMAKE_SOURCE_DIR}/Src/Game.h
        ${CMAKE_SOURCE_DIR}/Src/Game.cpp
        ${CMAKE_SOURCE_DIR}/Src/GameConfig.h
        ${CMAKE_SOURCE_DIR}/Src/GameConfig.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entity.h
        ${CMAKE_SOURCE_DIR}/Src/Entity.cpp
        ${CMAKE_SOURCE_DIR}/Src/ResourceManager.h
        ${CMAKE_SOURCE_DIR}/Src/ResourceManager.cpp
        ${CMAKE_SOURCE_DIR}/Src/SceneManager.h
        ${CMAKE_SOURCE_DIR}/Src/SceneManager.cpp
        ${CMAKE_SOURCE_DIR}/Src/GameStats.h
        ${CMAKE_SOURCE_DIR}/Src/GameStats.cpp
        ${CMAKE_SOURCE_DIR}/Src/Observer.h
        ${CMAKE_SOURCE_DIR}/Src/ScoreManager.h
        ${CMAKE_SOURCE_DIR}/Src/ScoreManager.cpp
        ${CMAKE_SOURCE_DIR}/Src/ScoreHUD.h
        ${CMAKE_SOURCE_DIR}/Src/ScoreHUD.cpp
        ${CMAKE_SOURCE_DIR}/Src/SoundManager.h
        ${CMAKE_SOURCE_DIR}/Src/SoundManager.cpp
        ${CMAKE_SOURCE_DIR}/Src/Subject.h
        ${CMAKE_SOURCE_DIR}/Src/Widgets/Widget.h
        ${CMAKE_SOURCE_DIR}/Src/Widgets/Widget.cpp
        ${CMAKE_SOURCE_DIR}/Src/Widgets/ImageWidget.h
        ${CMAKE_SOURCE_DIR}/Src/Widgets/ImageWidget.cpp
        ${CMAKE_SOURCE_DIR}/Src/Widgets/ShapeWidget.h
        ${CMAKE_SOURCE_DIR}/Src/Widgets/ShapeWidget.cpp
        ${CMAKE_SOURCE_DIR}/Src/Widgets/TextWidget.h
        ${CMAKE_SOURCE_DIR}/Src/Widgets/TextWidget.cpp
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/AbsGameState.h
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/AbsGameState.cpp
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/GameStateMachine.h
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/GameStateMachine.cpp
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/InitState.h
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/InitState.cpp
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/MenuState.h
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/MenuState.cpp
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/PlayState.h
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/PlayState.cpp
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/GameOverState.h
        ${CMAKE_SOURCE_DIR}/Src/StateMachine/GameOverState.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Background.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Background.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Block.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Block.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Bullet.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/EmeraldEnemy.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/EmeraldEnemy.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Enemy.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Enemy.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Emerald.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Emerald.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/FireBall.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/FireBall.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/FireEnemy.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/FireEnemy.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Fire.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Fire.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/HamonEnemy.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/HamonEnemy.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Hero.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Hero.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Knife.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Knife.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Obstacle.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Platform.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Platform.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/PowerUp.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Shield.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Shield.cpp
        ${CMAKE_SOURCE_DIR}/Src/Entities/Weapon.h
        ${CMAKE_SOURCE_DIR}/Src/Entities/Weapon.cpp
        )

target_include_directories(testrunner
        PUBLIC
        ${CMAKE_SOURCE_DIR}/Src
        )
#
# Googletest reference
#

target_include_directories(testrunner
        PUBLIC
        googletest/include
        googletest
        )

target_link_libraries(testrunner
        gtest
        gtest_main
        ${SFML_AUDIO_LIBRARY_DYNAMIC_RELEASE}
        ${SFML_GRAPHICS_LIBRARY_DYNAMIC_RELEASE}
        ${SFML_WINDOW_LIBRARY_DYNAMIC_RELEASE}
        ${SFML_SYSTEM_LIBRARY_DYNAMIC_RELEASE}
        ${SFML_NETWORK_LIBRARY_DYNAMIC_RELEASE}
        )

#
# Setup
#
file(COPY TestAsset DESTINATION ${CMAKE_BINARY_DIR}/Test)

enable_testing()
include(CTest)
include(Dart)

add_test(EntityTest, positionAssignement)
add_test(EntityTest, positionUpdate)
add_test(EntityTest, positionUpdate2)
add_test(EntityTest, previousPosition)
add_test(EntityTest, startedFlag)
add_test(EntityTest, DestroyedFlagNoTexture)
add_test(EntityTest, DestroyedFlag)
add_test(EntityTest, Bounds)


