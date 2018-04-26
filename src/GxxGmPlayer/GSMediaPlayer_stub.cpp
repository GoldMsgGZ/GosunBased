#include "GSMediaPlayer_stub.h"

GSMediaPlayer_stub::GSMediaPlayer_stub()
: GSMediaPlayerLib_(NULL)
{

}

GSMediaPlayer_stub::~GSMediaPlayer_stub()
{
	if (GSMediaPlayerLib_)
	{
		FreeLibrary(GSMediaPlayerLib_);
		GSMediaPlayerLib_ = NULL;
	}
}

int GSMediaPlayer_stub::Initialize()
{
	// ´Ó×¢²á±í¶ÁÈ¡
}