#第三次作业

###自动化少61 何奈特 2140506114

---

##题目一

>画出所有附件图像的直方图

* 所有图像都是BMP格式，256色位图。但是其中几个颜色不足256种，体现在文件头的bmpInfoHead.biClrUsed中，其缺省（=0）表示图片调色板给足了256色，其为0~255的数意为调色板中只有这么多种颜色。
* 对于上述的不足色文件，后面的数据可能会出现未定义颜色（像素字节值超过了biClrUsed）。Windows照片查看器等软件按黑色（00000000）显示处理，Photoshop等软件按白色（00FFFFFF）显示处理。**本题中我将其全部忽略**，这样画出的直方图更“好看”。
* 延续上次的传统，这次作业继续使用C++。对上次的BMP256类需要稍作修改，在BMP256::Palette中添加了成员变量count表示颜色个数，并增补了一些Palette的读写操作。
* 最初打算输出.csv用Excel画图，后来改为自行输出直方图文件。结果都是256*256的黑白图片，从左到右每列对应灰度0~255，每列上白条的高度反映了该灰度像素数的多少。（占总数的比例乘以5000取整，总数不含未定义颜色，详见p1\p1.cpp）

名称|图片|直方图
--|--|--
citywall|![](p1\citywall.bmp)|![](p1\_hg_citywall.bmp)
citywall1|![](p1\citywall1.bmp)|![](p1\_hg_citywall1.bmp)
citywall2|![](p1\citywall2.bmp)|![](p1\_hg_citywall2.bmp)
elain|![](p1\elain.bmp)|![](p1\_hg_elain.bmp)
elain1|![](p1\elain1.bmp)|![](p1\_hg_elain1.bmp)
elain2|![](p1\elain2.bmp)|![](p1\_hg_elain2.bmp)
elain3|![](p1\elain3.bmp)|![](p1\_hg_elain3.bmp)
lena|![](p1\lena.bmp)|![](p1\_hg_lena.bmp)
lena1|![](p1\lena1.bmp)|![](p1\_hg_lena1.bmp)
lena2|![](p1\lena2.bmp)|![](p1\_hg_lena2.bmp)
lena4|![](p1\lena4.bmp)|![](p1\_hg_lena4.bmp)
woman|![](p1\woman.bmp)|![](p1\_hg_woman.bmp)
woman1|![](p1\woman1.bmp)|![](p1\_hg_woman1.bmp)
woman2|![](p1\woman2.bmp)|![](p1\_hg_woman2.bmp)

##题目二

>把所有图像进行直方图均衡

* 和上题一样，**这里忽略所有未定义颜色的像素**（也不计入总数），这样做出的直方图均衡效果略好。
* 直方图均衡算法很简便，只要将每个灰度值改成（四舍五入）
$$255 * (所有小于该灰度值的像素数 / 像素总数)$$
* 实现时先读入原始灰度直方图，得到上述的映射，再直接修改原图的调色板即可。详见p2\p2.cpp中的eql函数。
* 将前题的代码搬了过来以输出修改前后的直方图。

名称|原图片|均衡后图片|原直方图|均衡后直方图
--|--|--|--|--
citywall|![](p2\citywall.bmp)|![](p2\citywall_eq.bmp)|![](p2\_hg_citywall.bmp)|![](p2\_hg_citywall_eq.bmp)
citywall1|![](p2\citywall1.bmp)|![](p2\citywall1_eq.bmp)|![](p2\_hg_citywall1.bmp)|![](p2\_hg_citywall1_eq.bmp)
citywall2|![](p2\citywall2.bmp)|![](p2\citywall2_eq.bmp)|![](p2\_hg_citywall2.bmp)|![](p2\_hg_citywall1_eq.bmp)
elain|![](p2\elain.bmp)|![](p2\elain_eq.bmp)|![](p2\_hg_elain.bmp)|![](p2\_hg_elain_eq.bmp)
elain1|![](p2\elain1.bmp)|![](p2\elain1_eq.bmp)|![](p2\_hg_elain1.bmp)|![](p2\_hg_elain1_eq.bmp)
elain2|![](p2\elain2.bmp)|![](p2\elain2_eq.bmp)|![](p2\_hg_elain2.bmp)|![](p2\_hg_elain2_eq.bmp)
elain3|![](p2\elain3.bmp)|![](p2\elain3_eq.bmp)|![](p2\_hg_elain3.bmp)|![](p2\_hg_elain3_eq.bmp)
lena|![](p2\lena.bmp)|![](p2\lena_eq.bmp)|![](p2\_hg_lena.bmp)|![](p2\_hg_lena_eq.bmp)
lena1|![](p2\lena1.bmp)|![](p2\lena1_eq.bmp)|![](p2\_hg_lena1.bmp)|![](p2\_hg_lena1_eq.bmp)
lena2|![](p2\lena2.bmp)|![](p2\lena2_eq.bmp)|![](p2\_hg_lena2.bmp)|![](p2\_hg_lena2_eq.bmp)
lena4|![](p2\lena4.bmp)|![](p2\lena4_eq.bmp)|![](p2\_hg_lena4.bmp)|![](p2\_hg_lena4_eq.bmp)
woman|![](p2\woman.bmp)|![](p2\woman_eq.bmp)|![](p2\_hg_woman.bmp)|![](p2\_hg_woman_eq.bmp)
woman1|![](p2\woman1.bmp)|![](p2\woman1_eq.bmp)|![](p2\_hg_woman1.bmp)|![](p2\_hg_woman1_eq.bmp)
woman2|![](p2\woman2.bmp)|![](p2\woman2_eq.bmp)|![](p2\_hg_woman2.bmp)|![](p2\_hg_woman2_eq.bmp)

