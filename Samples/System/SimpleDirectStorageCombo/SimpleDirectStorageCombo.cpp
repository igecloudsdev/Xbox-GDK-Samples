//--------------------------------------------------------------------------------------
// SimpleDirectStorage.cpp
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "pch.h"
#include "zlib/include/zlib.h"
#include "SimpleDirectStorageCombo.h"
#include "SampleImplementations/SimpleLoad.h"
#include "SampleImplementations/StatusBatch.h"
#include "SampleImplementations/FenceBatch.h"
#include "SampleImplementations/MultipleQueues.h"
#include "SampleImplementations/Cancellation.h"
#include "SampleImplementations/RecommendedPattern.h"
#include "SampleImplementations/XBoxZLibDecompression.h"
#include "SampleImplementations/XBoxInMemoryZLibDecompression.h"
#include "SampleImplementations/DesktopCPUDecompression.h"
#include "SampleImplementations/DesktopGPUDecompression.h"
#if (_GRDK_VER >= 0x585D073C) || defined(_GAMING_DESKTOP) /* GDK Edition 221000 */
#include "SampleImplementations/CompletionEvent.h"
#endif

#if defined(_GAMING_DESKTOP) || defined(_GAMING_XBOX)
#include "xsystem.h"
#endif

#include "ATGColors.h"
#include "FindMedia.h"

extern void ExitSample() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

#ifdef _GAMING_XBOX
const std::wstring Sample::c_dataFileName(L"d:\\DSTORAGEPreviewDataFile.dat");
const std::wstring Sample::c_zipDataFileName(L"d:\\DSTORAGEZipDataFile.zip");
#elif defined (_GAMING_DESKTOP)
std::wstring GetGamingDesktopRealFileName(const std::wstring& filename)
{
    wchar_t* folderPath;
    if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_NO_PACKAGE_REDIRECTION, nullptr, &folderPath) == S_OK)
    {
        // Path information
        std::wstring path(folderPath);
        path += L"\\Microsoft\\ATGSamples\\";

        if (!CreateDirectoryW(path.c_str(), nullptr))
        {
            if (GetLastError() != ERROR_ALREADY_EXISTS)
                return L"";
        }
        path += filename;
        return path;
    }
    return L"";
}

const std::wstring Sample::c_dataFileName(GetGamingDesktopRealFileName(L"DSTORAGEPreviewDataFile.dat"));
const std::wstring Sample::c_zipDataFileName(GetGamingDesktopRealFileName(L"DSTORAGEZipDataFile.zip"));
const std::wstring Sample::c_gDeflateDataFileName(GetGamingDesktopRealFileName(L"DSTORAGEGDeflateDataFile.gdeflate"));
#else
const std::wstring Sample::c_dataFileName(L"DSTORAGEPreviewDataFile.dat");
const std::wstring Sample::c_zipDataFileName(L"DSTORAGEZipDataFile.zip");
#endif

