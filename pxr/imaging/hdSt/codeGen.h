//
// Copyright 2016 Pixar
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
#ifndef PXR_IMAGING_HD_ST_CODE_GEN_H
#define PXR_IMAGING_HD_ST_CODE_GEN_H

#include "pxr/pxr.h"
#include "pxr/imaging/hdSt/api.h"
#include "pxr/imaging/hd/version.h"
#include "pxr/imaging/hdSt/resourceBinder.h"
#include "pxr/imaging/hdSt/glslProgram.h"
#include "pxr/imaging/hio/glslfxResourceLayout.h"

#include <map>
#include <vector>
#include <sstream>

PXR_NAMESPACE_OPEN_SCOPE

using HdStShaderCodeSharedPtr = std::shared_ptr<class HdStShaderCode>;
using HdStShaderCodeSharedPtrVector = std::vector<HdStShaderCodeSharedPtr>;
using HdSt_GeometricShaderPtr = std::shared_ptr<class HdSt_GeometricShader>;

class HgiCapabilities;

/// \class HdSt_CodeGen
///
/// A utility class to compose glsl shader sources and compile them
/// upon request of HdShaderSpec.
///
class HdSt_CodeGen
{
public:
    typedef size_t ID;

    /// Returns true if shader resource definitions are being
    /// generated by Hgi or false if shader resource definitions
    /// are generated as native GLSL.
    static bool IsEnabledHgiResourceGeneration(
               HgiCapabilities const *capabilities);

    /// Constructor.
    HDST_API
    HdSt_CodeGen(HdSt_GeometricShaderPtr const &geometricShader,
               HdStShaderCodeSharedPtrVector const &shaders,
               TfToken const &materialTag);

    /// Constructor for non-geometric use cases.
    /// Don't call compile when constructed this way.
    /// Call CompileComputeProgram instead.
    HDST_API
    HdSt_CodeGen(HdStShaderCodeSharedPtrVector const &shaders);
    
    /// Return the hash value of glsl shader to be generated.
    HDST_API
    ID ComputeHash() const;

    /// Generate shader source and compile it.
    HDST_API
    HdStGLSLProgramSharedPtr Compile(
        HdStResourceRegistry*const registry);

    /// Generate compute shader source and compile it.
    /// It uses the compute information in the meta data to determine
    /// layouts needed for a compute program.
    /// The caller should have populated the meta data before calling this
    /// using a method like HdSt_ResourceBinder::ResolveBindings.
    ///
    /// The layout and binding information is combined with the compute stage
    /// shader code from the shader vector to form a resolved shader for
    /// compilation.
    ///
    /// The generated code that is compiled is available for diagnostic
    /// purposes from GetComputeShaderSource.
    ///
    /// \see GetComputeShaderSource
    /// \see HdSt_ResourceBinder::ResolveBindings
    HDST_API
    HdStGLSLProgramSharedPtr CompileComputeProgram(
        HdStResourceRegistry*const registry);
    
    /// Return the generated vertex shader source
    const std::string &GetVertexShaderSource() const { return _vsSource; }

    /// Return the generated tess control shader source
    const std::string &GetTessControlShaderSource() const { return _tcsSource; }

    /// Return the generated tess eval shader source
    const std::string &GetTessEvalShaderSource() const { return _tesSource; }

    /// Return the generated geometry shader source
    const std::string &GetGeometryShaderSource() const { return _gsSource; }

    /// Return the generated fragment shader source
    const std::string &GetFragmentShaderSource() const { return _fsSource; }

    /// Return the generated compute shader source
    const std::string &GetComputeShaderSource() const { return _csSource; }

    /// Return the generated post tess control shader source
    const std::string &GetPostTessControlShaderSource() const {
        return _ptcsSource;
    }

    /// Return the generated post tess vertex shader source
    const std::string &GetPostTessVertexShaderSource() const {
        return _ptvsSource;
    }

    /// Return the pointer of metadata to be populated by resource binder.
    HdSt_ResourceBinder::MetaData *GetMetaData() { return &_metaData; }

private:
    void _GenerateDrawingCoord(
        bool const shaderDrawParametersEnabled,
        bool const requiresBasePrimitiveOffset,
        bool const requiresPrimitiveIdEmulation);
    void _GenerateConstantPrimvar();
    void _GenerateInstancePrimvar();
    void _GenerateElementPrimvar();
    void _GenerateVertexAndFaceVaryingPrimvar();
    void _GenerateShaderParameters(bool bindlessTextureEnabled);
    void _GenerateTopologyVisibilityParameters();

    void _GetShaderResourceLayouts(
        HdStShaderCodeSharedPtrVector const & shaders);

    std::string _GetFallbackScalarSwizzleString(TfToken const &returnType,
                                                TfToken const &paramName);

    void _PlumbInterstageElements(TfToken const &name, TfToken const &dataType);

    void _GenerateComputeParameters(HgiShaderFunctionDesc *csDesc);

    HdStGLSLProgramSharedPtr _CompileWithGeneratedGLSLResources(
        HdStResourceRegistry * const registry);

    HdStGLSLProgramSharedPtr _CompileWithGeneratedHgiResources(
        HdStResourceRegistry * const registry);

    HdSt_ResourceBinder::MetaData _metaData;
    HdSt_GeometricShaderPtr _geometricShader;
    HdStShaderCodeSharedPtrVector _shaders;
    TfToken _materialTag;

    // source buckets
    std::stringstream _genDefines;
    std::stringstream _genDecl;
    std::stringstream _genAccessors;
    std::stringstream _genVS, _genTCS, _genTES;
    std::stringstream _genPTCS, _genPTVS;
    std::stringstream _genGS, _genFS, _genCS;
    std::stringstream _procVS, _procTCS, _procTES, _procGS;
    std::stringstream _procPTVSOut;
    std::stringstream _osd;

    // resource buckets
    using ElementVector = HioGlslfxResourceLayout::ElementVector;
    ElementVector _resVS;
    ElementVector _resTCS;
    ElementVector _resTES;
    ElementVector _resGS;
    ElementVector _resFS;
    ElementVector _resPTCS;
    ElementVector _resPTVS;
    ElementVector _resCS;

    ElementVector _resInterstage;

    ElementVector _resCommon;
    ElementVector _resAttrib;
    ElementVector _resMaterial;

    using TextureElementVector = HioGlslfxResourceLayout::TextureElementVector;
    TextureElementVector _resTextures;

    // generated sources (for diagnostics)
    std::string _vsSource;
    std::string _tcsSource;
    std::string _tesSource;
    std::string _gsSource;
    std::string _fsSource;
    std::string _csSource;
    std::string _ptcsSource;
    std::string _ptvsSource;

    bool _hasVS;
    bool _hasTCS;
    bool _hasTES;
    bool _hasGS;
    bool _hasFS;
    bool _hasCS;
    bool _hasPTCS;
    bool _hasPTVS;

    bool _hasClipPlanes;
};


PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_CODE_GEN_H
