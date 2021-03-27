target_sources(${TARGET}
        PRIVATE
        main.cpp

        Animator.h
        Animator.cpp
        InputManager.h
        InputManager.cpp
        Factory.h
        Factory.cpp
        Game.h
        Game.cpp
        GameConfig.h
        GameConfig.cpp
        Entity.h
        Entity.cpp
        ResourceManager.h
        ResourceManager.cpp
        SceneManager.h
        SceneManager.cpp
        GameStats.h
        GameStats.cpp
        Observer.h
        Score.h
        Score.cpp
        ScoreHUD.h
        ScoreHUD.cpp
        Subject.h

        StateMachine/AbsGameState.h
        StateMachine/AbsGameState.cpp
        StateMachine/GameStateMachine.h
        StateMachine/GameStateMachine.cpp
        StateMachine/InitState.h
        StateMachine/InitState.cpp
        StateMachine/MenuState.h
        StateMachine/MenuState.cpp
        StateMachine/PlayState.h
        StateMachine/PlayState.cpp
        StateMachine/GameOverState.h
        StateMachine/GameOverState.cpp

        Entities/Background.h
        Entities/Background.cpp
        Entities/Block.h
        Entities/Block.cpp
        Entities/Bullet.h
        Entities/EmeraldEnemy.h
        Entities/EmeraldEnemy.cpp
        Entities/Enemy.h
        Entities/Enemy.cpp
        Entities/Emerald.h
        Entities/Emerald.cpp
        Entities/FireBall.h
        Entities/FireBall.cpp
        Entities/FireEnemy.h
        Entities/FireEnemy.cpp
        Entities/Fire.h
        Entities/Fire.cpp
        Entities/HamonEnemy.h
        Entities/HamonEnemy.cpp
        Entities/Hero.h
        Entities/Hero.cpp
        Entities/Knife.h
        Entities/Knife.cpp
        Entities/Obstacle.h
        Entities/Platform.h
        Entities/Platform.cpp
        Entities/PowerUp.h
        Entities/Shield.h
        Entities/Shield.cpp
        Entities/Weapon.h
        Entities/Weapon.cpp

        Widgets/Widget.h
        Widgets/Widget.cpp
        Widgets/ImageWidget.h
        Widgets/ImageWidget.cpp
        Widgets/ShapeWidget.h
        Widgets/ShapeWidget.cpp
        Widgets/TextWidget.h
        Widgets/TextWidget.cpp
        )

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