// All the actual Sample code runs in this function which is on it's own thread to avoid interference with rendering
void Sample::DSTORAGESampleFunc()
{
    m_creatingDataFile = e_pending;
    CreateDataFiles();
    m_creatingDataFile = e_success;

    SetThreadAffinityMask(GetCurrentThread(), 0x04);

    ImplementationBase::SetupDirectStorageObjects();

    try
    {
        SimpleLoad simpleLoadSample;
        m_simpleLoadStatus = simpleLoadSample.RunSample(c_dataFileName) ? e_success : e_failed;
    }
    catch (...)
    {
        m_simpleLoadStatus = e_exception;
    }

    try
    {
        StatusBatch statusBatchSample;
        m_statusBatchStatus = statusBatchSample.RunSample(c_dataFileName, c_dataFileSize) ? e_success : e_failed;
    }
    catch (...)
    {
        m_statusBatchStatus = e_exception;
    }

    try
    {
        FenceBatch fenceBatchSample;
        m_fenceBatchStatus = fenceBatchSample.RunSample(c_dataFileName, m_deviceResources->GetD3DDevice(), c_dataFileSize) ? e_success : e_failed;
    }
    catch (...)
    {
        m_fenceBatchStatus = e_exception;
    }

    try
    {
#if ((_GRDK_VER >= 0x585D073C)&&(defined _GAMING_XBOX_SCARLETT)) || defined(_GAMING_DESKTOP) /* GDK Edition 221000 */
        CompletionEvent completionEventSample;
        m_completionEventStatus = completionEventSample.RunSample(c_dataFileName, c_dataFileSize) ? e_success : e_failed;
#else
        m_completionEventStatus = e_notImplemented;
#endif
    }
    catch (...)
    {
        m_completionEventStatus = e_exception;
    }

    try
    {
#ifdef _GAMING_XBOX
        XBoxZLibDecompression decompressionSample;
        m_xBoxDecompressionStatus = decompressionSample.RunSample(c_zipDataFileName, c_zipFileSize) ? e_success : e_failed;
#else
        m_xBoxDecompressionStatus = e_notImplemented;
#endif
    }
    catch (...)
    {
        m_xBoxDecompressionStatus = e_exception;
    }

    try
    {
#ifdef _GAMING_XBOX_SCARLETT
        XBoxInMemoryZLibDecompression decompressionSample;
        m_xBoxInMemoryDecompressionStatus = decompressionSample.RunSample() ? e_success : e_failed;
#else
        m_xBoxDecompressionStatus = e_notImplemented;
#endif
    }
    catch (...)
    {
        m_xBoxInMemoryDecompressionStatus = e_exception;
    }

    try
    {
#ifndef _GAMING_XBOX
        DesktopCPUDecompression decompressionSample;
        m_desktopCPUDecompressionStatus = decompressionSample.RunSample(c_zipDataFileName, c_zipFileSize) ? e_success : e_failed;
#else
        m_desktopCPUDecompressionStatus = e_notImplemented;
#endif
    }
    catch (...)
    {
        m_desktopCPUDecompressionStatus = e_exception;
    }

    try
    {
#ifndef _GAMING_XBOX
        DesktopGPUDecompression decompressionSample;
        m_desktopGPUDecompressionStatus = decompressionSample.RunSample(c_gDeflateDataFileName, m_deviceResources->GetD3DDevice()) ? e_success : e_failed;
#else
        m_desktopGPUDecompressionStatus = e_notImplemented;
#endif
    }
    catch (...)
    {
        m_desktopGPUDecompressionStatus = e_exception;
    }

    try
    {
        MultipleQueues mulitpleQueuesSample;
        m_multipleQueuesStatus = mulitpleQueuesSample.RunSample(c_dataFileName, c_dataFileSize) ? e_success : e_failed;
    }
    catch (...)
    {
        m_multipleQueuesStatus = e_exception;
    }

    try
    {
        Cancellation cancellationSample;
        m_cancellationStatus = cancellationSample.RunSample(c_dataFileName, c_dataFileSize) ? e_success : e_failed;
    }
    catch (...)
    {
        m_cancellationStatus = e_exception;
    }

    try
    {
        RecommendedPattern recommendedPatternSample;
        m_recommendedPatternStatus = recommendedPatternSample.RunSample(c_dataFileName, c_dataFileSize) ? e_success : e_failed;
    }
    catch (...)
    {
        m_recommendedPatternStatus = e_exception;
    }

    ImplementationBase::ShutdownDirectStorageObjects();
}

