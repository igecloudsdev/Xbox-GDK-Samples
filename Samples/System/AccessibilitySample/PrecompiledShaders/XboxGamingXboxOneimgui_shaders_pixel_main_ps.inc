#if 0
;
; Input signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Position              0   xyzw        0      POS   float       
; COLOR                    0   xyzw        1     NONE   float   xyzw
; TEXCOORD                 0   xy          2     NONE   float   xy  
;
;
; Output signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Target                0   xyzw        0   TARGET   float   xyzw
;
; shader debug name: Compiled\XboxGamingXboxOneimgui_shaders_pixel_main_ps.pdb
; shader hash: a6e8c1d16ac7402a2565374f9291b557
;
; Pipeline Runtime Information: 
;
; Pixel Shader
; DepthOutput=0
; SampleFrequency=0
;
;
; Input signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; SV_Position              0          noperspective       
; COLOR                    0                 linear       
; TEXCOORD                 0                 linear       
;
; Output signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; SV_Target                0                              
;
; Buffer Definitions:
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
;                                   sampler      NA          NA      S0             s0     1
;                                   texture     f32          2d      T0             t0     1
;
;
; ViewId state:
;
; Number of inputs: 10, outputs: 4
; Outputs dependent on ViewId: {  }
; Inputs contributing to computation of Outputs:
;   output 0 depends on inputs: { 4, 8, 9 }
;   output 1 depends on inputs: { 5, 8, 9 }
;   output 2 depends on inputs: { 6, 8, 9 }
;   output 3 depends on inputs: { 7, 8, 9 }
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-xb1"

%dx.types.Handle = type { i8* }
%dx.types.ResRet.f32 = type { float, float, float, float, i32 }
%"class.Texture2D<vector<float, 4> >" = type { <4 x float>, %"class.Texture2D<vector<float, 4> >::mips_type" }
%"class.Texture2D<vector<float, 4> >::mips_type" = type { i32 }
%struct.SamplerState = type { i32 }

define void @main_ps() {
  %1 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 0, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %2 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 3, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %3 = call float @dx.op.loadInput.f32(i32 4, i32 2, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %4 = call float @dx.op.loadInput.f32(i32 4, i32 2, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %5 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %6 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %7 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 2, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %8 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 3, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %9 = call %dx.types.ResRet.f32 @dx.op.sample.f32(i32 60, %dx.types.Handle %1, %dx.types.Handle %2, float %3, float %4, float undef, float undef, i32 0, i32 0, i32 undef, float undef)  ; Sample(srv,sampler,coord0,coord1,coord2,coord3,offset0,offset1,offset2,clamp)
  %10 = extractvalue %dx.types.ResRet.f32 %9, 0
  %11 = extractvalue %dx.types.ResRet.f32 %9, 1
  %12 = extractvalue %dx.types.ResRet.f32 %9, 2
  %13 = extractvalue %dx.types.ResRet.f32 %9, 3
  %14 = fmul fast float %10, %5
  %15 = fmul fast float %11, %6
  %16 = fmul fast float %12, %7
  %17 = fmul fast float %13, %8
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %14)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %15)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %16)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 3, float %17)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  ret void
}

; Function Attrs: nounwind readnone
declare float @dx.op.loadInput.f32(i32, i32, i32, i8, i32) #0

; Function Attrs: nounwind
declare void @dx.op.storeOutput.f32(i32, i32, i32, i8, float) #1

; Function Attrs: nounwind readonly
declare %dx.types.ResRet.f32 @dx.op.sample.f32(i32, %dx.types.Handle, %dx.types.Handle, float, float, float, float, i32, i32, i32, float) #2

; Function Attrs: nounwind readonly
declare %dx.types.Handle @dx.op.createHandle(i32, i8, i32, i32, i1) #2

attributes #0 = { nounwind readnone }
attributes #1 = { nounwind }
attributes #2 = { nounwind readonly }

!xbox.compiler.options = !{!0, !1}
!llvm.ident = !{!2}
!dx.version = !{!3}
!dx.valver = !{!4}
!dx.shaderModel = !{!5}
!dx.resources = !{!6}
!dx.viewIdState = !{!12}
!dx.entryPoints = !{!13}

!0 = !{!"__XBOX_BACKEND_OPT_LEVEL", !"3"}
!1 = !{!"__XBOX_INTERNAL_OVERRIDE_BACKEND_OPT_LEVEL", !"1"}
!2 = !{!"dxcoob 2019.05.00"}
!3 = !{i32 1, i32 0}
!4 = !{i32 1, i32 7}
!5 = !{!"ps", i32 6, i32 0}
!6 = !{!7, null, null, !10}
!7 = !{!8}
!8 = !{i32 0, %"class.Texture2D<vector<float, 4> >"* undef, !"", i32 0, i32 0, i32 1, i32 2, i32 0, !9}
!9 = !{i32 0, i32 9}
!10 = !{!11}
!11 = !{i32 0, %struct.SamplerState* undef, !"", i32 0, i32 0, i32 1, i32 0, null}
!12 = !{[12 x i32] [i32 10, i32 4, i32 0, i32 0, i32 0, i32 0, i32 1, i32 2, i32 4, i32 8, i32 15, i32 15]}
!13 = !{void ()* @main_ps, !"main_ps", !14, !6, null}
!14 = !{!15, !22, null}
!15 = !{!16, !18, !20}
!16 = !{i32 0, !"SV_Position", i8 9, i8 3, !17, i8 4, i32 1, i8 4, i32 0, i8 0, null}
!17 = !{i32 0}
!18 = !{i32 1, !"COLOR", i8 9, i8 0, !17, i8 2, i32 1, i8 4, i32 1, i8 0, !19}
!19 = !{i32 3, i32 15}
!20 = !{i32 2, !"TEXCOORD", i8 9, i8 0, !17, i8 2, i32 1, i8 2, i32 2, i8 0, !21}
!21 = !{i32 3, i32 3}
!22 = !{!23}
!23 = !{i32 0, !"SV_Target", i8 9, i8 16, !17, i8 0, i32 1, i8 4, i32 0, i8 0, !19}

