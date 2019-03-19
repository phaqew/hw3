#include "bmp256.cpp"

int main(){
	BMP256 g1("elain.bmp");
	for(int i = 0; i < 256; i++)
		if(g1.palette.color[i].R < 178){
			g1.palette.color[i].R = 0;
			g1.palette.color[i].G = 0;
			g1.palette.color[i].B = 0;
		}
		else{
			g1.palette.color[i].R = 255;
			g1.palette.color[i].G = 255;
			g1.palette.color[i].B = 255;
		}
	g1.writeFile("elain_.bmp");
	BMP256 g2("woman.bmp");
	for(int i = 0; i < 256; i++)
		if(g2.palette.color[i].R < 86){
			g2.palette.color[i].R = 0;
			g2.palette.color[i].G = 0;
			g2.palette.color[i].B = 0;
		}
		else{
			g2.palette.color[i].R = 255;
			g2.palette.color[i].G = 255;
			g2.palette.color[i].B = 255;
		}
	g2.writeFile("woman_.bmp");
	return 0;
}
