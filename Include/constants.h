//*****************************************************************************
// The MIT License (MIT)
//
// Copyright � 2024 Piotr Walczak
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the �Software�), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//*****************************************************************************

//*****************************************************************************
// File: array_stack.h
//
// This file contains constant values that are used in the library.
//*****************************************************************************

#ifndef ALGLIB_INCLUDE_CONSTANTS_H_
#define ALGLIB_INCLUDE_CONSTANTS_H_

#include <string>

/// <summary>
/// Default namespace for the AlgLib library.
/// </summary>
namespace alglib {

/// <summary>
/// Namespace for errors in the AlgLib library.
/// </summary>
namespace errors {

// Error messages.
inline constexpr const char* kItemNotFound{"Item not found."};
inline constexpr const char* kIndexOutOfRange{"Index out of range."};
inline constexpr const char* kEmptyDeletion{"Cannot delete from empty object."};
inline constexpr const char* kObjectFull{"Object full."};
inline constexpr const char* kObjectEmpty{"Object empty."};
inline constexpr const char* kPeekAtEmpty{"Cannot peek at empty objects."};

}  // namespace errors

}  // namespace alglib

#endif  // ALGLIB_INCLUDE_CONSTANTS_H_
