# GR-CITRUSで手書き数字認識

WIP

手書き数字認識のサンプルプログラムです。
[e-AIトランスレータ チュートリアル](http://gadget.renesas.com/ja/product/e-ai/mnist_tutorial.html)を動かしてみました。

## 部品表
|部品|数|備考|
|---|--|--|
|GR-CITRUS|1| |
|タッチスクリーン|1| |
|抵抗 100kΩ|4|X+,Y+,X-,Y-とGNDの間に接続します。（プルダウン抵抗）|

## 接続方法
|タッチスクリーン|GR-CITRUS|
|-----------|---------|
|X+ | A3(17) |
|Y+ | A2(16) |
|X- | A1(15) |
|Y- | A0(14) |

## 使い方
ソースコード内のTOUCH_SCREEN_MIN_X、TOUCH_SCREEN_MIN_Y、TOUCH_SCREEN_MAX_X、TOUCH_SCREEN_MAX_Yはタッチスクリーンに合わせて設定する必要があります。
数字（0〜9）を手書きで書くと、認識されます。
