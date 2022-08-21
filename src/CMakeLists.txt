add_definitions(-DTRANSLATION_DOMAIN=\"libgrantleetheme\")

add_library(KF5GrantleeTheme)
add_library(KF5::GrantleeTheme ALIAS KF5GrantleeTheme)


add_subdirectory(plugin)

target_sources(KF5GrantleeTheme PRIVATE
    genericformatter.cpp
    grantleetheme.cpp
    grantleethememanager.cpp
    grantleethemeengine.cpp
    grantleeki18nlocalizer.cpp
    qtresourcetemplateloader.cpp

    genericformatter.h
    grantleetheme.h
    grantleethememanager.h
    grantleethemeengine.h
    grantleeki18nlocalizer.h
    qtresourcetemplateloader.h
    )

configure_file(config-grantleetheme.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-grantleetheme.h)

ecm_qt_declare_logging_category(KF5GrantleeTheme HEADER grantleetheme_debug.h IDENTIFIER GRANTLEETHEME_LOG CATEGORY_NAME org.kde.pim.grantleetheme
        OLD_CATEGORY_NAMES log_grantleetheme
        DESCRIPTION "kdepim (grantleetheme)" EXPORT LIBGRANTLEETHEME)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5GrantleeTheme PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF5GrantleeTheme BASE_NAME grantleetheme)


target_include_directories(KF5GrantleeTheme INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/GrantleeTheme/>")
target_include_directories(KF5GrantleeTheme PUBLIC "$<BUILD_INTERFACE:${GrantleeTheme_SOURCE_DIR}/src;${GrantleeTheme_BINARY_DIR}/src;>")

target_link_libraries(KF5GrantleeTheme
    PUBLIC
    ${MAIN_LIB}
    PRIVATE
    KF5::NewStuff
    KF5::I18n
    KF5::NewStuffWidgets
)
set_target_properties(KF5GrantleeTheme PROPERTIES
    VERSION ${GRANTLEETHEME_VERSION}
    SOVERSION ${GRANTLEETHEME_SOVERSION}
    EXPORT_NAME GrantleeTheme
)

install(TARGETS
    KF5GrantleeTheme
    EXPORT KF5GrantleeThemeTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
)

ecm_generate_headers(GrantleeTheme_CamelCase_HEADERS
  HEADER_NAMES
  GenericFormatter
  GrantleeThemeManager
  GrantleeTheme
  GrantleeThemeEngine
  QtResourceTemplateLoader
  GrantleeKi18nLocalizer
  REQUIRED_HEADERS GrantleeTheme_HEADERS
  PREFIX GrantleeTheme
)

ecm_generate_pri_file(BASE_NAME GrantleeTheme
    LIB_NAME KF5GrantleeTheme
    DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/GrantleeTheme
)


install(FILES
    ${GrantleeTheme_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/GrantleeTheme/GrantleeTheme
    COMPONENT Devel
)

install(FILES
    ${GrantleeTheme_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/grantleetheme_export.h
    ${GrantleeTheme_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/GrantleeTheme/grantleetheme
    COMPONENT Devel
)
install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


ecm_qt_install_logging_categories(EXPORT LIBGRANTLEETHEME FILE grantleetheme.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
