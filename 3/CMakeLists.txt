cmake_minimum_required(VERSION 3.28)
project(Lab3)

set(CMAKE_CXX_STANDARD 20)
find_package(Catch2 REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/TeamList
        ${CMAKE_CURRENT_SOURCE_DIR}/Team
        ${CMAKE_CURRENT_SOURCE_DIR}/Player
        ${CMAKE_CURRENT_SOURCE_DIR}/Player/Forward
        ${CMAKE_CURRENT_SOURCE_DIR}/Player/Defender
        ${CMAKE_CURRENT_SOURCE_DIR}/Player/Goalkeeper
        ${CMAKE_CURRENT_SOURCE_DIR}/NTP
        ${CMAKE_CURRENT_SOURCE_DIR}/MS_SS
        ${CMAKE_CURRENT_SOURCE_DIR}/SucS_UnSucS
        ${CMAKE_CURRENT_SOURCE_DIR}/Vector
        ${CMAKE_CURRENT_SOURCE_DIR}/Game
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Lab3
        main.cpp
        Player/Player.cpp
        NTP/NTP.cpp
        MS_SS/MS_SS.cpp
        SucS_UnSucS/SucS_UnSucS.cpp
        Player/Defender/Defender.cpp
        Player/Forward/Forward.cpp
        Player/Goalkeeper/Goalkeeper.cpp
        App.cpp
        App.h
)

add_executable(TestMenu
        main.cpp
        Player/Player.cpp
        Player/Defender/Defender.cpp
        Player/Forward/Forward.cpp
        Player/Goalkeeper/Goalkeeper.cpp
        NTP/NTP.cpp
        MS_SS/MS_SS.cpp
        SucS_UnSucS/SucS_UnSucS.cpp
)
add_executable(TestTemlate
        main.cpp
        NTP/NTP.cpp
        MS_SS/MS_SS.cpp
        SucS_UnSucS/SucS_UnSucS.cpp
        Player/Goalkeeper/Goalkeeper.cpp
        Player/Forward/Forward.cpp
        Player/Defender/Defender.cpp
        Player/Player.cpp
        Team/Team.cpp
        TeamList/TeamList.cpp
        Game/Game.cpp
        App.cpp
)

add_executable(AppTest
        App.cpp
        NTP/NTP.cpp
        MS_SS/MS_SS.cpp
        SucS_UnSucS/SucS_UnSucS.cpp
        Player/Goalkeeper/Goalkeeper.cpp
        Player/Forward/Forward.cpp
        Player/Defender/Defender.cpp
        Player/Player.cpp
        Team/Team.cpp
        TeamList/TeamList.cpp
        Game/Game.cpp
        tests/AppTests.cpp
)

target_link_libraries(AppTest Catch2::Catch2WithMain)