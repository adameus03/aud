#ifndef RAWAUDIOCONVERTER_H
#define RAWAUDIOCONVERTER_H

#include <AudioConverter.h>


class RawAudioConverter : public AudioConverter
{
    public:
        RawAudioConverter();
        virtual ~RawAudioConverter();
        HRESULT ConvertToRaw();
        HRESULT ConvertFromRaw();

    protected:

    private:
};

#endif // RAWAUDIOCONVERTER_H
