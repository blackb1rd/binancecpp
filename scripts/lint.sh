#!/bin/bash
# Script to run all code quality checks (clang-format, cpplint, cppcheck)

echo "🔍 Running code quality checks..."
echo

# Check if required tools are installed
if ! command -v clang-format &> /dev/null; then
    echo "❌ clang-format not found. Install with: sudo apt-get install clang-format"
    exit 1
fi

if ! command -v cpplint &> /dev/null; then
    echo "❌ cpplint not found. Install with: pip install cpplint"
    exit 1
fi

if ! command -v cppcheck &> /dev/null; then
    echo "❌ cppcheck not found. Install with: sudo apt-get install cppcheck"
    exit 1
fi

echo "✅ All tools available"
echo

# 1. Clang-format check
echo "📝 Checking code formatting with clang-format..."
FORMAT_ISSUES=0
find src example -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.cc" -o -name "*.cxx" | while IFS= read -r file; do
    if [ -f "$file" ]; then
        if ! clang-format --dry-run --Werror "$file" > /dev/null 2>&1; then
            echo "⚠️  Format issues: $file"
            FORMAT_ISSUES=1
        fi
    fi
done

if [ $FORMAT_ISSUES -eq 0 ]; then
    echo "✅ Code formatting OK"
else
    echo "⚠️  Some files need formatting. Run ./scripts/format.sh to fix."
fi
echo

# 2. CPPLint check
echo "🎨 Checking style with cpplint..."
LINT_ISSUES=0
find src example -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.cc" -o -name "*.cxx" | while IFS= read -r file; do
    if [ -f "$file" ]; then
        if ! cpplint --filter=-legal/copyright,-build/include_subdir,-readability/streams,-build/header_guard,-build/include_order,-build/namespaces,-whitespace/tab --linelength=80 "$file" 2>/dev/null; then
            LINT_ISSUES=1
        fi
    fi
done

if [ $LINT_ISSUES -eq 0 ]; then
    echo "✅ Style checks OK"
else
    echo "⚠️  Some style issues found (see above)"
fi
echo

# 3. Cppcheck static analysis
echo "🔍 Running static analysis with cppcheck..."
if cppcheck --enable=warning,style,performance,portability \
           --std=c++20 \
           --language=c++ \
           --suppress=missingIncludeSystem \
           --suppress=unusedFunction \
           --quiet \
           src/ example/ 2>&1; then
    echo "✅ Static analysis OK"
else
    echo "⚠️  Static analysis found issues (see above)"
fi

echo
echo "🎉 Code quality check complete!"
echo "💡 To fix formatting issues, run: ./scripts/format.sh"