cmake_minimum_required(VERSION 3.0.2)

project(codeporting)

set(CXX_CPP
    codeporting.json
    codeportingmanager.cpp
    codeportingplugin.cpp
    configwidget.cpp
    codeporting.cpp
    reportpane.cpp
    codeportingwidget.cpp
    )

set(CXX_H
    codeportingmanager.h
    codeportingplugin.h
    configwidget.h
    codeporting.h
    reportpane.h
    codeportingwidget.h
    )

add_library(${PROJECT_NAME}
    SHARED
    ${CXX_H}
    ${CXX_CPP}
    codeporting.qrc
    )

target_link_libraries(${PROJECT_NAME}
    duc-framework
    duc-base
    duc-services
    ${QtUseModules}
    ${PkgUserModules}
    )

install_logo(${PROJECT_NAME}.svg)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${PLUGIN_INSTALL_PATH})

