#pragma once
/**/
#ifndef _IRR_KLANG_ALREADY_LINKED_
#define _IRR_KLANG_ALREADY_LINKED_
#include <irr/irrKlang.h>
#endif
/**/


class ESound{
public:
	static void irrKlang_initiate_sound_engine();

	static irrklang::ISoundEngine* engine;
	static irrklang::ISoundSource* shootSound;
};