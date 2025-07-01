add_definitions(-DGRANTLEETHEME_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
add_definitions(
    -DGRANTLEETHEME_DATA_BUILD_DIR="${CMAKE_CURRENT_BINARY_DIR}/data"
)
ecm_add_test(grantleethemetest.cpp
    NAME_PREFIX "grantleetheme-"
    LINK_LIBRARIES Qt::Test KPim6::GrantleeTheme KF6::ConfigCore Qt::Gui KF6::ColorScheme
)
ecm_add_test(grantleethememanagertest.cpp
    NAME_PREFIX "grantleetheme-"
    LINK_LIBRARIES Qt::Test KPim6::GrantleeTheme KF6::ConfigCore KF6::XmlGui
)
