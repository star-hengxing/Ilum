#include "ShaderCompiler.hpp"

#include <Core/Path.hpp>

#include <glslang/Include/ResourceLimits.h>

#include <SPIRV/GLSL.std.450.h>
#include <SPIRV/GlslangToSpv.h>

#include <atlbase.h>
#include <dxcapi.h>

#include <sstream>

namespace glslang
{
const TBuiltInResource DefaultTBuiltInResource = {
    /* .MaxLights = */ 32,
    /* .MaxClipPlanes = */ 6,
    /* .MaxTextureUnits = */ 32,
    /* .MaxTextureCoords = */ 32,
    /* .MaxVertexAttribs = */ 64,
    /* .MaxVertexUniformComponents = */ 4096,
    /* .MaxVaryingFloats = */ 64,
    /* .MaxVertexTextureImageUnits = */ 32,
    /* .MaxCombinedTextureImageUnits = */ 80,
    /* .MaxTextureImageUnits = */ 32,
    /* .MaxFragmentUniformComponents = */ 4096,
    /* .MaxDrawBuffers = */ 32,
    /* .MaxVertexUniformVectors = */ 128,
    /* .MaxVaryingVectors = */ 8,
    /* .MaxFragmentUniformVectors = */ 16,
    /* .MaxVertexOutputVectors = */ 16,
    /* .MaxFragmentInputVectors = */ 15,
    /* .MinProgramTexelOffset = */ -8,
    /* .MaxProgramTexelOffset = */ 7,
    /* .MaxClipDistances = */ 8,
    /* .MaxComputeWorkGroupCountX = */ 65535,
    /* .MaxComputeWorkGroupCountY = */ 65535,
    /* .MaxComputeWorkGroupCountZ = */ 65535,
    /* .MaxComputeWorkGroupSizeX = */ 1024,
    /* .MaxComputeWorkGroupSizeY = */ 1024,
    /* .MaxComputeWorkGroupSizeZ = */ 64,
    /* .MaxComputeUniformComponents = */ 1024,
    /* .MaxComputeTextureImageUnits = */ 16,
    /* .MaxComputeImageUniforms = */ 8,
    /* .MaxComputeAtomicCounters = */ 8,
    /* .MaxComputeAtomicCounterBuffers = */ 1,
    /* .MaxVaryingComponents = */ 60,
    /* .MaxVertexOutputComponents = */ 64,
    /* .MaxGeometryInputComponents = */ 64,
    /* .MaxGeometryOutputComponents = */ 128,
    /* .MaxFragmentInputComponents = */ 128,
    /* .MaxImageUnits = */ 8,
    /* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
    /* .MaxCombinedShaderOutputResources = */ 8,
    /* .MaxImageSamples = */ 0,
    /* .MaxVertexImageUniforms = */ 0,
    /* .MaxTessControlImageUniforms = */ 0,
    /* .MaxTessEvaluationImageUniforms = */ 0,
    /* .MaxGeometryImageUniforms = */ 0,
    /* .MaxFragmentImageUniforms = */ 8,
    /* .MaxCombinedImageUniforms = */ 8,
    /* .MaxGeometryTextureImageUnits = */ 16,
    /* .MaxGeometryOutputVertices = */ 256,
    /* .MaxGeometryTotalOutputComponents = */ 1024,
    /* .MaxGeometryUniformComponents = */ 1024,
    /* .MaxGeometryVaryingComponents = */ 64,
    /* .MaxTessControlInputComponents = */ 128,
    /* .MaxTessControlOutputComponents = */ 128,
    /* .MaxTessControlTextureImageUnits = */ 16,
    /* .MaxTessControlUniformComponents = */ 1024,
    /* .MaxTessControlTotalOutputComponents = */ 4096,
    /* .MaxTessEvaluationInputComponents = */ 128,
    /* .MaxTessEvaluationOutputComponents = */ 128,
    /* .MaxTessEvaluationTextureImageUnits = */ 16,
    /* .MaxTessEvaluationUniformComponents = */ 1024,
    /* .MaxTessPatchComponents = */ 120,
    /* .MaxPatchVertices = */ 32,
    /* .MaxTessGenLevel = */ 64,
    /* .MaxViewports = */ 16,
    /* .MaxVertexAtomicCounters = */ 0,
    /* .MaxTessControlAtomicCounters = */ 0,
    /* .MaxTessEvaluationAtomicCounters = */ 0,
    /* .MaxGeometryAtomicCounters = */ 0,
    /* .MaxFragmentAtomicCounters = */ 8,
    /* .MaxCombinedAtomicCounters = */ 8,
    /* .MaxAtomicCounterBindings = */ 1,
    /* .MaxVertexAtomicCounterBuffers = */ 0,
    /* .MaxTessControlAtomicCounterBuffers = */ 0,
    /* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
    /* .MaxGeometryAtomicCounterBuffers = */ 0,
    /* .MaxFragmentAtomicCounterBuffers = */ 1,
    /* .MaxCombinedAtomicCounterBuffers = */ 1,
    /* .MaxAtomicCounterBufferSize = */ 16384,
    /* .MaxTransformFeedbackBuffers = */ 4,
    /* .MaxTransformFeedbackInterleavedComponents = */ 64,
    /* .MaxCullDistances = */ 8,
    /* .MaxCombinedClipAndCullDistances = */ 8,
    /* .MaxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .maxDualSourceDrawBuffersEXT = */ 1,

    /* .limits = */ {
        /* .nonInductiveForLoops = */ 1,
        /* .whileLoops = */ 1,
        /* .doWhileLoops = */ 1,
        /* .generalUniformIndexing = */ 1,
        /* .generalAttributeMatrixVectorIndexing = */ 1,
        /* .generalVaryingIndexing = */ 1,
        /* .generalSamplerIndexing = */ 1,
        /* .generalVariableIndexing = */ 1,
        /* .generalConstantMatrixVectorIndexing = */ 1,
    }};
}

