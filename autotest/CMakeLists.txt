add_definitions( -DGRANTLEETHEME_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )
add_definitions( -DGRANTLEETHEME_DATA_BUILD_DIR="${CMAKE_CURRENT_BINARY_DIR}/data" )
ecm_add_test(grantleethemetest.cpp
    NAME_PREFIX "grantleetheme-"
    LINK_LIBRARIES Qt::Test KF5::GrantleeTheme KF${KF_MAJOR_VERSION}::ConfigCore Qt::Gui KF${KF_MAJOR_VERSION}::ConfigWidgets
)
ecm_add_test(grantleethememanagertest.cpp
    NAME_PREFIX "grantleetheme-"
    LINK_LIBRARIES Qt::Test KF5::GrantleeTheme KF${KF_MAJOR_VERSION}::ConfigCore KF${KF_MAJOR_VERSION}::XmlGui
)
