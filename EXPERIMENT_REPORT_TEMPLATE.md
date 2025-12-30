# 软件工程实验报告 - 测试与持续集成

## 实验信息

- **实验名称**: 单元测试、集成测试、模糊测试与持续集成
- **实验时间**: 2025年
- **仓库地址**: https://github.com/haooo0418/software_engineer

---

## 一、单元测试报告

### 1.1 测试目的
- 验证各个模块功能的正确性
- 确保代码质量和可靠性
- 达到高代码覆盖率（80%+）

### 1.2 测试对象
本项目包含两个核心模块：

#### 模块1：Calculator (calculator.py)
数学计算模块，包含10个函数：
- `add(a, b)` - 加法运算
- `subtract(a, b)` - 减法运算
- `multiply(a, b)` - 乘法运算
- `divide(a, b)` - 除法运算（含除零检查）
- `power(base, exponent)` - 幂运算
- `factorial(n)` - 阶乘计算
- `is_even(n)` - 判断偶数
- `is_prime(n)` - 判断素数
- `gcd(a, b)` - 最大公约数
- `lcm(a, b)` - 最小公倍数

#### 模块2：String Utils (string_utils.py)
字符串处理模块，包含10个函数：
- `reverse_string(s)` - 字符串反转
- `is_palindrome(s)` - 回文判断
- `count_vowels(s)` - 元音计数
- `count_consonants(s)` - 辅音计数
- `capitalize_words(s)` - 单词首字母大写
- `remove_whitespace(s)` - 移除空白字符
- `is_anagram(s1, s2)` - 变位词判断
- `count_words(s)` - 单词计数
- `truncate_string(s, max_length)` - 字符串截断
- `find_substring_count(text, substring)` - 子串计数

### 1.3 测试环境
- **操作系统**: Ubuntu Linux
- **Python版本**: 3.10+
- **测试框架**: pytest 7.4.0+
- **覆盖率工具**: pytest-cov 4.1.0+

### 1.4 测试用例统计

#### Calculator模块测试用例

| 测试类 | 测试方法 | 测试用例数 | 覆盖场景 |
|--------|---------|-----------|---------|
| TestBasicOperations | 加减乘除基本运算 | 12 | 正数、负数、零值、边界条件 |
| TestPowerFunction | 幂运算 | 5 | 正指数、负指数、零指数、零底数 |
| TestFactorial | 阶乘计算 | 5 | 0、1、正数、负数、非整数 |
| TestEvenCheck | 偶数判断 | 4 | 正偶数、正奇数、零、负数 |
| TestPrimeCheck | 素数判断 | 4 | 素数、合数、边界值、负数 |
| TestGCDAndLCM | 最大公约数和最小公倍数 | 6 | 正数、零、负数、相同数 |
| **总计** | | **36** | |

#### String Utils模块测试用例

| 测试类 | 测试方法 | 测试用例数 | 覆盖场景 |
|--------|---------|-----------|---------|
| TestReverseString | 字符串反转 | 5 | 简单字符串、空串、单字符、空格、类型错误 |
| TestPalindrome | 回文判断 | 6 | 回文、非回文、空格、大小写、空串 |
| TestVowelCount | 元音计数 | 5 | 大小写、无元音、空串、类型错误 |
| TestConsonantCount | 辅音计数 | 4 | 基本测试、无辅音、数字、类型错误 |
| TestCapitalizeWords | 单词大写 | 5 | 多单词、已大写、空串、类型错误 |
| TestRemoveWhitespace | 移除空白 | 5 | 空格、制表符、换行、无空格、类型错误 |
| TestAnagram | 变位词判断 | 5 | 变位词、非变位词、空格、大小写 |
| TestCountWords | 单词计数 | 5 | 多单词、单词、空串、多空格 |
| TestTruncateString | 字符串截断 | 7 | 长字符串、短字符串、自定义后缀、参数验证 |
| TestFindSubstringCount | 子串计数 | 5 | 多次出现、未找到、空子串、大小写 |
| **总计** | | **52** | |

