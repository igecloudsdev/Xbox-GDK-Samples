//--------------------------------------------------------------------------------------
// StatusBatch.cpp
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "pch.h"
#include "StatusBatch.h"

#define VALIDATE_READS

bool StatusBatch::RunSample(const std::wstring& fileName, uint64_t dataFileSize)
{
    OpenFile(fileName);

    // Helper code that creates a set of random reads and matching destination buffers
    GenerateRandomReadLocationsAndDestinationBuffers(dataFileSize, c_dataBatches * c_readsPerBatch);

    // Create the status array with a single slot for each batch that is being enqueued
    DX::ThrowIfFailed(s_factory->CreateStatusArray(c_dataBatches, u8"StatusBatch Status Array", __uuidof(DStorageStatusArrayCrossPlatform), (void**)(m_statusEntries.ReleaseAndGetAddressOf())));

    // enqueue all the reads using multiple batches
    uint32_t curBuffer = 0;
    for (uint32_t curBatch = 0; curBatch < c_dataBatches; ++curBatch)
    {
        for (uint32_t curRead = 0; curRead < c_readsPerBatch; curRead++, ++curBuffer)
        {
            DStorageRequestCrossPlatform request = {};
            request.SetupUncompressedRead(s_files[fileName].Get(), m_destinationBuffers[curBuffer].get(), m_readLocations[curBuffer], m_readSizes[curBuffer]);
            s_queues[0]->EnqueueRequest(&request);
        }

        // Enqueue one status notification per batch as opposed to per read requeust
        s_queues[0]->EnqueueStatus(m_statusEntries.Get(), curBatch);
    }

    // Submit the entire queue to the hardware
    s_queues[0]->Submit();

    // Wait for the first batch to complete, signaled through slot 0 in the status array
    while (!m_statusEntries->IsComplete(0))
    {
        Sleep(1);
    }
    // At this point we can only say all reads in the first batch have completed

    // wait for the last batch to complete
    // signaled through the last slot in the status array
    while (!m_statusEntries->IsComplete(c_dataBatches - 1))
    {
        Sleep(1);
    }
    // At this point it's guaranteed all the batches have finished
    // Notification is always in FIFO order

    // check the contents of the data reads from the file to make sure the correct contents were loaded
#ifdef VALIDATE_READS
    curBuffer = 0;
    for (uint32_t curBatch = 0; curBatch < c_dataBatches; ++curBatch, ++curBuffer)
    {
        for (uint32_t curRead = 0; curRead < c_readsPerBatch; curRead++)
        {
            uint32_t startValue = static_cast<uint32_t> (m_readLocations[curBuffer] / sizeof(uint32_t));
            uint32_t* temp = (uint32_t*)m_destinationBuffers[curBuffer].get();
            uint32_t numberEntries = m_readSizes[curBuffer] / sizeof(uint32_t);
            for (uint32_t location = 0; location < numberEntries; location++)
            {
                if (temp[location] != startValue)
                    DebugBreak();
                assert(temp[location] == startValue);
                startValue++;
            }
        }
    }
#endif

    return true;
}
