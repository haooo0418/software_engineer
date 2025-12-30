# AFL++ 模糊测试指南

本文档提供了使用 AFL++ 对 C 程序进行模糊测试的完整指南。

## 目标程序

我们的目标是 `fuzz_target.c`，这是一个简单的命令解析器，支持以下命令格式：

```
ADD:5,3          # 加法: 5 + 3
CALC:10+5        # 计算器: 10 + 5
CALC:20/4        # 计算器: 20 / 4
REPEAT:3,hello   # 重复字符串 3 次
MAGIC:test       # 特殊命令
```

### 程序中故意植入的漏洞

为了演示模糊测试的有效性，程序包含以下潜在问题：

1. **缓冲区溢出**: `process_buffer()` 函数中的 `strcpy` 可能导致溢出
2. **除零错误**: `CALC` 命令中的除法操作
3. **格式解析问题**: 对非标准输入的处理

## 安装 AFL++

### Ubuntu/Debian

```bash
# 安装依赖
sudo apt-get update
sudo apt-get install -y build-essential python3-dev automake \
    cmake git flex bison libglib2.0-dev libpixman-1-dev python3-setuptools

# 从源码安装 AFL++
git clone https://github.com/AFLplusplus/AFLplusplus
cd AFLplusplus
make distrib
sudo make install

# 验证安装
afl-fuzz --version
```

### macOS

```bash
# 使用 Homebrew
brew install afl++

# 验证安装
afl-fuzz --version
```

## 编译目标程序

AFL++ 需要使用特殊的编译器来插桩代码：

```bash
# 使用 afl-clang-fast 编译
afl-clang-fast -o fuzz_target fuzz_target.c

# 或使用 afl-gcc
afl-gcc -o fuzz_target fuzz_target.c
```

## 准备测试用例

创建初始输入目录和测试用例：

```bash
# 创建目录
mkdir -p fuzz_input
mkdir -p fuzz_output

# 创建初始测试用例（种子输入）
echo "ADD:5,3" > fuzz_input/test1.txt
echo "CALC:10+5" > fuzz_input/test2.txt
echo "CALC:20/4" > fuzz_input/test3.txt
echo "REPEAT:3,hello" > fuzz_input/test4.txt
echo "MAGIC:test" > fuzz_input/test5.txt
echo "ADD:0,0" > fuzz_input/test6.txt
```

或使用提供的脚本：

```bash
chmod +x setup_fuzzing.sh
./setup_fuzzing.sh
```

## 运行模糊测试

### 基本运行

```bash
# 基本语法
afl-fuzz -i fuzz_input -o fuzz_output -- ./fuzz_target @@

# 参数说明:
# -i fuzz_input    : 输入目录（种子文件）
# -o fuzz_output   : 输出目录（保存结果）
# @@               : 表示文件输入位置
```

### 高级选项

```bash
# 使用多个核心并行模糊测试
# 主进程
afl-fuzz -i fuzz_input -o fuzz_output -M fuzzer01 -- ./fuzz_target @@

# 从进程（在另一个终端）
afl-fuzz -i fuzz_input -o fuzz_output -S fuzzer02 -- ./fuzz_target @@

# 指定超时时间（毫秒）
afl-fuzz -i fuzz_input -o fuzz_output -t 1000 -- ./fuzz_target @@

# 跳过确定性阶段（快速模式）
afl-fuzz -i fuzz_input -o fuzz_output -d -- ./fuzz_target @@
```

## 理解 AFL++ 输出

AFL++ 运行时会显示实时统计：

```
┌─ process timing ─────────────────────────────────┐
│        run time : 0 days, 0 hrs, 10 min, 30 sec  │
│   last new path : 0 days, 0 hrs, 5 min, 12 sec   │
└──────────────────────────────────────────────────┘

┌─ overall results ────────────────────────────────┐
│   cycles done : 15                                │
│  total paths : 127                                │
│ uniq crashes : 3                                  │
│   uniq hangs : 0                                  │
└──────────────────────────────────────────────────┘
```

### 关键指标

- **cycles done**: 完成的测试周期数
- **total paths**: 发现的唯一执行路径数
- **uniq crashes**: 发现的唯一崩溃数
- **uniq hangs**: 发现的唯一挂起数

## 分析崩溃

### 查看崩溃文件

```bash
# 崩溃文件位置
ls -la fuzz_output/default/crashes/

# 示例输出:
# id:000000,sig:06,src:000002,time:1234,op:havoc,rep:8
# id:000001,sig:11,src:000005,time:5678,op:splice,rep:2
```

### 文件名含义

