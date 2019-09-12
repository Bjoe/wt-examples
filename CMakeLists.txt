cmake_minimum_required(VERSION 3.5)

project(Wt-Example LANGUAGES CXX)

# See presentation
# https://www.youtube.com/watch?v=eusYGXC7KNc
# https://archive.fosdem.org/2018/schedule/event/web_development_in_c/attachments/slides/2443/export/events/attachments/web_development_in_c/slides/2443/Roel_Standaert___Introduction_to_Wt_4___FOSDEM2018.pdf

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set wt_DIR:PATH=/..../Development/wt/usr/lib/cmake/wt
find_package(wt CONFIG REQUIRED)

add_executable(wtex main.cpp)
target_link_libraries(wtex PUBLIC
  Wt::Wt
  Wt::HTTP
  Wt::Dbo
  Wt::DboSqlite3)
target_compile_features(wtex PUBLIC cxx_std_17)
