target_sources(${TARGET}
        PRIVATE
        AbsGameState.h
        AbsGameState.cpp
        Block.h
        Block.cpp
        EmeraldEnemy.h
        EmeraldEnemy.cpp
        Enemy.h
        Enemy.cpp
        Factory.h
        Factory.cpp
        FireEnemy.h
        FireEnemy.cpp
        FireWall.h
        FireWall.cpp
        GameConfig.h
        GameConfig.cpp
        Game.h
        Game.cpp
        GameStateMachine.h
        GameStateMachine.cpp
        GameOverState.h
        GameOverState.cpp
        HamonEnemy.h
        HamonEnemy.cpp
        Hero.h
        Hero.cpp
        InitState.h
        InitState.cpp
        Knife.h
        Knife.cpp
        main.cpp
        Map.h
        Map.cpp
        Observer.h
        PlayState.h
        PlayState.cpp
        PowerUp.h
        PowerUp.cpp
        ScoreHUD.h
        ScoreHUD.cpp
        Shield.h
        Shield.cpp
        Subject.h)

target_include_directories(${TARGET}
        PUBLIC
        ${CMAKE_SOURCE_DIR}/Src
        ${SFML_INCLUDE_DIR}
#        ${OPENGL_INCLUDE_DIRS}
#        ${GLUT_INCLUDE_DIRS}
#        ${GLEW_INCLUDE_DIRS}
        )

target_link_libraries(
        ${TARGET}
        ${SFML_AUDIO_LIBRARY_DYNAMIC_RELEASE}
        ${SFML_GRAPHICS_LIBRARY_DYNAMIC_RELEASE}
        ${SFML_WINDOW_LIBRARY_DYNAMIC_RELEASE}
        ${SFML_SYSTEM_LIBRARY_DYNAMIC_RELEASE}
        ${SFML_NETWORK_LIBRARY_DYNAMIC_RELEASE}
#        ${OPENGL_LIBRARIES}
#        ${GLUT_LIBRARIES}
#        ${GLEW_LIBRARIES}
)
