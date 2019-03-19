#include "bmp256.cpp"

char files[14][14] = {"citywall.bmp", "citywall1.bmp", "citywall2.bmp",
					  "elain.bmp", "elain1.bmp", "elain2.bmp", "elain3.bmp",
					  "lena.bmp", "lena1.bmp", "lena2.bmp", "lena4.bmp",
					  "woman.bmp", "woman1.bmp", "woman2.bmp"};
void stat(int *c, char *file){
	for(int i = 0; i < 256; i++) c[i] = 0;
	BMP256 bmp(file);
	for(int i = 0; i < bmp.bmpInfoHead.biHeight; i++){
		for (int j = 0; j < bmp.bmpInfoHead.biWidth; j++){
			int t = bmp.px[i][j];
			if(t < bmp.palette.count) c[bmp.palette.color[t].R]++;// same for r, g or b
			//else c[255]++;
		}
	}
	c[256] = bmp.bmpInfoHead.biHeight * bmp.bmpInfoHead.biWidth;
}

int main(){
	int c[257];
	for(int d = 0; d < 14; d++){
		stat(c, files[d]);
		BMP256 n(256, 256);
		for(int i = 0; i < 256; i++){
			int q = (int)((float)c[i]/(float)c[256]*5000.0);
			if(q > 256) q = 256;
			for(int j = 0; j < q; j++){
				n.px[j][i] = 255;
			}
		}
		char t[18] = "_hg_";
		for(int i = 0; i < 14; i++) t[i + 3] = files[d][i];
		n.writeFile(t);
	}	
	/*//output a .csv chart
	int **c;
	c = new int*[14];
	for(int i = 0; i < 14; i++){
		c[i] = new int[257]; //store sum in the last one
		stat(c[i], files[i]);
	}
	std::ofstream out("stat.csv", std::ios::out);
	for(int i = 0; i < 14; i++) out << files[i] << ",";
	out << "\n";
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 14; j++){
			out << (float)c[j][i] / (float)c[j][256] << ",";
		}
		out << "\n";
	}
	out.close();
	*/
	return 0;
}
