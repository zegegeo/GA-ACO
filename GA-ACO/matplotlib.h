//
// Created by Lwz on 2024/9/12.
//

#ifndef GA_ACO_MATPLOTLIB_H
#define GA_ACO_MATPLOTLIB_H
#include<vector>
#include<string>

// 将数据写入文件
void saveDataToFile(const std::string& x_file_path, const std::string& y_file_path,
                    const std::vector<double>& x_data, const std::vector<double>& y_data);

void generatePlot(const std::string& python_interpreter, const std::string& script_path,
                  const std::string& x_file_path, const std::string& y_file_path, const std::string& output_file);


#endif //GA_ACO_MATPLOTLIB_H
