#ifndef AUDIOCONVERTER_H
#define AUDIOCONVERTER_H

#include <iostream> //streambuf
#include <fstream> //ofstream
#include <combaseapi.h> //hresult

class AudioConverter
{
    public:
        AudioConverter();
        virtual ~AudioConverter();
        HRESULT CreateReadStreamBuf(const char* fileName);
        HRESULT CreateWriteStreamBuf(const char* fileName);
        std::streambuf* GetStreamBuf();
        HRESULT EndConversion();
        virtual HRESULT ConvertToRaw(){ std::cout << "VIRT" << std::endl; return 1; }
        virtual HRESULT ConvertFromRaw(){ std::cout << "VIRT" << std::endl; return 1; }

    protected:
        std::streambuf* pStreamBuf = NULL;
        //std::ofstream* pFileWriteStream = NULL;
        //std::ifstream* pFileReadStream = NULL;
        std::fstream* pFileStream = NULL;

    private:

};

#endif // AUDIOCONVERTER_H
