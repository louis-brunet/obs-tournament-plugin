# --- Detect if the plugin is build out of tree or not ---
if(CMAKE_PROJECT_NAME STREQUAL "obs-studio")
  set(BUILD_OUT_OF_TREE OFF)
  if(OBS_CMAKE_VERSION VERSION_GREATER_EQUAL 3.0.0)
    legacy_check()
  endif()
else()
  set(BUILD_OUT_OF_TREE ON)
  cmake_minimum_required(VERSION 3.18)
endif()

# project(obs-tournament-plugin VERSION 0.0.1)
# set(PROJECT_FULL_NAME "Tournament")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)

project(${_name} VERSION ${_version})
set(PROJECT_FULL_NAME ${_displayName})

include(compilerconfig)
include(defaults)
# include(helpers)

# Set new UUIDs when you start to create a new plugin.
set(MACOS_PACKAGE_UUID "F721F3E7-EBCA-49BF-ACB4-327FDCB8E78E")
set(MACOS_INSTALLER_UUID "3E600B4A-97D1-482F-8C4A-83F01D38F710")

add_library(${PROJECT_NAME} MODULE)
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h)

# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/plugin-support.c.in")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/plugin-support.c.in ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin-support.c @ONLY)
# add_library(plugin-support STATIC)
# target_sources(
#   plugin-support
#   PRIVATE src/plugin-support.c
#   PUBLIC src/plugin-support.h)
# target_include_directories(plugin-support PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
# if(OS_LINUX
#   OR OS_FREEBSD
#   OR OS_OPENBSD)
#     # add fPIC on Linux to prevent shared object errors
#     set_property(TARGET plugin-support PROPERTY POSITION_INDEPENDENT_CODE ON)
# endif()
# # endif()

target_sources(${PROJECT_NAME} PRIVATE 
    src/data/data-helpers.cpp
    src/data/data-helpers.hpp
    src/data/match-participant-from-match.cpp
    src/data/match-participant-from-match.hpp
    src/data/match-participant-player.cpp
    src/data/match-participant-player.hpp
    src/data/match-participant-unknown.cpp
    src/data/match-participant-unknown.hpp
    src/data/match-participant.cpp
    src/data/match-participant.hpp
    src/data/match-reference.cpp
    src/data/match-reference.hpp
    src/data/match-reference-remap.cpp
    src/data/match-reference-remap.hpp
    src/data/match.cpp
    src/data/match.hpp
    src/data/player-reference.cpp
    src/data/player-reference.hpp
    src/data/player.cpp
    src/data/player.hpp
    src/data/plugin-data.cpp
    src/data/plugin-data.hpp
    src/data/tournament-reference.cpp
    src/data/tournament-reference.hpp
    src/data/tournament-round-reference.cpp
    src/data/tournament-round-reference.hpp
    src/data/tournament-round.cpp
    src/data/tournament-round.hpp
    src/data/tournament.cpp
    src/data/tournament.hpp
    src/ui/components/button.cpp
    src/ui/components/button.hpp
    src/ui/components/icon.cpp
    src/ui/components/icon.hpp
    src/ui/components/label.cpp
    src/ui/components/label.hpp
    src/ui/components/labeled-input.cpp
    src/ui/components/labeled-input.hpp
    src/ui/components/line-edit.cpp
    src/ui/components/line-edit.hpp
    src/ui/dialogs/base-dialog.cpp
    src/ui/dialogs/base-dialog.hpp
    src/ui/dialogs/error-dialog.cpp
    src/ui/dialogs/error-dialog.hpp
    src/ui/dialogs/plugin-dialog.cpp
    src/ui/dialogs/plugin-dialog.hpp
    src/ui/tabs/custom-tournament/configuration/custom-tournament-configuration-frame.cpp
    src/ui/tabs/custom-tournament/configuration/custom-tournament-configuration-frame.hpp
    src/ui/tabs/custom-tournament/configuration/custom-tournament-match-configuration-frame.cpp
    src/ui/tabs/custom-tournament/configuration/custom-tournament-match-configuration-frame.hpp
    src/ui/tabs/custom-tournament/configuration/custom-tournament-round-configuration-frame.cpp
    src/ui/tabs/custom-tournament/configuration/custom-tournament-round-configuration-frame.hpp
    src/ui/tabs/custom-tournament/configuration/match-participant-input.cpp
    src/ui/tabs/custom-tournament/configuration/match-participant-input.hpp
    src/ui/tabs/custom-tournament/custom-tournament-tab.cpp
    src/ui/tabs/custom-tournament/custom-tournament-tab.hpp
    src/ui/tabs/setup/create-player-frame.cpp
    src/ui/tabs/setup/create-player-frame.hpp
    src/ui/tabs/setup/create-tournament-frame.cpp
    src/ui/tabs/setup/create-tournament-frame.hpp
    src/ui/tabs/setup/setup-tab.cpp
    src/ui/tabs/setup/setup-tab.hpp
    src/ui/tabs/setup/debug-frame.cpp
    src/ui/tabs/setup/debug-frame.hpp
    src/ui/tabs/base-tab.cpp
    src/ui/tabs/base-tab.hpp
    src/logger.cpp
    src/logger.hpp
    src/plugin-main.cpp
    src/plugin-support.c
    src/plugin-support.h
)

