#pragma once
#include "olcPixelGameEngine.h"

struct ScanLineDrawArea
{
	int x;
	int length;
	bool on;
};

class ScanLineSprite : public olc::Sprite
{
private:
	std::vector<std::vector<ScanLineDrawArea>> mScanLines;
	bool mNeedsRecalculate = true;
public:

	void RecalculateScanLines(int maskCutoff)
	{
		mNeedsRecalculate = false;
		mScanLines.clear();
		for (int y = 0; y < height; y++)
		{
			bool inLine = (GetPixel(0, y).a >= maskCutoff);
			int start = 0;
			std::vector<ScanLineDrawArea> currLine;
			for (int x = 0; x < width; x++)
			{
				if (inLine != (GetPixel(x, y).a >= maskCutoff)) {
					currLine.push_back(ScanLineDrawArea{ start, x - start, inLine });
					inLine = !inLine;
					start = x;
				}
			}
			currLine.push_back(ScanLineDrawArea{ start, width - start, inLine });
			mScanLines.push_back(currLine);
		}
	}

	ScanLineSprite(std::string sImageFile, int maskCutoff = 255) : Sprite(sImageFile)
	{
		RecalculateScanLines(maskCutoff);
	}

	ScanLineSprite(std::string sImageFile, olc::ResourcePack* pack, int maskCutoff = 255) : Sprite(sImageFile, pack)
	{
		RecalculateScanLines(maskCutoff);
	}

	ScanLineSprite(int32_t w, int32_t h) : Sprite(w, h)
	{
		//really if going to draw on a ScanLineSprite directly recalculate should be manually called before use
		mNeedsRecalculate = true;
	}

	void DrawOnTarget(olc::Sprite* target, int32_t x, int32_t y, olc::Pixel::Mode mode = olc::Pixel::MASK)
	{
		if ((mode == olc::Pixel::NORMAL) && (x == 0) && (y == 0) && (width == target->width) && (height == target->height))
		{
			olc::Pixel* srcpix = GetData();
			olc::Pixel* dstpix = target->GetData();
			memcpy(dstpix, srcpix, sizeof(olc::Pixel) * width * height);
		}
		else
		{
			DrawPeriodicOnTarget(target, x, y, 0, 0, width, height, mode);
		}
	}

	void DrawPeriodicOnTarget(olc::Sprite* target, int32_t x, int32_t y, int32_t ox, int32_t oy, int32_t w, int32_t h, olc::Pixel::Mode mode = olc::Pixel::MASK)
	{
		if (mNeedsRecalculate) {
			RecalculateScanLines(255);
		}

		if ((x > target->width) || (y > target->height))
		{
			return;
		}
		if (x < 0) {
			w = w + x;
			ox = ox - x;
			x = 0;
		}
		if (y < 0) {
			h = h + y;
			oy = oy - y;
			y = 0;
		}
		w = std::min(w, target->width - x);
		h = std::min(h, target->height - y);
		olc::Pixel* basetargetData = target->GetData();
		olc::Pixel* basesourceData = GetData();
		for (int j = 0; j < h; j++) {
			int sourcescanline = (oy + j) % height;
			std::vector<ScanLineDrawArea> slda = mScanLines[sourcescanline];
			int lookForX = ox % width;
			int startIndex = 0;
			int offset = 0;
			for (int i = 0; i < slda.size(); i++)
			{
				if (slda[i].x <= lookForX) {
					startIndex = i;
					offset = slda[i].x - lookForX;
				}
				else {
					break;
				}
			}
			int len = 0;
			int left = w;
			offset = lookForX - slda[startIndex].x;
			olc::Pixel* dst = basetargetData;
			dst += ((y + j) * target->width) + x;
			while (left > 0)
			{
				olc::Pixel* src = basesourceData;
				src += sourcescanline * width;
				src += slda[startIndex].x + offset;
				int toCopy = std::min(slda[startIndex].length - offset, left);
				if (slda[startIndex].on || mode == olc::Pixel::NORMAL)
				{
					if ((mode != olc::Pixel::ALPHA))
					{
						memcpy(dst, src, toCopy * sizeof(olc::Pixel));
					}
					else
					{
						olc::Pixel* currDst = dst;
						olc::Pixel* currSrc = src;
						for (int i = 0; i < toCopy; i++)
						{
							olc::Pixel d = *currDst;
							olc::Pixel p = *currSrc;
							if (p.a == 255)
							{
								*currDst = *currSrc;
							}
							else
							{
								float srcAlpha = p.a / 255.0f;
								float c = 1.0f - srcAlpha;
								uint8_t* col = (uint8_t*)currDst;
								*col = (uint8_t)(srcAlpha * (float)p.r + c * (float)d.r);
								col++;
								*col = (uint8_t)(srcAlpha * (float)p.g + c * (float)d.g);
								col++;
								*col = (uint8_t)(srcAlpha * (float)p.b + c * (float)d.b);
								//we don't really use this so we could remove it
								col++;
								*col = (uint8_t)(srcAlpha * (float)p.a + c * (float)d.a);
							}
							currDst++;
							currSrc++;
						}
					}
				}
				dst += toCopy;
				left -= toCopy;
				startIndex = (startIndex + 1) % slda.size();
				offset = 0;
			}
		}
	}
};