;
; DUMPING SHADER HARDWARE INSTRUCTIONS 
;
// Shader Type               : (PS)
// Shader Hw Stage           : (PS)

// Shader Instructions:
shader main
  asic(CI)
  type(PS)
                                                            // s_ps_state in s0
  s_mov_b64     s[12:13], exec
  s_wqm_b64     exec, exec // wrscc
  s_mov_b32     s1, 0
  s_load_dword  s4, s[0:1], 0x10
  s_mov_b32     s5, 0
  s_mov_b32     m0, s3
  v_interp_p1_f32  v2, v0, attr1.x
  v_interp_p1_f32  v3, v0, attr1.y
  s_waitcnt     lgkmcnt(0)
  s_load_dwordx8  s[4:11], s[4:5], 0x00
  v_interp_p1_f32  v4, v0, attr0.x
  v_interp_p1_f32  v5, v0, attr0.y
  v_interp_p1_f32  v6, v0, attr0.z
  v_interp_p1_f32  v7, v0, attr0.w
  v_interp_p2_f32  v2, v1, attr1.x
  v_interp_p2_f32  v3, v1, attr1.y
  v_interp_p2_f32  v4, v1, attr0.x
  v_interp_p2_f32  v5, v1, attr0.y
  v_interp_p2_f32  v6, v1, attr0.z
  v_interp_p2_f32  v7, v1, attr0.w
  s_and_b64     exec, exec, s[12:13] // wrscc
  s_movk_i32    s0, 0x7000
  s_mov_b32     s1, 0
  s_mov_b32     s2, 0x78500000
  s_mov_b32     s3, 0
  s_waitcnt     lgkmcnt(0)
  image_sample  v[0:3], v[2:3], s[4:11], s[0:3] dmask:0xf
  s_waitcnt     vmcnt(0)
  v_mul_legacy_f32  v5, v1, v5
  v_mul_legacy_f32  v2, v2, v6
  v_mul_legacy_f32  v3, v3, v7
  v_mul_legacy_f32  v4, v0, v4
  v_cvt_pkrtz_f16_f32  v0, v4, v5
  v_cvt_pkrtz_f16_f32  v1, v2, v3
  exp           mrt0, v0, v0, v1, v1 done compr vm
  s_endpgm      
end


NumVGPR=8,NumSGPR=16,LDS=0,Scratch=0,Occpancy=10


#endif

