cmake_minimum_required(VERSION 3.20)

set(PostgresSQL_ADDITIONAL_VERSION "16" )

project(Homework_04)

add_subdirectory("C:\\Users\\alexr\\Desktop\\04\\libpqxx-7.8.1" libpqxx-build)

add_executable(Homework_04 main.cpp)

target_compile_features(Homework_04 PRIVATE cxx_std_17)

target_link_libraries(Homework_04 PRIVATE pqxx)