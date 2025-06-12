#include <algorithm>  // 用于 std::sort 函数
#include <chrono>     // 用于精确时间测量
#include <iomanip>    // 用于 std::fixed 和 std::setprecision
#include <iostream>   // 用于控制台输入/输出
#include <limits>     // 用于清除输入缓冲区
#include <string>     // 用于字符串操作 (用户名)
#include <vector>     // 用于存储排行榜条目的动态数组
#include <cstdlib>    // 用于std::rand, std::srand
#include <ctime>      // 用于std::time
#include <random>     // 用于std::mt19937 和 std::shuffle
#include <sstream>    // 用于从字符串流中读取数据

#include "Leaderboard.h"  // 包含排行榜功能的头文件

// 计算两个整数的最大公约数，使用欧几里得算法
int gcd(int a, int b)
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 判断两个数字是否可以消除
bool canEliminate(int num1, int num2)
{
    if (num1 == 0 || num2 == 0) return false; // 0不能参与消除
    if (num1 == num2) {
        return true;
    }
    int divisor = gcd(num1, num2);
    return (num1 / divisor == 1) || (num2 / divisor == 1);
}

// 生成指定大小的盘面

std::vector<std::vector<int>> generateBoard(int size)
{
    std::vector<std::vector<int>> board(size, std::vector<int>(size));
    std::vector<int> numbers;
    numbers.reserve(size * size);

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(2, 100);

    for (int i = 0; i < (size * size) / 2; ++i)
    {
        int num = dist(rng);
        numbers.push_back(num);
        numbers.push_back(num);
    }

    std::shuffle(numbers.begin(), numbers.end(), rng);

    int k = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            board[i][j] = numbers[k++];
        }
    }
    return board;
}

// 打印当前的盘面状态
void printBoard(const std::vector<std::vector<int>>& board)
{
    int size = board.size();
    std::cout << "当前盘面:\n";

    // 打印列数
    std::cout << "    "; // 为行号留出空间
    for (int j = 1; j <= size; ++j)
    {
        std::cout << std::setw(4) << j;
    }
    std::cout << std::endl;

    // 打印分隔线
    std::cout << "   " << std::string(size * 4 + 1, '-') << std::endl;

    for (int i = 0; i < size; ++i)
    {
        std::cout << std::setw(2) << i + 1 << " |"; // 打印行号和分隔符
        for (int num : board[i])
        {
            if (num == 0)
            {
                std::cout << std::setw(4) << " ";
            }
            else
            {
                std::cout << std::setw(4) << num;
            }
        }
        std::cout << std::endl;
    }
}

// 处理用户点击的两个位置的数字消除操作
bool handleClick(std::vector<std::vector<int>>& board, int x1, int y1, int x2, int y2)
{
    int size = board.size();

    // 检查输入的坐标是否有效

    if (x1 < 1 || x1 > size || y1 < 1 || y1 > size || x2 < 1 || x2 > size || y2 < 1 || y2 > size)
    {
        std::cout << "输入的坐标无效，请输入 1 到 " << size << " 之间的整数。" << std::endl;
        return false;
    }

    // 将 1 - size 的坐标转换为 0 - size-1 的索引

    x1--; y1--; x2--; y2--;
    int num1 = board[x1][y1];
    int num2 = board[x2][y2];

    // 检查所选位置是否已经为空

    if (num1 == 0 || num2 == 0)
    {
        std::cout << "所选位置已经没有数字，请重新选择。" << std::endl;
        return false;
    }

    // 检查是否选择了同一个位置

    if (x1 == x2 && y1 == y2)
    {
        std::cout << "不能选择同一个位置的数字进行消除。请重新选择。" << std::endl;
        return false;
    }

    if (canEliminate(num1, num2))
    {
        board[x1][y1] = 0;
        board[x2][y2] = 0;
        std::cout << "消除成功！" << std::endl;
        return true;
    }
    std::cout << "无法消除，请重新选择。" << std::endl;
    return false;
}

// 检查盘面是否所有数字都已消除
bool isBoardCleared(const std::vector<std::vector<int>>& board)
{
    for (const auto& row : board)
    {
        for (int num : row)
        {
            if (num != 0)
            {
                return false;
            }
        }
    }
    return true;
}

