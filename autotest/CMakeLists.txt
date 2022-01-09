add_definitions( -DGRANTLEETHEME_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )
add_definitions( -DGRANTLEETHEME_DATA_BUILD_DIR="${CMAKE_CURRENT_BINARY_DIR}/data" )
ecm_add_test(grantleethemetest.cpp
    NAME_PREFIX "grantleetheme-"
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::GrantleeTheme KF5::ConfigCore Qt${QT_MAJOR_VERSION}::Gui KF5::ConfigWidgets
)
ecm_add_test(grantleethememanagertest.cpp
    NAME_PREFIX "grantleetheme-"
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::GrantleeTheme KF5::ConfigCore KF5::XmlGui
)
