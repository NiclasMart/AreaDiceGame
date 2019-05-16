#include "stdafx.h"
#include "CFieldSprite.h"


CFieldSprite::CFieldSprite()
	:state(TRUE)
{
}


CFieldSprite::~CFieldSprite()
{
}

void CFieldSprite::ResetState() {
	state = TRUE;
}
