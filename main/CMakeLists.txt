idf_component_register(SRCS "esp_rest_main.c" 
                            "rest_server.c"
                            "ledc.c"
                    INCLUDE_DIRS ".")

if(CONFIG_EXAMPLE_WEB_DEPLOY_SF)
    set(WEB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../front/web")
    if(EXISTS ${WEB_SRC_DIR}/build)
        spiffs_create_partition_image(www ${WEB_SRC_DIR}/build FLASH_IN_PROJECT)
    else()
        message(FATAL_ERROR "${WEB_SRC_DIR}/build doesn't exit. Please run 'npm run build' in ${WEB_SRC_DIR}")
    endif()
endif()
