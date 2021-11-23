/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- FontInfo.hpp

Abstract:
- This serves as the structure defining font information.  There are three
  relevant classes defined.

- FontInfo - derived from FontInfoBase.  It also has font size
  information - both the width and height of the requested font, as
  well as the measured height and width of L'0' from GDI.  All
  coordinates { X, Y } pair are non zero and always set to some
  reasonable value, even when GDI APIs fail.  This helps avoid
  divide by zero issues while performing various sizing
  calculations.

Author(s):
- Michael Niksa (MiNiksa) 17-Nov-2015
--*/

#pragma once

#include "FontInfoBase.hpp"

class FontInfo : public FontInfoBase
{
public:
    FontInfo(const std::wstring_view& faceName,
             const unsigned char family,
             const unsigned int weight,
             const COORD coordSize,
             const unsigned int codePage,
             const bool fSetDefaultRasterFont = false) noexcept;

    bool operator==(const FontInfo& other) noexcept;

    COORD GetSize() const noexcept;
    COORD GetUnscaledSize() const noexcept;
    void SetFromEngine(const std::wstring_view& faceName,
                       const unsigned char family,
                       const unsigned int weight,
                       const bool fSetDefaultRasterFont,
                       const COORD coordSize,
                       const COORD coordSizeUnscaled) noexcept;
    void SetFallback(const bool didFallback) noexcept;
    void ValidateFont() noexcept;

private:
    void _ValidateCoordSize() noexcept;

    COORD _coordSize;
    COORD _coordSizeUnscaled;
    bool _didFallback;
};