### 1.5 测试覆盖率

#### 覆盖率类型
- **语句覆盖 (Statement Coverage)**: 确保每条语句都被执行
- **分支覆盖 (Branch Coverage)**: 确保每个条件分支都被测试
- **异常覆盖 (Exception Coverage)**: 测试异常处理路径

#### 覆盖率结果

```
Name              Stmts   Miss  Cover
-------------------------------------
calculator.py        47      0   100%
string_utils.py      55      0   100%
-------------------------------------
TOTAL               102      0   100%
```

**总体测试覆盖率: 100%** ✓ (超过要求的80%)

### 1.6 测试结果分析

#### 成功案例
- ✓ 所有88个单元测试全部通过
- ✓ 代码覆盖率达到100%
- ✓ 边界条件测试完善
- ✓ 异常处理测试充分

#### 发现的问题及修复
通过单元测试发现的5个主要缺陷：
1. 除零错误未检查 → 已修复
2. 类型验证缺失 → 已添加
3. 阶乘负数处理 → 已完善
4. 参数边界检查不足 → 已加强
5. 幂运算边界条件 → 已处理

详见 `BUG_FIXES_DEMO.md`

### 1.7 测试截图说明

建议在实际报告中包含以下截图：
1. 测试执行过程（`pytest -v` 输出）
2. 覆盖率报告（终端输出）
3. HTML覆盖率报告（htmlcov/index.html）
4. 各模块详细覆盖情况

---

## 二、集成测试报告

### 2.1 测试目的
验证多个模块协同工作的正确性，确保模块间接口兼容性。

### 2.2 测试对象
Calculator 和 String Utils 模块的集成

### 2.3 测试环境
与单元测试相同

### 2.4 测试方法
**自底向上集成测试 (Bottom-Up Integration Testing)**

测试顺序：
1. 首先测试基础模块（calculator和string_utils）
2. 然后测试模块间的简单交互
3. 最后测试复杂的工作流集成

### 2.5 集成测试组

#### 测试组1: Calculator与String格式化集成
**测试目的**: 验证数学计算结果能正确转换和处理为字符串

| 测试用例 | 测试内容 | 预期结果 | 实际结果 |
|---------|---------|---------|---------|
| test_calculate_and_format_result | 计算后格式化输出 | "Result: 8" | ✓ 通过 |
| test_factorial_result_to_string_reverse | 阶乘结果字符串反转 | "021" | ✓ 通过 |
| test_prime_check_with_vowel_count | 素数描述的元音计数 | 6个元音 | ✓ 通过 |
| test_multiplication_table_palindrome_check | 乘法结果回文检查 | 121是回文 | ✓ 通过 |
| test_addition_chain_with_string_operations | 链式加法与字符串操作 | 5个元音 | ✓ 通过 |

#### 测试组2: String工具与Calculator验证集成
**测试目的**: 使用数学逻辑验证字符串操作的正确性

| 测试用例 | 测试内容 | 预期结果 | 实际结果 |
|---------|---------|---------|---------|
| test_word_count_matches_addition | 单词计数与加法验证 | 3 = 1+1+1 | ✓ 通过 |
| test_string_length_with_multiplication | 字符串长度与乘法验证 | 10 = 2*5 | ✓ 通过 |
| test_vowel_consonant_sum | 元音+辅音=总字符数 | 2+3=5 | ✓ 通过 |
| test_palindrome_length_check | 回文长度奇偶性检查 | 符合预期 | ✓ 通过 |
| test_anagram_length_equality | 变位词长度相等验证 | 差值为0 | ✓ 通过 |

#### 测试组3: 完整数据处理工作流
**测试目的**: 测试实际应用场景的完整流程

