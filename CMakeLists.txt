project(kwaterscreensaver)

#TODO: Remove these lines later when integrated into playground or kdeartwork
find_package(KDE4 REQUIRED)
find_package(Strigi REQUIRED)
include_directories(${KDE4_INCLUDES})
include(KDE4Defaults)

set(kwater.kss_SRCS water.cpp)

kde4_add_executable(kwater.kss ${kwater.kss_SRCS})

target_link_libraries(kwater.kss ${KDE4_KDEUI_LIBS} ${STRIGI_LIBRARIES} kscreensaver)

install(TARGETS kwater.kss ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES KWater.desktop DESTINATION ${SERVICES_INSTALL_DIR}/ScreenSavers)


