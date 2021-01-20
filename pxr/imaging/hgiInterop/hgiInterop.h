//
// Copyright 2020 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_IMAGING_HGIINTEROP_HGIINTEROP_H
#define PXR_IMAGING_HGIINTEROP_HGIINTEROP_H

#include "pxr/pxr.h"
#include "pxr/base/tf/token.h"
#include "pxr/base/gf/vec4i.h"
#include "pxr/imaging/hgiInterop/api.h"
#include "pxr/imaging/hgi/texture.h"

#include <memory>

PXR_NAMESPACE_OPEN_SCOPE

class Hgi;
class HgiInteropMetal;
class HgiInteropOpenGL;
class HgiInteropVulkan;


/// \class HgiInterop
///
/// Hydra Graphics Interface Interop.
///
/// HgiInterop provides functionality to transfer render targets between
/// supported APIs as efficiently as possible.
///
class HgiInterop final
{
public:
    HGIINTEROP_API
    HgiInterop();

    HGIINTEROP_API
    ~HgiInterop();

    /// Composite the provided textures over the application / viewer's
    /// framebuffer contents.
    /// `hgi`: 
    ///     Determines the source format/platform of the textures.
    ///     Eg. if hgi is of type HgiMetal, the textures are HgiMetalTexture.
    /// `interopDst`: 
    ///     Determines what target format/platform the application is using.
    ///     E.g. If hgi==HgiMetal and interopDst==OpenGL then TransferToApp
    ///     will present the metal textures to the gl application.
    /// `compRegion`:
    ///     Subrect region of the framebuffer over which to composite.
    ///     Coordinates are (left, BOTTOM, width, height) which is the same
    ///     convention as OpenGL viewport coordinates.
    /// `color`: is the source color aov texture to composite to screen.
    /// `depth`: (optional) is the depth aov texture to composite to screen.
    ///
    /// Note:
    /// To composite correctly, blending is enabled. 
    /// If `depth` is provided, depth testing is enabled.
    /// As a result, the contents of the application framebuffer matter. In
    /// order to use the contents of `color` and `depth` as-is (i.e., blit), the
    /// color attachment should be cleared to (0,0,0,0) and the depth
    /// attachment needs to be cleared to 1.
    /// 
    HGIINTEROP_API
    void TransferToApp(
        Hgi *hgi,
        TfToken const &interopDst,
        GfVec4i const &compRegion,
        HgiTextureHandle const &color,
        HgiTextureHandle const &depth);

private:
    HgiInterop & operator=(const HgiInterop&) = delete;
    HgiInterop(const HgiInterop&) = delete;

#if defined(PXR_METAL_SUPPORT_ENABLED)
    std::unique_ptr<HgiInteropMetal> _metalToOpenGL;
#elif defined(PXR_VULKAN_SUPPORT_ENABLED)
    std::unique_ptr<HgiInteropVulkan> _vulkanToOpenGL;
#else
    std::unique_ptr<HgiInteropOpenGL> _openGLToOpenGL;
#endif
};


PXR_NAMESPACE_CLOSE_SCOPE

#endif
