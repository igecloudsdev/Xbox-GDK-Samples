// AMD AMDUtils code
// 
// Copyright(c) 2018 Advanced Micro Devices, Inc.All rights reserved.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

// Disable warning "switch of enum X is not explicitly handled by a case label" 
#pragma warning(disable:4061)
#include "../json/json.h"
#pragma warning(default:4061)

using json = nlohmann::json;

unsigned GetFormatSize(unsigned id);
unsigned GetDimensions(const std::string &str);
void SplitGltfAttribute(std::string attribute, std::string *semanticName, uint32_t *semanticIndex);

DirectX::XMVECTOR GetVector(const json::array_t &accessor);
DirectX::XMMATRIX GetMatrix(const json::array_t &accessor);
std::string GetElementString(const json::object_t &root, const char *path, std::string pDefault);
float GetElementFloat(const json::object_t &root, const char *path, float pDefault);
int GetElementInt(const json::object_t &root, const char *path, int pDefault);
unsigned int GetElementUnsignedInt(const json::object_t& root, const char* path, unsigned int pDefault);
bool GetElementBoolean(const json::object_t &root, const char *path, bool pDefault);
json::array_t GetElementJsonArray(const json::object_t &root, const char *path, json::array_t pDefault);
DirectX::XMVECTOR GetElementVector(json::object_t &root, const char *path, DirectX::XMVECTOR );

namespace AMDTK
{
    DXGI_FORMAT GetFormat(const std::string &str, int id);
    void CreateSamplerForPBR(uint32_t samplerIndex, D3D12_STATIC_SAMPLER_DESC *pSamplerDesc);
    void CreateSamplerForBrdfLut(uint32_t samplerIndex, D3D12_STATIC_SAMPLER_DESC *pSamplerDesc);
    void CreateSamplerForShadowMap(uint32_t samplerIndex, D3D12_STATIC_SAMPLER_DESC *pSamplerDesc);
    void CreateSamplerForShadowBuffer(uint32_t samplerIndex, D3D12_STATIC_SAMPLER_DESC *pSamplerDesc);
}

