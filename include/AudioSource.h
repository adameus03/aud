#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <string>

#include <GuidDef.h>
#include <Objbase.h>
#include <guiddef.h>

#include <iostream>
#include <comdef.h> // for _com_error
/* Ole32.dll for COM */
#include <combaseapi.h>  // For CoCreateInstance
#include <mmdeviceapi.h>
#include <audioclient.h>

class AudioSource
{
    public:
        AudioSource();
        virtual ~AudioSource();
        HRESULT SetFormat(WAVEFORMATEX* pwfx);
        HRESULT LoadData(UINT32 numFramesAvailable, BYTE* pData, DWORD* pFlags);
        void SetInputStreamBuf(std::streambuf* pInputStreamBuf);

    protected:

    private:
        WAVEFORMATEX* pwfx = NULL;
        UINT32 current_frame_index = 0;
        std::streambuf* pInputStreamBuf = NULL;
};

#endif // AUDIOSOURCE_H
