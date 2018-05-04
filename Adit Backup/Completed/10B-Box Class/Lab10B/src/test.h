#pragma once

void Test(bool result);
void RunAllTests();
bool CanInstantiateDefaultBox();
bool HasAppropriateGetters();
bool DefaultBoxHasCorrectDefaultHeightWidthDepth();
bool CanInstantiateBoxProvidingHeightWidthDepth();
bool CanNotInstantiateBoxWithInvalidDimensions();
bool CanNotInstantiateBoxWithInvalidHeight();
bool CanNotInstantiateBoxWithInvalidWidth();
bool CanNotInstantiateBoxWithInvalidDepth();
bool ClassHasCorrectStaticConstDEFAULT_DIMENSION();
bool InstantiatingWithInvalidDimensionUsesDefault();
bool HasAppropriateSetters();
bool SettingInvalidHeightUsesDefault();
bool SettingInvalidWidthUsesDefault();
bool SettingInvalidDepthUsesDefault();
bool BoxShouldHaveCorrectVolume();