namespace Ilum
{
static CComPtr<IDxcUtils>          DXCUtils              = nullptr;
static CComPtr<IDxcCompiler3>      DXCCompiler           = nullptr;
static CComPtr<IDxcIncludeHandler> DefaultIncludeHandler = nullptr;

std::wstring to_wstring(const std::string &str)
{
	const auto slength = static_cast<int>(str.length()) + 1;
	const auto len     = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, nullptr, 0);
	const auto buf     = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);
	std::wstring result(buf);
	delete[] buf;
	return result;
}

inline std::string GetTargetProfile(RHIShaderStage stage)
{
	switch (stage)
	{
		case RHIShaderStage::Vertex:
			return "vs_6_6";
		case RHIShaderStage::Fragment:
			return "ps_6_6";
		case RHIShaderStage::TessellationControl:
			return "hs_6_6";
		case RHIShaderStage::TessellationEvaluation:
			return "ds_6_6";
		case RHIShaderStage::Geometry:
			return "gs_6_6";
		case RHIShaderStage::Compute:
			return "cs_6_6";
		case RHIShaderStage::RayGen:
		case RHIShaderStage::AnyHit:
		case RHIShaderStage::ClosestHit:
		case RHIShaderStage::Miss:
		case RHIShaderStage::Intersection:
		case RHIShaderStage::Callable:
			return "lib_6_6";
		case RHIShaderStage::Mesh:
			return "ms_6_6";
		case RHIShaderStage::Task:
			return "as_6_6";
		default:
			break;
	}
	return "";
}

inline EShLanguage GetShaderLanguage(RHIShaderStage stage)
{
	switch (stage)
	{
		case RHIShaderStage::Vertex:
			return EShLangVertex;
		case RHIShaderStage::Fragment:
			return EShLangFragment;
		case RHIShaderStage::TessellationControl:
			return EShLangTessControl;
		case RHIShaderStage::TessellationEvaluation:
			return EShLangTessEvaluation;
		case RHIShaderStage::Geometry:
			return EShLangGeometry;
		case RHIShaderStage::Compute:
			return EShLangCompute;
		case RHIShaderStage::RayGen:
			return EShLangRayGen;
		case RHIShaderStage::AnyHit:
			return EShLangAnyHit;
		case RHIShaderStage::ClosestHit:
			return EShLangClosestHit;
		case RHIShaderStage::Miss:
			return EShLangMiss;
		case RHIShaderStage::Intersection:
			return EShLangIntersect;
		case RHIShaderStage::Callable:
			return EShLangCallable;
		case RHIShaderStage::Mesh:
			return EShLangMeshNV;
		case RHIShaderStage::Task:
			return EShLangTaskNV;
		default:
			break;
	}
	return EShLangCount;
}

