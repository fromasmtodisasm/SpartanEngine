/*
Copyright(c) 2016-2019 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//= INCLUDES =====================================
#include "IResource.h"
#include "../Audio/AudioClip.h"
#include "../Rendering/Model.h"
#include "../Rendering/Font/Font.h"
#include "../Rendering/Deferred/ShaderVariation.h"
//================================================

//= NAMESPACES ==========
using namespace std;
using namespace Spartan;
//=======================

IResource::IResource(Context* context, const Resource_Type type)
{
	m_context			= context;
	m_resource_type		= type;
	m_resource_id		= GENERATE_GUID;
	m_load_state		= LoadState_Idle;
}

template <typename T>
constexpr Resource_Type IResource::TypeToEnum() { return Resource_Unknown; }

// Explicit template instantiation
#define INSTANTIATE_TO_RESOURCE_TYPE(T, enumT) template<> SPARTAN_CLASS Resource_Type IResource::TypeToEnum<T>() { return enumT; }

// To add a new component to the engine, simply register it here
INSTANTIATE_TO_RESOURCE_TYPE(RHI_Texture,		Resource_Texture)
INSTANTIATE_TO_RESOURCE_TYPE(AudioClip,			Resource_Audio)
INSTANTIATE_TO_RESOURCE_TYPE(Material,			Resource_Material)
INSTANTIATE_TO_RESOURCE_TYPE(ShaderVariation,	Resource_Shader)
INSTANTIATE_TO_RESOURCE_TYPE(Mesh,				Resource_Mesh)
INSTANTIATE_TO_RESOURCE_TYPE(Model,				Resource_Model)
INSTANTIATE_TO_RESOURCE_TYPE(Animation,			Resource_Animation)
INSTANTIATE_TO_RESOURCE_TYPE(Font,				Resource_Font)