- `id:000000` - 崩溃编号
- `sig:06` - 信号类型 (6=SIGABRT, 11=SIGSEGV)
- `src:000002` - 源自哪个测试用例
- `time:1234` - 发现时间（微秒）
- `op:havoc` - 使用的变异操作

### 复现崩溃

```bash
# 方法 1: 直接运行
./fuzz_target fuzz_output/default/crashes/id:000000*

# 方法 2: 使用输入重定向
./fuzz_target < fuzz_output/default/crashes/id:000000*

# 方法 3: 使用调试器
gdb ./fuzz_target
(gdb) run fuzz_output/default/crashes/id:000000*
(gdb) bt  # 查看调用栈
```

## 使用 AddressSanitizer 增强检测

AddressSanitizer (ASan) 可以检测更多内存错误：

```bash
# 使用 ASan 编译
AFL_USE_ASAN=1 afl-clang-fast -o fuzz_target_asan fuzz_target.c

# 运行模糊测试
afl-fuzz -i fuzz_input -o fuzz_output_asan -m none -- ./fuzz_target_asan @@

# 复现时会看到详细的 ASan 报告
./fuzz_target_asan fuzz_output_asan/default/crashes/id:000000*
```

## 预期发现的漏洞示例

### 漏洞 1: 缓冲区溢出

**触发输入**:
```
MAGIC:AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```

**症状**: SIGSEGV (信号 11)

**原因**: `process_buffer()` 中的 `strcpy` 将过长的输入复制到 64 字节的缓冲区

### 漏洞 2: 除零错误

**触发输入**:
```
CALC:10/0
```

**症状**: SIGFPE (信号 8)

**原因**: 除法操作未检查除数为零

### 漏洞 3: 整数溢出

**触发输入**:
```
ADD:2147483647,1
```

**症状**: 可能导致意外结果

## 修复建议

### 修复缓冲区溢出

```c
// 修复前
strcpy(buffer, input + 6);

// 修复后
strncpy(buffer, input + 6, sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';
```

### 修复除零错误

已在代码中包含：
```c
case '/': 
    if (num2 == 0) {
        fprintf(stderr, "Division by zero!\n");
        return -1;
    }
    return num1 / num2;
```

## 测试时长建议

- **快速测试**: 30 分钟 - 1 小时
- **标准测试**: 2-5 小时
- **深度测试**: 8+ 小时
- **完整测试**: 24+ 小时

## 停止模糊测试

```bash
# 按 Ctrl+C 停止
# 或发送 SIGTERM
pkill afl-fuzz
```

## 查看完整报告

```bash
# AFL++ 会生成统计文件
cat fuzz_output/default/fuzzer_stats

# 查看图表（需要 gnuplot）
afl-plot fuzz_output/default fuzz_output/plots
```

## 常见问题

### 问题: "AFL++ 抱怨 CPU 频率调节器"

```bash
# 临时解决
sudo sh -c "echo performance | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor"

# 或使用 -d 选项跳过检查
afl-fuzz -d -i fuzz_input -o fuzz_output -- ./fuzz_target @@
```

### 问题: "系统内核不支持 core dumps"

```bash
# 设置 core dump pattern
sudo sh -c "echo core > /proc/sys/kernel/core_pattern"

# 或使用 -C 选项
afl-fuzz -C -i fuzz_input -o fuzz_output -- ./fuzz_target @@
```

### 问题: "没有发现新路径"

可能原因：
1. 种子输入质量不好
2. 程序逻辑简单
3. 需要运行更长时间

解决方案：
1. 添加更多样化的种子输入
2. 使用字典文件（-x 选项）
3. 延长运行时间

## 实验报告截图建议

1. **安装截图**: AFL++ 版本信息
   ```bash
   afl-fuzz --version
   ```

2. **编译截图**: 编译过程
   ```bash
   afl-clang-fast -o fuzz_target fuzz_target.c
   ```

3. **运行截图**: AFL++ 运行界面（显示统计信息）

4. **崩溃截图**: 
   - 崩溃文件列表
   - 崩溃复现过程
   - 错误信息输出

5. **运行时长证明**: 
   - fuzzer_stats 文件内容
   - run_time 字段显示至少 5 小时

## 总结

AFL++ 是一个强大的模糊测试工具，能够自动发现程序中的安全漏洞。通过：
1. 适当的编译选项
2. 高质量的种子输入
3. 充足的运行时间

可以有效地发现缓冲区溢出、除零错误、整数溢出等各类漏洞。

## 参考资源

- AFL++ 官方文档: https://aflplus.plus/
- AFL++ GitHub: https://github.com/AFLplusplus/AFLplusplus
- 模糊测试教程: https://www.jianshu.com/p/b7936d29be28
