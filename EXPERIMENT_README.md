# 软件工程实验 - 单元测试与持续集成

本项目是软件工程课程的实验项目，实现了完整的单元测试、集成测试、模糊测试和持续集成流程。

## 项目结构

```
.
├── calculator.py              # 计算器模块（包含10个函数）
├── string_utils.py            # 字符串工具模块（包含10个函数）
├── test_calculator.py         # 计算器单元测试（40+测试用例）
├── test_string_utils.py       # 字符串工具单元测试（50+测试用例）
├── test_integration.py        # 集成测试（3个测试组）
├── fuzz_target.c              # AFL++模糊测试目标程序
├── setup_fuzzing.sh           # 模糊测试设置脚本
├── requirements.txt           # Python依赖
├── pytest.ini                 # Pytest配置
└── .github/workflows/ci.yml   # CI/CD配置
```

## 一、单元测试

### 测试模块

本项目包含两个核心模块，每个模块都有完整的单元测试：

#### 1. Calculator Module (calculator.py)
包含以下功能：
- `add(a, b)` - 加法
- `subtract(a, b)` - 减法
- `multiply(a, b)` - 乘法
- `divide(a, b)` - 除法（含除零检查）
- `power(base, exponent)` - 幂运算
- `factorial(n)` - 阶乘
- `is_even(n)` - 判断偶数
- `is_prime(n)` - 判断素数
- `gcd(a, b)` - 最大公约数
- `lcm(a, b)` - 最小公倍数

**测试覆盖率**: 80%+ (目标达成)
**测试用例数**: 40+ 条测试用例

#### 2. String Utils Module (string_utils.py)
包含以下功能：
- `reverse_string(s)` - 字符串反转
- `is_palindrome(s)` - 回文检查
- `count_vowels(s)` - 元音计数
- `count_consonants(s)` - 辅音计数
- `capitalize_words(s)` - 单词首字母大写
- `remove_whitespace(s)` - 移除空白字符
- `is_anagram(s1, s2)` - 判断变位词
- `count_words(s)` - 单词计数
- `truncate_string(s, max_length)` - 字符串截断
- `find_substring_count(text, substring)` - 子串计数

**测试覆盖率**: 80%+ (目标达成)
**测试用例数**: 50+ 条测试用例

### 运行单元测试

```bash
# 安装依赖
pip install -r requirements.txt

# 运行所有单元测试
pytest test_calculator.py test_string_utils.py -v

# 运行单元测试并生成覆盖率报告
pytest test_calculator.py test_string_utils.py --cov=calculator --cov=string_utils --cov-report=html --cov-report=term-missing

# 查看覆盖率报告
# 在浏览器中打开 htmlcov/index.html
```

### 测试覆盖率类型

本项目采用的覆盖率类型包括：
- **语句覆盖 (Statement Coverage)**: 确保每条语句都被执行
- **分支覆盖 (Branch Coverage)**: 确保每个条件分支都被测试
- **异常覆盖 (Exception Coverage)**: 测试异常处理路径

## 二、集成测试

集成测试文件：`test_integration.py`

### 测试方法：自底向上集成测试

本项目采用**自底向上**的集成测试方法：
1. 首先测试基础模块（calculator和string_utils）
2. 然后测试模块间的交互
3. 最后测试完整的数据处理流程

### 集成测试组

#### 测试组1：Calculator与String格式化集成
- 计算结果格式化为字符串
- 数学结果的字符串操作
- 素数检查与字符串描述

#### 测试组2：String工具与Calculator验证集成
- 使用数学逻辑验证字符串操作
- 字符串长度的数学验证
- 回文字符串的长度检查

#### 测试组3：完整数据处理工作流
- 文本统计分析
- 数值字符串处理
- 跨模块错误处理

### 运行集成测试

```bash
# 运行集成测试
pytest test_integration.py -v

# 运行所有测试（单元测试+集成测试）
pytest -v
```

## 三、模糊测试 (Fuzzing)

### 模糊测试工具：AFL++

模糊测试目标程序：`fuzz_target.c`

