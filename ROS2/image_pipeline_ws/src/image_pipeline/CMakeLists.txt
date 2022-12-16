cmake_minimum_required(VERSION 3.8)
project(image_pipeline)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS highgui imgcodecs imgproc videoio)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)


add_executable(publisher_cpp src/publisher_cpp.cpp)

target_link_libraries(publisher_cpp 
  cv_bridge::cv_bridge
  image_transport::image_transport
  ${OpenCV_LIBS}
  rclcpp::rclcpp
)

add_executable(subscriber_cpp src/subscriber_cpp.cpp)

target_link_libraries(subscriber_cpp 
  cv_bridge::cv_bridge
  image_transport::image_transport
  ${OpenCV_LIBS}
  rclcpp::rclcpp
)

# Install executables
install(
  TARGETS publisher_cpp subscriber_cpp
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

# Install include directories
install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

# Install Python executables
install(PROGRAMS
  scripts/setup.py
  image_pipeline/publisher_py.py
  image_pipeline/subscriber_py.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

ament_package()
