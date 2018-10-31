
#include "stdafx.h"
#include "Sound.h"
#include "WaveFile.h"

#pragma comment(lib, "Dsound.lib")

const char *SamplesFiles[] = {
	"Data\\Ball2Ball.wav",   // bila z bila
	"Data\\Ball2Band.wav",   // bila z banda
	"Data\\Ball2Hole.wav",   // bila z dolkiem
	"Data\\Stick2Ball.wav"   // kij z bila
};

const int BuffersCount[SAMPLES_MAX] = {
	10,  // bila z bila
	6,   // bila z banda
	6,   // bila z dolkiem
	1    // kij z bila
};

CSound Sound;

CSound::CSound(void)
{
	CoInitialize(NULL);
}

CSound::~CSound(void)
{
	CoUninitialize();
}

int CSound::Initialize(HWND hWnd)
{
	// utworz instnacje DirectSound
	if (DirectSoundCreate(NULL, &DirectSound, NULL) != DS_OK)
		return 0;

	// ustaw priorytet
	if (DirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY) != DS_OK)
		return 0;

	for (int i = 0; i < SAMPLES_MAX; i++)
	{
		UINT cbSize = 0;
		DWORD pcSamples = 0;
		PWAVEFORMATEX pWaveFormat = NULL;
		BYTE *pData = NULL;

		if (!WaveLoadFile(SamplesFiles[i], &cbSize, &pcSamples, &pWaveFormat, &pData))
		{
			DSBUFFERDESC dsBuffDesc;

			pWaveFormat->cbSize = sizeof(WAVEFORMATEX);
			dsBuffDesc.dwSize = sizeof(DSBUFFERDESC);
			dsBuffDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC;
			dsBuffDesc.dwBufferBytes = cbSize;
			dsBuffDesc.dwReserved = 0;
			dsBuffDesc.lpwfxFormat = pWaveFormat;
			dsBuffDesc.guid3DAlgorithm = GUID_NULL;

			Samples[i].Count = BuffersCount[i];
			Samples[i].Items = new IDirectSoundBuffer* [Samples[i].Count];

			if (DirectSound->CreateSoundBuffer(&dsBuffDesc, &Samples[i].Items[0], NULL) != DS_OK)
				return 0;
			
			LPVOID Buffer;
			DWORD dwBytes;

			Samples[i].Items[0]->Lock(0, 0, &Buffer, &dwBytes, NULL, NULL, DSBLOCK_ENTIREBUFFER);
			memcpy(Buffer, pData, dwBytes);
			Samples[i].Items[0]->Unlock(Buffer, dwBytes, NULL, 0);

			for (int j = 1; j < Samples[i].Count; j++)
				if (DirectSound->DuplicateSoundBuffer(Samples[i].Items[0], &Samples[i].Items[j]) != DS_OK)
					return 0;

			GlobalFree(pData);
			GlobalFree(pWaveFormat);
		}
	}

	return 1;
}

void CSound::Finalize(void)
{
	for (int i = 0; i < SAMPLES_MAX; i++)
	{
		for (int j = 0; j < Samples[i].Count; j++)
			Samples[i].Items[j]->Release();

		delete Samples[i].Items;
	}

	DirectSound->Release();
}

void CSound::Play(int iSample, long Volume)
{
	if ((iSample > -1) && (iSample < SAMPLES_MAX))
	{
		for (int i = 0; i < Samples[iSample].Count; i++)
		{
			DWORD dwStatus;

			Samples[iSample].Items[i]->GetStatus(&dwStatus);

			if (dwStatus & DSBSTATUS_BUFFERLOST)
			{
				Samples[iSample].Items[i]->Restore();
			}

			if (!(dwStatus & DSBSTATUS_PLAYING))
			{
				Samples[iSample].Items[i]->SetVolume(Volume);
				Samples[iSample].Items[i]->SetCurrentPosition(0);

				if (Samples[iSample].Items[i]->Play(0, 0, 0) == DSERR_BUFFERLOST)
					Samples[iSample].Items[i]->Restore();
			}
		}
	}
}
