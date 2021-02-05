#include "Holder.h"

holder& holder::get()
{
	static holder hold;
	return hold;
}

holder::holder() : fonts("czcionki", "ttf"), textures("tekstury", "png"), sounds("dzwieki", "wav")
{

}