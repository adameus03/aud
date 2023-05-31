#include "AudioSource.h"

AudioSource::AudioSource()
{
    //ctor
}

AudioSource::~AudioSource()
{
    //dtor
}

HRESULT AudioSource::SetFormat(WAVEFORMATEX* pwfx){
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
    return S_OK;
}
HRESULT AudioSource::LoadData(UINT32 numFramesAvailable, BYTE* pData, DWORD* pFlags){//bufferFrameCount ===> numFramesAvailable
    if(this->pInputStreamBuf == NULL) return 1;

    std::streamsize inStreamAvailableBytesNumber = this->pInputStreamBuf->in_avail();
    UINT32 inStreamAvailableFramesNumber = inStreamAvailableBytesNumber / this->pwfx->nBlockAlign;
    if(inStreamAvailableFramesNumber){
        *pFlags = 0;

        if(0 && (inStreamAvailableFramesNumber < numFramesAvailable)){
            memset(pData, 0, numFramesAvailable * this->pwfx->nBlockAlign);
            this->pInputStreamBuf->sgetn((char*)pData, inStreamAvailableFramesNumber);
        }
        else {
            this->pInputStreamBuf->sgetn((char*)pData, numFramesAvailable * this->pwfx->nBlockAlign);
        }

    }
    else {
        *pFlags = AUDCLNT_BUFFERFLAGS_SILENT;
    }

    return S_OK;
}

void AudioSource::SetInputStreamBuf(std::streambuf* pInputStreamBuf){
    this->pInputStreamBuf = pInputStreamBuf;
}
