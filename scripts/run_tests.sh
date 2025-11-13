#!/bin/bash
set -e

echo "🧩 Building tests..."
mkdir -p build/tests
cd build/tests

for test_file in ../../tests/*.cpp; do
  test_name=$(basename "$test_file" .cpp)
  echo "Compiling $test_name..."
  g++ -std=c++17 -I../../include -I../../src "$test_file" -o "$test_name"
done

echo "🚀 Running tests..."
for exe in *; do
  if [[ -x "$exe" ]]; then
    echo "Running $exe..."
    ./"$exe"
  fi
done

echo "✅ All tests passed."