template <ShaderSource Src, ShaderTarget Tar>
inline std::vector<uint8_t> CompileShader(const std::string &code, RHIShaderStage stage, const std::string &entry_point, const std::vector<std::string> &macros)
{
	return {};
}

template <>
std::vector<uint8_t> CompileShader<ShaderSource::GLSL, ShaderTarget::SPIRV>(const std::string &code, RHIShaderStage stage, const std::string &entry_point, const std::vector<std::string> &macros)
{
	EShMessages msgs = static_cast<EShMessages>(EShMsgDefault | EShMsgVulkanRules | EShMsgSpvRules);

	EShLanguage lang = GetShaderLanguage(stage);

	std::string info_log = "";

	const char *file_name_list[1] = {""};
	const char *shader_source     = reinterpret_cast<const char *>(code.data());

	glslang::TShader shader(lang);
	shader.setStringsWithLengthsAndNames(&shader_source, nullptr, file_name_list, 1);
	shader.setEntryPoint(entry_point.c_str());
	shader.setSourceEntryPoint(entry_point.c_str());
	shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_5);
	shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_2);
	for (const auto &macro : macros)
	{
		shader.setPreamble(macro.c_str());
	}

	if (!shader.parse(&glslang::DefaultTBuiltInResource, 100, false, msgs))
	{
		info_log = std::string(shader.getInfoLog()) + "\n" + std::string(shader.getInfoDebugLog());
		LOG_ERROR(info_log);
		return {};
	}

	// Add shader to a new program
	glslang::TProgram program;
	program.addShader(&shader);

	// Link program
	if (!program.link(msgs))
	{
		info_log = std::string(program.getInfoLog()) + "\n" + std::string(program.getInfoDebugLog());
		LOG_ERROR(info_log);
		return {};
	}

	// Save info log
	if (shader.getInfoLog())
	{
		info_log = std::string(shader.getInfoLog()) + "\n" + std::string(shader.getInfoDebugLog());
	}

	if (program.getInfoLog())
	{
		info_log = std::string(program.getInfoLog()) + "\n" + std::string(program.getInfoDebugLog());
	}

	glslang::TIntermediate *intermediate = program.getIntermediate(lang);

	if (!intermediate)
	{
		info_log += "Failed to get shared intermediate code!\n";
		LOG_ERROR(info_log);
		return {};
	}

	spv::SpvBuildLogger logger;

	std::vector<uint32_t> spirv;
	std::vector<uint8_t>  result;

	glslang::GlslangToSpv(*intermediate, spirv, &logger);
	result.resize(spirv.size() * 4);
	std::memcpy(result.data(), spirv.data(), result.size());

	return result;
}

