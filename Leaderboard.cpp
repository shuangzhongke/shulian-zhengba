#include "Leaderboard.h"  // 包含自定义的头文件

#include <algorithm>  // 尽管std::sort在main中，但这里包含以防未来扩展
#include <fstream>    // 用于文件输入/输出操作 (ifstream, ofstream)
#include <sstream>    // 用于从文件行解析组件

// 排行榜文件名常量定义

const std::string LEADERBOARD_FILE = "leaderboard.txt";

// 从文件加载排行榜数据

void loadLeaderboard(std::vector<PlayerScore>& leaderboard,
    const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "错误：无法打开文件 '" << filename
            << "' 进行读取。将初始化一个空排行榜。" << std::endl;
        return;  // 文件不存在或无法打开，返回空排行榜
    }

    leaderboard.clear();  // 清除任何现有数据
    std::string line;
    while (std::getline(inputFile, line)) {  // 逐行读取文件
        std::istringstream iss(line);
        double time_from_file;
        int difficulty_from_file = 0; // Initialize
        int board_size_from_file = 0; // Initialize
        std::string username_from_file;

        // 尝试按最新格式解析：time difficulty_code (board_size) username
        if (iss >> time_from_file)
        {
            // 尝试读取难度
            if (iss >> difficulty_from_file) {
                // 如果是自定义模式，尝试读取棋盘大小
                if (difficulty_from_file == 4)
                {
                    iss >> board_size_from_file;
                }
                // 读取剩余的作为用户名，跳过前导空格

                iss >> std::ws; // 消耗前导空白（即去除字符串开头的空格、制表符等空白字符）

                std::getline(iss, username_from_file);


            }
            else
            {
                // 如果读取难度失败，说明可能是旧格式：time username
                // 将iss重置，并只读取用户名
                iss.clear(); // 清除错误标志
                iss.seekg(0); // 回到行首
                std::string temp_time_str; // 先将时间作为字符串读取以便丢弃
                iss >> temp_time_str; // 丢弃时间字符串
                iss >> std::ws; // 消耗前导空白（即去除字符串开头的空格、制表符等空白字符）
                std::getline(iss, username_from_file);
                // 对于旧格式，难度和棋盘大小都为0
                difficulty_from_file = 0;
                board_size_from_file = 0;
            }

            if (!username_from_file.empty())// 确保用户名非空
            {
                leaderboard.push_back(PlayerScore(username_from_file, time_from_file, difficulty_from_file, board_size_from_file));
            }
        }
    }
    inputFile.close();  // 显式关闭文件
}


// 将排行榜数据保存到文件
void saveLeaderboard(const std::vector<PlayerScore>& leaderboard,
    const std::string& filename)
{
    // 以截断模式打开文件，这将删除文件中的所有现有内容
    std::ofstream outputFile(filename, std::ios::trunc);
    if (!outputFile.is_open())
    {
        std::cerr << "错误：无法打开文件 '" << filename << "' 进行写入！"
            << std::endl;
        return;
    }

    for (const auto& score : leaderboard) {
        // 写入时间，然后是难度代码，如果是自定义模式则写入棋盘大小，然后是用户名，用空格分隔
        outputFile << std::fixed << std::setprecision(2) << score.time_taken << " "
            << score.difficulty;
        if (score.difficulty == 4)
        {
            outputFile << " " << score.board_size;
        }
        outputFile << " " << score.username << '\n';
    }
    outputFile.close();  // 显式关闭文件
}

//从代码和棋盘大小获取难度字符串的辅助函数

std::string getDifficultyString(int difficulty_code, int board_size)
{
    switch (difficulty_code)
    {
    case 1: return "简单";
    case 2: return "普通";
    case 3: return "困难";
    case 4: return "自定义(" + std::to_string(board_size) + "x" + std::to_string(board_size) + ")";
    default: return "未知"; // 对于较旧的条目或无效数据
    }
}

// 显示排行榜

void displayLeaderboard(const std::vector<PlayerScore>& leaderboard)
{
    if (leaderboard.empty())
    {
        std::cout << "排行榜为空。快来成为第一个玩家吧！" << std::endl;
        return;
    }

    int rank = 1;
    for (const auto& score : leaderboard)
    {
        std::cout << rank++ << ". " << score.username << " - "
            << std::fixed << std::setprecision(2) << score.time_taken << "s"
            << " (难度: " << getDifficultyString(score.difficulty, score.board_size) << ")" << std::endl;
    }
}
