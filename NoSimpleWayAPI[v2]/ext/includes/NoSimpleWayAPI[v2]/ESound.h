#pragma once
/**/
#ifndef _IRR_KLANG_ALREADY_LINKED_
#define _IRR_KLANG_ALREADY_LINKED_
#include <irr/irrKlang.h>
#endif
/**/

//#ifndef _E_TEXT_CORE_ALREADY_LINKED_
///**/#define _E_TEXT_CORE_ALREADY_LINKED_
///**/#include "ETextCore.h"
//#endif


/**/#include "ETextCore.h"



class ESound{
public:
	static void irrKlang_initiate_sound_engine();

	static irrklang::ISoundEngine* engine;
	static irrklang::ISoundSource* shootSound;

	
};

class ENamedSound
{
public:
	ELocalisationText			localisation_text;
	irrklang::ISoundSource*		sound;
	std::string					full_path;

	ENamedSound(std::string _path);
};