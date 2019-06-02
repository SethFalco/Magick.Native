// Copyright 2013-2019 Dirk Lemstra <https://github.com/dlemstra/Magick.Native/>
//
// Licensed under the ImageMagick License (the "License"); you may not use this file except in
// compliance with the License. You may obtain a copy of the License at
//
//   https://www.imagemagick.org/script/license.php
//
// Unless required by applicable law or agreed to in writing, software distributed under the
// License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions
// and limitations under the License.

#include "Stdafx.h"
#include "Quantum.h"

MAGICK_NATIVE_EXPORT size_t Quantum_Depth_Get(void)
{
  return MAGICKCORE_QUANTUM_DEPTH;
}

MAGICK_NATIVE_EXPORT Quantum Quantum_Max_Get(void)
{
#if (MAGICKCORE_QUANTUM_DEPTH == 8)
  return (Quantum)255;
#elif (MAGICKCORE_QUANTUM_DEPTH == 16)
  return (Quantum)65535;
#else
#error Not implemented!
#endif
}

MAGICK_NATIVE_EXPORT unsigned char Quantum_ScaleToByte(const Quantum value)
{
  return ScaleQuantumToChar(value);
}