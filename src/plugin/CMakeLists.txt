kde_enable_exceptions()

set(grantleeplugin_SRCS
    kdegrantleeplugin.cpp
    color.cpp
    colorscheme.cpp
    icon.cpp
    palette.cpp
)

add_library(kde_grantlee_plugin MODULE ${grantleeplugin_SRCS})
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kde_grantlee_plugin PROPERTIES UNITY_BUILD ON)
endif()
kpim_grantlee_adjust_plugin_name(kde_grantlee_plugin)
target_link_libraries(kde_grantlee_plugin
    Grantlee5::Templates
    KF5::IconThemes
    KF5::GuiAddons
    KF5::ConfigWidgets
)

install(TARGETS kde_grantlee_plugin
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}/grantlee/${Grantlee5_VERSION_MAJOR}.${Grantlee5_VERSION_MINOR}/
)
