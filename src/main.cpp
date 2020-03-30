#include <iostream>
#include <vector>
#include "tga.h"
TGA Multiply(TGA tgaOne, TGA tgaTwo) {
	TGA multiplied;
	std::vector<unsigned char> one = tgaOne.GetPixelData();
	std::vector<unsigned char> two = tgaTwo.GetPixelData();
	std::vector<unsigned char> multipliedData;
	float m;
	for (int i = 0; i < one.size(); i++) {
		m = ((float) one[i] * (float) two[i]) / 255;
		m -= 0.5f;
		multipliedData.push_back(m + 1);
	}
	TGA headParameters = tgaOne;
	multiplied.SetAllFromList(headParameters.GetIdLength(), headParameters.GetColorMapType(), headParameters.GetDataTypeCode(), headParameters.GetColorMapOrigin(), headParameters.GetColorMapLength(), headParameters.GetColorMapDepth(), headParameters.GetXOrigin(), headParameters.GetYOrigin(), headParameters.GetWidth(), headParameters.GetHeight(), headParameters.GetBitsPerPixel(), headParameters.GetImageDescriptor(), headParameters.GetPixelCount(), multipliedData);
	return multiplied;
}
TGA Subtract(TGA top, TGA bottom) {
	TGA subtracted;
	std::vector<unsigned char> topData = top.GetPixelData();
	std::vector<unsigned char> bottomData = bottom.GetPixelData();
	std::vector<unsigned char> subtractedData;
	int m;
	for (int i = 0; i < topData.size(); i++) {
		if (topData[i] > bottomData[i]) {
			m = 0;
		}
		else {
			m = (int) bottomData[i] - (int) topData[i];
		}
		subtractedData.push_back(m);
	}
	TGA headParameters = top;
	subtracted.SetAllFromList(headParameters.GetIdLength(), headParameters.GetColorMapType(), headParameters.GetDataTypeCode(), headParameters.GetColorMapOrigin(), headParameters.GetColorMapLength(), headParameters.GetColorMapDepth(), headParameters.GetXOrigin(), headParameters.GetYOrigin(), headParameters.GetWidth(), headParameters.GetHeight(), headParameters.GetBitsPerPixel(), headParameters.GetImageDescriptor(), headParameters.GetPixelCount(), subtractedData);
	return subtracted;
}
TGA Screen(TGA tgaOne, TGA tgaTwo) {
	TGA screened;
	std::vector<unsigned char> one = tgaOne.GetPixelData();
	std::vector<unsigned char> two = tgaTwo.GetPixelData();
	std::vector<unsigned char> screenedData;
	float s;
	for (int i = 0; i < one.size(); i++) {
		s = 1 - (1 - one[i] / 255.0f) * (1 - two[i] /255.0f);
		s *= 255;
		s += 0.5f;
		screenedData.push_back(s);
	}
	TGA headParameters = tgaOne;
	screened.SetAllFromList(headParameters.GetIdLength(), headParameters.GetColorMapType(), headParameters.GetDataTypeCode(), headParameters.GetColorMapOrigin(), headParameters.GetColorMapLength(), headParameters.GetColorMapDepth(), headParameters.GetXOrigin(), headParameters.GetYOrigin(), headParameters.GetWidth(), headParameters.GetHeight(), headParameters.GetBitsPerPixel(), headParameters.GetImageDescriptor(), headParameters.GetPixelCount(), screenedData);
	return screened;
}
TGA Overlay(TGA tgaTop, TGA tgaBottom) {
	TGA overlayed;
	std::vector<unsigned char> top = tgaTop.GetPixelData();
	std::vector<unsigned char> bottom = tgaBottom.GetPixelData();
	std::vector<unsigned char> overlayedData;
	float o;
	for (int i = 0; i < top.size(); i++) {
		if (bottom[i] > (255 / 2)) {
			o = 1 - 2 * (1 - top[i] / 255.0f) * (1 - bottom[i] / 255.0f);
			o *= 255;
			o += 0.5f;
		}
		else {
			o = 2 * (top[i] / 255.0f) * (bottom[i] / 255.0f);
			o *= 255;
			o += 0.5f;
		}
		overlayedData.push_back(o);
	}
	TGA headParameters = tgaTop;
	overlayed.SetAllFromList(headParameters.GetIdLength(), headParameters.GetColorMapType(), headParameters.GetDataTypeCode(), headParameters.GetColorMapOrigin(), headParameters.GetColorMapLength(), headParameters.GetColorMapDepth(), headParameters.GetXOrigin(), headParameters.GetYOrigin(), headParameters.GetWidth(), headParameters.GetHeight(), headParameters.GetBitsPerPixel(), headParameters.GetImageDescriptor(), headParameters.GetPixelCount(), overlayedData);
	return overlayed;
}
int main() {
	//Task 1
	std::cout << "Beginning Task 1" << std::endl;
	TGA exampleOne;
	exampleOne.SetAllFromFile("examples/EXAMPLE_part1.tga");
	TGA layerOne;
	layerOne.SetAllFromFile("input/layer1.tga");
	TGA patternOne;
	patternOne.SetAllFromFile("input/pattern1.tga");
	TGA taskOne = Multiply(layerOne, patternOne);
	taskOne.WriteFile("output/part1.tga");
	if (taskOne.Compare(exampleOne)) {
		std::cout << "Task 1: Success" << std::endl;
	}
	//Task 2
	std::cout << "Beginning Task 2" << std::endl;
	TGA exampleTwo;
	exampleTwo.SetAllFromFile("examples/EXAMPLE_part2.tga");
	TGA layerTwo;
	layerTwo.SetAllFromFile("input/layer2.tga");
	TGA car;
	car.SetAllFromFile("input/car.tga");
	TGA taskTwo = Subtract(layerTwo, car);
	taskTwo.WriteFile("output/part2.tga");
	if (taskTwo.Compare(exampleTwo)) {
		std::cout << "Task 2: Success" << std::endl;
	}
	//Task 3
	std::cout << "Beginning Task 3" << std::endl;
	TGA exampleThree;
	exampleThree.SetAllFromFile("examples/EXAMPLE_part3.tga");
	TGA patternTwo;
	patternTwo.SetAllFromFile("input/pattern2.tga");
	TGA tempTGA = Multiply(layerOne, patternTwo);
	TGA textTGA;
	textTGA.SetAllFromFile("input/text.tga");
	TGA taskThree = Screen(tempTGA, textTGA);
	taskThree.WriteFile("output/part3.tga");
	if (taskThree.Compare(exampleThree)) {
		std::cout << "Task 3: Success" << std::endl;
	}
	//Task 4
	std::cout << "Beginning Task 4" << std::endl;
	TGA exampleFour;
	exampleFour.SetAllFromFile("examples/EXAMPLE_part4.tga");
	TGA circlesTGA;
	circlesTGA.SetAllFromFile("input/circles.tga");
	tempTGA = Multiply(layerTwo, circlesTGA);
	TGA taskFour = Subtract(patternTwo, tempTGA);
	taskFour.WriteFile("output/part4.tga");
	if (taskFour.Compare(exampleFour)) {
		std::cout << "Task 4: Success" << std::endl;
	}
	//Task 5
	std::cout << "Beginning Task 5" << std::endl;
	TGA exampleFive;
	exampleFive.SetAllFromFile("examples/EXAMPLE_part5.tga");
	TGA taskFive = Overlay(layerOne, patternOne);
	taskFive.WriteFile("output/part5.tga");
	if (taskFive.Compare(exampleFive)) {
		std::cout << "Task 5: Success" << std::endl;
	}
	//Task 6
	std::cout << "Beginning Task 6" << std::endl;
	TGA exampleSix;
	exampleSix.SetAllFromFile("examples/EXAMPLE_part6.tga");
	TGA taskSix = car;
	std::vector<unsigned int> modifyIndexes = taskSix.GetIndexOfColor('g');
	for (int i = 0; i < modifyIndexes.size(); i++) {
		taskSix.IncreaseColor(modifyIndexes[i], 200);
	}
	taskSix.WriteFile("output/part6.tga");
	if (taskSix.Compare(exampleSix)) {
		std::cout << "Task 6: Success" << std::endl;
	}
	//Task 7
	std::cout << "Beginning Task 7" << std::endl;
	TGA exampleSeven;
	exampleSeven.SetAllFromFile("examples/EXAMPLE_part7.tga");
	TGA taskSeven = car;
	modifyIndexes = taskSeven.GetIndexOfColor('r');
	for (int i = 0; i < modifyIndexes.size(); i++) {
		taskSeven.ScaleColor(modifyIndexes[i], 4);
	}
	modifyIndexes = taskSeven.GetIndexOfColor('b');
	for (int i = 0; i < modifyIndexes.size(); i++) {
		taskSeven.ScaleColor(modifyIndexes[i], 0);
	}
	taskSeven.WriteFile("output/part7.tga");
	if (taskSeven.Compare(exampleSeven)) {
		std::cout << "Task 7: Success" << std::endl;
	}
	//Task 8
	std::cout << "Beginning Task 8" << std::endl;
	TGA exampleEightB;
	exampleEightB.SetAllFromFile("examples/EXAMPLE_part8_b.tga");
	TGA exampleEightG;
	exampleEightG.SetAllFromFile("examples/EXAMPLE_part8_g.tga");
	TGA exampleEightR;
	exampleEightR.SetAllFromFile("examples/EXAMPLE_part8_r.tga");
	TGA headParameters = car;
	TGA taskEightB;
	std::vector<unsigned char> bData = car.GetColorData('b');
	taskEightB.SetAllFromList(headParameters.GetIdLength(), headParameters.GetColorMapType(), headParameters.GetDataTypeCode(), headParameters.GetColorMapOrigin(), headParameters.GetColorMapLength(), headParameters.GetColorMapDepth(), headParameters.GetXOrigin(), headParameters.GetYOrigin(), headParameters.GetWidth(), headParameters.GetHeight(), headParameters.GetBitsPerPixel(), headParameters.GetImageDescriptor(), headParameters.GetPixelCount(), bData);
	TGA taskEightG;
	std::vector<unsigned char> gData = car.GetColorData('g');
	taskEightG.SetAllFromList(headParameters.GetIdLength(), headParameters.GetColorMapType(), headParameters.GetDataTypeCode(), headParameters.GetColorMapOrigin(), headParameters.GetColorMapLength(), headParameters.GetColorMapDepth(), headParameters.GetXOrigin(), headParameters.GetYOrigin(), headParameters.GetWidth(), headParameters.GetHeight(), headParameters.GetBitsPerPixel(), headParameters.GetImageDescriptor(), headParameters.GetPixelCount(), gData);
	TGA taskEightR;
	std::vector<unsigned char> rData = car.GetColorData('r');
	taskEightR.SetAllFromList(headParameters.GetIdLength(), headParameters.GetColorMapType(), headParameters.GetDataTypeCode(), headParameters.GetColorMapOrigin(), headParameters.GetColorMapLength(), headParameters.GetColorMapDepth(), headParameters.GetXOrigin(), headParameters.GetYOrigin(), headParameters.GetWidth(), headParameters.GetHeight(), headParameters.GetBitsPerPixel(), headParameters.GetImageDescriptor(), headParameters.GetPixelCount(), rData);
	taskEightB.WriteFile("output/part8_b.tga");
	taskEightG.WriteFile("output/part8_g.tga");
	taskEightR.WriteFile("output/part8_r.tga");
	if (taskEightB.Compare(exampleEightB) && taskEightG.Compare(exampleEightG) && taskEightR.Compare(exampleEightR)) {
		std::cout << "Task 8: Success" << std::endl;
	}
	//Task 9
	std::cout << "Beginning Task 9" << std::endl;
	TGA exampleNine;
	exampleNine.SetAllFromFile("examples/EXAMPLE_part9.tga");
	TGA taskNine;
	taskNine.SetAllFromColorFilesBGR("input/layer_blue.tga", "input/layer_green.tga", "input/layer_red.tga");
	taskNine.WriteFile("output/part9.tga");
	if (taskNine.Compare(exampleNine)) {
		std::cout << "Task 9: Success" << std::endl;
	}
	//Task 10
	std::cout << "Beginning Task 10" << std::endl;
	TGA exampleTen;
	exampleTen.SetAllFromFile("examples/EXAMPLE_part10.tga");
	TGA taskTen;
	taskTen.SetAllFromFileRotated("input/text2.tga", 180);
	std::vector<unsigned char> tenData;
	taskTen.WriteFile("output/part10.tga");
	if (taskTen.Compare(exampleTen)) {
			std::cout << "Task 10: Success" << std::endl;
	}
}
