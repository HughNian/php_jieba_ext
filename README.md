php exteion jieba
=================

jieba中文分词,PHP扩展
=====================

## Introduction
此扩展是基于cppjieba中文分词,更多关于cppjieba可查看其github主页,https://github.com/yanyiwu/cppjieba

### 依赖软件
*g++ (version >=4.1 recommended) or clang++;
### 下载和编译
和一遍编译PHP的扩展一致,只是需要把字典文件放在程序可以找到的位置
phpize
./configure --with-php-config=你的php-config目录
make
sudo make install

##扩展信息页面
![phpinfo](https://raw.githubusercontent.com/HughNian/php_jieba_ext/master/jieba.png)

##使用
```php
<?php
$str = "万万没想到,啦啦啦啦";
$fenci = jieba_cut($str);
echo $fenci; //output 万万/没想到/,/啦/啦/啦/啦
```
:smile::clap:
##结果实例
```
我来到北京清华大学
我/来到/北京/清华大学

他来到了网易杭研大厦
他/来到/了/网易/杭/研/大厦

小明硕士毕业于中国科学院计算所，后在日本京都大学深造
小/明/硕士/毕业/于/中国科学院/计算所/，/后/在/日本京都大学/深造
```

##鸣谢
:beers:
*"cppjieba"作者：yanyiwu https://github.com/yanyiwu i@yanyiwu.com
*"结巴"中文分词作者：SunJunyi https://github.com/fxsjy/jieba
