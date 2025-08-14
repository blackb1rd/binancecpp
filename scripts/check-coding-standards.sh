#!/bin/bash

# Coding Standards Checker for C++20 Binance API Project
# Checks for:
# 1. No "using namespace std;" declarations
# 2. Minimal "auto" keyword usage (warns when > 3 per file)
# 3. Unqualified std names usage

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
VIOLATIONS=0
FILES_CHECKED=0

echo "Checking coding standards in project source files..."

# Function to check files in a directory
check_files_in_dir() {
    local dir="$1"
    echo "Checking $dir directory..."

    find "$dir" -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | while read -r file; do
        echo "Checking $file..."
        FILES_CHECKED=$((FILES_CHECKED + 1))

        # Check for "using namespace std;"
        if grep -q "using namespace std" "$file" 2>/dev/null; then
            echo -e "${RED}ERROR:${NC} $file contains 'using namespace std;'"
            grep -n "using namespace std" "$file" | while IFS= read -r line; do
                line_num=$(echo "$line" | cut -d: -f1)
                line_content=$(echo "$line" | cut -d: -f2-)
                echo -e "  ${RED}Line $line_num:${NC} $line_content"
            done
            VIOLATIONS=$((VIOLATIONS + 1))
        fi

        # Check for excessive auto usage (warn, don't error)
        auto_count=$(grep -c "\bauto\b" "$file" 2>/dev/null || echo 0)
        if [ "$auto_count" -gt 3 ]; then
            echo -e "${YELLOW}WARNING:${NC} $file has $auto_count usages of 'auto' keyword (consider explicit types)"
            grep -n "\bauto\b" "$file" 2>/dev/null | head -5 | while IFS= read -r line; do
                line_num=$(echo "$line" | cut -d: -f1)
                line_content=$(echo "$line" | cut -d: -f2-)
                echo -e "  ${YELLOW}Line $line_num:${NC} $line_content"
            done
        fi

        # Check for unqualified std names (simple check for common ones)
        if grep -q "\bstring\b" "$file" && ! grep -q "std::string" "$file" && ! grep -q "using namespace std" "$file"; then
            echo -e "${YELLOW}WARNING:${NC} $file may contain unqualified 'string' usage"
        fi

        if grep -q "\bvector\b" "$file" && ! grep -q "std::vector" "$file" && ! grep -q "using namespace std" "$file"; then
            echo -e "${YELLOW}WARNING:${NC} $file may contain unqualified 'vector' usage"
        fi

        if grep -q "\bcout\b" "$file" && ! grep -q "std::cout" "$file" && ! grep -q "using namespace std" "$file"; then
            echo -e "${YELLOW}WARNING:${NC} $file may contain unqualified 'cout' usage"
        fi
    done
}

# Check directories
if [ -d "src" ]; then
    check_files_in_dir "src"
fi

if [ -d "example" ]; then
    check_files_in_dir "example"
fi

echo "====================================="
echo "Files checked: $FILES_CHECKED"
if [ $VIOLATIONS -eq 0 ]; then
    echo -e "${GREEN}✓ No coding standard violations found!${NC}"
    exit 0
else
    echo -e "${RED}✗ Found $VIOLATIONS coding standard violations${NC}"
    exit 1
fi
