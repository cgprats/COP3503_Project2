#pragma once
#include <vector>
class TGA {
	private:
		char _idLength;
		char _colorMapType;
		char _dataTypeCode;
		short _colorMapOrigin;
		short _colorMapLength;
		char _colorMapDepth;
		short _xOrigin;
		short _yOrigin;
		short _width;
		short _height;
		char _bitsPerPixel;
		char _imageDescriptor;
		unsigned int _pixelCount;
		std::vector<unsigned char> _pixelData;
		std::vector<unsigned int> _bIndexes;
		std::vector<unsigned char> _bData;
		std::vector<unsigned int> _gIndexes;
		std::vector<unsigned char> _gData;
		std::vector<unsigned int> _rIndexes;
		std::vector<unsigned char> _rData;
	public:
		TGA();
		void SetAllFromFile(std::string);
		void SetAllFromFileRotated(std::string, int);
		void SetAllFromColorFilesBGR(std::string, std::string, std::string);
		void SetAllFromList(char, char, char, short, short, char, short, short, short, short, char, char, unsigned int, std::vector<unsigned char>);
		char GetIdLength();
		char GetColorMapType();
		char GetDataTypeCode();
		short GetColorMapOrigin();
		short GetColorMapLength();
		char GetColorMapDepth();
		short GetXOrigin();
		short GetYOrigin();
		short GetWidth();
		short GetHeight();
		char GetBitsPerPixel();
		char GetImageDescriptor();
		unsigned int GetPixelCount();
		std::vector<unsigned char> GetPixelData();
		std::vector<unsigned char> GetColorData(char);
		bool Compare(TGA);
		void WriteFile(std::string);
		std::vector<unsigned int> GetIndexOfColor(char);
		void IncreaseColor(unsigned int, int);
		void ScaleColor(unsigned int, int);
};