template <>
std::vector<uint8_t> CompileShader<ShaderSource::HLSL, ShaderTarget::SPIRV>(const std::string &code, RHIShaderStage stage, const std::string &entry_point, const std::vector<std::string> &macros)
{
	DxcBuffer                 dxc_buffer    = {};
	CComPtr<IDxcBlobEncoding> blob_encoding = nullptr;
	{
		if (FAILED(DXCUtils->CreateBlobFromPinned(code.c_str(), static_cast<uint32_t>(code.size()), CP_UTF8, &blob_encoding)))
		{
			LOG_ERROR("Failed to load shader source.");
			return {};
		}

		dxc_buffer.Ptr      = blob_encoding->GetBufferPointer();
		dxc_buffer.Size     = blob_encoding->GetBufferSize();
		dxc_buffer.Encoding = DXC_CP_ACP;        // Assume BOM says UTF8 or UTF16 or this is ANSI text.
	}

	std::vector<std::wstring> arguments;

	// Compile arguments
	arguments.emplace_back(L"-E");
	arguments.emplace_back(to_wstring(entry_point));
	arguments.emplace_back(L"-T");
	arguments.emplace_back(to_wstring(GetTargetProfile(stage)));
	arguments.emplace_back(L"-I");
	arguments.emplace_back(to_wstring(Path::GetInstance().GetCurrent() + "/Source/Shaders"));
	arguments.emplace_back(L"-spirv");
	arguments.emplace_back(L"-fspv-target-env=vulkan1.2");
	arguments.emplace_back(L"-fspv-extension=SPV_KHR_ray_tracing");
	arguments.emplace_back(L"-fspv-extension=SPV_KHR_shader_draw_parameters");
	arguments.emplace_back(L"-fspv-extension=SPV_EXT_descriptor_indexing");
	arguments.emplace_back(L"-fspv-extension=SPV_EXT_shader_viewport_index_layer");
	arguments.emplace_back(L"-fspv-extension=SPV_NV_mesh_shader");

	for (const auto &macro : macros)
	{
		arguments.emplace_back(to_wstring(std::string("-D") + macro));
	}

	// Convert arguments to LPCWSTR
	std::vector<LPCWSTR> arguments_lpcwstr;
	arguments_lpcwstr.reserve(arguments.size());
	for (const std::wstring &wstr : arguments)
	{
		arguments_lpcwstr.emplace_back(wstr.c_str());
	}

	// Compile
	IDxcResult *dxc_result = nullptr;
	DXCCompiler->Compile(
	    &dxc_buffer,
	    arguments_lpcwstr.data(),
	    static_cast<uint32_t>(arguments_lpcwstr.size()),
	    DefaultIncludeHandler,
	    IID_PPV_ARGS(&dxc_result));

	// Get error buffer
	IDxcBlobEncoding *error_buffer = nullptr;
	HRESULT           result       = dxc_result->GetErrorBuffer(&error_buffer);
	if (SUCCEEDED(result))
	{
		// Log info, warnings and errors
		std::stringstream ss(std::string(static_cast<char *>(error_buffer->GetBufferPointer()), error_buffer->GetBufferSize()));
		std::string       line;
		while (getline(ss, line, '\n'))
		{
			if (line.find("error") != std::string::npos)
			{
				LOG_ERROR("{}", line);
			}
			else if (line.find("warning") != std::string::npos)
			{
				LOG_WARN("{}", line);
			}
			else if (!line.empty())
			{
				LOG_INFO("{}", line);
			}
		}
	}
	else
	{
		LOG_ERROR("Failed to get error buffer");
	}

	// Release error buffer
	if (error_buffer)
	{
		error_buffer->Release();
		error_buffer = nullptr;
	}

	// Return status
	dxc_result->GetStatus(&result);

	// Check for errors
	if (result != S_OK)
	{
		LOG_ERROR("Failed to compile");

		if (dxc_result)
		{
			dxc_result->Release();
			dxc_result = nullptr;
		}
		else
		{
			ASSERT(false);
		}
	}

	IDxcBlob *shader_buffer = nullptr;
	dxc_result->GetResult(&shader_buffer);

	std::vector<uint8_t> spirv(shader_buffer->GetBufferSize());
	std::memcpy(spirv.data(), shader_buffer->GetBufferPointer(), shader_buffer->GetBufferSize());

	return spirv;
}

