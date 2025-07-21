cmake_minimum_required(VERSION 3.19)
project(rpg_v2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(rpg_v2
    WIN32 MACOSX_BUNDLE
    main.cpp


    mainwindow.ui
    room.h
    roomfactory.cpp
    roomfactory.h
    player.cpp
    player.h
    gamewindow.cpp
    gamewindow.h
    equipmentroom.cpp
    equipmentroom.h
    enemy.cpp
    enemy.h
    combatroom.cpp
    combatroom.h
    character.cpp
    character.h
    bossroom.cpp
    bossroom.h
    bonfireroom.cpp
    bonfireroom.h
    storyroom.h storyroom.cpp



)

target_link_libraries(rpg_v2
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS rpg_v2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET rpg_v2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
