/**/
#ifndef _ESOUND_ALREADY_LINKED_
#define _ESOUND_ALREADY_LINKED_
#include "ESound.h"
#endif
/**/

irrklang::ISoundEngine* ESound::engine;
irrklang::ISoundSource* ESound::shootSound;

void ESound::irrKlang_initiate_sound_engine()
{
	engine = irrklang::createIrrKlangDevice(irrklang::E_SOUND_OUTPUT_DRIVER::ESOD_WIN_MM);
	//shootSound = engine->addSoundSourceFromFile("data/sounds/flippy.wav");

	//engine->play2D(shootSound);
}

ENamedSound::ENamedSound(std::string _path)
{
	if (ESound::engine != nullptr) { sound = ESound::engine->addSoundSourceFromFile(_path.c_str()); }
	full_path = _path;
}

ENamedSound::~ENamedSound()
{
	//delete sound;
}
