// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#pragma once

#include <concepts>

namespace fsd {

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

}  // namespace fsd