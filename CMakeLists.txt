#TODO: Remove these 5 lines later when integrated into playground or kdeartwork
project(kwaterscreensaver)
find_package(KDE4 REQUIRED)
find_package(Strigi REQUIRED)
include_directories(${KDE4_INCLUDES})
include(KDE4Defaults)
#####################

set(kwater.kss_SRCS kwater.cpp)

kde4_add_executable(kwater.kss ${kwater.kss_SRCS})

target_link_libraries(kwater.kss ${KDE4_KDEUI_LIBS} ${STRIGI_LIBRARIES} kscreensaver)

install(TARGETS kwater.kss ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES kwater.desktop DESTINATION ${SERVICES_INSTALL_DIR}/ScreenSavers)
