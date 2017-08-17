#ifndef __UIPOSITIONPANEL_H
#define __UIPOSITIONPANEL_H


#include "UI.h"
#include "UIDataStruction.h"


typedef struct
{
	i4 targetX;
	i4 targetY;
	float maxX;
	float minX;
	float maxY;
	float minY;
	ui2 crossColor;
	ui2 R;
}PositionPanelBody_Type;


void PositionPanelInitDefault(Control_Type *PositionPanel);
void PositionPanel_Draw(ui2 *Buffer, Control_Type *PositionPanel);


#endif
