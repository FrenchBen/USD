//
// Copyright 2022 Pixar
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
#ifndef EXT_RMANPKG_25_0_PLUGIN_RENDERMAN_PLUGIN_HD_PRMAN_TOKENS_H
#define EXT_RMANPKG_25_0_PLUGIN_RENDERMAN_PLUGIN_HD_PRMAN_TOKENS_H

#include "pxr/pxr.h"
#include "hdPrman/api.h"
#include "pxr/base/tf/staticTokens.h"

PXR_NAMESPACE_OPEN_SCOPE

#define HD_PRMAN_TOKENS                         \
    (meshLight)                                 \
    (meshLightSourceMesh)                       \
    (meshLightSourceVolume)                     \
    (sourceGeom)

TF_DECLARE_PUBLIC_TOKENS(HdPrmanTokens, HDPRMAN_API, HD_PRMAN_TOKENS);

///
/// HdPrmanRileyPrimTypeTokens correspond to Riley::Create/Modify/Delete calls.
///
/// Dependencies are as follows:
///
/// lightShader     <----------------------------< lightInstance
///                                               /
/// material      <------------------------------*---< geometryInstance
///                                             /
/// coordinateSystem  <------------------------*
///                                           /
/// displacement  <----< geometryPrototype <-*
///
/// clippingPlane
///
/// renderOutput <-------------------------------< display
///             \                                 / 
///              *-----<  renderTarget <---------*
///                                   \                            _
/// integrator <-----------------------*
///                                     \                          _
/// displayFilter <----------------------*---------< renderView
///                                     /
/// sampleFilter <---------------------*
///                                   /
/// camera  <------------------------*
///
#define HD_PRMAN_RILEY_PRIM_TYPE_TOKENS         \
    ((renderOutput, "riley:renderOutput"))      \
    ((renderTarget, "riley:renderTarget"))

TF_DECLARE_PUBLIC_TOKENS(HdPrmanRileyPrimTypeTokens, HDPRMAN_API,
                         HD_PRMAN_RILEY_PRIM_TYPE_TOKENS);

#define HD_PRMAN_PLUGIN_TOKENS \
    ((motionBlur,       "HdPrman_MotionBlurSceneIndexPlugin")) \
    ((extComp,          "HdPrman_ExtComputationPrimvarPruningSceneIndexPlugin"))

TF_DECLARE_PUBLIC_TOKENS(HdPrmanPluginTokens, HD_PRMAN_PLUGIN_TOKENS);

const std::vector<std::string>& HdPrman_GetPluginDisplayNames();

PXR_NAMESPACE_CLOSE_SCOPE

#endif //EXT_RMANPKG_25_0_PLUGIN_RENDERMAN_PLUGIN_HD_PRMAN_TOKENS_H
