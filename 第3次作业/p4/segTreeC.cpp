class segTreeC { //special segment tree for counting
	private:
		int m;
		int *n;
	public:
		segTreeC(int mm): m(mm) {
			n = new int[m + 1];
			for(int i = 0; i <= m; i++) n[i] = 0;
		}
		~segTreeC() {
			delete[] n;
		}
		void clr(){
			for(int i = 0; i <= m; i++) n[i] = 0;
		}
		void inc(int p) {
			n[++p]++;
			for(int t = 1; p < m; t <<= 1)
				if(p & t) n[p += t]++;
		}
		void dec(int p) {
			n[++p]--;
			for(int t = 1; p < m; t <<= 1)
				if(p & t) n[p += t]--;
		}
		int sum(int p) {
			int s = 0;
			for(int t = 0; p > 0; t++, p >>= 1)
				if(p & 1) s += n[p << t];
			return s;
		}
};
/*//example
int main() {
	segTreeC st(256);
	st.inc(34);
	st.dec(157);
	st.inc(233);
	for(int i = 1; i <= 256; i++) cout << i << "\t" << st.sum(i) << "\n";
	return 0;
}
*/
