set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS Sql Core Network Gui)

#use dbus on linux, bsd etc, but not andoid and apple stuff
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

set(tagging_SRCS
    tagging.cpp
    tagging.h
    tagdb.cpp
    tagdb.h
    tag.h
    )


qt5_add_resources(tagging_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tagging.qrc)

add_library(TAGGING STATIC ${tagging_SRCS} ${tagging_RESOURCES})

target_link_libraries(TAGGING
    Qt5::Core
    Qt5::Sql
    Qt5::Gui
    Qt5::Network
    )


