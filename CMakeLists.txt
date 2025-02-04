cmake_minimum_required(VERSION 3.16)
project(tanks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/)
message("CMake runtime output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

SET(PTHREAD "-pthread")
SET(GCC_OPTIMIZE "-O2") 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PTHREAD} ${GCC_OPTIMIZE}")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(SQLite3 REQUIRED)

link_libraries(sfml-graphics)
link_libraries(sfml-audio)
link_libraries(sqlite3)

add_executable(model_tests
        model_tests.cpp
        source/model/blocks.cpp
        source/model/entity.cpp
        source/model/game_model.cpp
        source/model/projectile.cpp
        source/model/tank.cpp
        source/model/grouped_entities.cpp
        source/model/game_map.cpp
        source/model/entity_holder.cpp
        source/model/foreground_entity.cpp
        source/model/movable_entity.cpp
        source/model/handler.cpp
        source/model/event.cpp
        source/model/server_game_model.cpp
        source/model/player_action_handler.cpp
        source/model/event_executor.cpp
        source/model/client_game_model.cpp
        source/model/spawners.cpp
        source/model/network_utils.cpp
        source/model/bonus.cpp
        source/model/tank_handler.cpp
)

add_executable(
        menu_tests
        menu_tests.cpp
        source/database.cpp
        source/menu/menu.cpp
        source/menu/menu_items.cpp
)

SET(COMPILER_FLAGS_FOR_MENU_TEST "-D MENU_TEST")
target_compile_options(menu_tests PRIVATE ${COMPILER_FLAGS_FOR_MENU_TEST})

add_executable(
        tanks
        source/main.cpp
        source/menu/menu_controller.cpp
        source/menu/menu.cpp
        source/menu/menu_items.cpp
        source/menu/users_menu.cpp
        source/menu/main_menu.cpp
        source/menu/new_game_menu.cpp
        source/menu/levels_menu.cpp
        source/menu/textbox.cpp
        source/menu/input_menu.cpp
        source/menu/upgrade_menu.cpp
        source/menu/progress_bar.cpp
        source/menu/rating_menu.cpp
        source/menu/settings_menu.cpp
        source/menu/slider_bar.cpp
        source/menu/multiplayer_menu.cpp
        source/sound/background_music.cpp
        source/game.cpp
        source/sound/shoot_sound.cpp
        source/sound/block_destroy_sound.cpp
        source/game_controller.cpp
        source/game_environment.cpp
        source/pause.cpp
        source/database.cpp
        source/view/game_view.cpp
        source/view/tank_view.cpp
        source/view/bullets_view.cpp
        source/view/bonus_view.cpp
        source/sound/shoot_sound.cpp
        source/sound/background_music.cpp
        source/sound/tank_destroy_sound.cpp
        source/model/blocks.cpp
        source/model/entity.cpp
        source/model/game_model.cpp
        source/model/projectile.cpp
        source/model/tank.cpp
        source/model/grouped_entities.cpp
        source/model/game_map.cpp
        source/model/entity_holder.cpp
        source/model/foreground_entity.cpp
        source/model/movable_entity.cpp
        source/model/handler.cpp
        source/model/event.cpp
        source/model/server_game_model.cpp
        source/model/player_action_handler.cpp
        source/model/event_executor.cpp
        source/model/client_game_model.cpp
        source/model/spawners.cpp
        source/model/network_utils.cpp
        source/model/bonus.cpp
        source/model/tank_handler.cpp
        source/server.cpp
        source/server.h
)

target_link_libraries(tanks sfml-audio)
