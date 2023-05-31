#include "RawAudioConverter.h"
#include <random>
#include <ctime>

RawAudioConverter::RawAudioConverter()
{
    srand(time(NULL));
    //ctor
}

RawAudioConverter::~RawAudioConverter()
{
    //dtor
}

HRESULT RawAudioConverter::ConvertToRaw(){
    /*
        As it is already a *raw* audio converter - do nothing
    */
    return S_OK;
}

HRESULT RawAudioConverter::ConvertFromRaw(){
    /*
        Again, this is a *raw* audio converter - do nothing
    */
    std::cout << "CONVERT FROM RAW" << std::endl;
    //this->pFileStream->seekp(0);
    //this->pStreamBuf = this->pFileStream->rdbuf();

    this->pStreamBuf->pubseekpos(0, this->pFileStream->in);

    size_t n = this->pStreamBuf->in_avail();
    unsigned char* buffer = new unsigned char[n];
    this->pStreamBuf->sgetn((char*)buffer, n);
    for(size_t i=0; i<n; i++){
        buffer[i] = (i % 480 < 240) ? buffer[i] : 0x0;
        //std::cout << buffer[i];
    }
    //this->pFileStream->truncate
    //this->pFileStream->seekp(0);
    //this->pStreamBuf = this->pFileStream->rdbuf();
    //this->pStreamBuf->pubseekpos(0, this->pFileStream->out);
    this->pStreamBuf->pubseekpos(0, std::ios_base::out);
    this->pStreamBuf->sputn((char*)buffer, n);
    delete[] buffer;
    return S_OK;
}
