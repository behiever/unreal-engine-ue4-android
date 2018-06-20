# ue4androiddemo
## 一、 概述
UE4是类似于Unity的新一代游戏开发平台，提高PC端，移动端接入功能，采用C++语言开发。 
这是一个ue4的android版本demo,内有调用facebook渠道登陆的例子，采用了插件化的设计结构，旨在告诉大家一个ue4-android工程的正常目录结构。让大家少走弯路。

## 二、UE4工程配置说明  
### 2.1 目录介绍
+ Binaries - 编译文件等。
+ Intermediate - 构建引擎或者游戏的中间文件. 可删除重新编译生成。
+ iTOP.uplugin - 插件信息说明
 
+ Source/iTOPSample - demo的源代码
       - Private - cpp实现
       - Public - .h头文件
       - iTOP.Build.cs - 加载各类SDK/Framework的配置脚本
       - iTOPAndroid_APL.xml - 加载各类SDK/Framework的配置脚本
+ Plugins/iTOP - 配合Source使用的插件目录，可以抽离出去给其他工程调用
+ Plugins/iTOP/Resources - 插件图标资源 
+ Plugins/iTOP/iTOP - APL文件，包含了android的各类manifest配置及c++调用java的jni代码
+ Plugins/iTOP/lib - 用来放各种jar包及res

### 2.2 iTOP中的配置说明
+ 修改GameId等配置
  - Android: iTOPAndroid_APL.xml
  
> iTOPAndroid_APL.xml文件是Android平台需要的一个重要的文件，对ITOP SDK相关配置，依赖的修改，添加，可以在iTOPAndroid_APL.xml文件中进行修改。
	   
### 2.3 接入插件
+ 在项目工程配置文件`xx.Build.cs`添加插件引用(例如我们当前的插件目录为plugins/iTOP),所以插件导入的地方写iTOP即可

	```
	public class iTOPSample : ModuleRules
	{
		public iTOPSample(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
			PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","Json", "JsonUtilities" }); 
	
			PrivateDependencyModuleNames.AddRange(new string[] { "iTOP" });//添加iTop的UE4插件
		}
	}
	```

### 三、调用插件  
    首先你要学会c++如何调用蓝图，学会了以后查看iTOPWidget.cpp(和蓝图对应的demo类)里有对应的Jni代码实现</br>
    
![image](https://github.com/ShibinHuang/HomeAnimationImageView/blob/master/ezgif-5-710f8d46fe.gif)
    
