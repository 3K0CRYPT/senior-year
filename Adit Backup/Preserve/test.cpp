#include "test.h"
#include "box.h"
#include <iostream>
#include <string>

using namespace std;

// A generic test function, that simply prints "PASSED" if result is
// true and otherwise prints false.
void Test(string testName, bool result) {
    cout.width(50);
    cout << testName;
    if (result) cout << " PASSED\n";
    else cout << " FAILED\n";
}

// Test suite executor. Calls test() for every unit test.
void RunAllTests() {
    Test("CanInstantiateDefaultBox()", CanInstantiateDefaultBox());
    Test("HasAppropriateGetters()", HasAppropriateGetters());
    Test("ClassHasCorrectStaticConstDEFAULT_DIMENSION()",
        ClassHasCorrectStaticConstDEFAULT_DIMENSION());
    Test("DefaultBoxHasCorrectDefaultHeightWidthDepth()",
        DefaultBoxHasCorrectDefaultHeightWidthDepth());
    Test("CanInstantiateBoxProvidingHeightWidthDepth()",
        CanInstantiateBoxProvidingHeightWidthDepth());
    Test("CanNotInstantiateBoxWithInvalidDimensions()",
        CanNotInstantiateBoxWithInvalidDimensions());
    Test("InstantiatingWithInvalidDimensionUsesDefault()",
        InstantiatingWithInvalidDimensionUsesDefault());
    Test("CanNotInstantiateBoxWithInvalidHeight()",
        CanNotInstantiateBoxWithInvalidHeight());
    Test("CanNotInstantiateBoxWithInvalidWidth()",
        CanNotInstantiateBoxWithInvalidWidth());
    Test("CanNotInstantiateBoxWithInvalidDepth()",
        CanNotInstantiateBoxWithInvalidDepth());
    Test("HasAppropriateSetters()", HasAppropriateSetters());
    Test("SettingInvalidHeightUsesDefault()",
        SettingInvalidHeightUsesDefault());
    Test("SettingInvalidWidthUsesDefault()",
        SettingInvalidHeightUsesDefault());
    Test("SettingInvalidDepthUsesDefault()",
        SettingInvalidHeightUsesDefault());
    Test("BoxShouldHaveCorrectVolume()",
        BoxShouldHaveCorrectVolume());
    return;
}

bool CanInstantiateDefaultBox() {
    Box box;
    return true;
}

bool HasAppropriateGetters() {
    int h = 1;
    int w = 1;
    int d = 1;
    // Instantiate four boxes and check their dimensions.
    while (h < 5) {
        Box b(h, w, d);
        if (b.GetHeight() != h && b.GetWidth() != w && b.GetDepth() != d) {
            return false;
        }
        ++h; ++w; ++d;
    }
    return true;
}

bool ClassHasCorrectStaticConstDEFAULT_DIMENSION() {
    if (Box::DEFAULT_DIMENSION == 1) {
        return true;
    }
    else {
        return false;
    }
}

// A default box should have a height, width and depth of 1, respectively.
bool DefaultBoxHasCorrectDefaultHeightWidthDepth() {
    Box box;
    if (box.GetHeight() == Box::DEFAULT_DIMENSION &&
        box.GetWidth() == Box::DEFAULT_DIMENSION &&
        box.GetDepth() == Box::DEFAULT_DIMENSION) {
        return true;
    }
    else {
        return false;
    }
}

bool CanInstantiateBoxProvidingHeightWidthDepth() {
    Box box(20, 30, 40);
    if (box.GetHeight() == 20 && box.GetWidth() == 30 && box.GetDepth() == 40) {
        return true;
    }
    else {
        return false;
    }
}

bool CanNotInstantiateBoxWithInvalidDimensions() {
    Box box(-20, -10, 0);
    if (box.GetHeight() <= 0 || box.GetWidth() <= 0 || box.GetDepth() <= 0) {
        return false;
    }
    else {
        return true;
    }
}

bool CanNotInstantiateBoxWithInvalidHeight() {
    Box box(-20, 10, 10);
    if (box.GetHeight() <= 0) {
        return false;
    }
    else if (box.GetWidth() == 10 && box.GetDepth() == 10) {
        return true;
    }
    else return false;
}

bool CanNotInstantiateBoxWithInvalidWidth() {
    Box box(10, -20, 10);
    if (box.GetWidth() <= 0) {
        return false;
    }
    else if (box.GetHeight() == 10 && box.GetDepth() == 10) {
        return true;
    }
    else return false;
}

bool CanNotInstantiateBoxWithInvalidDepth() {
    Box box(10, 10, -20);
    if (box.GetDepth() <= 0) {
        return false;
    }
    else if (box.GetHeight() == 10 && box.GetWidth() == 10) {
        return true;
    }
    else return false;
}

bool InstantiatingWithInvalidDimensionUsesDefault() {
    Box box(-20, -10, 0);
    if (box.GetHeight() == Box::DEFAULT_DIMENSION &&
        box.GetWidth() == Box::DEFAULT_DIMENSION &&
        box.GetDepth() == Box::DEFAULT_DIMENSION) {
        return true;
    }
    else {
        return false;
    }
}

bool HasAppropriateSetters() {
    Box b;
    int h = 1;
    int w = 1;
    int d = 1;
    while (h < 5) {
        b.SetHeight(h);
        b.SetWidth(w);
        b.SetDepth(d);
        if (b.GetHeight() != h && b.GetWidth() != w && b.GetDepth() != d) {
            return false;
        }
        ++h; ++w; ++d;
    }
    return true;
}

bool SettingInvalidHeightUsesDefault() {
    Box box(10, 10, 10);
    for (int i = -5; i <= 0; ++i) {
        box.SetHeight(i);
        if (box.GetHeight() != Box::DEFAULT_DIMENSION) {
            return false;
        }
    }
    return true;
}

bool SettingInvalidWidthUsesDefault() {
    Box box(10, 10, 10);
    for (int i = -5; i <= 0; ++i) {
        box.SetWidth(i);
        if (box.GetWidth() != Box::DEFAULT_DIMENSION) {
            return false;
        }
    }
    return true;
}

bool SettingInvalidDepthUsesDefault() {
    Box box(10, 10, 10);
    for (int i = -5; i <= 0; ++i) {
        box.SetDepth(i);
        if (box.GetDepth() != Box::DEFAULT_DIMENSION) {
            return false;
        }
    }
    return true;
}

bool BoxShouldHaveCorrectVolume() {
    Box b;
    int h = 1;
    int w = 1;
    int d = 1;
    while (h < 5) {
        b.SetHeight(h);
        b.SetWidth(w);
        b.SetDepth(d);
        if (b.GetHeight() * b.GetWidth() * b.GetDepth() != b.Volume()) {
            return false;
        }
        ++h; ++w; ++d;
    }
    return true;
}
