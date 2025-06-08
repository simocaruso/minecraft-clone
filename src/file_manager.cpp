//
// Created by simone on 08/06/25.
//

#include "file_manager.hpp"
#include <filesystem>
#include <unistd.h>
#include <iostream>

std::string FileManager::get_file_path(const std::string &dir_name,
                                       const std::string &file_name,
                                       const std::string &file_extension) {
    std::string abs_dir_path = get_dir(dir_name);
    return (std::filesystem::path(abs_dir_path) / dir_name / (file_name + "." + file_extension)).string();
}

std::string FileManager::get_dir(const std::string &dir_name) { // NOLINT(*-convert-member-functions-to-static)
    auto dir = get_executable_directory();
    std::cout << dir;
    return dir;
}

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <limits.h>
#else

#include <unistd.h>
#include <climits>
#include <fstream>

#endif

std::string FileManager::get_executable_directory() {
    char buffer[PATH_MAX];

#if defined(_WIN32)
    GetModuleFileNameA(nullptr, buffer, PATH_MAX);
#elif defined(__APPLE__)
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) != 0)
        throw std::runtime_error("Path too long");
#else
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len == -1)
        throw std::runtime_error("Cannot resolve executable path");
    buffer[len] = '\0';
#endif

    return std::filesystem::path(buffer).parent_path().string();
}

std::string FileManager::load_text_file(const std::string &dir_name, const std::string &file_name,
                                        const std::string &file_extension) {
    std::ifstream file(get_file_path(dir_name, file_name, file_extension));
    if (!file) {
        throw std::runtime_error("File not found: " + get_file_path(dir_name, file_name, file_extension));
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