template <>
std::vector<uint8_t> CompileShader<ShaderSource::HLSL, ShaderTarget::DXIL>(const std::string &code, RHIShaderStage stage, const std::string &entry_point, const std::vector<std::string> &macros)
{
	DxcBuffer                 dxc_buffer    = {};
	CComPtr<IDxcBlobEncoding> blob_encoding = nullptr;
	{
		if (FAILED(DXCUtils->CreateBlobFromPinned(code.c_str(), static_cast<uint32_t>(code.size()), CP_UTF8, &blob_encoding)))
		{
			LOG_ERROR("Failed to load shader source.");
			return {};
		}

		dxc_buffer.Ptr      = blob_encoding->GetBufferPointer();
		dxc_buffer.Size     = blob_encoding->GetBufferSize();
		dxc_buffer.Encoding = DXC_CP_ACP;
	}

	std::vector<std::wstring> arguments;

	// Compile arguments
	arguments.emplace_back(L"-E");
	arguments.emplace_back(to_wstring(entry_point));
	arguments.emplace_back(L"-T");
	arguments.emplace_back(to_wstring(GetTargetProfile(stage)));
	arguments.emplace_back(L"-I");
	arguments.emplace_back(to_wstring(Path::GetInstance().GetCurrent() + "/Source/Shaders"));

	for (const auto &macro : macros)
	{
		arguments.emplace_back(to_wstring(std::string("-D") + macro));
	}

	// Convert arguments to LPCWSTR
	std::vector<LPCWSTR> arguments_lpcwstr;
	arguments_lpcwstr.reserve(arguments.size());
	for (const std::wstring &wstr : arguments)
	{
		arguments_lpcwstr.emplace_back(wstr.c_str());
	}

	// Compile
	IDxcResult *dxc_result = nullptr;
	DXCCompiler->Compile(
	    &dxc_buffer,
	    arguments_lpcwstr.data(),
	    static_cast<uint32_t>(arguments_lpcwstr.size()),
	    DefaultIncludeHandler,
	    IID_PPV_ARGS(&dxc_result));

	// Get error buffer
	IDxcBlobEncoding *error_buffer = nullptr;
	HRESULT           result       = dxc_result->GetErrorBuffer(&error_buffer);
	if (SUCCEEDED(result))
	{
		// Log info, warnings and errors
		std::stringstream ss(std::string(static_cast<char *>(error_buffer->GetBufferPointer()), error_buffer->GetBufferSize()));
		std::string       line;
		while (getline(ss, line, '\n'))
		{
			if (line.find("error") != std::string::npos)
			{
				LOG_ERROR("{}", line);
			}
			else if (line.find("warning") != std::string::npos)
			{
				LOG_WARN("{}", line);
			}
			else if (!line.empty())
			{
				LOG_INFO("{}", line);
			}
		}
	}
	else
	{
		LOG_ERROR("Failed to get error buffer");
	}

	// Release error buffer
	if (error_buffer)
	{
		error_buffer->Release();
		error_buffer = nullptr;
	}

	// Return status
	dxc_result->GetStatus(&result);

	// Check for errors
	if (result != S_OK)
	{
		LOG_ERROR("Failed to compile");

		if (dxc_result)
		{
			dxc_result->Release();
			dxc_result = nullptr;
		}
		else
		{
			ASSERT(false);
		}
	}

	IDxcBlob *shader_buffer = nullptr;
	dxc_result->GetResult(&shader_buffer);

	std::vector<uint8_t> dxil(shader_buffer->GetBufferSize());
	std::memcpy(dxil.data(), shader_buffer->GetBufferPointer(), shader_buffer->GetBufferSize());

	return dxil;
}

ShaderCompiler::ShaderCompiler()
{
	// Init glslang
	glslang::InitializeProcess();

	// Init dxc
	DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&DXCUtils));
	DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&DXCCompiler));
	DXCUtils->CreateDefaultIncludeHandler(&DefaultIncludeHandler);
}

ShaderCompiler::~ShaderCompiler()
{
	glslang::FinalizeProcess();
}

std::vector<uint8_t> ShaderCompiler::Compile(const ShaderDesc &desc)
{
	if (desc.source == ShaderSource::GLSL)
	{
		if (desc.target == ShaderTarget::SPIRV)
		{
			return CompileShader<ShaderSource::GLSL, ShaderTarget::SPIRV>(desc.code, desc.stage, desc.entry_point, desc.macros);
		}
		else if (desc.target == ShaderTarget::DXIL)
		{
			return CompileShader<ShaderSource::GLSL, ShaderTarget::DXIL>(desc.code, desc.stage, desc.entry_point, desc.macros);
		}
	}
	else if (desc.source == ShaderSource::HLSL)
	{
		if (desc.target == ShaderTarget::SPIRV)
		{
			return CompileShader<ShaderSource::HLSL, ShaderTarget::SPIRV>(desc.code, desc.stage, desc.entry_point, desc.macros);
		}
		else if (desc.target == ShaderTarget::DXIL)
		{
			return CompileShader<ShaderSource::HLSL, ShaderTarget::DXIL>(desc.code, desc.stage, desc.entry_point, desc.macros);
		}
	}

	return {};
}
}        // namespace Ilum