#include "bmp256.cpp"

char files[14][17] = {"citywall.bmp", "citywall1.bmp", "citywall2.bmp",
                      "elain.bmp", "elain1.bmp", "elain2.bmp", "elain3.bmp",
                      "lena.bmp", "lena1.bmp", "lena2.bmp", "lena4.bmp",
                      "woman.bmp", "woman1.bmp", "woman2.bmp"
                     };
void stat(char *file) {
	int c[256] = {0};
	BMP256 *bmp;
	try{
		bmp = new BMP256(file);
	}
	catch(int n){
		return;
	}
	for(int i = 0; i < bmp->bmpInfoHead.biHeight; i++) {
		for (int j = 0; j < bmp->bmpInfoHead.biWidth; j++) {
			int t = bmp->px[i][j];
			if(t < bmp->palette.count) c[bmp->palette.color[t].R]++;// same for r, g or b
			//else c[255]++;
		}
	}
	int s = bmp->bmpInfoHead.biHeight * bmp->bmpInfoHead.biWidth;
	BMP256 n(256, 256);
	for(int i = 0; i < 256; i++) {
		int q = (int)((float)c[i] / (float)s * 5000.0);
		if(q > 256) q = 256;
		for(int j = 0; j < q; j++) {
			n.px[j][i] = 255;
		}
	}
	char t[21] = "_hg_";
	for(int i = 0; i < 17; i++) t[i + 4] = file[i];
	n.writeFile(t);
}

int main() {
	for(int d = 0; d < 14; d++) {
		stat(files[d]);
		char e[17]; //attach "-eq" at the end of file name
		for(int i = 0, j = 0; (e[i] = files[d][j]) != '\0'; i++, j++)
			if(e[i] == '.') {
				e[i++] = '_';
				e[i++] = 'e';
				e[i++] = 'q';
				e[i] = '.';
			}
		stat(e);
	}
	return 0;
}