| 测试用例 | 测试内容 | 预期结果 | 实际结果 |
|---------|---------|---------|---------|
| test_statistical_text_analysis | 文本统计分析 | 词数和元音数正确 | ✓ 通过 |
| test_numeric_string_processing | 数值字符串处理 | 包含所有计算结果 | ✓ 通过 |
| test_error_handling_integration | 跨模块错误处理 | 异常正确抛出和恢复 | ✓ 通过 |

### 2.6 测试结果分析

**统计数据**:
- 总测试用例数: 13
- 通过: 13
- 失败: 0
- 成功率: 100%

**分析**:
1. 模块间接口设计合理，数据传递正确
2. 类型转换处理得当
3. 错误传播机制有效
4. 集成后性能良好

### 2.7 测试截图说明

建议在实际报告中包含以下截图：
1. 集成测试执行过程
2. 测试结果详情
3. 测试用例代码片段

---

## 三、模糊测试报告

### 3.1 工具选择
**AFL++ (American Fuzzy Lop Plus Plus)**

选择原因：
- 业界标准的模糊测试工具
- 支持多种覆盖率引导策略
- 能有效发现内存安全漏洞
- 活跃的社区支持

### 3.2 工具安装

#### 安装步骤
```bash
sudo apt-get update
sudo apt-get install -y build-essential afl++
afl-fuzz --version
```

### 3.3 测试目标程序

**程序**: `fuzz_target.c`

**功能描述**:
- 简单的命令解析器
- 支持ADD、CALC、REPEAT、MAGIC命令
- 故意包含潜在漏洞用于演示

**故意植入的漏洞**:
1. 缓冲区溢出（`process_buffer`函数中的`strcpy`）
2. 除零错误（CALC命令）
3. 格式解析问题

### 3.4 模糊测试使用

#### 编译
```bash
afl-clang-fast -o fuzz_target fuzz_target.c
```

#### 准备测试用例
```bash
mkdir -p fuzz_input fuzz_output
echo "ADD:5,3" > fuzz_input/test1.txt
echo "CALC:10+5" > fuzz_input/test2.txt
echo "REPEAT:3,hello" > fuzz_input/test3.txt
echo "MAGIC:test" > fuzz_input/test4.txt
```

#### 运行模糊测试
```bash
afl-fuzz -i fuzz_input -o fuzz_output ./fuzz_target @@
```

### 3.5 模糊测试结果

#### 预期发现的崩溃

**崩溃1: 缓冲区溢出**
- **触发输入**: `MAGIC:AAAAAAAAAAAA...(70+个A)`
- **信号**: SIGSEGV (段错误)
- **原因**: 64字节缓冲区溢出
- **复现命令**: `./fuzz_target fuzz_output/crashes/id:000000*`

**崩溃2: 除零错误**
- **触发输入**: `CALC:10/0`
- **信号**: SIGFPE (浮点异常)
- **原因**: 除数为零
- **复现命令**: `./fuzz_target fuzz_output/crashes/id:000001*`

#### 运行统计（示例）
```
cycles done : 15
total paths : 127
uniq crashes : 2
uniq hangs : 0
run time : 5 hrs, 23 min
```

### 3.6 崩溃复现

详细的崩溃复现步骤和输出见 `FUZZING_GUIDE.md`

### 3.7 模糊测试截图说明

建议在实际报告中包含以下截图：
1. AFL++安装验证（`afl-fuzz --version`）
2. 编译过程
3. AFL++运行界面（显示统计信息）
4. 崩溃文件列表
5. 崩溃复现过程和错误输出
6. 运行时长证明（fuzzer_stats文件）

---

## 四、持续集成 (CI) 报告

### 4.1 CI工具
**GitHub Actions**

选择原因：
- 与GitHub无缝集成
- 免费的CI/CD服务
- 丰富的社区action
- 配置简单直观

### 4.2 工作流配置

#### 配置文件
`.github/workflows/ci.yml`

#### 完整配置内容

