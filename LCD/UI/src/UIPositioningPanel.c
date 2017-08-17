#include "UIPositioningPanel.h"
#include "UIDrawRAM.h"


void PositionPanelInitDefault(Control_Type *PositionPanel)
{
	((PositionPanelBody_Type *)(PositionPanel->body))->targetX = 0;
	((PositionPanelBody_Type *)(PositionPanel->body))->targetY = 0;
	((PositionPanelBody_Type *)(PositionPanel->body))->maxX = 130;
	((PositionPanelBody_Type *)(PositionPanel->body))->minX = -130;
	((PositionPanelBody_Type *)(PositionPanel->body))->maxY = 130;
	((PositionPanelBody_Type *)(PositionPanel->body))->minY = -130;
	((PositionPanelBody_Type *)(PositionPanel->body))->R = 7;
     	((PositionPanelBody_Type *)(PositionPanel->body))->crossColor = 0xF800;
	PositionPanel->backColor = 0x0000;
	PositionPanel->frameColor = 0x001F;
	PositionPanel->frontColor = 0x07E0;
	PositionPanel->OnPush = NULL;
	PositionPanel->OnLift = NULL;
}


void PositionPanel_Draw(ui2 *Buffer, Control_Type *PositionPanel)
{
	uint16_t sx, sy, ex, ey;
	float xRate, yRate;
	
	DrawRAM_Rect(Buffer, PositionPanel->pos.x, PositionPanel->pos.y, PositionPanel->size.x, PositionPanel->size.y, PositionPanel->backColor, 1, 1);
	DrawRAM_Rect(Buffer, PositionPanel->pos.x, PositionPanel->pos.y, PositionPanel->size.x, PositionPanel->size.y, PositionPanel->frontColor, 5, 0);
	
	xRate = (float)(PositionPanel->size.x) / (((PositionPanelBody_Type *)(PositionPanel->body))->maxX - ((PositionPanelBody_Type *)(PositionPanel->body))->minX);
	yRate = (float)(PositionPanel->size.y) / (((PositionPanelBody_Type *)(PositionPanel->body))->maxY - ((PositionPanelBody_Type *)(PositionPanel->body))->minY);
	
	//»­×ÝÖá
	if((((PositionPanelBody_Type *)(PositionPanel->body))->maxX > 0)
		&& (((PositionPanelBody_Type *)(PositionPanel->body))->minX < 0))
	{
		sx = PositionPanel->pos.x + ((PositionPanelBody_Type *)(PositionPanel->body))->maxX * xRate;
		sy = PositionPanel->pos.y;
		ex = sx;
		ey = PositionPanel->pos.y + PositionPanel->size.y;
		DrawRAM_Line(Buffer, sx, sy, ex, ey, ((PositionPanelBody_Type *)(PositionPanel->body))->crossColor, 1);			
	}
	
	//»­ºáÖá
	if((((PositionPanelBody_Type *)(PositionPanel->body))->maxY > 0)
		&& (((PositionPanelBody_Type *)(PositionPanel->body))->minY < 0))
	{
		sx = PositionPanel->pos.x;
		sy = PositionPanel->pos.y + ((PositionPanelBody_Type *)(PositionPanel->body))->maxY * yRate;
		ex = PositionPanel->pos.x + PositionPanel->size.x;
		ey = sy;
		DrawRAM_Line(Buffer, sx, sy, ex, ey, ((PositionPanelBody_Type *)(PositionPanel->body))->crossColor, 1);			
	}
	
	//»­Ô²
	if((((((PositionPanelBody_Type *)(PositionPanel->body))->maxX - ((PositionPanelBody_Type *)(PositionPanel->body))->targetX) * xRate) > ((PositionPanelBody_Type *)(PositionPanel->body))->R)
		&& (((((PositionPanelBody_Type *)(PositionPanel->body))->targetX - ((PositionPanelBody_Type *)(PositionPanel->body))->minX) * xRate) > ((PositionPanelBody_Type *)(PositionPanel->body))->R)
		&& (((((PositionPanelBody_Type *)(PositionPanel->body))->maxY - ((PositionPanelBody_Type *)(PositionPanel->body))->targetY) * yRate) > ((PositionPanelBody_Type *)(PositionPanel->body))->R)
		&& (((((PositionPanelBody_Type *)(PositionPanel->body))->targetY - ((PositionPanelBody_Type *)(PositionPanel->body))->minY) * yRate) > ((PositionPanelBody_Type *)(PositionPanel->body))->R))
	{
		DrawRAM_Circle(Buffer, 
						(((PositionPanelBody_Type *)(PositionPanel->body))->targetX - ((PositionPanelBody_Type *)(PositionPanel->body))->minX) * xRate + PositionPanel->pos.x,
						PositionPanel->pos.y + PositionPanel->size.y - (((PositionPanelBody_Type *)(PositionPanel->body))->targetY - ((PositionPanelBody_Type *)(PositionPanel->body))->minY) * yRate,
						((PositionPanelBody_Type *)(PositionPanel->body))->R,
						PositionPanel->frontColor,
						1);
	}
	
}