if(BUILD_OUT_OF_TREE)
  find_package(libobs REQUIRED)
  find_package(obs-frontend-api REQUIRED)
  include(cmake/ObsPluginHelpers.cmake)
  set(OBS_FRONTEND_API_NAME "obs-frontend-api")
else()
	set(OBS_FRONTEND_API_NAME "frontend-api")
endif()

if(OS_WINDOWS)
	get_filename_component(ISS_FILES_DIR "${CMAKE_BINARY_DIR}\\..\\package" ABSOLUTE)
	file(TO_NATIVE_PATH "${ISS_FILES_DIR}" ISS_FILES_DIR)
	get_filename_component(ISS_PACKAGE_DIR "${CMAKE_PACKAGE_PREFIX}\\.." ABSOLUTE)
	file(TO_NATIVE_PATH "${ISS_PACKAGE_DIR}" ISS_PACKAGE_DIR)
	get_filename_component(ISS_SOURCE_DIR "${PROJECT_SOURCE_DIR}" ABSOLUTE)
	file(TO_NATIVE_PATH "${ISS_SOURCE_DIR}" ISS_SOURCE_DIR)
	configure_file("installer.iss.in"
			"${PROJECT_BINARY_DIR}/installer.iss"
		)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resource.rc.in ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.rc)
	target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.rc)
	
elseif(OS_MACOS)
	set(MACOS_BUNDLEID "com.exeldro.${PROJECT_NAME}")
	set(MACOSX_PLUGIN_GUI_IDENTIFIER "${MACOS_BUNDLEID}")
	set(MACOSX_PLUGIN_BUNDLE_VERSION "${PROJECT_VERSION}")
	set(MACOSX_PLUGIN_SHORT_VERSION_STRING "1")
	configure_file(cmake/bundle/macos/installer-macos.pkgproj.in ${CMAKE_BINARY_DIR}/installer-macos.generated.pkgproj)
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
endif()

# lines if you want add Qt UI in your plugin
find_qt(COMPONENTS Widgets COMPONENTS_LINUX Gui)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON AUTOUIC ON AUTORCC ON)

target_link_libraries(${PROJECT_NAME}
		OBS::${OBS_FRONTEND_API_NAME}
		Qt::Widgets
		OBS::libobs)

if(BUILD_OUT_OF_TREE)
    if(NOT LIB_OUT_DIR)
        set(LIB_OUT_DIR "/lib/x86_64-linux-gnu/obs-plugins")
    endif()
    if(NOT DATA_OUT_DIR)
        set(DATA_OUT_DIR "/share/obs/obs-plugins/${PROJECT_NAME}")
    endif()
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
    install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_OUT_DIR})
    install(DIRECTORY data/locale
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${DATA_OUT_DIR})
    install(DIRECTORY data/icons
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${DATA_OUT_DIR})
    setup_plugin_target(${PROJECT_NAME})
else()
    target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/UI/obs-frontend-api")
    if(OBS_CMAKE_VERSION VERSION_GREATER_EQUAL 3.0.0)
        set_target_properties_obs(${PROJECT_NAME} PROPERTIES FOLDER "plugins/exeldro" PREFIX "")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "plugins/exeldro")
        setup_plugin_target(${PROJECT_NAME})
    endif()
endif()
