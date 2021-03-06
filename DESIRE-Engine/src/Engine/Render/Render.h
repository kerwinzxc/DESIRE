#pragma once

#include "Engine/Core/String.h"

#include <memory>

class IWindow;
class View;
class Mesh;
class DynamicMesh;
class Material;
class Shader;
class Texture;
class RenderTarget;
class Matrix4;

class Render
{
public:
	enum class EDepthTest
	{
		DISABLED,
		LESS,
		LESS_EQUAL,
		GREATER,
		GREATER_EQUAL,
		EQUAL,
		NOT_EQUAL
	};

	enum class ECullMode
	{
		NONE,
		CCW,
		CW
	};

	enum class EBlend
	{
		ZERO,				// 0, 0, 0, 0
		ONE,				// 1, 1, 1, 1
		SRC_COLOR,			// Rs, Gs, Bs, As
		INV_SRC_COLOR,		// 1-Rs, 1-Gs, 1-Bs, 1-As
		SRC_ALPHA,			// As, As, As, As
		INV_SRC_ALPHA,		// 1-As, 1-As, 1-As, 1-As
		DEST_ALPHA,			// Ad, Ad, Ad, Ad
		INV_DEST_ALPHA,		// 1-Ad, 1-Ad, 1-Ad ,1-Ad
		DEST_COLOR,			// Rd, Gd, Bd, Ad
		INV_DEST_COLOR,		// 1-Rd, 1-Gd, 1-Bd, 1-Ad
		SRC_ALPHA_SAT,		// f, f, f, 1; where f = min(As, 1-Ad)
		BLEND_FACTOR,		// blendFactor
		INV_BLEND_FACTOR	// 1-blendFactor
	};

	enum class EBlendOp
	{
		ADD,
		SUBTRACT,
		REV_SUBTRACT,
		MIN,
		MAX
	};

	enum class EAddressMode
	{
		REPEAT,
		CLAMP,
		MIRRORED_REPEAT,
		MIRROR_ONCE,
		BORDER
	};

	enum class EFilterMode
	{
		POINT,			// No filtering, the texel with coordinates nearest to the desired pixel value is used (at most 1 texel being sampled)
		BILINEAR,		// Texture samples are averaged (at most 4 samples)
		TRILINEAR,		// Texture samples are averaged and also blended between mipmap levels (at most 8 samples)
		ANISOTROPIC,	// Use anisotropic interpolation
	};

	Render();
	virtual ~Render();

	virtual void Init(IWindow *mainWindow) = 0;
	virtual void UpdateRenderWindow(IWindow *window) = 0;
	virtual void Kill() = 0;

	virtual String GetShaderFilenameWithPath(const String& shaderFilename) const = 0;

	virtual void BeginFrame(IWindow *window) = 0;
	virtual void EndFrame() = 0;

	void RenderMesh(Mesh *mesh, Material *material);
	void RenderScreenSpaceQuad(Material *material);

	// Sets the current view that the rendering will happen on. (Use nullptr to set the default view which is using the frame buffer)
	virtual void SetView(View *view) = 0;

	virtual void SetWorldMatrix(const Matrix4& worldMatrix) = 0;
	virtual void SetViewProjectionMatrices(const Matrix4& viewMatrix, const Matrix4& projMatrix) = 0;

	// Render state setup
	virtual void SetScissor(uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0) = 0;
	virtual void SetClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
	virtual void SetColorWriteEnabled(bool r, bool g, bool b, bool a) = 0;
	virtual void SetDepthWriteEnabled(bool enabled) = 0;
	virtual void SetDepthTest(EDepthTest deptTest) = 0;
	virtual void SetCullMode(ECullMode cullMode) = 0;
	void SetBlendMode(EBlend srcBlend, EBlend destBlend, EBlendOp blendOp = EBlendOp::ADD);
	virtual void SetBlendModeSeparated(EBlend srcBlendRGB, EBlend destBlendRGB, EBlendOp blendOpRGB, EBlend srcBlendAlpha, EBlend destBlendAlpha, EBlendOp blendOpAlpha) = 0;
	virtual void SetBlendModeDisabled() = 0;

	// Resource bind
	virtual void Bind(Mesh *mesh) = 0;
	virtual void Bind(Shader *shader) = 0;
	virtual void Bind(Texture *texture) = 0;
	virtual void Bind(RenderTarget *renderTarget) = 0;

	// Resource unbind
	virtual void Unbind(Mesh *mesh) = 0;
	virtual void Unbind(Shader *shader) = 0;
	virtual void Unbind(Texture *texture) = 0;
	virtual void Unbind(RenderTarget *renderTarget) = 0;

	// Resource update
	virtual void UpdateDynamicMesh(DynamicMesh *mesh) = 0;

protected:
	void SetDefaultRenderStates();

	virtual void SetViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height) = 0;

	std::unique_ptr<Shader> screenSpaceQuadVertexShader;

private:
	virtual void SetMesh(Mesh *mesh) = 0;
	virtual void SetScreenSpaceQuadMesh() = 0;
	void SetMaterial(Material *material);
	virtual void SetVertexShader(Shader *vertexShader) = 0;
	virtual void SetFragmentShader(Shader *fragmentShader) = 0;
	virtual void SetTexture(uint8_t samplerIdx, Texture *texture, EFilterMode filterMode, EAddressMode addressMode = EAddressMode::REPEAT) = 0;
	virtual void UpdateShaderParams(const Material *material) = 0;

	// Submit draw command
	virtual void DoRender() = 0;
};