* 可以从直方图中看出，对于citywall1、citywall2、elain3、lena2这几幅图来说，灰度差被拉开，对比度增强比较明显。

##题目三

>按照对源图像直方图进行直方图匹配

* **本题中将未定义颜色视为白色**（00FFFFFF），这样得到的效果贴近原图。
* 前一题的*直方图均衡*可以看做是对**均匀分布**做*直方图匹配*，可以看成有另一个数组，其所有值都是像素总数/256（均匀分布），将图片灰度的序列和对应于这个数组的求和，这样去进行匹配。
* 对于非均匀分布同理，拿到给定的直方图，把它的序列和拿去对应目标图片灰度的序列和，求出映射关系，这里是核心代码：（详见p3\p3.cpp的feql函数）
*注：给定直方图存储于f[256]中，目标图片直方图存储于c[256]中*
```
int m[256], sf = f[0], sc = 0; //m:映射关系, sf:f的和, sc:c的和
for(int i = 0, j = 0; i < 256; i++){ //i递进
	while(sc > sf) sf += f[++j]; //j递进
	m[i] = j; //c[]中的第i个对应于f[]中的第j个
	sc += c[i];
}
```
* 接下来将目标图片调色板中所有的灰度k修改为m[k]即可。

名称|原图片|均衡后图片|原直方图|均衡后直方图
--|--|--|--|--
citywall|![](p3\citywall.bmp)| |![](p3\_hg_citywall.bmp)| 
citywall1|![](p3\citywall1.bmp)|![](p3\citywall1_eq.bmp)|![](p3\_hg_citywall1.bmp)|![](p3\_hg_citywall1_eq.bmp)
citywall2|![](p3\citywall2.bmp)|![](p3\citywall2_eq.bmp)|![](p3\_hg_citywall2.bmp)|![](p3\_hg_citywall1_eq.bmp)
elain|![](p3\elain.bmp)| |![](p3\_hg_elain.bmp)| 
elain1|![](p3\elain1.bmp)|![](p3\elain1_eq.bmp)|![](p3\_hg_elain1.bmp)|![](p3\_hg_elain1_eq.bmp)
elain2|![](p3\elain2.bmp)|![](p3\elain2_eq.bmp)|![](p3\_hg_elain2.bmp)|![](p3\_hg_elain2_eq.bmp)
elain3|![](p3\elain3.bmp)|![](p3\elain3_eq.bmp)|![](p3\_hg_elain3.bmp)|![](p3\_hg_elain3_eq.bmp)
lena|![](p3\lena.bmp)| |![](p3\_hg_lena.bmp)| 
lena1|![](p3\lena1.bmp)|![](p3\lena1_eq.bmp)|![](p3\_hg_lena1.bmp)|![](p3\_hg_lena1_eq.bmp)
lena2|![](p3\lena2.bmp)|![](p3\lena2_eq.bmp)|![](p3\_hg_lena2.bmp)|![](p3\_hg_lena2_eq.bmp)
lena4|![](p3\lena4.bmp)|![](p3\lena4_eq.bmp)|![](p3\_hg_lena4.bmp)|![](p3\_hg_lena4_eq.bmp)
woman|![](p3\woman.bmp)| |![](p3\_hg_woman.bmp)| 
woman1|![](p3\woman1.bmp)|![](p3\woman1_eq.bmp)|![](p3\_hg_woman1.bmp)|![](p3\_hg_woman1_eq.bmp)
woman2|![](p3\woman2.bmp)|![](p3\woman2_eq.bmp)|![](p3\_hg_woman2.bmp)|![](p3\_hg_woman2_eq.bmp)

* 可以看出，每个图片的直方图都匹配到了源图像的形状（当然那些“*未定义颜色*”的部分都丢失了）。

##题目四

>对elain和lena图像进行7*7的局部直方图均衡

* **边缘不作处理！**默认留黑边。（因为懒）
* 与前面的直方图均衡一样，求出邻域中所有灰度小于中心点灰度的像素个数，乘255除49，即可求出应给中心点分配的新灰度值。
* 局部直方图均衡计算量大，可以优化加速。首先，每个像素与和它相邻的像素的7*7邻域只有7个像素的区别，可以递推减少计算量。
* 这里设计了一个长度为256的**线段树**（详见p4\segTreeC.cpp），对其插入和求和复杂度都是log(256)（不会随邻域大小变化）。利用它存放7*7邻域的所有像素灰度值，每次可以快速计算灰度小于中点像素的个数，以及递推到相邻点的邻域。哪怕邻域大至31*31也可以秒出结果。

名称|原图片|局部直方图处理后
--|--|--
elain|![](p4\elain.bmp)|![](p4\_lhe_elain.bmp)
lena|![](p4\lena.bmp)|![](p4\_lhe_lena.bmp)

##题目五

>利用直方图对图像elain和woman进行分割

* 题意不明，原图的直方图并没有明显分界。这里勉强给出结果：

名称|分割后图片
--|--
elain|![](p5\elain.bmp)|![](p5\elain_.bmp)
woman|![](p5\woman.bmp)|![](p5\woman_.bmp)