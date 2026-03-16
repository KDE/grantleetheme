macro(kpim_grantlee_adjust_plugin_name pluginname)
    set_target_properties(
        ${pluginname}
        PROPERTIES
            PREFIX
                ""
            LIBRARY_OUTPUT_DIRECTORY
                "${CMAKE_BINARY_DIR}/bin/grantlee"
            RUNTIME_OUTPUT_DIRECTORY
                "${CMAKE_BINARY_DIR}/bin/grantlee"
            DEBUG_POSTFIX
                "d"
    )
    if(NOT DEFINED CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_CONFIGURATION_TYPES)
    endif()
    foreach(cfg ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${cfg} CFG)
        set_target_properties(
            ${pluginname}
            PROPERTIES
                LIBRARY_OUTPUT_DIRECTORY_${CFG}
                    "${CMAKE_BINARY_DIR}/bin/grantlee"
                RUNTIME_OUTPUT_DIRECTORY_${CFG}
                    "${CMAKE_BINARY_DIR}/bin/grantlee"
        )
    endforeach()
endmacro()
