# software_by_gonglei
第一次作业
因为直接按照课件的指示来完成实验所以避免了课件上的问题的发生，但是还是出现了一个错误，缺少"kernel32.lib"文件，百度之后，将 C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib 中的该文件复制到VC2010相应位置中就行了。


第二次作业
作业1
这次作业与上次作业有一定关系，所以也用了上一次实验的代码，再结合这次课件的代码，完成了这次实验。
在过程中也遇到了一些问题，因为不了解相关代码的含义，所输出的图片和原图片相同，检查代码后发现，错误原因是我先输出了红色区域后输出原图片，所以我更改了顺序，先输出原图，在更改颜色

作业2
这个与上一个原理一样，但是黑色与白色与三个通道都相关，所以要读取三个通道的值，白色RGB（255,255,255），黑色RGB（0，0,0）
但是因为我定义了两个buffertmp,一个存储原图时使用，一个存储原图，一个存储指定区域，因为过程中弄错了变量，所以导致不能得到黑色与白色，修改后就行了
