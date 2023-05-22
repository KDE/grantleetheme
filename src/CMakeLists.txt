add_definitions(-DTRANSLATION_DOMAIN=\"libgrantleetheme\")

add_library(KPim6GrantleeTheme)
add_library(KPim6::GrantleeTheme ALIAS KPim6GrantleeTheme)


add_subdirectory(plugin)

target_sources(KPim6GrantleeTheme PRIVATE
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

ecm_qt_declare_logging_category(KPim6GrantleeTheme HEADER grantleetheme_debug.h IDENTIFIER GRANTLEETHEME_LOG CATEGORY_NAME org.kde.pim.grantleetheme
        OLD_CATEGORY_NAMES log_grantleetheme
        DESCRIPTION "kdepim (grantleetheme)" EXPORT LIBGRANTLEETHEME)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim6GrantleeTheme PROPERTIES UNITY_BUILD ON)
endif()
ecm_generate_export_header(KPim6GrantleeTheme
    BASE_NAME grantleetheme
    VERSION ${GRANTLEETHEME_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)

target_include_directories(KPim6GrantleeTheme INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/GrantleeTheme/>")
target_include_directories(KPim6GrantleeTheme PUBLIC "$<BUILD_INTERFACE:${GrantleeTheme_SOURCE_DIR}/src;${GrantleeTheme_BINARY_DIR}/src;>")

target_link_libraries(KPim6GrantleeTheme
    PUBLIC
    KF6::TextTemplate
    PRIVATE
    KF6::NewStuffCore
    KF6::I18n
    KF6::NewStuffWidgets
    KF6::ConfigCore
    KF6::XmlGui
)
set_target_properties(KPim6GrantleeTheme PROPERTIES
    VERSION ${GRANTLEETHEME_VERSION}
    SOVERSION ${GRANTLEETHEME_SOVERSION}
    EXPORT_NAME GrantleeTheme
)

install(TARGETS
    KPim6GrantleeTheme
    EXPORT KPim6GrantleeThemeTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
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
    LIB_NAME KPim6GrantleeTheme
    DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR}/KPim6/GrantleeTheme
)


install(FILES
    ${GrantleeTheme_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/GrantleeTheme/GrantleeTheme
    COMPONENT Devel
)

install(FILES
    ${GrantleeTheme_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/grantleetheme_export.h
    ${GrantleeTheme_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/GrantleeTheme/grantleetheme
    COMPONENT Devel
)
install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KPim6GrantleeTheme_QCH
        NAME GrantleeTheme
        BASE_NAME KPim6GrantleeTheme
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${GrantleeTheme_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt6Core_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            GRANTLEETHEME_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

ecm_qt_install_logging_categories(EXPORT LIBGRANTLEETHEME FILE grantleetheme.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
