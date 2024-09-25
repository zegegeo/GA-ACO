import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import sys

# 设置样式（类似顶刊论文的风格）
sns.set(style="whitegrid")
plt.rcParams['font.size'] = 12  # 设置字体大小
plt.rcParams['axes.labelsize'] = 14
plt.rcParams['axes.titlesize'] = 16
plt.rcParams['legend.fontsize'] = 12

def plot_graph(x_file_path, y_file_path, output_file):
    # 从文件读取数据
    with open(x_file_path, 'r') as f:
        x_data = [float(line.strip()) for line in f]

    with open(y_file_path, 'r') as f:
        y_data = [float(line.strip()) for line in f]

    # 创建图形
    plt.figure(figsize=(10, 8))

    # 绘制适应度随代数变化的折线图
    plt.plot(x_data, y_data, label='Best Fitness', color='steelblue', linewidth=2.5, marker='o', markersize=3, markerfacecolor='red')

    # 图表细节调整
    plt.title('Evolution of Best Fitness Across Generations')
    plt.xlabel('Generation')
    plt.ylabel('Best Fitness')
    plt.xticks(np.arange(0, 10, step=1))  # x轴标记每隔10代显示一次
    plt.yticks(np.arange(-1000,-700, step=100))  # y轴标记适应度范围

    # 显示图例
    plt.legend()

    # 减少不必要的边框线
    sns.despine()

    # 显示图形
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python plot.py <x_data_file> <y_data_file> <output_image>")
        sys.exit(1)

    x_file_path = sys.argv[1]
    y_file_path = sys.argv[2]
    output_file = sys.argv[3]

    plot_graph(x_file_path, y_file_path, output_file)