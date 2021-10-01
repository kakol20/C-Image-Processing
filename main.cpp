#include <iostream>
#include <stdio.h>
#include <charconv>
#include <sstream>
#include <vector>
#include <set>

#include "Image.h"
#include "Filters.h"
#include "String.h";

int main(int argc, char** argv) {
	//std::cout << "Hello World \n";

	//Image jihyo("images/jihyo/jihyo_blurred.png");
	//Image jihyoBN = jihyo;
	//Image jihyoTM = jihyo;

	//OrderedDithering(&jihyoBN, DitherFilter::FULLCOLOR, Threshold::BLUENOISE_16, 15);
	//OrderedDithering(&jihyoTM, DitherFilter::FULLCOLOR, Threshold::ORDERED_8, 15);

	//jihyoBN.Write("images/jihyo/jihyo_bluenoise_col_15.png");
	//jihyoTM.Write("images/jihyo/jihyo_ordered_col_15.png");

	Image firstFrame("images/rollingShutter/sequence/rolling_0000.png");
	int h = firstFrame.GetHeight();
	int w = firstFrame.GetWidth();
	int channel = firstFrame.GetChannels();

	Image still(w, h, channel);

	int max = 300;

	std::vector<Image*> images;
	images.reserve(max);

	//std::set<Image*> images;

	for (int i = 0; i < max; i++)
	{
		//String file("rolling shutter/sequence/rolling_0000.png");
		String file = "images/rollingShutter/sequence/rolling_";

		int numInt = i % max;

		if (numInt < 1000) file += "0";
		if (numInt < 100) file += "0";
		if (numInt < 10) file += "0";

		std::stringstream tmp;
		tmp << numInt;

		//file += number;

		String number = tmp.str().c_str();

		file += number + ".png";

		images.push_back(new Image(file.GetChar()));
		//images.insert(new Image(file.GetChar()));
	}

	for (int i = 0; i < h; i++)
	{
		int vectInd = i % max;

		for (int j = 0; j < w; j++)
		{
			int imgInd = images[vectInd]->GetIndex(j, i);

			for (int c = 0; c < channel; c++)
			{
				uint8_t p = images[vectInd]->GetData(imgInd + c);
				still.SetData(imgInd + c, p);

				/*uint8_t p = current->GetData(imgInd + c);
				output.SetData(imgInd + c, p);*/
			}
		}
	}

	// ----- ANIMATE -----

	still.Write("images/rollingShutter/angled.png");

	Image animation(w, h, channel);

	for (int frame = 0; frame < h; frame++)
	{
		int vectInd = frame % max;

		for (int y = frame; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				int imgInd = images[vectInd]->GetIndex(x, y);

				for (int c = 0; c < channel; c++)
				{
					uint8_t p;

					if (y <= frame)
					{
						p = still.GetData(imgInd + c);
					}
					else if (y > frame && y <= frame + 3)
					{
						//p = 255 - images[vectInd]->GetData(imgInd + c);

						if (c == 1)
						{
							p = 255;
						}
						else
						{
							p = 0;
						}
					}
					else
					{
						p = images[vectInd]->GetData(imgInd + c);
					}

					animation.SetData(imgInd + c, p);
				}
			}
		}

		String file = "images/rollingShutter/angled/rolling_";

		if (frame < 1000) file += "0";
		if (frame < 100) file += "0";
		if (frame < 10) file += "0";

		std::stringstream tmp;
		tmp << frame;

		//file += number;

		String number = tmp.str().c_str();

		file += number + ".png";

		animation.Write(file.GetChar());
	}

	// ----- DELETE -----

	for (auto image : images)
	{
		delete image;
		image = nullptr;
	}
	images.clear();

	system("PAUSE");

	return 0;
}