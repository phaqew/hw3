#include "bmp256.cpp"

char files[14][14] = {"citywall.bmp", "citywall1.bmp", "citywall2.bmp",
					  "elain.bmp", "elain1.bmp", "elain2.bmp", "elain3.bmp",
					  "lena.bmp", "lena1.bmp", "lena2.bmp", "lena4.bmp",
					  "woman.bmp", "woman1.bmp", "woman2.bmp"};
					  
void eql(char *file){
	BMP256 g(file);
	int s = 0, c[256] = {0};
	for(int i = 0; i < g.bmpInfoHead.biHeight; i++)
		for (int j = 0; j < g.bmpInfoHead.biWidth; j++){
			BYTE t = g.px[i][j];
			if(t < g.palette.count){
				c[g.palette.color[t].R]++;
				s++;
			}
		}
	for(int i = 1; i < 256; i++) c[i] = c[i] + c[i-1]; //sum of pr function
	for(int i = 0; i < 256; i++) c[i] = (c[i] * 255 + s / 2) / s; // give new color
	for(int i = 0; i < g.palette.count; i++){ //rewrite file head palette
		g.palette.color[i].B = c[g.palette.color[i].R];
		g.palette.color[i].G = c[g.palette.color[i].R];
		g.palette.color[i].R = c[g.palette.color[i].R];
	}
	char ef[17]; //attach "-eq" at the end of file name
	for(int i = 0, j = 0; (ef[i] = file[j]) != '\0'; i++, j++)
		if(ef[i] == '.') {ef[i++] = '_'; ef[i++] = 'e'; ef[i++] = 'q'; ef[i] = '.';}
	g.writeFile(ef);
}

int main(){
	for(int i = 0; i < 14; i++)
		eql(files[i]);
	return 0;
}
