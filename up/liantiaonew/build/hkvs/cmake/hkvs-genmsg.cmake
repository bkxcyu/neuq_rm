# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "hkvs: 2 messages, 0 services")

set(MSG_I_FLAGS "-Ihkvs:/home/tyj/liantiaonew/src/hkvs/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(hkvs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/square.msg" NAME_WE)
add_custom_target(_hkvs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hkvs" "/home/tyj/liantiaonew/src/hkvs/msg/square.msg" ""
)

get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg" NAME_WE)
add_custom_target(_hkvs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hkvs" "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/square.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hkvs
)
_generate_msg_cpp(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hkvs
)

### Generating Services

### Generating Module File
_generate_module_cpp(hkvs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hkvs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(hkvs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(hkvs_generate_messages hkvs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/square.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_cpp _hkvs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_cpp _hkvs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hkvs_gencpp)
add_dependencies(hkvs_gencpp hkvs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hkvs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/square.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hkvs
)
_generate_msg_eus(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hkvs
)

### Generating Services

### Generating Module File
_generate_module_eus(hkvs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hkvs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(hkvs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(hkvs_generate_messages hkvs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/square.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_eus _hkvs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_eus _hkvs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hkvs_geneus)
add_dependencies(hkvs_geneus hkvs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hkvs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/square.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hkvs
)
_generate_msg_lisp(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hkvs
)

### Generating Services

### Generating Module File
_generate_module_lisp(hkvs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hkvs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(hkvs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(hkvs_generate_messages hkvs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/square.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_lisp _hkvs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_lisp _hkvs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hkvs_genlisp)
add_dependencies(hkvs_genlisp hkvs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hkvs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/square.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hkvs
)
_generate_msg_nodejs(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hkvs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(hkvs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hkvs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(hkvs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(hkvs_generate_messages hkvs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/square.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_nodejs _hkvs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_nodejs _hkvs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hkvs_gennodejs)
add_dependencies(hkvs_gennodejs hkvs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hkvs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/square.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hkvs
)
_generate_msg_py(hkvs
  "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hkvs
)

### Generating Services

### Generating Module File
_generate_module_py(hkvs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hkvs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(hkvs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(hkvs_generate_messages hkvs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/square.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_py _hkvs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/tyj/liantiaonew/src/hkvs/msg/vel.msg" NAME_WE)
add_dependencies(hkvs_generate_messages_py _hkvs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hkvs_genpy)
add_dependencies(hkvs_genpy hkvs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hkvs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hkvs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hkvs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(hkvs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hkvs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hkvs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(hkvs_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hkvs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hkvs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(hkvs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hkvs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hkvs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(hkvs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hkvs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hkvs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hkvs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(hkvs_generate_messages_py std_msgs_generate_messages_py)
endif()