// 获取用户输入的用户名
std::string getUsername()
{
    std::string username;
    while (true)
    {
        std::cout << "请输入您的用户名: ";
        std::getline(std::cin, username);

        // 检查用户名是否为空或只包含空白字符
        if (username.empty() || username.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
        {
            std::cout << "用户名不能为空或只包含空白字符。请重新输入。" << std::endl;
        }
        else
        {
            break;
        }
    }
    return username;
}

// 游戏主逻辑
void startGame(std::vector<PlayerScore>& leaderboard_entries)
{
    std::string current_username = getUsername();
    std::cout << "欢迎, " << current_username << "!" << std::endl;

    int difficulty_choice;
    int board_size = 0; // 初始化棋盘大小

    while (true)
    {
        std::cout << "请选择游戏难度：\n";
        std::cout << "1. 简单模式 (4x4)\n";
        std::cout << "2. 普通模式 (6x6)\n";
        std::cout << "3. 困难模式 (8x8)\n";
        std::cout << "4. 自定义模式\n";
        std::cout << "请输入您的选择 (1-4): ";

        while (!(std::cin >> difficulty_choice))
        {
            std::cout << "输入无效，请输入整数。" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "请输入您的选择 (1-4): ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除缓冲区

        if (difficulty_choice == 1)
        {
            board_size = 4;
            break;
        }
        else if (difficulty_choice == 2)
        {
            board_size = 6;
            break;
        }
        else if (difficulty_choice == 3)
        {
            board_size = 8;
            break;
        }
        else if (difficulty_choice == 4)
        {
            while (true)
            {
                std::cout << "请输入棋盘大小 (2-10的偶数): ";
                while (!(std::cin >> board_size))
                {
                    std::cout << "输入无效，请输入整数。" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "请输入棋盘大小 (2-10的偶数): ";
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除缓冲区
                if (board_size >= 2 && board_size <= 10 && board_size % 2 == 0)
                {
                    break;
                }
                else
                {
                    std::cout << "棋盘大小必须是 2 到 10 之间的偶数。请重新输入。\n";
                }
            }
            break; // 在输入有效的自定义尺寸后退出难度选择循环
        }
        else
        {
            std::cout << "无效的选择，请重新输入 1 到 4 之间的数字。\n";
        }
    }

    std::cout << "\n游戏开始!" << std::endl;
    std::vector<std::vector<int>> game_board = generateBoard(board_size);
    printBoard(game_board);

    auto start_time = std::chrono::high_resolution_clock::now();

    while (!isBoardCleared(game_board))
    {
        int x1, y1, x2, y2;
        std::string input;

        // 获取第一个数字的坐标
        std::cout << "请输入第一个数字的坐标 (行 列)，范围 1 - " << board_size << " (输入 'a' 退出游戏)：";
        std::getline(std::cin, input);
        if (input == "a" || input == "A") {
            std::cout << "您已选择退出游戏，当前游戏数据将不计入排行榜。\n";
            return; // 退出游戏，不计入排行榜
        }
        std::istringstream iss1(input);
        while (!(iss1 >> x1 >> y1)) {
            std::cout << "输入无效，请输入整数或 'a' 退出。" << std::endl;
            std::cout << "请输入第一个数字的坐标 (行 列)，范围 1 - " << board_size << " (输入 'a' 退出游戏)：";
            std::getline(std::cin, input);
            if (input == "a" || input == "A") {
                std::cout << "您已选择退出游戏，当前游戏数据将不计入排行榜。\n";
                return; // 退出游戏，不计入排行榜
            }
            iss1.clear();
            iss1.str(input);
        }

        // 获取第二个数字的坐标
        std::cout << "请输入第二个数字的坐标 (行 列)，范围 1 - " << board_size << " (输入 'a' 退出游戏)：";
        std::getline(std::cin, input);
        if (input == "a" || input == "A") {
            std::cout << "您已选择退出游戏，当前游戏数据将不计入排行榜。\n";
            return; // 退出游戏，不计入排行榜
        }
        std::istringstream iss2(input);
        while (!(iss2 >> x2 >> y2)) {
            std::cout << "输入无效，请输入整数或 'a' 退出。" << std::endl;
            std::cout << "请输入第二个数字的坐标 (行 列)，范围 1 - " << board_size << " (输入 'a' 退出游戏)：";
            std::getline(std::cin, input);
            if (input == "a" || input == "A") {
                std::cout << "您已选择退出游戏，当前游戏数据将不计入排行榜。\n";
                return; // 退出游戏，不计入排行榜
            }
            iss2.clear();
            iss2.str(input);
        }

        handleClick(game_board, x1, y1, x2, y2);
        printBoard(game_board);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    std::cout << "恭喜你，所有数字已消除完毕！" << std::endl;
    std::cout << "游戏结束! 您用时: " << std::fixed << std::setprecision(2)
        << elapsed_seconds.count() << " 秒" << std::endl;

    PlayerScore new_score(current_username, elapsed_seconds.count(), difficulty_choice, board_size); // Pass difficulty and board_size
    leaderboard_entries.push_back(new_score);

    std::sort(leaderboard_entries.begin(), leaderboard_entries.end(),
        [](const PlayerScore& a, const PlayerScore& b)
        {
            return a.time_taken < b.time_taken;
        });

    std::cout << "正在保存排行榜数据..." << std::endl;
    saveLeaderboard(leaderboard_entries, LEADERBOARD_FILE);
    std::cout << "排行榜数据保存完成。" << std::endl;

    std::cout << "\n--- 最新排行榜 ---" << std::endl;
    displayLeaderboard(leaderboard_entries);
}


int main()
{
    std::vector<PlayerScore> leaderboard_entries;
    std::cout << "欢迎来到数连争霸！" << std::endl;

    // 尝试加载现有排行榜数据
    loadLeaderboard(leaderboard_entries, LEADERBOARD_FILE);

    int choice;
    while (true)
    {
        std::cout << "\n请选择功能:\n";
        std::cout << "1. 游戏规则\n";
        std::cout << "2. 开始游戏\n";
        std::cout << "3. 排行榜\n";
        std::cout << "4. 退出游戏\n"; // 新增的退出选项
        std::cout << "请输入您的选择 (1-4): ";

        while (!(std::cin >> choice))
        {
            std::cout << "输入无效，请输入整数。" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "请输入您的选择 (1-4): ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除缓冲区

        switch (choice)
        {
        case 1:
            std::cout << "\n游戏规则:\n";
            std::cout << "输入你想消除的两个数字的坐标，输入格式为“行 列”。\n";
            std::cout << "若两个数字相同，或者较大数是较小数的整数倍，则消除成功。\n";
            std::cout << "全部数字消除完毕即为游戏胜利。\n";
            break;
        case 2:
            startGame(leaderboard_entries);
            break;
        case 3:
            std::cout << "\n--- 当前排行榜 ---\n";
            displayLeaderboard(leaderboard_entries);
            break;
        case 4: // 处理退出游戏选项
            std::cout << "已退出游戏，感谢您的游玩！" << std::endl;
            return 0; // 退出程序
        default:
            std::cout << "无效的选择，请重新输入 1 到 4 之间的数字。\n";
            break;
        }
    }

    return 0;
}
