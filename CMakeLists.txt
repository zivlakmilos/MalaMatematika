cmake_minimum_required(VERSION 2.8)
project(MalaMatematika)

find_package(Qt4 COMPONENTS QtCore QtGui QtSql QtNetwork REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_AUTORCC on)

include_directories(
    ${QT_INCLUDE}
    ${CMAKE_CURRENT_BINARY_DIR}
)
include_directories(include/)

include(${QT_USE_FILE})

set(SOURCES
    src/core/exception.cpp
    src/core/exceptionzagrada.cpp
    src/core/random.cpp
    src/matematika.cpp
    src/dna.cpp
    src/ai.cpp
    src/aithread.cpp

    src/ui/wigra.cpp
    src/ui/mainwindow.cpp

    src/main.cpp
)

set(HEADERS
    include/aithread.h
    include/ui/wigra.h
    include/ui/mainwindow.h
)

set(UI
    res/ui/igra.ui
)

set(RESOURCES
)

foreach(MOCheader ${HEADERS})
    QT4_WRAP_CPP(MOCsrc ${MOCheader})
endforeach(MOCheader)

foreach(UIheader ${UI})
    QT4_WRAP_UI(UIsrc ${UIheader})
endforeach(UIheader)

add_executable(${PROJECT_NAME} ${SOURCES} ${MOCsrc} ${RESOURCES} ${UIsrc})
target_link_libraries(${PROJECT_NAME}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTSQL_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
