//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_FILE_MANAGER_HPP
#define MINECRAFT_FILE_MANAGER_HPP

#include <string>

class FileManager {
public:
    static std::string load_text_file(const std::string &dir_name, const std::string &file_name, const std::string &file_extension);
private:
    static std::string get_file_path(const std::string &dir_name, const std::string &file_name, const std::string &file_extension);

    static std::string get_dir(const std::string &dir_name);

    static std::string get_executable_directory();
};


#endif //MINECRAFT_FILE_MANAGER_HPP
