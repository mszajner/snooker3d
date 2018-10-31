
#pragma once

#include <windows.h>
#include <mmsystem.h>
#include "DSound.h"

#define SAMPLES_BALL2BALL   0
#define SAMPLES_BALL2BAND   1
#define SAMPLES_BALL2HOLE   2
#define SAMPLES_STICK2BALL  3
#define SAMPLES_MAX         4

#define BUFFER_MAX         20

class CSound {

	private:
		IDirectSound *DirectSound;
		struct {
			int Count;
			IDirectSoundBuffer **Items;
		} Samples[SAMPLES_MAX];

	public:
		CSound(void);
		~CSound(void);

	public:
		int Initialize(HWND hWnd);
		void Finalize(void);

	public:
		void Play(int iSample, long Volume = (DSBVOLUME_MIN + DSBVOLUME_MAX) / 2);

};

extern CSound Sound;