#ifndef _GAMING_XBOX
void Sample::CreateGDeflateDataFile()
{
    uint32_t* rootBuffer = static_cast<uint32_t*> (VirtualAlloc(nullptr, c_gDeflateFileSize, MEM_COMMIT, PAGE_READWRITE));
    for (uint32_t j = 0; j < c_gDeflateFileSize / sizeof(uint32_t); j++)
    {
        rootBuffer[j] = j;
    }
    uint8_t* srcData = reinterpret_cast<uint8_t*>(rootBuffer);

    using Chunk = std::vector<uint8_t>;

    std::vector<Chunk> chunks;
    chunks.resize(c_gDeflateNumChunks);

    std::atomic<size_t> nextChunk(0);

    std::vector<std::thread> threads;
    uint32_t numThreads = std::thread::hardware_concurrency();
    threads.reserve(numThreads);

    for (uint32_t i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(
            [&]()
            {
                // Each thread needs its own instance of the codec
                Microsoft::WRL::ComPtr <IDStorageCompressionCodec> codec;
                DX::ThrowIfFailed(DStorageCreateCompressionCodec(DSTORAGE_COMPRESSION_FORMAT_GDEFLATE, 1, __uuidof(IDStorageCompressionCodec), (void**)(codec.ReleaseAndGetAddressOf())));

                while (true)
                {
                    size_t chunkIndex = nextChunk.fetch_add(1);
                    if (chunkIndex >= c_gDeflateNumChunks)
                        return;

                    size_t thisChunkOffset = chunkIndex * c_gDeflateChunkSize;
                    size_t thisChunkSize = std::min<size_t>(c_gDeflateFileSize - thisChunkOffset, c_gDeflateChunkSize);

                    Chunk chunk(codec->CompressBufferBound(thisChunkSize));

                    uint8_t* uncompressedStart = srcData + thisChunkOffset;

                    size_t compressedSize = 0;
                    DX::ThrowIfFailed(codec->CompressBuffer(uncompressedStart, thisChunkSize, DSTORAGE_COMPRESSION_BEST_RATIO, chunk.data(), chunk.size(), &compressedSize));
                    chunk.resize(compressedSize);

                    chunks[chunkIndex] = std::move(chunk);
                }
            });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    CREATEFILE2_EXTENDED_PARAMETERS params = {};

    params.dwSize = sizeof(params);
    params.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
    params.dwFileFlags = 0;
    HANDLE dataFile = CreateFile2(c_gDeflateDataFileName.c_str(), GENERIC_WRITE, 0, CREATE_ALWAYS, &params);
    if (dataFile == INVALID_HANDLE_VALUE)
        DX::ThrowIfFailed(static_cast<HRESULT> (GetLastError()));

    DWORD actualWrite;
    uint64_t toWrite(c_gDeflateNumChunks);
    WriteFile(dataFile, &toWrite, 8, &actualWrite, nullptr);
    toWrite = c_gDeflateChunkSize;
    WriteFile(dataFile, &toWrite, 8, &actualWrite, nullptr);

    uint64_t curChunkOffset(16 * c_gDeflateNumChunks);
    curChunkOffset += 16;
    for (uint32_t i = 0; i < c_gDeflateNumChunks; ++i)
    {
        uint64_t chunkSize = chunks[i].size();
        WriteFile(dataFile, &curChunkOffset, 8, &actualWrite, nullptr);
        WriteFile(dataFile, &chunkSize, 8, &actualWrite, nullptr);
        curChunkOffset += chunkSize;
    }

    for (uint32_t i = 0; i < c_gDeflateNumChunks; ++i)
    {
        uint32_t chunkSize = static_cast<uint32_t> (chunks[i].size());
        WriteFile(dataFile, chunks[i].data(), chunkSize, &actualWrite, nullptr);
    }

    VirtualFree(srcData, 0, MEM_RELEASE);
    CloseHandle(dataFile);
}
#endif

void Sample::CreateDataFiles()
{
    WIN32_FILE_ATTRIBUTE_DATA dataInfo;
    WIN32_FILE_ATTRIBUTE_DATA zipInfo;
    bool validDataInfo(false), validZipInfo(false), validGDeflateInfo(true);

    // If the file already exists and is the correct size then nothing needs to be done
    validDataInfo = GetFileAttributesExW(c_dataFileName.c_str(), GetFileExInfoStandard, &dataInfo);
    validZipInfo = GetFileAttributesExW(c_zipDataFileName.c_str(), GetFileExInfoStandard, &zipInfo);
#ifndef _GAMING_XBOX
    WIN32_FILE_ATTRIBUTE_DATA gDeflateInfo;
    validGDeflateInfo = GetFileAttributesExW(c_gDeflateDataFileName.c_str(), GetFileExInfoStandard, &gDeflateInfo);
#endif
    if (validDataInfo && validZipInfo && validGDeflateInfo)
    {
        uint64_t dataSize;
        dataSize = dataInfo.nFileSizeHigh;
        dataSize = (dataSize << 32ULL) + dataInfo.nFileSizeLow;

        // assume zip size is correct otherwise we'd have to unzip the file to determine its raw size
        if (dataSize == c_realDataFileSize)
            return;
    }

    // Create raw data file for sample
    {
        uint64_t numberDataBlocks = c_realDataFileSize / c_dataBlockSize;									// only write 1gig at a time

        uint32_t* buffer = static_cast<uint32_t*> (VirtualAlloc(nullptr, c_dataBlockSize, MEM_COMMIT, PAGE_READWRITE));
        {
            CREATEFILE2_EXTENDED_PARAMETERS params = {};

            params.dwSize = sizeof(params);
            params.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
            params.dwFileFlags = 0;
            HANDLE dataFile = CreateFile2(c_dataFileName.c_str(), GENERIC_WRITE, 0, CREATE_ALWAYS, &params);
            if (dataFile == INVALID_HANDLE_VALUE)
                DX::ThrowIfFailed(static_cast<HRESULT> (GetLastError()));

            uint32_t currentSeedValue = 0;

            for (uint64_t blockIndex = 0; blockIndex < numberDataBlocks; blockIndex++)
            {
                for (uint32_t j = 0; j < c_dataBlockSize / sizeof(uint32_t); j++)
                {
                    buffer[j] = currentSeedValue++;
                }
                DWORD actualWrite;
                WriteFile(dataFile, buffer, static_cast<DWORD>(c_dataBlockSize), &actualWrite, nullptr);
            }

            CloseHandle(dataFile);
        }
        VirtualFree(buffer, 0, MEM_RELEASE);
    }

    // Create zipped data file for testing
    {
        uint32_t* buffer = static_cast<uint32_t*> (VirtualAlloc(nullptr, c_zipFileSize, MEM_COMMIT, PAGE_READWRITE));
        for (uint32_t j = 0; j < c_zipFileSize / sizeof(uint32_t); j++)
        {
            buffer[j] = j;
        }

        uint64_t compressedSize = 0;
        z_stream strm = {};
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        int err = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
        if (err != Z_OK)
            return;

        uint64_t zipBufferSize = deflateBound(&strm, static_cast<uint32_t> (c_zipFileSize));
        void* destBuffer = VirtualAlloc(nullptr, zipBufferSize, MEM_COMMIT, PAGE_READWRITE);

        strm.avail_in = c_zipFileSize;
        strm.next_in = reinterpret_cast<Bytef*> (buffer);

        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        strm.avail_out = static_cast<uInt> (zipBufferSize);
        strm.next_out = static_cast<Bytef*> (destBuffer);
        err = deflate(&strm, Z_FINISH);    /* no bad return value */
        if (err == Z_STREAM_ERROR)
            throw std::runtime_error("Error in deflate on zipped file creation");
        assert(err != Z_STREAM_ERROR);  /* state not clobbered */
        if (strm.avail_in != 0)
            throw std::runtime_error("Failed to zip the entire stream in file creation");

        compressedSize = strm.total_out;
        (void)deflateEnd(&strm);

        CREATEFILE2_EXTENDED_PARAMETERS params = {};

        params.dwSize = sizeof(params);
        params.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
        params.dwFileFlags = 0;
        HANDLE dataFile = CreateFile2(c_zipDataFileName.c_str(), GENERIC_WRITE, 0, CREATE_ALWAYS, &params);
        if (dataFile == INVALID_HANDLE_VALUE)
            DX::ThrowIfFailed(static_cast<HRESULT> (GetLastError()));

        // NOTE: Compressed data must start on a 16 byte aligned offset, in this case it's at offset 0.
        DWORD actualWrite;
        WriteFile(dataFile, destBuffer, static_cast<DWORD>(compressedSize), &actualWrite, nullptr);
        VirtualFree(buffer, 0, MEM_RELEASE);
        VirtualFree(destBuffer, 0, MEM_RELEASE);
        CloseHandle(dataFile);
    }
}

Sample::Sample() noexcept(false) :
    m_dstorageSampleExecution(nullptr)
    , m_simpleLoadStatus(e_pending)
    , m_cancellationStatus(e_pending)
    , m_xBoxDecompressionStatus(e_pending)
    , m_xBoxInMemoryDecompressionStatus(e_pending)
    , m_desktopCPUDecompressionStatus(e_pending)
    , m_desktopGPUDecompressionStatus(e_pending)
    , m_multipleQueuesStatus(e_pending)
    , m_statusBatchStatus(e_pending)
    , m_fenceBatchStatus(e_pending)
    , m_completionEventStatus(e_pending)
    , m_recommendedPatternStatus(e_pending)
    , m_creatingDataFile(e_pending)
    , m_frame(0)
{
    // Renders only 2D, so no need for a depth buffer.
    m_deviceResources = std::make_unique<DX::DeviceResources>(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_UNKNOWN);
    m_deviceResources->SetClearColor(ATG::Colors::Background);
    m_deviceResources->RegisterDeviceNotify(this);
#if defined(_GAMING_XBOX_XBOXONE)
    m_xBoxInMemoryDecompressionStatus = e_notImplemented;
    m_desktopCPUDecompressionStatus = e_notImplemented;
    m_desktopGPUDecompressionStatus = e_notImplemented;
#elif defined (_GAMING_XBOX_SCARLETT)
    m_desktopCPUDecompressionStatus = e_notImplemented;
    m_desktopGPUDecompressionStatus = e_notImplemented;
#else
    m_xBoxDecompressionStatus = e_notImplemented;
    m_xBoxInMemoryDecompressionStatus = e_notImplemented;
#endif
#if (_GRDK_VER < 0x585D073C) && !defined(_GAMING_DESKTOP) /* GDK Edition 221000 */
    m_completionEventStatus = e_notImplemented;
#endif
}

Sample::~Sample()
{
    if (m_deviceResources)
    {
        m_deviceResources->WaitForGpu();
    }
}

// Initialize the Direct3D resources required to run.
void Sample::Initialize(HWND window, int width, int height)
{
    m_gamePad = std::make_unique<GamePad>();

    m_keyboard = std::make_unique<Keyboard>();

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();
}

#pragma region Frame Update
// Executes basic render loop.
void Sample::Tick()
{
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Frame %llu", m_frame);

#ifdef _GAMING_XBOX
    m_deviceResources->WaitForOrigin();
#endif

    m_timer.Tick([&]()
        {
            Update(m_timer);
        });

    Render();

    PIXEndEvent();
    m_frame++;
}

// Updates the world.
void Sample::Update(DX::StepTimer const& timer)
{
    if (timer.GetFrameCount() == 3)
    {
        m_dstorageSampleExecution = new std::thread(&Sample::DSTORAGESampleFunc, this);
    }

    auto pad = m_gamePad->GetState(0);
    if (pad.IsConnected())
    {
        m_gamePadButtons.Update(pad);

        if (pad.IsViewPressed())
        {
            ExitSample();
        }
    }
    else
    {
        m_gamePadButtons.Reset();
    }
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Sample::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    RECT safeRect = SimpleMath::Viewport::ComputeTitleSafeArea(1920, 1080);
    XMFLOAT2 pos(float(safeRect.left), float(safeRect.top));

    // Prepare the command list to render a new frame.
    m_deviceResources->Prepare();
    Clear();

    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Render");

    ID3D12DescriptorHeap* pHeaps[] = { m_resourceDescriptors->Heap() };
    commandList->SetDescriptorHeaps(_countof(pHeaps), pHeaps);

    m_spriteBatch->Begin(commandList);

    m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(Descriptors::Background), GetTextureSize(m_background.Get()), XMFLOAT2(0, 0));

    if (m_timer.GetFrameCount() > 3)
    {
#ifdef FORCE_DS_WIN32
#endif
        m_largeFont->DrawString(m_spriteBatch.get(), L"Simple DirectStorage Sample", pos);
#ifdef FORCE_DS_WIN32
        pos.y += m_largeFont->GetLineSpacing();
        pos.x += XMVectorGetX(m_regularFont->MeasureString(L"XXX"));
        m_largeFont->DrawString(m_spriteBatch.get(), L"Force Win32 DirectStorage", pos);
#endif
        pos.y += (m_largeFont->GetLineSpacing() * 2);
        pos.x += XMVectorGetX(m_regularFont->MeasureString(L"XXX"));

        DisplayStatusLine(m_creatingDataFile, L"Creating Data File", pos);
        DisplayStatusLine(m_simpleLoadStatus, L"Simple Load", pos);
        DisplayStatusLine(m_cancellationStatus, L"Cancellation", pos);
#ifdef _GAMING_XBOX_XBOXONE
        DisplayStatusLine(m_xBoxDecompressionStatus, L"Xbox Software Decompression", pos);
#else
        DisplayStatusLine(m_xBoxDecompressionStatus, L"Xbox Hardware Decompression", pos);
#endif
        DisplayStatusLine(m_xBoxInMemoryDecompressionStatus, L"Xbox In Memory Hardware Decompression", pos);
        DisplayStatusLine(m_desktopCPUDecompressionStatus, L"Desktop CPU Decompression", pos);
        DisplayStatusLine(m_desktopGPUDecompressionStatus, L"Desktop GPU Decompression", pos);
        DisplayStatusLine(m_multipleQueuesStatus, L"Multiple Queues", pos);
        DisplayStatusLine(m_statusBatchStatus, L"Status Batch", pos);
        DisplayStatusLine(m_fenceBatchStatus, L"Fence Batch", pos);
#if ((_GRDK_VER >= 0x585D073C)&&(defined _GAMING_XBOX_SCARLETT)) || defined(_GAMING_DESKTOP) /* GDK Edition 221000 */
        DisplayStatusLine(m_completionEventStatus, L"Completion Event", pos);
#elif defined(_GAMING_XBOX_XBOXONE)
        pos.y += m_regularFont->GetLineSpacing();
        m_regularFont->DrawString(m_spriteBatch.get(), L"Completion Event not supported on Xbox One", pos);
#else
        pos.y += m_regularFont->GetLineSpacing();
        m_regularFont->DrawString(m_spriteBatch.get(), L"Completion Event requires PC or at least the October 2022 GXDK", pos);
#endif

        DisplayStatusLine(m_recommendedPatternStatus, L"Recommended Pattern", pos);
    }

    m_spriteBatch->End();

    PIXEndEvent(commandList);

    // Show the new frame.
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
    m_deviceResources->Present();
    m_graphicsMemory->Commit(m_deviceResources->GetCommandQueue());
    PIXEndEvent();
}

