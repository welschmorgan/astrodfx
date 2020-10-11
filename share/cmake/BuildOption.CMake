function(declare_build_option NAME DESC DEF_VALUE)
    set(${NAME} "${DEF_VALUE}" CACHE BOOL "${DESC}")
    set(VAR_NAME "${NAME}_C")
    if (${${NAME}})
        set(${VAR_NAME} 1 PARENT_SCOPE) #
    else()
        set(${VAR_NAME} 0 PARENT_SCOPE)
    endif ()
endfunction()