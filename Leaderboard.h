#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>
#include <iostream> // 在函数声明中处理 std::cerr（尽管实际使用在 .cpp 文件中）
#include <iomanip>  // 在显示排行榜（displayLeaderboard）时使用 std::fixed 和 std::setprecision（用于格式化输出精度）
#include <sstream> // 用于从文件行解析组件

// 定义排行榜条目的结构体
struct PlayerScore
{
    std::string username;
    double time_taken;
    int difficulty; // 已添加到难度存储：1=简单，2=普通，3=困难，4=自定义
    int board_size; // 已添加到存储自定义棋盘大小

    // 默认构造函数，用于在读取文件时创建临时对象
    PlayerScore() : username(""), time_taken(0.0), difficulty(0), board_size(0) {}

    PlayerScore(const std::string& name, double time, int diff, int size) : username(name), time_taken(time), difficulty(diff), board_size(size) {}
};

// 排行榜文件名常量声明

extern const std::string LEADERBOARD_FILE;

// 函数声明

void loadLeaderboard(std::vector<PlayerScore>& leaderboard, const std::string& filename);
void saveLeaderboard(const std::vector<PlayerScore>& leaderboard, const std::string& filename);
void displayLeaderboard(const std::vector<PlayerScore>& leaderboard);
std::string getDifficultyString(int difficulty_code, int board_size); // Modified helper function

#endif // LEADERBOARD_H
