target_sources(${TARGET}
        PRIVATE
        main.cpp
        AnimationManager.h
        AnimationManager.cpp
        CollisionManager.h
        CollisionManager.cpp
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
        ScoreManager.h
        ScoreManager.cpp
        ScoreHUD.h
        ScoreHUD.cpp
        SoundManager.h
        SoundManager.cpp
        Subject.h
        )

add_subdirectory(StateMachine)
add_subdirectory(Entities)
add_subdirectory(Widgets)


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
