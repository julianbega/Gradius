#include "Sounds.h"
#include "Global/Global.h"

namespace gamesystem {

	static bool noVolume = false;
	static float maxVolumeLevel = 1.0f;


	void initializeMusic()
	{
		music = LoadMusicStream("../../Resources/Music.ogg");
		//shoot = LoadSound("../Resources/Shoot.wav");
		PlayMusicStream(music);
	}

	void updateMusic()
	{
		if (noVolume == false)
			UpdateMusicStream(music);

		if (IsKeyPressed(KEY_M))
		{
			if (noVolume == true)
			{
				SetMasterVolume(maxVolumeLevel);
				noVolume = false;
			}
			else if (noVolume == false)
			{
				SetMasterVolume(0.0f);
				noVolume = true;
			}

		}
	}
}