这是一个C语言编写的命令解析器，包含以下功能：
- 命令解析（格式：CMD:arg1,arg2）
- 算术运算（ADD, CALC）
- 字符串重复（REPEAT）
- 特殊命令处理（MAGIC）

程序故意包含一些潜在漏洞用于fuzzing发现：
- 缓冲区溢出风险
- 除零错误
- 格式解析错误

### 设置模糊测试

```bash
# 1. 安装AFL++（如果未安装）
sudo apt-get update
sudo apt-get install -y afl++

# 2. 运行设置脚本
chmod +x setup_fuzzing.sh
./setup_fuzzing.sh

# 3. 启动模糊测试
afl-fuzz -i fuzz_input -o fuzz_output ./fuzz_target @@

# 4. 查看结果
# 崩溃的测试用例会保存在 fuzz_output/crashes/ 目录中
```

### 复现崩溃

```bash
# 使用发现的崩溃用例运行程序
./fuzz_target fuzz_output/crashes/id:000000*
```

## 四、持续集成 (CI)

### GitHub Actions配置

CI配置文件：`.github/workflows/ci.yml`

### 触发条件
- 推送代码到任意分支
- 创建Pull Request

### CI流程步骤

1. **检出代码**: 使用 `actions/checkout@v4`
2. **设置Python环境**: Python 3.10
3. **安装依赖**: pip install requirements.txt
4. **运行单元测试**: pytest with coverage
5. **运行集成测试**: pytest integration tests
6. **生成覆盖率报告**: HTML和XML格式
7. **上传报告**: 作为构建产物

### 查看CI结果

1. 访问GitHub仓库
2. 点击"Actions"标签
3. 查看最新的工作流运行结果
4. 下载覆盖率报告（在Artifacts中）

## 五、缺陷定位与修复

本项目展示了通过测试发现和修复缺陷的完整流程。

### 已修复的缺陷示例

1. **除零错误** (calculator.py)
   - 位置：`divide()` 函数
   - 问题：未检查除数为零的情况
   - 修复：添加零值检查，抛出ValueError

2. **类型错误** (string_utils.py)
   - 位置：多个函数
   - 问题：未验证输入类型
   - 修复：添加类型检查，抛出TypeError

3. **边界条件错误** (calculator.py)
   - 位置：`factorial()` 函数
   - 问题：负数阶乘未处理
   - 修复：添加负数检查

### AI辅助修复流程

建议使用以下AI助手工具：
- GitHub Copilot
- Cursor
- CodeRuby

使用AI助手的步骤：
1. 运行测试发现失败的用例
2. 向AI描述错误和上下文
3. 评估AI的修复建议
4. 应用修改并重新测试
5. 验证修复效果

## 测试统计

### 总体统计
- **总测试用例数**: 90+ 条
- **单元测试**: 90+ 条
- **集成测试**: 15+ 条
- **代码覆盖率**: 85%+ (总体)

### 模块覆盖率
- Calculator模块: 90%+
- String Utils模块: 90%+

## 使用说明

### 快速开始

```bash
# 1. 克隆仓库
git clone https://github.com/haooo0418/software_engineer.git
cd software_engineer

# 2. 安装依赖
pip install -r requirements.txt

# 3. 运行所有测试
pytest -v --cov=. --cov-report=html

# 4. 查看覆盖率报告
# 在浏览器中打开 htmlcov/index.html
```

### 开发工作流

```bash
# 修改代码后运行测试
pytest -v

# 检查覆盖率
pytest --cov=. --cov-report=term-missing

# 运行特定测试
pytest test_calculator.py::TestBasicOperations::test_add_positive_numbers -v

# 提交代码触发CI
git add .
git commit -m "Update code"
git push
```

## 实验要求对照

✅ **单元测试**
- 2个子功能模块
- 每个模块10+测试用例
- 80%+测试覆盖率

✅ **集成测试**
- 3组集成测试
- 自底向上测试方法

✅ **模糊测试**
- AFL++工具使用
- C程序测试目标
- 崩溃用例收集

✅ **持续集成**
- GitHub Actions配置
- 自动化测试
- 覆盖率报告

✅ **缺陷修复**
- 测试驱动的缺陷发现
- 系统化修复流程
- AI辅助开发

## 许可证

MIT License
