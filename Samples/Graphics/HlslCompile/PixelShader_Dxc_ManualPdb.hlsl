//--------------------------------------------------------------------------------------
// PixelShader_Dxc_ManualPdb.hlsl
//
// Simple shader to render a triangle
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

struct Interpolants
{
	float4 position : SV_Position;
	float4 color    : COLOR0;
};

struct Pixel
{
	float4 color    : SV_TARGET0;
};

[RootSignature("RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT)")]
Pixel main(Interpolants In)
{
	Pixel Out;
	Out.color = In.color;
	Out.color.w = 0.09f;	// Add a unique constant to prevent PIX from recognizing duplicate PDBs
	return Out;
}