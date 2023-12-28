#ifndef DRAWING_H
#define DRAWING_H

#include "../core/types.h"
#include "../core/graphics.h"


void drawLine(drawbuffer* pBuffer, int fromX, int fromY, int toX, int toY, color4 color);
void drawBox(drawbuffer* pBuffer, int fromX, int fromY, int toX, int toY, color4 color);
void rescaleBuffer(drawbuffer* srcBuf, int srcW, int srcH, int srcBpp, drawbuffer* dstBuf, int dstW, int dstH, int dstBpp);

#endif
