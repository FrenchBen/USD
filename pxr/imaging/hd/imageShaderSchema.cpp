//
// Copyright 2023 Pixar
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
////////////////////////////////////////////////////////////////////////

/* ************************************************************************** */
/* **                                                                      ** */
/* ** This file is generated by a script.                                  ** */
/* **                                                                      ** */
/* ** Do not edit it directly (unless it is within a CUSTOM CODE section)! ** */
/* ** Edit hdGen/schema.py instead to make changes.                        ** */
/* **                                                                      ** */
/* ************************************************************************** */

#include "pxr/imaging/hd/imageShaderSchema.h"

#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdImageShaderSchemaTokens,
    HD_IMAGE_SHADER_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdBoolDataSourceHandle
HdImageShaderSchema::GetEnabled()
{
    return _GetTypedDataSource<HdBoolDataSource>(
        HdImageShaderSchemaTokens->enabled);
}

HdIntDataSourceHandle
HdImageShaderSchema::GetPriority()
{
    return _GetTypedDataSource<HdIntDataSource>(
        HdImageShaderSchemaTokens->priority);
}

HdStringDataSourceHandle
HdImageShaderSchema::GetFilePath()
{
    return _GetTypedDataSource<HdStringDataSource>(
        HdImageShaderSchemaTokens->filePath);
}

HdSampledDataSourceContainerSchema
HdImageShaderSchema::GetConstants()
{
    return HdSampledDataSourceContainerSchema(_GetTypedDataSource<HdContainerDataSource>(
        HdImageShaderSchemaTokens->constants));
}

/*static*/
HdContainerDataSourceHandle
HdImageShaderSchema::BuildRetained(
        const HdBoolDataSourceHandle &enabled,
        const HdIntDataSourceHandle &priority,
        const HdStringDataSourceHandle &filePath,
        const HdContainerDataSourceHandle &constants
)
{
    TfToken _names[4];
    HdDataSourceBaseHandle _values[4];

    size_t _count = 0;

    if (enabled) {
        _names[_count] = HdImageShaderSchemaTokens->enabled;
        _values[_count++] = enabled;
    }

    if (priority) {
        _names[_count] = HdImageShaderSchemaTokens->priority;
        _values[_count++] = priority;
    }

    if (filePath) {
        _names[_count] = HdImageShaderSchemaTokens->filePath;
        _values[_count++] = filePath;
    }

    if (constants) {
        _names[_count] = HdImageShaderSchemaTokens->constants;
        _values[_count++] = constants;
    }
    return HdRetainedContainerDataSource::New(_count, _names, _values);
}

HdImageShaderSchema::Builder &
HdImageShaderSchema::Builder::SetEnabled(
    const HdBoolDataSourceHandle &enabled)
{
    _enabled = enabled;
    return *this;
}

HdImageShaderSchema::Builder &
HdImageShaderSchema::Builder::SetPriority(
    const HdIntDataSourceHandle &priority)
{
    _priority = priority;
    return *this;
}

HdImageShaderSchema::Builder &
HdImageShaderSchema::Builder::SetFilePath(
    const HdStringDataSourceHandle &filePath)
{
    _filePath = filePath;
    return *this;
}

HdImageShaderSchema::Builder &
HdImageShaderSchema::Builder::SetConstants(
    const HdContainerDataSourceHandle &constants)
{
    _constants = constants;
    return *this;
}

HdContainerDataSourceHandle
HdImageShaderSchema::Builder::Build()
{
    return HdImageShaderSchema::BuildRetained(
        _enabled,
        _priority,
        _filePath,
        _constants
    );
}

/*static*/
HdImageShaderSchema
HdImageShaderSchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdImageShaderSchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdImageShaderSchemaTokens->imageShader))
        : nullptr);
}

/*static*/
const TfToken &
HdImageShaderSchema::GetSchemaToken()
{
    return HdImageShaderSchemaTokens->imageShader;
}

/*static*/
const HdDataSourceLocator &
HdImageShaderSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(GetSchemaToken());
    return locator;
}

/* static */
const HdDataSourceLocator &
HdImageShaderSchema::GetEnabledLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdImageShaderSchemaTokens->enabled);
    return locator;
}

/* static */
const HdDataSourceLocator &
HdImageShaderSchema::GetPriorityLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdImageShaderSchemaTokens->priority);
    return locator;
}

/* static */
const HdDataSourceLocator &
HdImageShaderSchema::GetFilePathLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdImageShaderSchemaTokens->filePath);
    return locator;
}

/* static */
const HdDataSourceLocator &
HdImageShaderSchema::GetConstantsLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdImageShaderSchemaTokens->constants);
    return locator;
} 

PXR_NAMESPACE_CLOSE_SCOPE