#!/bin/bash
# Script to format all C++ source files using clang-format with Google style

echo "Formatting all C++ source files with Google style..."

# Find all C++ source files and format them
find src example -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.cc" -o -name "*.cxx" | while IFS= read -r file; do
    if [ -f "$file" ]; then
        echo "Formatting: $file"
        clang-format -i "$file"
    fi
done

echo "✅ Code formatting complete!"
echo "💡 To check formatting without modifying files, run:"
echo "   find src example -name '*.cpp' -o -name '*.h' | xargs clang-format --dry-run --Werror"