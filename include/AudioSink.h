#ifndef AUDIOSINK_H
#define AUDIOSINK_H

#include <iostream> //verbose + streambuf
#include <string>
#include <cmath> //ceil

#include <GuidDef.h>
#include <Objbase.h>
#include <guiddef.h>

#include <comdef.h> // for _com_error
/* Ole32.dll for COM */
#include <combaseapi.h>  // For CoCreateInstance
#include <mmdeviceapi.h>
#include <audioclient.h>


class AudioSink
{
    public:
        AudioSink(UINT32 duration_ms);
        virtual ~AudioSink();
        HRESULT SetFormat(WAVEFORMATEX* pwfx);
        HRESULT CopyData(BYTE* pData, UINT32 numFramesAvailable, BOOL* pbDone);
        void SetOutputStreamBuf(std::streambuf* pOutputStreamBuf);

    protected:

    private:
        WAVEFORMATEX* pwfx = NULL;
        UINT32 duration_ms = 0;
        UINT32 num_remaining_frames = 0;
        std::streambuf* pOutputStreamBuf = NULL;
};









#endif // AUDIOSINK_H
