#include "AudioConverter.h"

AudioConverter::AudioConverter()
{
    //ctor
}

AudioConverter::~AudioConverter()
{
    //dtor
}

HRESULT AudioConverter::CreateWriteStreamBuf(const char* fileName){
    std::cout << "W R I T E" << std::endl;
    //this->pFileStream = new std::ofstream(fileName, std::ofstream::trunc|std::ofstream::binary);
    this->pFileStream = new std::fstream(fileName, std::ios::out|std::ios::trunc|std::ios::binary|std::ios::in);
    HRESULT hr = this->pFileStream->good();
    if(SUCCEEDED(hr)) this->pStreamBuf = this->pFileStream->rdbuf();
    return hr;
}

HRESULT AudioConverter::CreateReadStreamBuf(const char* fileName){
    std::cout << "R E A D" << std::endl;
    //this->pFileStream = new std::ifstream(fileName, std::ifstream::binary);
    this->pFileStream = new std::fstream(fileName, std::ios::in|std::ios::binary|std::ios::out);
    HRESULT hr = this->pFileStream->good();
    if(SUCCEEDED(hr)){
        this->pStreamBuf = this->pFileStream->rdbuf();
        this->pStreamBuf->pubseekpos(0, this->pFileStream->in);
    }
    return hr;
    //return S_OK;
}

std::streambuf* AudioConverter::GetStreamBuf(){
    return this->pStreamBuf;
}

HRESULT AudioConverter::EndConversion(){
    HRESULT hr = this->pFileStream->bad();
    this->pFileStream->close();
    delete this->pFileStream;
    return hr;
}
