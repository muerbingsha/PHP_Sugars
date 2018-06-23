
看了网上的一些文章，有些借鉴，但和我实际操作还是有些出入，我在php版7.1.14， mac机，源码php7.1.18，测试成功。

 

A——1）进入源码ext文件夹

./ext_skel –extname=deng

A——2）修改config.m4

去掉这三个dnl注释

PHP_ARG_ENABLE(deng, whether to enable deng support,

Make sure that the comment is aligned:

[  –enable-deng           Enable deng support])

A——3）命令行输入phpize，编程php模块

./configure

make

make install

没错误的话，会提示在某地址生成.so模块文件

至此，模块生成。

A——4）加载模块

修改php.ini，php.ini地址有2个

/etc/php.ini 修改无效

/usr/local/etc/php.ini 修改有效

加入extension = deng.so

命令行输入php -m查看所有模块

在源码文件夹有/ext/deng/deng.php

执行php deng.php可以看模块支持函数

A——5）测试，

没有任何外部函数，只有一个内置confirm_deng_compiled(“okok”);

命令行下能成功输出，网页不行。
