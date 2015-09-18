cmake_minimum_required(VERSION 3.2)
project(SortNews)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(SortNews ${SOURCE_FILES} data/business.seg extractTerms/Utility.h extractTerms/Utility.cpp extractTerms/tl_codetbl.cpp extractTerms/tl_codetbl.h extractTerms/simpleDic.cpp extractTerms/simpleDic.h extractTerms/searchTerm.cpp extractTerms/searchTerm.h extractTerms/fileOperation.cpp extractTerms/fileOperation.h extractTerms/countWord.cpp extractTerms/countWord.h term.cpp term.h article.cpp article.h articleSpool.cpp articleSpool.h heapUtil.h heapUtil.cpp heapUtil.cpp heapUtil.h)