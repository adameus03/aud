#include "AudioSink.h"
//#include <mmreg.h> //inspect

AudioSink::AudioSink(UINT32 duration_ms)
{
    //ctor
    this->duration_ms = duration_ms;
}

AudioSink::~AudioSink()
{
    //dtor
}

/*
    typedef struct tWAVEFORMATEX {
      WORD  wFormatTag;
      WORD  nChannels;
      DWORD nSamplesPerSec;
      DWORD nAvgBytesPerSec;
      WORD  nBlockAlign;
      WORD  wBitsPerSample;
      WORD  cbSize;
    } WAVEFORMATEX, *PWAVEFORMATEX, *NPWAVEFORMATEX, *LPWAVEFORMATEX;

*/

HRESULT AudioSink::SetFormat(WAVEFORMATEX* pwfx){
    //std::cout << std::hex;
    //WAVE_FORMAT_PCM
    std::cout << "//==========================" << std::endl;
    std::cout << "|| wFormatTag: " << pwfx->wFormatTag << std::endl;
    std::cout << "|| nChannels: " << pwfx->nChannels << std::endl;
    std::cout << "|| nSamplesPerSec: " << pwfx->nSamplesPerSec << std::endl;
    std::cout << "|| nAvgBytesPerSec: " << pwfx->nAvgBytesPerSec << std::endl;
    std::cout << "|| nBlockAlign: " << pwfx->nBlockAlign << std::endl;
    std::cout << "|| wBitsPerSample: " << pwfx->wBitsPerSample << std::endl;
    std::cout << "|| cbSize: " << pwfx->cbSize << std::endl;
    std::cout << "\\\\========================" << std::endl;
    //std::cout << std::dec;

    this->pwfx = pwfx;
    this->num_remaining_frames = ceil(0.001 * this->duration_ms * pwfx->nSamplesPerSec);
    return S_OK;
}

HRESULT AudioSink::CopyData(BYTE* pData, UINT32 numFramesAvailable, BOOL* pbDone){
    if(this->pOutputStreamBuf == NULL) return 1;

    UINT32 numFrames;
    if(numFramesAvailable > this->num_remaining_frames){
        numFrames = this->num_remaining_frames;
    }
    else{
        numFrames = numFramesAvailable;
    }

    UINT32 numBytes = numFrames * this->pwfx->nBlockAlign;

    this->pOutputStreamBuf->sputn((char*)pData, numBytes);

    this->num_remaining_frames -= numFrames;
    *pbDone = (WINBOOL)(!(this->num_remaining_frames));
    return S_OK;
}

void AudioSink::SetOutputStreamBuf(std::streambuf* pOutputStreamBuf){
    this->pOutputStreamBuf = pOutputStreamBuf;
}