const unsigned char imgui_shaders_pixel_main_ps[] = {
  0x44, 0x58, 0x42, 0x43, 0xbe, 0x8a, 0xd3, 0x76, 0xbf, 0x94, 0x27, 0x01,
  0xb9, 0x06, 0x01, 0xba, 0x90, 0xfc, 0xc6, 0x69, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x0e, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0xdb, 0x00, 0x00, 0x00, 0x15, 0x01, 0x00, 0x00,
  0x19, 0x02, 0x00, 0x00, 0xad, 0x02, 0x00, 0x00, 0xf5, 0x02, 0x00, 0x00,
  0x11, 0x03, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0x83, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x53, 0x56, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x00,
  0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f,
  0x52, 0x44, 0x00, 0x4f, 0x53, 0x47, 0x31, 0x32, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74,
  0x00, 0x50, 0x53, 0x56, 0x30, 0xfc, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x03, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, 0x58, 0x43,
  0x4f, 0x4f, 0x52, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x44, 0x03, 0x03, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x44, 0x00, 0x03, 0x02, 0x00,
  0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x42,
  0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x44, 0x10, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x54, 0x53,
  0x30, 0x8c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
  0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00,
  0x00, 0x1d, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
  0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x15, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
  0x00, 0x49, 0x4c, 0x44, 0x4e, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39,
  0x00, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x64, 0x5c, 0x58, 0x62,
  0x6f, 0x78, 0x47, 0x61, 0x6d, 0x69, 0x6e, 0x67, 0x58, 0x62, 0x6f, 0x78,
  0x4f, 0x6e, 0x65, 0x69, 0x6d, 0x67, 0x75, 0x69, 0x5f, 0x73, 0x68, 0x61,
  0x64, 0x65, 0x72, 0x73, 0x5f, 0x70, 0x69, 0x78, 0x65, 0x6c, 0x5f, 0x6d,
  0x61, 0x69, 0x6e, 0x5f, 0x70, 0x73, 0x2e, 0x70, 0x64, 0x62, 0x00, 0x00,
  0x00, 0x48, 0x41, 0x53, 0x48, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xa6, 0xe8, 0xc1, 0xd1, 0x6a, 0xc7, 0x40, 0x2a, 0x25, 0x65, 0x37,
  0x4f, 0x92, 0x91, 0xb5, 0x57, 0x44, 0x58, 0x49, 0x4c, 0xe8, 0x0a, 0x00,
  0x00, 0x60, 0x00, 0x00, 0x00, 0xba, 0x02, 0x00, 0x00, 0x44, 0x58, 0x49,
  0x4c, 0x00, 0x01, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x44, 0x07, 0x00,
  0x00, 0x58, 0x44, 0x41, 0x54, 0x06, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00,
  0x00, 0x07, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x5c, 0x07, 0x00,
  0x00, 0x10, 0x00, 0x00, 0x00, 0xc8, 0x07, 0x00, 0x00, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x07, 0x00, 0x00, 0xf5, 0x01, 0x00,
  0x00, 0x03, 0x00, 0x00, 0x00, 0xd0, 0x09, 0x00, 0x00, 0xb0, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x80, 0x0a, 0x00, 0x00, 0x4c, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0xcc, 0x0a, 0x00, 0x00, 0x1a, 0x00, 0x00,
  0x00, 0x60, 0x00, 0x00, 0x00, 0xd7, 0x01, 0x00, 0x00, 0x44, 0x58, 0x49,
  0x4c, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x44, 0x07, 0x00,
  0x00, 0x42, 0x43, 0xc0, 0xde, 0x21, 0x0c, 0x00, 0x00, 0xce, 0x01, 0x00,
  0x00, 0x0b, 0x82, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00,
  0x00, 0x07, 0x81, 0x23, 0x91, 0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32,
  0x39, 0x92, 0x01, 0x84, 0x0c, 0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b,
  0x62, 0x80, 0x14, 0x45, 0x02, 0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32,
  0x14, 0x38, 0x08, 0x18, 0x4b, 0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14,
  0x20, 0x43, 0x46, 0x88, 0xa5, 0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e,
  0x90, 0x91, 0x22, 0xc4, 0x50, 0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5,
  0x8a, 0x04, 0x29, 0x46, 0x06, 0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x1b, 0x8c, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8,
  0x0d, 0x84, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x20, 0x6d, 0x30, 0x86,
  0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x09, 0xa8, 0x00, 0x49, 0x18, 0x00,
  0x00, 0x03, 0x00, 0x00, 0x00, 0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x89, 0x20, 0x00, 0x00, 0x43, 0x00, 0x00,
  0x00, 0x32, 0x22, 0x48, 0x09, 0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4,
  0x84, 0x04, 0x93, 0x22, 0xe3, 0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a,
  0x8c, 0x0b, 0x84, 0xa4, 0x4c, 0x10, 0x68, 0x23, 0x00, 0x25, 0x00, 0x14,
  0x66, 0x00, 0xe6, 0x08, 0xc0, 0x60, 0x8e, 0x00, 0x29, 0xc6, 0x20, 0x84,
  0x14, 0x42, 0xa6, 0x18, 0x80, 0x10, 0x52, 0x06, 0xa1, 0x9b, 0x86, 0xcb,
  0x9f, 0xb0, 0x87, 0x90, 0xfc, 0x95, 0x90, 0x56, 0x62, 0xf2, 0x8b, 0xdb,
  0x46, 0xc5, 0x18, 0x63, 0x10, 0x2a, 0xf7, 0x0c, 0x97, 0x3f, 0x61, 0x0f,
  0x21, 0xf9, 0x21, 0xd0, 0x0c, 0x0b, 0x81, 0x82, 0x55, 0x18, 0x45, 0x18,
  0x1b, 0x63, 0x0c, 0x42, 0xc8, 0xa0, 0x36, 0x47, 0x10, 0x14, 0x83, 0x91,
  0x42, 0xc8, 0x23, 0x38, 0x10, 0x30, 0x8c, 0x40, 0x0c, 0x33, 0xb5, 0xc1,
  0x38, 0xb0, 0x43, 0x38, 0xcc, 0xc3, 0x3c, 0xb8, 0x01, 0x2d, 0x94, 0x03,
  0x3e, 0xd0, 0x43, 0x3d, 0xc8, 0x43, 0x39, 0xc8, 0x01, 0x29, 0xf0, 0x81,
  0x3d, 0x94, 0xc3, 0x38, 0xd0, 0xc3, 0x3b, 0xc8, 0x03, 0x1f, 0x98, 0x03,
  0x3b, 0xbc, 0x43, 0x38, 0xd0, 0x03, 0x1b, 0x80, 0x01, 0x1d, 0xf8, 0x01,
  0x18, 0xf8, 0x81, 0x1e, 0xe8, 0x41, 0x3b, 0xa4, 0x03, 0x3c, 0xcc, 0xc3,
  0x2f, 0xd0, 0x43, 0x3e, 0xc0, 0x43, 0x39, 0xa0, 0x80, 0xcc, 0x24, 0x06,
  0xe3, 0xc0, 0x0e, 0xe1, 0x30, 0x0f, 0xf3, 0xe0, 0x06, 0xb4, 0x50, 0x0e,
  0xf8, 0x40, 0x0f, 0xf5, 0x20, 0x0f, 0xe5, 0x20, 0x07, 0xa4, 0xc0, 0x07,
  0xf6, 0x50, 0x0e, 0xe3, 0x40, 0x0f, 0xef, 0x20, 0x0f, 0x7c, 0x60, 0x0e,
  0xec, 0xf0, 0x0e, 0xe1, 0x40, 0x0f, 0x6c, 0x00, 0x06, 0x74, 0xe0, 0x07,
  0x60, 0xe0, 0x07, 0x48, 0x98, 0x94, 0xea, 0x4d, 0xd2, 0x14, 0x51, 0xc2,
  0xe4, 0xb3, 0x00, 0xf3, 0x2c, 0x44, 0xc4, 0x4e, 0xc0, 0x44, 0xa0, 0x80,
  0xd0, 0x4d, 0x06, 0x02, 0x00, 0x13, 0x16, 0x72, 0xc0, 0x87, 0x74, 0x60,
  0x87, 0x36, 0x68, 0x87, 0x79, 0x68, 0x03, 0x7c, 0x10, 0x87, 0x38, 0xd8,
  0xf0, 0x0a, 0xe5, 0xd0, 0x06, 0xed, 0xa0, 0x07, 0xe5, 0xd0, 0x06, 0xf0,
  0xa0, 0x07, 0x73, 0x20, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9,
  0x10, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x80, 0x07, 0x7a,
  0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x10, 0x07, 0x76, 0xa0, 0x07, 0x73,
  0x20, 0x07, 0x6d, 0x90, 0x0e, 0x73, 0x20, 0x07, 0x7a, 0x30, 0x07, 0x72,
  0xd0, 0x06, 0xe9, 0x60, 0x07, 0x74, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x6d,
  0x60, 0x0e, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe6,
  0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x60, 0x0e, 0x76,
  0x40, 0x07, 0x7a, 0x60, 0x07, 0x74, 0xd0, 0x06, 0xee, 0x80, 0x07, 0x7a,
  0x10, 0x07, 0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x7a, 0x60, 0x07, 0x74,
  0x30, 0xe4, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0xc8, 0x63, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0x90, 0x07, 0x01, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0x21, 0x4f, 0x03, 0x04, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x1e, 0x08, 0x08, 0x80, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb2, 0x40, 0x00, 0x0f, 0x00, 0x00,
  0x00, 0x32, 0x1e, 0x98, 0x14, 0x19, 0x11, 0x4c, 0x90, 0x8c, 0x09, 0x26,
  0x47, 0xc6, 0x04, 0x43, 0x22, 0x25, 0x30, 0x02, 0x50, 0x0e, 0xc5, 0x50,
  0x04, 0x25, 0x51, 0x06, 0xe5, 0x41, 0xa5, 0x24, 0xca, 0xa0, 0x10, 0x46,
  0x00, 0x8a, 0xa0, 0x40, 0xc8, 0xce, 0x00, 0x10, 0x9e, 0x01, 0xa0, 0x3c,
  0x16, 0xa3, 0x10, 0x00, 0x00, 0x00, 0x81, 0x40, 0x20, 0xcf, 0x03, 0x00,
  0x00, 0x79, 0x18, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x1a, 0x03, 0x4c,
  0x90, 0x46, 0x02, 0x13, 0x44, 0xec, 0xeb, 0x0b, 0x4b, 0xe8, 0x09, 0xeb,
  0x4b, 0x28, 0x68, 0x68, 0xa9, 0xc8, 0x89, 0xe8, 0xeb, 0x09, 0x8a, 0xea,
  0x8b, 0xa9, 0xc8, 0xaa, 0x88, 0x89, 0xc1, 0xcc, 0x06, 0x21, 0x10, 0xa8,
  0x06, 0x5f, 0x5f, 0x58, 0x42, 0x4f, 0x58, 0x5f, 0x49, 0x4e, 0x54, 0x45,
  0x52, 0x4e, 0x41, 0x4c, 0x5f, 0x4f, 0x56, 0x45, 0x52, 0x52, 0x49, 0x44,
  0x45, 0x5f, 0x42, 0x41, 0x43, 0x4b, 0x45, 0x4e, 0x44, 0x5f, 0x4f, 0x50,
  0x54, 0x5f, 0x4c, 0x45, 0x56, 0x45, 0x4c, 0x0c, 0x62, 0x36, 0x08, 0x44,
  0xc1, 0x88, 0x0c, 0x6f, 0xec, 0xed, 0x4d, 0x0c, 0x44, 0x06, 0x26, 0x26,
  0xc7, 0x05, 0xa6, 0xc6, 0x05, 0x06, 0x66, 0x43, 0x70, 0x4c, 0x10, 0x88,
  0x62, 0x82, 0x40, 0x18, 0x1b, 0x84, 0x44, 0x99, 0x20, 0x10, 0xc7, 0x06,
  0x21, 0x61, 0x28, 0xc0, 0xcd, 0x4d, 0x10, 0x08, 0x64, 0xc3, 0xe0, 0x3c,
  0xca, 0x04, 0xc1, 0x9a, 0x08, 0x4c, 0x10, 0x88, 0x64, 0x82, 0x40, 0x28,
  0x1b, 0x04, 0x85, 0xda, 0x90, 0x28, 0x91, 0xa4, 0x28, 0xc9, 0xa4, 0x54,
  0x1b, 0x02, 0x6b, 0x82, 0x80, 0x51, 0x1b, 0x10, 0x05, 0x93, 0x14, 0x25,
  0x51, 0x80, 0x0d, 0x41, 0xb6, 0x81, 0xb8, 0x00, 0x40, 0x9b, 0x20, 0x64,
  0xd5, 0x86, 0x80, 0x9b, 0x20, 0x08, 0x00, 0x8f, 0xb6, 0xb0, 0x34, 0xb7,
  0x2f, 0xb8, 0x39, 0x2e, 0x53, 0x56, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74,
  0x69, 0x6f, 0x6e, 0x13, 0x84, 0xa2, 0x99, 0x20, 0x14, 0xce, 0x86, 0x40,
  0x99, 0x20, 0x14, 0xcf, 0x04, 0xa1, 0x80, 0x36, 0x2c, 0x0a, 0x18, 0x84,
  0x81, 0x18, 0x8c, 0x01, 0x19, 0x24, 0x64, 0xa0, 0x94, 0x01, 0xc0, 0x62,
  0xe8, 0x89, 0xe9, 0x49, 0x6a, 0x82, 0x50, 0x44, 0x13, 0x04, 0x62, 0x99,
  0x20, 0x10, 0xcc, 0x06, 0x21, 0x0d, 0xd4, 0x60, 0xc3, 0x92, 0x9c, 0x41,
  0x18, 0x94, 0xc1, 0x18, 0xa0, 0x41, 0x42, 0x06, 0x49, 0x19, 0xac, 0x01,
  0x11, 0xaa, 0x22, 0xac, 0xa1, 0xa7, 0x27, 0x29, 0xa2, 0x0d, 0x42, 0x1a,
  0xa4, 0xc1, 0x86, 0x65, 0x6a, 0x83, 0x30, 0x28, 0x83, 0x31, 0x40, 0x83,
  0x04, 0x0d, 0xa6, 0x32, 0x70, 0x83, 0x0d, 0x83, 0x19, 0xb0, 0xc1, 0x1b,
  0x30, 0x99, 0xb2, 0xfa, 0xa2, 0x0a, 0x93, 0x3b, 0x2b, 0xa3, 0x9b, 0x20,
  0x14, 0xd2, 0x86, 0x45, 0x89, 0x83, 0x30, 0x90, 0x83, 0x31, 0x28, 0x83,
  0x84, 0x0c, 0x94, 0x32, 0x58, 0x83, 0x0d, 0xc1, 0x1c, 0x6c, 0x18, 0xe0,
  0x80, 0x0e, 0x80, 0x0d, 0x85, 0xf7, 0xd5, 0xc1, 0x06, 0xb4, 0xc2, 0x13,
  0x7b, 0xc3, 0x73, 0x19, 0x7b, 0x6b, 0x83, 0x4b, 0x63, 0x2b, 0x93, 0x73,
  0x79, 0x83, 0xa3, 0x4b, 0x7b, 0x73, 0x9b, 0x9b, 0x22, 0x08, 0x45, 0x15,
  0x36, 0x36, 0xbb, 0x36, 0x97, 0x34, 0xb2, 0x32, 0x37, 0xba, 0x29, 0xc1,
  0x51, 0x85, 0x0c, 0xcf, 0xc5, 0xae, 0x4c, 0x6e, 0x2e, 0xed, 0xcd, 0x6d,
  0x4a, 0xa0, 0x34, 0x21, 0xc3, 0x73, 0xb1, 0x0b, 0x63, 0xb3, 0x2b, 0x93,
  0x9b, 0x12, 0x30, 0x75, 0xc8, 0xf0, 0x5c, 0xe6, 0xd0, 0xc2, 0xc8, 0xca,
  0xe4, 0x9a, 0xde, 0xc8, 0xca, 0xd8, 0xa6, 0x04, 0x4f, 0x19, 0x32, 0x3c,
  0x17, 0xb9, 0xb2, 0xb9, 0xb7, 0x3a, 0xb9, 0xb1, 0xb2, 0xb9, 0x29, 0x81,
  0x56, 0x87, 0x0c, 0xcf, 0xc5, 0x2e, 0xad, 0xec, 0x2e, 0x89, 0x6c, 0x8a,
  0x2e, 0x8c, 0xae, 0x6c, 0x4a, 0xc0, 0xd5, 0x21, 0xc3, 0x73, 0x29, 0x73,
  0xa3, 0x93, 0xcb, 0x83, 0x7a, 0x4b, 0x73, 0xa3, 0x9b, 0x9b, 0x12, 0xd4,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x79, 0x18, 0x00, 0x00, 0x4c, 0x00, 0x00,
  0x00, 0x33, 0x08, 0x80, 0x1c, 0xc4, 0xe1, 0x1c, 0x66, 0x14, 0x01, 0x3d,
  0x88, 0x43, 0x38, 0x84, 0xc3, 0x8c, 0x42, 0x80, 0x07, 0x79, 0x78, 0x07,
  0x73, 0x98, 0x71, 0x0c, 0xe6, 0x00, 0x0f, 0xed, 0x10, 0x0e, 0xf4, 0x80,
  0x0e, 0x33, 0x0c, 0x42, 0x1e, 0xc2, 0xc1, 0x1d, 0xce, 0xa1, 0x1c, 0x66,
  0x30, 0x05, 0x3d, 0x88, 0x43, 0x38, 0x84, 0x83, 0x1b, 0xcc, 0x03, 0x3d,
  0xc8, 0x43, 0x3d, 0x8c, 0x03, 0x3d, 0xcc, 0x78, 0x8c, 0x74, 0x70, 0x07,
  0x7b, 0x08, 0x07, 0x79, 0x48, 0x87, 0x70, 0x70, 0x07, 0x7a, 0x70, 0x03,
  0x76, 0x78, 0x87, 0x70, 0x20, 0x87, 0x19, 0xcc, 0x11, 0x0e, 0xec, 0x90,
  0x0e, 0xe1, 0x30, 0x0f, 0x6e, 0x30, 0x0f, 0xe3, 0xf0, 0x0e, 0xf0, 0x50,
  0x0e, 0x33, 0x10, 0xc4, 0x1d, 0xde, 0x21, 0x1c, 0xd8, 0x21, 0x1d, 0xc2,
  0x61, 0x1e, 0x66, 0x30, 0x89, 0x3b, 0xbc, 0x83, 0x3b, 0xd0, 0x43, 0x39,
  0xb4, 0x03, 0x3c, 0xbc, 0x83, 0x3c, 0x84, 0x03, 0x3b, 0xcc, 0xf0, 0x14,
  0x76, 0x60, 0x07, 0x7b, 0x68, 0x07, 0x37, 0x68, 0x87, 0x72, 0x68, 0x07,
  0x37, 0x80, 0x87, 0x70, 0x90, 0x87, 0x70, 0x60, 0x07, 0x76, 0x28, 0x07,
  0x76, 0xf8, 0x05, 0x76, 0x78, 0x87, 0x77, 0x80, 0x87, 0x5f, 0x08, 0x87,
  0x71, 0x18, 0x87, 0x72, 0x98, 0x87, 0x79, 0x98, 0x81, 0x2c, 0xee, 0xf0,
  0x0e, 0xee, 0xe0, 0x0e, 0xf5, 0xc0, 0x0e, 0xec, 0x30, 0x03, 0x62, 0xc8,
  0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xcc, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xdc,
  0x61, 0x1c, 0xca, 0x21, 0x1c, 0xc4, 0x81, 0x1d, 0xca, 0x61, 0x06, 0xd6,
  0x90, 0x43, 0x39, 0xc8, 0x43, 0x39, 0x98, 0x43, 0x39, 0xc8, 0x43, 0x39,
  0xb8, 0xc3, 0x38, 0x94, 0x43, 0x38, 0x88, 0x03, 0x3b, 0x94, 0xc3, 0x2f,
  0xbc, 0x83, 0x3c, 0xfc, 0x82, 0x3b, 0xd4, 0x03, 0x3b, 0xb0, 0xc3, 0x0c,
  0xc4, 0x21, 0x07, 0x7c, 0x70, 0x03, 0x7a, 0x28, 0x87, 0x76, 0x80, 0x87,
  0x19, 0xd1, 0x43, 0x0e, 0xf8, 0xe0, 0x06, 0xe4, 0x20, 0x0e, 0xe7, 0xe0,
  0x06, 0xf6, 0x10, 0x0e, 0xf2, 0xc0, 0x0e, 0xe1, 0x90, 0x0f, 0xef, 0x50,
  0x0f, 0xf4, 0x00, 0x00, 0x00, 0x71, 0x20, 0x00, 0x00, 0x13, 0x00, 0x00,
  0x00, 0x46, 0x20, 0x0d, 0x97, 0xef, 0x3c, 0xbe, 0x10, 0x11, 0xc0, 0x44,
  0x84, 0x40, 0x33, 0x2c, 0x84, 0x05, 0x4c, 0xc3, 0xe5, 0x3b, 0x8f, 0xbf,
  0x38, 0xc0, 0x20, 0x36, 0x0f, 0x35, 0xf9, 0xc5, 0x6d, 0xdb, 0x00, 0x34,
  0x5c, 0xbe, 0xf3, 0xf8, 0x12, 0xc0, 0x3c, 0x0b, 0xe1, 0x17, 0xb7, 0x6d,
  0x02, 0xd5, 0x70, 0xf9, 0xce, 0xe3, 0x4b, 0x93, 0x13, 0x11, 0x28, 0x35,
  0x3d, 0xd4, 0xe4, 0x17, 0xb7, 0x6d, 0x00, 0x07, 0x03, 0x20, 0xcd, 0xff,
  0x48, 0x00, 0x00, 0x00, 0x00, 0x61, 0x20, 0x00, 0x00, 0x3b, 0x00, 0x00,
  0x00, 0x13, 0x04, 0x41, 0x2c, 0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
  0x00, 0xf4, 0x46, 0x00, 0x88, 0xcc, 0x00, 0x14, 0x42, 0x29, 0x94, 0x5c,
  0xe1, 0x51, 0x29, 0x01, 0x1a, 0x33, 0x00, 0x00, 0x00, 0x23, 0x06, 0x09,
  0x00, 0x82, 0x60, 0x00, 0x69, 0x84, 0x83, 0x61, 0xc8, 0x88, 0x41, 0x02,
  0x80, 0x20, 0x18, 0x40, 0x5b, 0x11, 0x65, 0x59, 0x32, 0x62, 0x90, 0x00,
  0x20, 0x08, 0x06, 0xc6, 0x87, 0x5c, 0x1a, 0x94, 0x8c, 0x18, 0x24, 0x00,
  0x08, 0x82, 0x81, 0x01, 0x06, 0x09, 0xb6, 0x15, 0xca, 0x88, 0x41, 0x02,
  0x80, 0x20, 0x18, 0x18, 0x61, 0xa0, 0x74, 0x9c, 0xb4, 0x8c, 0x18, 0x24,
  0x00, 0x08, 0x82, 0x81, 0x21, 0x06, 0x8b, 0xd7, 0x1d, 0xcc, 0x88, 0x41,
  0x02, 0x80, 0x20, 0x18, 0x18, 0x63, 0xc0, 0x7c, 0xde, 0xd4, 0x8c, 0x18,
  0x24, 0x00, 0x08, 0x82, 0x81, 0x41, 0x06, 0x0d, 0x18, 0x7c, 0x97, 0x33,
  0x62, 0xf0, 0x00, 0x20, 0x08, 0x06, 0xcd, 0x18, 0x2c, 0xc8, 0x61, 0x14,
  0x49, 0x02, 0x06, 0x60, 0xf0, 0x24, 0xa3, 0x09, 0x01, 0x30, 0x9a, 0x20,
  0x04, 0xa3, 0x09, 0x83, 0x30, 0x9a, 0x40, 0x0c, 0x46, 0x24, 0xf2, 0x31,
  0x22, 0x91, 0x8f, 0x11, 0x89, 0x7c, 0x8c, 0x48, 0xe4, 0x33, 0x62, 0x90,
  0x00, 0x20, 0x08, 0x06, 0x48, 0x1b, 0x58, 0x69, 0x90, 0x06, 0x1f, 0x31,
  0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0x48, 0x1b, 0x58, 0x69, 0x90, 0x06,
  0xd3, 0x30, 0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0x48, 0x1b, 0x58, 0x69,
  0x90, 0x06, 0x9e, 0x30, 0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0x48, 0x1b,
  0x58, 0x69, 0x90, 0x06, 0x61, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xa6, 0xe8, 0xc1, 0xd1, 0x6a, 0xc7, 0x40, 0x2a, 0x25, 0x65, 0x37,
  0x4f, 0x92, 0x91, 0xb5, 0x57, 0x17, 0x00, 0x01, 0x00, 0x29, 0xf0, 0x0e,
  0x00, 0x78, 0x01, 0xed, 0x97, 0xbf, 0x4b, 0x1c, 0x41, 0x14, 0xc7, 0xdf,
  0xcc, 0xec, 0xad, 0x77, 0xe7, 0xdd, 0xee, 0x89, 0x0a, 0x1a, 0x14, 0x24,
  0x68, 0x13, 0x84, 0x58, 0x04, 0xac, 0x8c, 0x16, 0x62, 0xab, 0x9d, 0x20,
  0x87, 0x1c, 0x82, 0x8d, 0xd5, 0x95, 0x56, 0xe7, 0xfa, 0x2b, 0x36, 0x57,
  0x18, 0xb1, 0xb0, 0xb0, 0x4e, 0x6d, 0x8a, 0x34, 0x29, 0xf6, 0x34, 0x4d,
  0xa6, 0x13, 0xb1, 0xf1, 0x4f, 0xb0, 0x53, 0xb0, 0xb1, 0x10, 0xf5, 0x7d,
  0xe7, 0x66, 0xe2, 0x2a, 0x07, 0x36, 0x0a, 0x1a, 0xf6, 0x03, 0xdf, 0x37,
  0xf3, 0x9d, 0xdd, 0x37, 0x3b, 0xcc, 0xdb, 0x62, 0xe6, 0x32, 0x20, 0x43,
  0x75, 0xe8, 0xe7, 0x14, 0xda, 0x8b, 0xe3, 0xc2, 0x69, 0xb9, 0x8d, 0x28,
  0xc3, 0x7d, 0xc1, 0x42, 0x0b, 0xf6, 0x8a, 0x88, 0x44, 0x1b, 0xf6, 0xfd,
  0x3c, 0x82, 0x25, 0xcb, 0x2a, 0xb1, 0xc0, 0x04, 0x82, 0x05, 0xf9, 0x44,
  0xd1, 0x57, 0xd6, 0x38, 0x7a, 0x4f, 0x09, 0x59, 0xc8, 0x73, 0xb9, 0x49,
  0x24, 0xab, 0x99, 0xff, 0xd0, 0x82, 0x64, 0xdf, 0xa1, 0x58, 0x18, 0x47,
  0x8e, 0xc3, 0xad, 0x7b, 0xed, 0x5b, 0x27, 0x7f, 0x9f, 0x26, 0x59, 0xb4,
  0xfb, 0xfb, 0xb3, 0x59, 0xc7, 0xd5, 0x59, 0x7e, 0xcc, 0xb6, 0x78, 0xf6,
  0x6e, 0x69, 0xb5, 0x17, 0xae, 0x4e, 0x60, 0x1f, 0xe1, 0x19, 0x3c, 0x04,
  0xe6, 0x8b, 0xad, 0xab, 0xab, 0xe5, 0x21, 0xab, 0xd5, 0xfc, 0xe0, 0x8e,
  0x19, 0x40, 0xc7, 0x92, 0xec, 0xa3, 0x06, 0xbe, 0x08, 0x23, 0x4c, 0xe4,
  0xcb, 0xce, 0xa8, 0x65, 0x71, 0xff, 0x73, 0x7c, 0x04, 0x06, 0x7b, 0x01,
  0x61, 0x0b, 0xf0, 0xaf, 0x3b, 0xdc, 0x9e, 0x7f, 0x44, 0xa0, 0xa8, 0x01,
  0x6d, 0xf7, 0xd0, 0x35, 0x9c, 0xf3, 0x82, 0x7d, 0xf3, 0xbd, 0xa6, 0x57,
  0xf0, 0xe6, 0xa7, 0x4e, 0x78, 0xfe, 0xf1, 0xbd, 0x76, 0x9a, 0x97, 0x6d,
  0x72, 0x3e, 0xec, 0xe3, 0x7c, 0x2e, 0x18, 0xfb, 0x32, 0xfb, 0x72, 0xc2,
  0xcf, 0xb1, 0x9f, 0x4b, 0xf8, 0x0a, 0xfb, 0x4a, 0xc2, 0x2f, 0xb0, 0x5f,
  0x70, 0xde, 0xcd, 0x1f, 0x9a, 0xef, 0x49, 0x85, 0x5a, 0x63, 0xf4, 0x2d,
  0x93, 0xae, 0xf1, 0x65, 0x48, 0xd7, 0xf8, 0x32, 0xa4, 0x6b, 0x4c, 0x49,
  0x49, 0x49, 0x49, 0x79, 0x6d, 0x6a, 0x5e, 0x3d, 0xae, 0xe5, 0x6f, 0xe3,
  0x48, 0xad, 0xc6, 0x25, 0x21, 0x0f, 0x23, 0xb5, 0x19, 0x2b, 0x75, 0x13,
  0x93, 0x97, 0xd5, 0x94, 0x29, 0xe8, 0x15, 0xaa, 0x37, 0x28, 0xf3, 0x87,
  0x8f, 0xf3, 0x25, 0x4d, 0xa2, 0x4b, 0x93, 0xec, 0xd1, 0xa4, 0xfa, 0xb4,
  0xf0, 0x72, 0x5a, 0x64, 0x8a, 0x5a, 0x50, 0x87, 0x16, 0xa2, 0x5b, 0x0b,
  0xd9, 0xab, 0x85, 0xea, 0xd7, 0xb5, 0xc2, 0xed, 0x16, 0x55, 0xe9, 0x00,
  0xf3, 0xdd, 0xa9, 0xb5, 0x98, 0x68, 0x66, 0x39, 0x52, 0xeb, 0xb1, 0x99,
  0x27, 0x8c, 0x2e, 0x25, 0x1f, 0x12, 0xab, 0x61, 0xbd, 0x21, 0xda, 0xf3,
  0x81, 0x2c, 0x7a, 0x81, 0x0a, 0xfd, 0x80, 0x72, 0xd9, 0x80, 0xcf, 0x91,
  0x8f, 0xce, 0xa1, 0x44, 0xab, 0x8d, 0x0f, 0x68, 0x4a, 0xe6, 0x02, 0x50,
  0x41, 0x00, 0x18, 0x13, 0xc2, 0xdc, 0x18, 0x46, 0x10, 0x1c, 0x22, 0xfb,
  0x78, 0xcc, 0x4c, 0xd1, 0x3c, 0x00, 0xff, 0xcb, 0x75, 0xec, 0xdb, 0xbb,
  0xca, 0x30, 0x2b, 0xc7, 0xf2, 0xf9, 0xb6, 0x37, 0xc8, 0xad, 0xc9, 0xb1,
  0x78, 0xf6, 0x14, 0xfe, 0xe3, 0xfc, 0xe8, 0x64, 0xe9, 0xef, 0xc4, 0xa7,
  0xa1, 0xc5, 0xd1, 0xe9, 0x9d, 0xef, 0xbf, 0x66, 0xef, 0x01, 0x7e, 0x33,
  0x86, 0x43, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50,
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10,
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x20, 0x02, 0x08, 0x02, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x78, 0x01, 0x63,
  0x64, 0x60, 0x60, 0x60, 0x02, 0x62, 0x09, 0x20, 0x06, 0xb1, 0x23, 0x80,
  0x58, 0x16, 0x88, 0x41, 0x6c, 0x10, 0x30, 0x00, 0x11, 0x40, 0xc0, 0x0a,
  0xc4, 0x36, 0x40, 0x0c, 0x03, 0x02, 0x40, 0x0c, 0x52, 0xe3, 0x02, 0xc4,
  0x20, 0x00, 0x53, 0x0f, 0x02, 0xff, 0x81, 0x40, 0x14, 0x48, 0x83, 0xc4,
  0x60, 0x18, 0x06, 0x38, 0x40, 0x04, 0x16, 0xc0, 0xca, 0xc0, 0xc0, 0x00,
  0x00, 0x6d, 0x5d, 0x05, 0x7b, 0x78, 0x62, 0x6f, 0x70, 0x02, 0x00, 0x00,
  0x00, 0x78, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x33, 0x79, 0x02,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00
};