#pragma once

namespace TrickyUnits{
bool IsLittleEndian();
bool IsBigEndian();

_int32 ToBigEndian(_int32 i);
_int32 ToLittleEndian(_int32 i);
}
