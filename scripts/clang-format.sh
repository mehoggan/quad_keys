set -e

SCRIPT_DIR=$(dirname $(cd -- "$(dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd))

echo "Running clang-format from ${SCRIPT_DIR}..."

find "${SCRIPT_DIR}" -name "*.h" -o -name "*.cpp" -o -name "*.cxx" -o -name "*.hpp" \
  | grep -v "deps\|build" \
  | xargs clang-format -i
