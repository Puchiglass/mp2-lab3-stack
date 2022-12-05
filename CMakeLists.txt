cmake_minimum_required(VERSION 2.8) #Проверка версии CMake.

set(PROJECT_NAME Stack) #Создаем обычную локальную переменную с именем проекта
project(${PROJECT_NAME}) # Название проекта

#set(stack StackMain) #Переменная с именем приложения
set(stacklib stackLib) #Переменная с именем библиотеки
set(sample samples)
set(testlib gtest)
set(test testMain)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) #Создается переменная CMAKE_CONFIGURATION_TYPES со значением "Debug;Release" и меткой/разделом Configs, переменная сохраниется в специальном файле доступном из всех файлов,
if(NOT CMAKE_BUILD_TYPE) # проверка имеющихся у компилятора вариантов сборки
  set(CMAKE_BUILD_TYPE Release) #Если нет то устанавливаем Release
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/stackLib) #Добавляем директорию "${CMAKE_CURRENT_SOURCE_DIR}/vectorlib" в дополняемые каталоги включаемых файлов
#${CMAKE_CURRENT_SOURCE_DIR} - стандартная переменная с адресом рабочей директории

#add_subdirectory(Vector) #Добавляем директорию с под-CMakeList-ом, и выполняем под-CMakeList
add_subdirectory(stackLib)
add_subdirectory(gtest)
#add_subdirectory(Stack)
add_subdirectory(samples)
add_subdirectory(test)