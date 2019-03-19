#include<fstream>
#include<iostream>
#include<windows.h>
#define DEBUG 0 //set true to show debug information
struct BMP256 {
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER bmpInfoHead;
	struct Palette{
		struct Color{
			BYTE B;
			BYTE G;
			BYTE R;
			BYTE A;
		};
		Color *color;
		int count;
		void read(std::ifstream *in, int c){
			count = (c == 0 ? 256 : c);
			color = new Color[count];
			in->read((char*)color, 4 * count);
		}
		void write(std::ofstream *out){
			out->write((char*)color, 4 * count);
		}
		~Palette(){
			delete[] color;
			if(DEBUG) std::cout << "Palette destructed." << std::endl;
		}
	};
	Palette palette;
	BYTE** px;

	BMP256(const char* fileName) {
		//filestream
		std::ifstream inBmp(fileName, std::ios::in | std::ios::binary);
		if (!inBmp) {
			std::cout << "Read file error!" << std::endl;
			exit(1);
		}
		if(DEBUG) std::cout << "Reading from file " << fileName << std::endl;
		//filehead
		inBmp.read((char*)&fileHead, sizeof(fileHead));
		inBmp.read((char*)&bmpInfoHead, sizeof(bmpInfoHead));
		if (bmpInfoHead.biBitCount != 8) {
			std::cout << "Not a 256 color bitmap!" << std::endl;
			exit(0);
		}
		palette.read(&inBmp, bmpInfoHead.biClrUsed);
		//read pxs
		px = new BYTE*[bmpInfoHead.biHeight];
		for (int i = 0; i < bmpInfoHead.biHeight; i++) px[i] = new BYTE[bmpInfoHead.biWidth];
		int dataSizePerLine = ((bmpInfoHead.biWidth + 7) / 8) * 8;
		for (int i = 0; i < bmpInfoHead.biHeight; i++) {
			inBmp.seekg(fileHead.bfOffBits + i * dataSizePerLine, std::ios_base::beg);
			for (int j = 0; j < bmpInfoHead.biWidth; j++) px[i][j] = inBmp.get();
		}
		if(DEBUG) std::cout << "Reading finished." << std::endl;
		inBmp.close();
	}

	BMP256(int row, int column) {
		int dataSizePerLine = ((column + 7) / 8) * 8;
		int fileSize = row * dataSizePerLine + 1078;
		fileHead.bfType = 19778;//short		"BM"
		fileHead.bfSize = fileSize;//long
		fileHead.bfReserved1 = 0;//short
		fileHead.bfReserved2 = 0;//short
		fileHead.bfOffBits = 1078;//long	0436h
		bmpInfoHead.biSize = sizeof(bmpInfoHead);//long
		bmpInfoHead.biWidth = column;//long
		bmpInfoHead.biHeight = row;//long
		bmpInfoHead.biPlanes = 1;//short
		bmpInfoHead.biBitCount = 8;//short
		bmpInfoHead.biCompression = 0;//long
		bmpInfoHead.biSizeImage = fileSize - 1078;//long
		bmpInfoHead.biXPelsPerMeter = 0;//long
		bmpInfoHead.biYPelsPerMeter = 0;//long
		bmpInfoHead.biClrUsed = 0;//long
		bmpInfoHead.biClrImportant = 0;//long
		//initial a gray palette
		palette.count = 256;
		palette.color = new Palette::Color[256];
		for(int i = 0; i < 256; i++){
			palette.color[i].B = i;
			palette.color[i].G = i;
			palette.color[i].R = i;
			palette.color[i].A = 0;
		}
		//fill blank image with 0
		px = new BYTE*[bmpInfoHead.biHeight];
		for (int i = 0; i < bmpInfoHead.biHeight; i++) {
			px[i] = new BYTE[bmpInfoHead.biWidth];
			for (int j = 0; j < bmpInfoHead.biWidth; j++)
				px[i][j] = 0;
		}
	}

	BMP256(BMP256* b) {
		this->fileHead = b->fileHead;
		this->bmpInfoHead = b->bmpInfoHead;
		this->palette.count = b->palette.count;
		palette.color = new Palette::Color[palette.count];
		for(int i = 0; i < palette.count; i++)
			this->palette.color[i] = b->palette.color[i];
		px = new BYTE*[bmpInfoHead.biHeight];
		for (int i = 0; i < bmpInfoHead.biHeight; i++) {
			px[i] = new BYTE[bmpInfoHead.biWidth];
			for (int j = 0; j < bmpInfoHead.biWidth; j++)
				this->px[i][j] = b->px[i][j];
		}
	}

	~BMP256() {
		for(int i = 0; i < bmpInfoHead.biHeight; i++) delete[] px[i];
		delete[] px;
		if(DEBUG) std::cout << "BMP256 destructed." << std::endl;
	}

	void writeFile(const char* FileName) {
		int dataSizePerLine = ((bmpInfoHead.biWidth + 7) / 8) * 8;
		int fileSize = bmpInfoHead.biHeight * dataSizePerLine + 1078;

		std::ofstream outBmp(FileName, std::ios::out | std::ios::binary);
		if (!outBmp) {
			std::cout << "Write file error!" << std::endl;
			exit(1);
		}
		
		if(DEBUG) std::cout << "Writing to file " << FileName << std::endl;
		outBmp.write((char*)&fileHead, sizeof(fileHead));
		outBmp.write((char*)&bmpInfoHead, sizeof(bmpInfoHead));
		palette.write(&outBmp);

		BYTE* buffer = new BYTE[dataSizePerLine];
		for (int i = 0; i < bmpInfoHead.biHeight; i++) {
			int k = 0;
			for (int j = 0; j < bmpInfoHead.biWidth; j++) {
				buffer[k++] = px[i][j];
			}
			outBmp.write((char*)buffer, dataSizePerLine);
		}
		delete[] buffer;
		if(DEBUG) std::cout << "Writing finished." << std::endl;
		outBmp.close();
	}
};
