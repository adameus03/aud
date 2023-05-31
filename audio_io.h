#ifndef AUDIO_IO_H_INCLUDED
#define AUDIO_IO_H_INCLUDED

#include <string>

#include <GuidDef.h>
#include <Objbase.h>
#include <guiddef.h>

#include <comdef.h> // for _com_error
/* Ole32.dll for COM */
#include <combaseapi.h>  // For CoCreateInstance
#include <mmdeviceapi.h>
#include <audioclient.h>

#include "AudioSink.h"
#include "AudioSource.h"

HRESULT InitializeCOM();

HRESULT RecordAudioStream(AudioSink *pMySink);

HRESULT PlayAudioStream(AudioSource *pMySource);


#endif // AUDIO_IO_H_INCLUDED
