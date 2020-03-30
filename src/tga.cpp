#include <iostream>
#include <fstream>
#include "tga.h"
TGA::TGA(){
}
void TGA::SetAllFromFile(std::string fileName) {
	std::ifstream tgaFile(fileName, std::ios_base::binary);
	tgaFile.read(&_idLength, 1);
	tgaFile.read(&_colorMapType, 1);
	tgaFile.read(&_dataTypeCode, 1);
	tgaFile.read((char*) &_colorMapOrigin, 2);
	tgaFile.read((char*) &_colorMapLength, 2);
	tgaFile.read(&_colorMapDepth, 1);
	tgaFile.read((char*) &_xOrigin, 2);
	tgaFile.read((char*) &_yOrigin, 2);
	tgaFile.read((char*) &_width, 2);
	tgaFile.read((char*) &_height,2);
	tgaFile.read(&_bitsPerPixel, 1);
	tgaFile.read(&_imageDescriptor, 1);
	_pixelCount = (_xOrigin + _width) * (_yOrigin + _height);
	unsigned char data;
	unsigned char color = 'b';
	for (unsigned int i = 0; i < _pixelCount * 3; i++) {
		tgaFile.read((char*) &data, 1);
		_pixelData.push_back(data);
		if (color == 'b') {
			_bIndexes.push_back(i);
			_bData.push_back(data);
			_bData.push_back(data);
			_bData.push_back(data);
			color = 'g';
		}
		else if (color == 'g') {
			_gIndexes.push_back(i);
			_gData.push_back(data);
			_gData.push_back(data);
			_gData.push_back(data);
			color = 'r';
		}
		else if (color == 'r') {
			_rIndexes.push_back(i);
			_rData.push_back(data);
			_rData.push_back(data);
			_rData.push_back(data);
			color = 'b';
		}
	}
}
void TGA::SetAllFromFileRotated(std::string fileName, int degrees) {
	std::ifstream tgaFile(fileName, std::ios_base::binary);
	tgaFile.read(&_idLength, 1);
	tgaFile.read(&_colorMapType, 1);
	tgaFile.read(&_dataTypeCode, 1);
	tgaFile.read((char*) &_colorMapOrigin, 2);
	tgaFile.read((char*) &_colorMapLength, 2);
	tgaFile.read(&_colorMapDepth, 1);
	tgaFile.read((char*) &_xOrigin, 2);
	tgaFile.read((char*) &_yOrigin, 2);
	tgaFile.read((char*) &_width, 2);
	tgaFile.read((char*) &_height,2);
	tgaFile.read(&_bitsPerPixel, 1);
	tgaFile.read(&_imageDescriptor, 1);
	_pixelCount = (_xOrigin + _width) * (_yOrigin + _height);
	unsigned char data;
	std::vector<unsigned char> _temp;
	for (unsigned int i = 0; i < _pixelCount * 3; i++) {
		tgaFile.read((char*) &data, 1);
		_temp.push_back(data);
	}
	if (degrees == 180) {
		for (int i = _temp.size() - 1; i >= 2; i -= 3) {
			_pixelData.push_back(_temp[i - 2]);
			_pixelData.push_back(_temp[i -1]);
			_pixelData.push_back(_temp[i]);
		}
	}
}
void TGA::SetAllFromColorFilesBGR(std::string blueFile, std::string greenFile, std::string redFile) {
	std::ifstream blue(blueFile, std::ios_base::binary);
	std::ifstream green(greenFile, std::ios_base::binary);
	std::ifstream red(redFile, std::ios_base::binary);
	red.read(&_idLength, 1);
	red.read(&_colorMapType, 1);
	red.read(&_dataTypeCode, 1);
	red.read((char*) &_colorMapOrigin, 2);
	red.read((char*) &_colorMapLength, 2);
	red.read(&_colorMapDepth, 1);
	red.read((char*) &_xOrigin, 2);
	red.read((char*) &_yOrigin, 2);
	red.read((char*) &_width, 2);
	red.read((char*) &_height,2);
	red.read(&_bitsPerPixel, 1);
	red.read(&_imageDescriptor, 1);
	_pixelCount = (_xOrigin + _width) * (_yOrigin + _height);
	unsigned char data;
	unsigned char color = 'b';
	for (unsigned int i = 18; i < (_pixelCount * 3) + 18; i++) {
		if (color == 'b') {
			blue.seekg(i);
			blue.read((char*) &data, 1);
			_pixelData.push_back(data);
			_bIndexes.push_back(i);
			_bData.push_back(data);
			_bData.push_back(data);
			_bData.push_back(data);
			color = 'g';
		}
		else if (color == 'g') {
			green.seekg(i);
			green.read((char*) &data, 1);
			_pixelData.push_back(data);
			_gIndexes.push_back(i);
			_gData.push_back(data);
			_gData.push_back(data);
			_gData.push_back(data);
			color = 'r';
		}
		else if (color == 'r') {
			red.seekg(i);
			red.read((char*) &data, 1);
			_pixelData.push_back(data);
			_rIndexes.push_back(i);
			_rData.push_back(data);
			_rData.push_back(data);
			_rData.push_back(data);
			color = 'b';
		}
	}
}
void TGA::SetAllFromList(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength, char colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel, char imageDescriptor, unsigned int pixelCount, std::vector<unsigned char> pixelData) {
	_idLength = idLength;
	_colorMapType = colorMapType;
	_dataTypeCode = dataTypeCode;
	_colorMapOrigin = colorMapOrigin;
	_colorMapLength = colorMapLength;
	_colorMapDepth = colorMapDepth;
	_xOrigin = xOrigin;
	_yOrigin = yOrigin;
	_width = width;
	_height = height;
	_bitsPerPixel = bitsPerPixel;
	_imageDescriptor = imageDescriptor;
	_pixelCount = pixelCount;
	_pixelData = pixelData;
}
char TGA::GetIdLength() {
	return _idLength;
}
char TGA::GetColorMapType() {
	return _colorMapType;
}
char TGA::GetDataTypeCode() {
	return _dataTypeCode;
}
short TGA::GetColorMapOrigin() {
	return _colorMapOrigin;
}
short TGA::GetColorMapLength() {
	return _colorMapLength;
}
char TGA::GetColorMapDepth() {
	return _colorMapDepth;
}
short TGA::GetXOrigin() {
	return _xOrigin;
}
short TGA::GetYOrigin() {
	return _yOrigin;
}
short TGA::GetWidth() {
	return _width;
}
short TGA::GetHeight() {
	return _height;
}
char TGA::GetBitsPerPixel() {
	return _bitsPerPixel;
}
char TGA::GetImageDescriptor() {
	return _imageDescriptor;
}
unsigned int TGA::GetPixelCount() {
	return _pixelCount;
}
std::vector<unsigned char> TGA::GetPixelData() {
	return _pixelData;
}
std::vector<unsigned char> TGA::GetColorData(char color) {
	std::vector<unsigned char> returnVector;
	if (color == 'b') {
		returnVector = _bData;
	}
	else if (color == 'g') {
		returnVector = _gData;
	}
	else if (color == 'r') {
		returnVector = _rData;
	}
	return returnVector;
}
bool TGA::Compare(TGA compareTo) {
	bool status = true;
	if (_idLength != compareTo.GetIdLength()) {
		status = false;
	}
	if (_colorMapType != compareTo.GetColorMapType()) {
		status = false;
	}
	if (_dataTypeCode != compareTo.GetDataTypeCode()) {
		status = false;
	}
	if (_colorMapOrigin != compareTo.GetColorMapOrigin()) {
		status = false;
	}
	if (_colorMapLength != compareTo.GetColorMapLength()) {
		status = false;
	}
	if (_xOrigin != compareTo.GetXOrigin()) {
		status = false;
	}
	if (_yOrigin != compareTo.GetYOrigin()) {
		status = false;
	}
	if (_width != compareTo.GetWidth()) {
		status = false;
	}
	if (_height != compareTo.GetHeight()) {
		status = false;
	}
	if (_bitsPerPixel != compareTo.GetBitsPerPixel()) {
		status = false;
	}
	if (_imageDescriptor != compareTo.GetImageDescriptor()) {
		status = false;
	}
	if (_pixelCount != compareTo.GetPixelCount()) {
		status = false;
	}
	if (_pixelData != compareTo.GetPixelData()) {
		status = false;
	}
	return status;
}
void TGA::WriteFile(std::string fileName) {
	std::ofstream outFile(fileName, std::ios_base::binary);
	outFile.write((char*) &_idLength, 1);
	outFile.write((char*) &_colorMapType, 1);
	outFile.write((char*) &_dataTypeCode, 1);
	outFile.write((char*) &_colorMapOrigin, 2);
	outFile.write((char*) &_colorMapLength, 2);
	outFile.write((char*) &_colorMapDepth, 1);
	outFile.write((char*) &_xOrigin, 2);
	outFile.write((char*) &_yOrigin, 2);
	outFile.write((char*) &_width, 2);
	outFile.write((char*) &_height, 2);
	outFile.write((char*) &_bitsPerPixel, 1);
	outFile.write((char*) &_imageDescriptor, 1);
	for (int i = 0; i < _pixelData.size(); i++) {
		outFile.write((char*) &_pixelData[i], 1);
	}
}
std::vector<unsigned int> TGA::GetIndexOfColor(char color) {
	std::vector<unsigned int> returnVector;
	if (color == 'b') {
		returnVector = _bIndexes;
	}
	else if (color == 'g') {
		returnVector = _gIndexes;
	}
	else if (color == 'r') {
		returnVector = _rIndexes;
	}
	return returnVector;
}
void TGA::IncreaseColor(unsigned int index, int increaseAmount) {
	if (((int) _pixelData[index] + increaseAmount) > 255) {
		_pixelData[index] = 255;
	}
	else if (((int) _pixelData[index] + increaseAmount) < 0) {
		_pixelData[index] = 0;
	}
	else {
		_pixelData[index] += increaseAmount;
	}
}
void TGA::ScaleColor(unsigned int index, int scaleFactor) {
	if ((_pixelData[index] * scaleFactor) > 255) {
		_pixelData[index] = 255;
	}
	else {
		_pixelData[index] *= scaleFactor;
	}
}