void Sample::DisplayStatusLine(testStatus status, const wchar_t* sampleName, XMFLOAT2& pos)
{
    static const wchar_t* statusText[] = {
        L"Pending",
        L"Success",
        L"Failed",
        L"Exception",
        L"Not Implemented"
    };
    wchar_t buffer[128];

    if (status == e_notImplemented)
    {
#if defined(_GAMING_DESKTOP) || defined(_GAMING_XBOX)
        XSystemDeviceType info;
        info = XSystemGetDeviceType();
        switch (info)
        {
        case XSystemDeviceType::Pc:
            swprintf(buffer, 128, L"%s - Not supported on Desktop", sampleName);
            break;
        case XSystemDeviceType::XboxOne:
        case XSystemDeviceType::XboxOneS:
        case XSystemDeviceType::XboxOneX:
        case XSystemDeviceType::XboxOneXDevkit:
            swprintf(buffer, 128, L"%s - Not supported on Xbox One", sampleName);
            break;
        case XSystemDeviceType::XboxScarlettLockhart:
        case XSystemDeviceType::XboxScarlettAnaconda:
        case XSystemDeviceType::XboxScarlettDevkit:
            swprintf(buffer, 128, L"%s - %s", sampleName, statusText[status]);
            break;
        case XSystemDeviceType::Unknown:
        default:
            swprintf(buffer, 128, L"%s - Not supported on Unknown hardware", sampleName);
            break;
        }
#else
        swprintf(buffer, 128, L"%s - Not supported on PC hardware", sampleName);
#endif
    }
    else
    {
        swprintf(buffer, 128, L"%s - %s", sampleName, statusText[status]);
    }

    pos.y += m_regularFont->GetLineSpacing();
    m_regularFont->DrawString(m_spriteBatch.get(), buffer, pos);
    //pos.y += m_regularFont->GetLineSpacing();
}

