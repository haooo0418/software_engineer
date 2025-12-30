# Software Engineering Lab - Unit Testing & CI/CD

软件工程实验 - 单元测试、集成测试、模糊测试与持续集成

## 快速开始

```bash
# 安装依赖
pip install -r requirements.txt

# 运行所有测试
pytest -v --cov=. --cov-report=html

# 查看覆盖率报告
open htmlcov/index.html
```

## 项目内容

本项目完成了以下实验要求：

✅ **单元测试** - 2个模块，100+测试用例，100%覆盖率  
✅ **集成测试** - 3个测试组，自底向上集成方法  
✅ **模糊测试** - AFL++工具，C程序漏洞检测  
✅ **持续集成** - GitHub Actions自动化测试  
✅ **缺陷修复** - 测试驱动的5+缺陷修复流程  

## 文档

- [📘 完整实验说明](EXPERIMENT_README.md) - 详细的实验指南和使用说明
- [🐛 缺陷修复演示](BUG_FIXES_DEMO.md) - 5个缺陷的发现与修复过程
- [🔍 模糊测试指南](FUZZING_GUIDE.md) - AFL++使用教程

## 测试统计

- **总测试用例**: 101 条
- **代码覆盖率**: 100%
- **单元测试**: 88 条
- **集成测试**: 13 条

## CI/CD 状态

![CI Status](https://github.com/haooo0418/software_engineer/workflows/Python%20Project%20CI/badge.svg)

查看 [.github/workflows/ci.yml](.github/workflows/ci.yml) 了解CI配置详情。