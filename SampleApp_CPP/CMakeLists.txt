# use a compiled version of wxWidgets: https://docs.wxwidgets.org/trunk/overview_cmake.html
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/image_converter)
include_directories(${CMAKE_SOURCE_DIR}/device_manager/inc)
include_directories(${CMAKE_SOURCE_DIR}/monochrome_sdk/include)
include_directories(${CMAKE_SOURCE_DIR}/imaging_library/include)

# includes
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../../3rd_party/opencv/opencv_install_dir/include/opencv4/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(OPENCV_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../3rd_party/opencv/opencv_install_dir/lib/")
LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../3rd_party/opencv/opencv_install_dir/lib/")

SET(GCC_COVERAGE_LINK_FLAGS    "-lpng")
include_directories(${CMAKE_SOURCE_DIR}/camera_client/zebra_camera_manager_client)
include_directories(${CMAKE_SOURCE_DIR}/camera_client/zebra_camera_client)

# sources
file(GLOB SOURCE "*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(bioptic_color_camera_demo ${SOURCE})

# link libzebracam
#target_link_libraries(bioptic_color_camera_demo zebracam)
target_link_libraries(bioptic_color_camera_demo ${wxWidgets_LIBRARIES})
target_link_libraries(bioptic_color_camera_demo image_converter)
target_link_libraries(bioptic_color_camera_demo camera_imaging_lib)
target_link_libraries(bioptic_color_camera_demo device_manager)

target_link_libraries(bioptic_color_camera_demo monochrome-sdk)
# link libraries

target_link_libraries(bioptic_color_camera_demo ${OPENCV_LIB_DIR}/libopencv_core.so)
target_link_libraries(bioptic_color_camera_demo ${OPENCV_LIB_DIR}/libopencv_imgproc.so)
target_link_libraries(bioptic_color_camera_demo ${OPENCV_LIB_DIR}/libopencv_video.so)
target_link_libraries(bioptic_color_camera_demo ${OPENCV_LIB_DIR}/libopencv_imgcodecs.so)
target_link_libraries(bioptic_color_camera_demo ${OPENCV_LIB_DIR}/libopencv_features2d.so)
target_link_libraries(bioptic_color_camera_demo ${OPENCV_LIB_DIR}/libopencv_videoio.so)
target_link_libraries(bioptic_color_camera_demo ${OPENCV_LIB_DIR}/libopencv_highgui.so)

#target_link_libraries(bioptic_color_camera_demo device_manager)
target_link_libraries(bioptic_color_camera_demo zebra_camera_manager_client)
target_link_libraries(bioptic_color_camera_demo zebra_camera_client)

