#!/bin/bash

# Comprehensive Code Quality Checker for C++20 Binance API Project
# Combines custom coding standards checks with cppcheck static analysis

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}Running comprehensive code quality checks...${NC}"
echo "=============================================="

# Run custom coding standards checker
echo -e "${BLUE}1. Checking coding standards...${NC}"
if ./scripts/check-coding-standards.sh; then
    echo -e "${GREEN}✓ Coding standards check passed${NC}"
    standards_result=0
else
    echo -e "${RED}✗ Coding standards violations found${NC}"
    standards_result=1
fi

echo ""

# Run cppcheck static analysis
echo -e "${BLUE}2. Running static analysis with cppcheck...${NC}"
if cppcheck --project=.cppcheck --std=c++20 --enable=all --suppress=missingIncludeSystem --error-exitcode=1 --quiet; then
    echo -e "${GREEN}✓ Static analysis passed${NC}"
    cppcheck_result=0
else
    echo -e "${RED}✗ Static analysis found issues${NC}"
    cppcheck_result=1
fi

echo ""
echo "=============================================="

# Summary
if [ $standards_result -eq 0 ] && [ $cppcheck_result -eq 0 ]; then
    echo -e "${GREEN}✓ All code quality checks passed!${NC}"
    exit 0
else
    echo -e "${RED}✗ Code quality issues found:${NC}"
    if [ $standards_result -ne 0 ]; then
        echo -e "  ${RED}- Coding standards violations${NC}"
    fi
    if [ $cppcheck_result -ne 0 ]; then
        echo -e "  ${RED}- Static analysis issues${NC}"
    fi
    echo ""
    echo -e "${YELLOW}Please fix the issues above before proceeding.${NC}"
    exit 1
fi
