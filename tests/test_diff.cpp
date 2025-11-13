#include "../src/core/diff.h"
#include <cassert>
#include <iostream>

void testDiff() {
    std::string oldText = "line1\nline2\nline3";
    std::string newText = "line1\nline2 changed\nline3\nline4";

    auto diff = Diff::generate(oldText, newText);

    assert(!diff.empty());
    assert(diff[0] == "- line2");
    assert(diff[1] == "+ line2 changed");
    assert(diff[2] == "+ line4");

    std::cout << "testDiff passed.\n";
}

int main() {
    testDiff();
    return 0;
}