//
// Created by Lwz on 2024/9/12.
//

#include "matplotlib.h"

#include <fstream>
#include <iostream>

// 将数据写入文件
void saveDataToFile(const std::string& x_file_path, const std::string& y_file_path,
                    const std::vector<double>& x_data, const std::vector<double>& y_data) {

    std::ofstream x_file(x_file_path);
    std::ofstream y_file(y_file_path);

    if (!x_file || !y_file) {
        std::cerr << "Error opening file for writing." << std::endl;
        exit(1);
    }

    for (const auto& value : x_data) {
        x_file << value << "\n";
    }
    for (const auto& value : y_data) {
        y_file << value << "\n";
    }

    x_file.close();
    y_file.close();
}

// 调用 Python 脚本生成图像
void generatePlot(const std::string& python_interpreter, const std::string& script_path,
                  const std::string& x_file_path, const std::string& y_file_path, const std::string& output_file) {

    std::string command = python_interpreter + " " + script_path + " " + x_file_path + " " + y_file_path + " " + output_file;

    // 执行 Python 脚本
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Python script execution failed." << std::endl;
        exit(1);
    }

    std::cout << "Command exit status: " << result << std::endl;
}