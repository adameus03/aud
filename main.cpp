#include <iostream>
#include <cstring>
#include <cstdlib> //strtol
#include "audio_io.h"
#include "RawAudioConverter.h"

enum AUD_MODE {
    RECORD,
    RENDER
};

AUD_MODE mode;
char* fileName = NULL;
UINT32 duration = 0;

void usage(char* argv0){
    std::cout << "Usage: " << std::endl;
    std::cout << "    " << argv0 << " record <file_name> <duration_ms>" << std::endl;
    std::cout << "    " << argv0 << " render <file_name>" << std::endl;
}

unsigned char verify_args(int argc, char** argv){
    if(!(argc == 3 || argc==4)){
        std::cerr << "Invalid #ARGS!" << std::endl;
        if(!argc) usage((char*)"aud");
        else usage(argv[0]);
        return 0x1;
    }
    else if(!strcmp("record", argv[1])){
        if(argc != 4){
            std::cerr << "\"aud record\" expects <file_name> and <duration_ms> parameters" << std::endl;
            return 0x1;
        }
        else {

            char* endp;
            INT32 _duration = strtol(argv[3], &endp, 10);
            if(*endp == '\0'){
                if(_duration < 0){
                    std::cerr << "duration_ms is expected to be positive!" << std::endl;
                    return 0x1;
                }
                else {
                    duration = _duration;
                    mode = AUD_MODE::RECORD;
                    return 0x0;
                }
            }
            else {
                std::cerr << "duration_ms is expected to be an integer!" << std::endl;
                return 0x1;
            }
        }
    }
    else if(!strcmp("render", argv[1])){
        if(argc != 3){
            std::cerr << "\"aud render\" expects only the <file_name> argument" << std::endl;
            return 0x1;
        }
        else {
            mode = AUD_MODE::RENDER;
            return 0x0;
        }
    }
    else {
        std::cerr << "First argument can be either \"record\" or \"render\"." << std::endl;
        usage(argv[0]);
        return 0x1;
    }
}

HRESULT record(AudioConverter* pAudioConverter){
    AudioSink audioSink(duration);
    audioSink.SetOutputStreamBuf(pAudioConverter->GetStreamBuf());
    if(FAILED(RecordAudioStream(&audioSink))) return 1;
    if(FAILED(pAudioConverter->ConvertFromRaw())) return 1;
    if(FAILED(pAudioConverter->EndConversion())){
        std::cerr << "Unknown error occured during the recorder dump" << std::endl;
        return 1;
    }
    return 0;
}

HRESULT render(AudioConverter* pAudioConverter){
    AudioSource audioSource;
    audioSource.SetInputStreamBuf(pAudioConverter->GetStreamBuf());
    if(FAILED(PlayAudioStream(&audioSource))) return 1;
    if(FAILED(pAudioConverter->ConvertToRaw())) return 1;
    if(FAILED(pAudioConverter->EndConversion())) return 1;

    return 0;
}

int main(int argc, char** argv)
{
    if(verify_args(argc, argv)) return 0;
    std::cout << "aud - command line raw audio recorder/renderer" << std::endl;

    HRESULT hr;
    RawAudioConverter rawAudioConverter;
    AudioConverter* audioConverter = &rawAudioConverter;

    hr = mode==AUD_MODE::RENDER ? audioConverter->CreateReadStreamBuf(argv[2]) : audioConverter->CreateWriteStreamBuf(argv[2]);
    if(FAILED(hr)){
        std::cout << "Failed to open file: \"" << argv[2] << "\"" << std::endl;
    }

    hr = InitializeCOM();
    if(hr == S_OK){
        if(mode == AUD_MODE::RECORD){
            hr = record(audioConverter);
        }
        else{
            hr = render(audioConverter);
        }
    }

    if(SUCCEEDED(hr)){
        std::cout << "Task completed successfully" << std::endl;
    }
    else {
        std::cout << "Task exited abnormally" << std::endl;
    }

    ///////////////
    std::cout << "Exiting aud" << std::endl;
    return 0;
}
