cmake_minimum_required(VERSION 3.5)

set(KF5_MIN_VERSION "5.68.0")
set(PIM_VERSION "5.14.40")

project(GrantleeTheme VERSION ${PIM_VERSION})


find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${GrantleeTheme_SOURCE_DIR}/cmake ${ECM_MODULE_PATH})
set(LIBRARY_NAMELINK)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(FeatureSummary)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)

include(KPIMGrantleeMacros)

if (POLICY CMP0053)
    cmake_policy(SET CMP0053 NEW)
endif()

set(GRANTLEETHEME_LIB_VERSION ${PIM_VERSION})

set(QT_REQUIRED_VERSION "5.12.0")
set(GRANTLEE_VERSION "5.1")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Network)
find_package(KF5GuiAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5NewStuff ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(Grantlee5 ${GRANTLEE_VERSION} CONFIG REQUIRED)

ecm_setup_version(PROJECT VARIABLE_PREFIX GRANTLEETHEME
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/grantleetheme_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5GrantleeThemeConfigVersion.cmake"
                        SOVERSION 5
)

########### Targets ###########

if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
   add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050e00)
   add_definitions(-DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x054400)
endif()

add_definitions(-DQT_NO_FOREACH)


########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5GrantleeTheme")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5GrantleeThemeConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5GrantleeThemeConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5GrantleeThemeConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5GrantleeThemeConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5GrantleeThemeTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5GrantleeThemeTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/grantleetheme_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)


add_subdirectory(src)
if (BUILD_TESTING)
    find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Test)
   add_subdirectory(autotest)
endif()

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

