#include "bmp256.cpp"
#include "segTreeC.cpp"

void lhe(const char *file, int z){
	BMP256 g(file);
	BMP256 n(&g);
	segTreeC t(256);
	float r = 255.0 / (float)z / (float)z;
	for(int y = z / 2; y < g.bmpInfoHead.biHeight - z / 2 - 1; y++){
		t.clr(); //initial segtree for a row
		for(int i = y - z / 2; i <= y + z / 2; i++)
			for(int j = 0; j < z; j++) t.inc(g.px[i][j]);
		n.px[y][z / 2] = (int)(r * (float)t.sum(g.px[y][z / 2]));	
		for(int x = 1 + z / 2; x < g.bmpInfoHead.biWidth - z / 2 - 1; x++){
			for(int i = y - z / 2; i <= y + z / 2; i++){
				t.inc(g.px[i][x + z / 2]); //adjust segtree
				t.dec(g.px[i][x - z / 2 - 1]);
			}
			n.px[y][x] = (int)(r * (float)t.sum(g.px[y][x])); //assign color
		}
	}
	char f[15] = "_lhe_";
	for(int i = 0; i < 10; i++) f[5 + i] = file[i];
	n.writeFile(f);
}



void feql(char *rfile, char *file){ //refrence and target file
	BMP256 r(rfile);
	BMP256 g(file); // assume they are the same large
	int f[256] = {0}, c[256] = {0};
	for(int i = 0; i < g.bmpInfoHead.biHeight; i++)
		for (int j = 0; j < g.bmpInfoHead.biWidth; j++){
			f[r.palette.color[r.px[i][j]].R]++; //function of refrence
			BYTE t = g.px[i][j];
			if(t < g.palette.count) c[g.palette.color[t].R]++;
			else c[255]++; //replace undefined pixels with white
		}
	int m[256], sf = f[0], sc = 0; //magic
	for(int i = 0, j = 0; i < 256; i++){
		while(sc > sf) sf += f[++j];
		m[i] = j;
		sc += c[i];
	}
	for(int i = 0; i < g.palette.count; i++){ //rewrite file head palette
		g.palette.color[i].B = m[g.palette.color[i].R];
		g.palette.color[i].G = m[g.palette.color[i].R];
		g.palette.color[i].R = m[g.palette.color[i].R];
	}
	char ef[17]; //attach "_eq" at the end of file name
	for(int i = 0, j = 0; (ef[i] = file[j]) != '\0'; i++, j++)
		if(ef[i] == '.') {ef[i++] = '_'; ef[i++] = 'e'; ef[i++] = 'q'; ef[i] = '.';}
	g.writeFile(ef);
}

int main(){
	lhe("elain.bmp", 7);
	lhe("lena.bmp", 7);
	return 0;
}