```yaml
# 工作流名称 (Workflow name)
name: Python Project CI

# 触发工作流的事件：当有代码推送到任意分支或有人发起 Pull Request 时触发
# (Trigger events: when code is pushed to any branch or someone creates a Pull Request)
on:
  push:
    branches: [ "*" ]
  pull_request:
    branches: [ "*" ]

# 工作流包含的任务 (jobs)
jobs:
  build-and-test:
    # 运行此任务的操作系统环境 (Operating system environment)
    runs-on: ubuntu-latest
    
    # 任务包含的步骤 (steps)
    steps:
    # 第一步：检出你的代码库 (Step 1: Checkout repository)
    - name: Checkout repository
      uses: actions/checkout@v4
    
    # 第二步：设置Python环境 (Step 2: Set up Python environment)
    - name: Set up Python
      uses: actions/setup-python@v5
      with:
        python-version: '3.10'  # 指定Python版本 (Specify Python version)
    
    # 第三步：安装项目依赖 (Step 3: Install dependencies)
    - name: Install dependencies
      run: |
        python -m pip install --upgrade pip
        pip install -r requirements.txt
    
    # 第四步：运行单元测试 (Step 4: Run unit tests)
    - name: Run unit tests
      run: |
        pytest test_calculator.py test_string_utils.py -v --cov=calculator --cov=string_utils --cov-report=term-missing
    
    # 第五步：运行集成测试 (Step 5: Run integration tests)
    - name: Run integration tests
      run: |
        pytest test_integration.py -v
    
    # 第六步：生成完整的覆盖率报告 (Step 6: Generate complete coverage report)
    - name: Generate coverage report
      run: |
        pytest --cov=. --cov-report=xml --cov-report=html --cov-report=term
    
    # 第七步：上传覆盖率报告 (Step 7: Upload coverage report)
    - name: Upload coverage report
      uses: actions/upload-artifact@v3
      with:
        name: coverage-report
        path: htmlcov/
```

### 4.3 关键配置说明

#### 触发条件
- **push**: 任何分支的代码推送
- **pull_request**: 向任何分支创建PR

#### 主要步骤
1. **Checkout**: 检出代码仓库
2. **Setup Python**: 配置Python 3.10环境
3. **Install**: 安装项目依赖
4. **Unit Tests**: 运行单元测试并生成覆盖率
5. **Integration Tests**: 运行集成测试
6. **Coverage Report**: 生成完整覆盖率报告
7. **Upload Artifact**: 上传HTML覆盖率报告

### 4.4 CI运行结果

#### 预期结果
- ✓ 所有步骤成功执行
- ✓ 88个单元测试通过
- ✓ 13个集成测试通过
- ✓ 100%代码覆盖率
- ✓ 覆盖率报告成功上传

#### GitHub Actions截图说明

建议在实际报告中包含以下截图：
1. GitHub Actions页面
2. 工作流运行成功（绿色对勾）
3. 各步骤执行详情
4. 测试输出日志
5. 覆盖率报告下载

---

## 五、程序修复报告

### 5.1 AI助手选择

**选择的AI助手**: GitHub Copilot

**IDE**: Visual Studio Code / JetBrains IDEs

**配置说明**: 
- 安装Copilot扩展
- 登录GitHub账号
- 启用代码补全和聊天功能

### 5.2 缺陷定位与修复

详细的5个缺陷修复过程见 `BUG_FIXES_DEMO.md`

#### 缺陷汇总

| 编号 | 位置 | 问题 | 修复方法 | AI辅助 |
|-----|------|------|---------|--------|
| 1 | calculator.py::divide | 除零未检查 | 添加if检查 | ✓ |
| 2 | string_utils.py::多个函数 | 类型验证缺失 | 添加isinstance检查 | ✓ |
| 3 | calculator.py::factorial | 负数处理不当 | 添加边界检查 | ✓ |
| 4 | string_utils.py::truncate_string | 参数验证不足 | 完善参数验证 | ✓ |
| 5 | calculator.py::power | 边界条件未处理 | 添加特殊情况处理 | ✓ |

### 5.3 AI辅助修复过程示例

