#include "bmp256.cpp"

char files[14][14] = {"citywall.bmp", "citywall1.bmp", "citywall2.bmp",
					  "elain.bmp", "elain1.bmp", "elain2.bmp", "elain3.bmp",
					  "lena.bmp", "lena1.bmp", "lena2.bmp", "lena4.bmp",
					  "woman.bmp", "woman1.bmp", "woman2.bmp"};
					  
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
	feql(files[0], files[1]); //citywall
	feql(files[0], files[2]);
	feql(files[3], files[4]); //elain
	feql(files[3], files[5]);
	feql(files[3], files[6]); 
	feql(files[7], files[8]); //lena
	feql(files[7], files[9]);
	feql(files[7], files[10]);
	feql(files[11], files[12]); //woman
	feql(files[11], files[13]);
	return 0;
}
