#include "drawing.h"

#include <string.h>
#include <math.h>

#include "../core/constants.h"
#include "../utils/maths.h"


void drawLine(drawbuffer* pBuffer, int fromX, int fromY, int toX, int toY, color4 color) {
#if TARGET_3DS
    float xSize = (float) (toX - fromX);
    float ySize = (float) (toY - fromY);
    
    float lineSize = ((xSize * xSize) + (ySize * ySize)) / 2.0;
    
    for (int i = 0; i < lineSize; i++) {
        int x = fromX + (toX-fromX) * ((float) i / lineSize);
        int y = fromY + (toY-fromY) * ((float) i / lineSize);
        
        memcpy(pBuffer->buffer + (x * (pBuffer->height) + (pBuffer->height - 1 - y)) * SCREEN_BPP * sizeof(uint8),
               &color,     // belek au format qui doit être compatbile 3DS (du BGR je crois) (voir get3DSFramebufferFormat)
               SCREEN_BPP * sizeof(uint8)
               );
    }
#elif TARGET_SDL || TARGET_SDL2
    float xSize = (float) (toX - fromX);
    float ySize = (float) (toY - fromY);

    float lineSize = ((xSize * xSize) + (ySize * ySize)) / 2.0;
    
    for (int i = 0; i < lineSize; i++) {
        int x = fromX + (toX-fromX) * ((float) i / lineSize);
        int y = fromY + (toY-fromY) * ((float) i / lineSize);
        
        memcpy(
               pBuffer->buffer + (x + (y * pBuffer->width)) * SCREEN_BPP * sizeof(uint8),
               &color,     // belek au format qui doit être compatbile 3DS (du BGR je crois) (voir get3DSFramebufferFormat)
               SCREEN_BPP * sizeof(uint8)
               );
    }
#endif
}

void drawBox(drawbuffer* pBuffer, int fromX, int fromY, int toX, int toY, color4 color) {
    int x, y;

    uint8* oneColorCol;

#if TARGET_3DS
    int boxHeight = std::abs(toY - fromY);

    oneColorCol = malloc((pBuffer->colorDepth * boxHeight) * sizeof(uint8));

    fromY = minInt(fromY, toY);
    toY = maxInt(fromY, toY);

    for (y = 0; y < boxHeight; y++) {
        memmove(oneColorCol + (y * pBuffer->colorDepth * sizeof(uint8)),
            &color,
            pBuffer->colorDepth * sizeof(uint8)
        );
    }

    for (x = fromX; x <= toX; x++) {
        memmove(pBuffer->buffer + ((pBuffer->height-1 - toY) * pBuffer->colorDepth * sizeof(uint8)) + (x * pBuffer->colorDepth * sizeof(uint8) * pBuffer->height),  // Attention, on inverse from et to et 239- parce que la DS a un système de coord qui part d'en bas à gauche
            oneColorCol,
            pBuffer->colorDepth * boxHeight * sizeof(uint8)
        );
    }

#elif TARGET_SDL || TARGET_SDL2 || TARGET_PSVITA
    fromX = minInt(maxInt(minInt(fromX, toX), 0), pBuffer->width-1);
    toX = minInt(maxInt(maxInt(fromX, toX), 0), pBuffer->width-1);

    fromY = minInt(maxInt(fromY, 0), pBuffer->height-1);
    toY = minInt(maxInt(toY, 0), pBuffer->height-1);

    int boxWidth = fabs((float)(toX - fromX + 1));

    oneColorCol = malloc((pBuffer->colorDepth * boxWidth) * sizeof(uint8));

    for (x = 0; x < boxWidth; x++) {
        memmove(oneColorCol + (x * pBuffer->colorDepth * sizeof(uint8)),
            &color,
            pBuffer->colorDepth * sizeof(uint8)
        );
    }

    for (y = fromY; y <= toY; y++) {
        memmove(pBuffer->buffer + (fromX * pBuffer->colorDepth * sizeof(uint8)) + (y * pBuffer->colorDepth * sizeof(uint8) * pBuffer->width),
            oneColorCol,
            pBuffer->colorDepth * boxWidth * sizeof(uint8)
        );
    }

#endif

    free(oneColorCol);
}

void rescaleBuffer(drawbuffer* srcBuf, int srcW, int srcH, int srcBpp, drawbuffer* dstBuf, int dstW, int dstH, int dstBpp) {
	int srcBufSize = srcW * srcH;
	int dstBufSize = dstW * dstH;
	int scaleRatio = dstBufSize / srcBufSize;

	for (int i = srcBufSize - 1; i >= 0; i--) {
		uint8* dstBufPtr = (dstBuf->buffer + (uint8) (i * srcBpp * scaleRatio));
		uint8* srcBufPtr = (srcBuf->buffer + (uint8) (i * srcBpp));
		// uint8 currVal = *(dstBufPtr + i);
		memcpy(dstBufPtr, srcBufPtr, srcBpp);
	}
}