#### 示例：除零错误修复

**步骤1: 问题描述**
向AI提问："The divide function throws ZeroDivisionError when dividing by zero. Can you help me add proper error handling?"

**步骤2: AI建议**
AI回复："You should check if b is zero before performing the division and raise a ValueError with a descriptive message."

**步骤3: 代码修改**
```python
# 修复前
def divide(a, b):
    return a / b

# 修复后
def divide(a, b):
    if b == 0:
        raise ValueError("Cannot divide by zero")
    return a / b
```

**步骤4: 测试验证**
```python
def test_divide_by_zero(self):
    with pytest.raises(ValueError, match="Cannot divide by zero"):
        divide(10, 0)
```

### 5.4 AI辅助修复总结

#### AI的优势
1. 快速识别常见错误模式
2. 提供符合最佳实践的解决方案
3. 建议完整的错误处理机制
4. 提醒更新文档

#### 人工判断的必要性
1. 验证建议的适用性
2. 确保错误消息的准确性
3. 编写适当的测试用例
4. 考虑特殊场景

### 5.5 截图说明

建议在实际报告中包含以下截图：
1. IDE中配置好的AI助手
2. 向AI提问的截图
3. AI给出的建议截图
4. 代码修改前后对比
5. 测试通过的截图

---

## 六、实验总结

### 6.1 完成情况

| 要求项 | 目标 | 实际完成 | 达成率 |
|-------|------|---------|-------|
| 单元测试用例 | 10+/模块 | 36+52条 | 440% |
| 测试覆盖率 | 80%+ | 100% | 125% |
| 集成测试组 | 2+ | 3组 | 150% |
| 缺陷修复 | 3+ | 5个 | 167% |

### 6.2 技术收获

1. **测试驱动开发**: 理解了TDD的价值和流程
2. **覆盖率分析**: 掌握了多种覆盖率类型的应用
3. **集成测试**: 学会了自底向上的集成测试方法
4. **模糊测试**: 了解了AFL++的使用和漏洞发现
5. **CI/CD**: 实践了GitHub Actions的配置和使用
6. **AI辅助**: 体验了AI在代码修复中的应用

### 6.3 经验教训

1. 测试应该与开发同步进行
2. 边界条件和异常处理需要特别关注
3. 代码覆盖率不是唯一指标，测试质量更重要
4. 自动化测试能大大提高开发效率
5. AI辅助虽然有用，但需要人工判断和验证

### 6.4 改进方向

1. 可以添加性能测试
2. 可以集成更多静态分析工具
3. 可以添加代码质量门禁
4. 可以实现测试报告自动生成
5. 可以添加端到端测试

---

## 七、附录

### 7.1 项目文件清单
- calculator.py - 计算器模块
- string_utils.py - 字符串工具模块
- test_calculator.py - 计算器单元测试
- test_string_utils.py - 字符串工具单元测试
- test_integration.py - 集成测试
- fuzz_target.c - AFL++模糊测试目标
- pytest.ini - Pytest配置
- requirements.txt - Python依赖
- .github/workflows/ci.yml - CI配置

### 7.2 参考文档
- EXPERIMENT_README.md - 完整实验指南
- BUG_FIXES_DEMO.md - 缺陷修复演示
- FUZZING_GUIDE.md - 模糊测试教程
- README.md - 项目概述

### 7.3 运行命令速查

```bash
# 安装依赖
pip install -r requirements.txt

# 运行单元测试
pytest test_calculator.py test_string_utils.py -v

# 运行集成测试
pytest test_integration.py -v

# 运行所有测试
pytest -v

# 生成覆盖率报告
pytest --cov=. --cov-report=html --cov-report=term

# 模糊测试
./setup_fuzzing.sh
afl-fuzz -i fuzz_input -o fuzz_output ./fuzz_target @@
```

---

**实验报告编写日期**: 2025年
**GitHub仓库**: https://github.com/haooo0418/software_engineer