// Helper method to clear the back buffers.
void Sample::Clear()
{
    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Clear");

    // Clear the views.
    auto rtvDescriptor = m_deviceResources->GetRenderTargetView();

    commandList->OMSetRenderTargets(1, &rtvDescriptor, FALSE, nullptr);
    commandList->ClearRenderTargetView(rtvDescriptor, ATG::Colors::Background, 0, nullptr);

    // Set the viewport and scissor rect.
    auto viewport = m_deviceResources->GetScreenViewport();
    auto scissorRect = m_deviceResources->GetScissorRect();
    commandList->RSSetViewports(1, &viewport);
    commandList->RSSetScissorRects(1, &scissorRect);

    PIXEndEvent(commandList);
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Sample::OnActivated()
{
}

void Sample::OnDeactivated()
{
}

void Sample::OnSuspending()
{
    m_deviceResources->Suspend();
}

void Sample::OnResuming()
{
    m_deviceResources->Resume();
    m_timer.ResetElapsedTime();
    m_gamePadButtons.Reset();
    m_keyboardButtons.Reset();
}

void Sample::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Sample::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();
}

// Properties
void Sample::GetDefaultSize(int& width, int& height) const noexcept
{
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Sample::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    wchar_t strFilePath[MAX_PATH] = {};

    m_graphicsMemory = std::make_unique<GraphicsMemory>(device);

    m_resourceDescriptors = std::make_unique<DescriptorHeap>(device, Descriptors::Count);

    ResourceUploadBatch resourceUpload(device);

    resourceUpload.Begin();

    DX::FindMediaFile(strFilePath, MAX_PATH, L"ATGSampleBackground.dds");
    DX::ThrowIfFailed(
        CreateDDSTextureFromFile(device, resourceUpload,
            strFilePath,
            m_background.ReleaseAndGetAddressOf()));

    CreateShaderResourceView(device, m_background.Get(), m_resourceDescriptors->GetCpuHandle(Descriptors::Background));

    RenderTargetState rtState(m_deviceResources->GetBackBufferFormat(), m_deviceResources->GetDepthBufferFormat());
    SpriteBatchPipelineStateDescription pd(rtState);

    m_spriteBatch = std::make_unique<SpriteBatch>(device, resourceUpload, pd);

    {
        DX::FindMediaFile(strFilePath, MAX_PATH, L"SegoeUI_18.spritefont");
        m_regularFont = std::make_unique<SpriteFont>(device, resourceUpload,
            strFilePath,
            m_resourceDescriptors->GetCpuHandle(Descriptors::RegularFont),
            m_resourceDescriptors->GetGpuHandle(Descriptors::RegularFont));
    }

    {
        DX::FindMediaFile(strFilePath, MAX_PATH, L"SegoeUI_24.spritefont");
        m_largeFont = std::make_unique<SpriteFont>(device, resourceUpload,
            strFilePath,
            m_resourceDescriptors->GetCpuHandle(Descriptors::LargeFont),
            m_resourceDescriptors->GetGpuHandle(Descriptors::LargeFont));
    }

    {
        DX::FindMediaFile(strFilePath, MAX_PATH, L"XboxOneController.spritefont");
        m_ctrlFont = std::make_unique<SpriteFont>(device, resourceUpload,
            strFilePath,
            m_resourceDescriptors->GetCpuHandle(Descriptors::CtrlFont),
            m_resourceDescriptors->GetGpuHandle(Descriptors::CtrlFont));
    }

    auto uploadResourcesFinished = resourceUpload.End(m_deviceResources->GetCommandQueue());

    uploadResourcesFinished.wait();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Sample::CreateWindowSizeDependentResources()
{
    auto viewport = m_deviceResources->GetScreenViewport();
    m_spriteBatch->SetViewport(viewport);
}

void Sample::OnDeviceLost()
{
    m_regularFont.reset();
    m_largeFont.reset();
    m_ctrlFont.reset();
    m_spriteBatch.reset();
    m_resourceDescriptors.reset();

    m_background.Reset();

    m_graphicsMemory.reset();
}

void Sample::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
