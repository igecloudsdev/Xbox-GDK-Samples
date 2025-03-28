//--------------------------------------------------------------------------------------
// SimpleFrontPanel.h
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <XFrontPanelDisplay.h>


// A basic sample implementation that creates a D3D12 device and
// provides a render loop.
class Sample
{
public:

    Sample() noexcept(false);

    // Initialization and management
    void Initialize(HWND window);

    // Basic render loop
    void Tick();

    // Messages
    void OnSuspending();
    void OnResuming();

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Fill the front panel buffer with a checkerboard pattern
    void CheckerboardFillPanelBuffer();

    // Fill the front panel buffer with a gradient pattern
    void GradientFillPanelBuffer();

    // Reduce the brightness of the panel buffer pixels
    void DimPanelBuffer();

    // Increase the brightness of the panel buffer pixels
    void BrightenPanelBuffer();

    // Toggle the light associated with the provided button
    void ToggleButtonLight(XFrontPanelButton whichButton);

    // Conditionally present the front panel when there are dirty pixels
    void PresentFrontPanel();

    // Save the contents of the front panel buffer as a .dds surface
    void CaptureFrontPanelScreen(const wchar_t *fileName);

    // Device resources.
    std::unique_ptr<DX::DeviceResources>             m_deviceResources;

    // Rendering loop timer.
    uint64_t                                         m_frame;
    DX::StepTimer                                    m_timer;

    // Input device.
    std::unique_ptr<DirectX::GamePad>                m_gamePad;
    DirectX::GamePad::ButtonStateTracker             m_gamePadButtons;

    // DirectXTK objects.
    std::unique_ptr<DirectX::GraphicsMemory>         m_graphicsMemory;
    std::unique_ptr<DirectX::DescriptorHeap>         m_resourceDescriptors;
    std::unique_ptr<DirectX::SpriteBatch>            m_batch;
    Microsoft::WRL::ComPtr<ID3D12Resource>           m_background;

    enum Descriptors
    {
        Background,
        Count
    };

    // Front panel information
    uint32_t                                         m_screenWidth;
    uint32_t                                         m_screenHeight;

    // Tracks the buttons states from the previous update in order to facilitate "button held" events
    XFrontPanelButton                                m_rememberedButtons; 
    std::unique_ptr<uint8_t>                         m_panelBuffer;

    // The m_dirty member will be set whenever there are changes to front panel pixels.
    // This way we will only call IXboxFrontPanelControl::PresentBuffer() when there
    // are changes to pixels. Note that it is only necessary to present to the front
    // panel when there are changes to the pixels.
    bool                                             m_dirty;
    bool                                             m_checkerboard;

    // Remember availability of the Front Panel
    bool                                             m_available;
};
