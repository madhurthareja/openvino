// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <vector>

#include "low_precision_transformations/concat_with_different_precision_on_children.hpp"
#include "common_test_utils/test_constants.hpp"

using namespace LayerTestsDefinitions;

namespace {
const std::vector<ov::element::Type> netPrecisions = {
    ov::element::f32,
    ov::element::f16
};

const std::vector<ConcatWithDifferentChildrenTransformationParam> testValues = {
    // U8
    {
        1,
        { 256ul, ov::Shape({}), {0.f}, {2.55f}, {0.f}, {2.55f} },
        { 256ul, ov::Shape({}), {0.f}, {2.55f}, {0.f}, {2.55f / 2.f} }
    },
    // U8 and unsupported concat axis
    {
        2,
        { 256ul, ov::Shape({}), {0.f}, {2.55f}, {0.f}, {2.55f} },
        { 256ul, ov::Shape({}), {0.f}, {2.55f}, {0.f}, {2.55f / 2.f} }
    },
    // I8
    {
        1,
        { 256ul, ov::Shape({}), {-1.28f}, {1.27f}, {-1.28f}, {1.27f} },
        { 256ul, ov::Shape({}), {-1.28f}, {1.27f}, {-1.28f / 2.f}, {1.27f / 2.f} }
    },
    // mixed: U8 + I8
    {
        1,
        { 256ul, ov::Shape({}), {0.f}, {2.55f}, {0.f}, {2.55f} },
        { 256ul, ov::Shape({}), {-1.28f}, {1.27f}, {-1.28f}, {1.27f} }
    },
    // mixed: I8 + U8
    {
        1,
        { 256ul, ov::Shape({}), {-1.28f}, {1.27f}, {-1.28f}, {1.27f} },
        { 256ul, ov::Shape({}), {0.f}, {2.55f}, {0.f}, {2.55f} }
    }
};

INSTANTIATE_TEST_SUITE_P(smoke_LPT, ConcatWithDifferentChildrenTransformation,
    ::testing::Combine(
        ::testing::ValuesIn(netPrecisions),
        ::testing::Values(ov::PartialShape({ 1, 3, 10, 10 })),
        ::testing::Values(ov::test::utils::DEVICE_GPU),
        ::testing::ValuesIn(testValues)),
    ConcatWithDifferentChildrenTransformation::getTestCaseName);
}  // namespace
