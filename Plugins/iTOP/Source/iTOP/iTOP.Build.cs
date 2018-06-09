// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class iTOP : ModuleRules
{
	public iTOP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"iTOP/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"iTOP/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Json",
                "JsonUtilities"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore" 
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		//add itop
		if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
            string pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
            string aplPath = pluginPath + "\\iTOPAndroid_APL.xml";
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", aplPath));
            System.Console.WriteLine("aplPath = " + aplPath);
        }  else if (Target.Platform == UnrealTargetPlatform.IOS) {
		            System.Console.WriteLine("--------------Add iOS IMSDK");
            		//IMSDK
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKCoreKit", "../lib/iOS/C11/IMSDKCoreKit.embeddedframework.zip", "IMSDKAppSetting.bundle"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKFriendFacebook", "../lib/iOS/C11/IMSDKFriendFacebook.embeddedframework.zip", ""));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKLoginFacebook",   "../lib/iOS/C11/IMSDKLoginFacebook.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKLoginGameCenter",   "../lib/iOS/C11/IMSDKLoginGameCenter.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKNotice",   "../lib/iOS/C11/IMSDKNotice.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKPushXG",   "../lib/iOS/C11/IMSDKPushXG.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKStatAdjust",   "../lib/iOS/C11/IMSDKStatAdjust.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKStatBugly",   "../lib/iOS/C11/IMSDKStatBugly.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKStatBeacon",   "../lib/iOS/C11/IMSDKStatBeacon.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKExtendTool",   "../lib/iOS/C11/IMSDKExtendTool.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKWebView",   "../lib/iOS/C11/IMSDKWebView.embeddedframework.zip", "IMSDKWebViewResource.bundle"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKStatFacebook",   "../lib/iOS/C11/IMSDKStatFacebook.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKFriendTwitter",   "../lib/iOS/C11/IMSDKFriendTwitter.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKStatFirebase",   "../lib/iOS/C11/IMSDKStatFirebase.embeddedframework.zip", "GoogleService-Info.plist"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKLoginWeChat",   "../lib/iOS/C11/IMSDKLoginWeChat.embeddedframework.zip" ));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKFriendWeChat",   "../lib/iOS/C11/IMSDKFriendWeChat.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKLoginTwitter",   "../lib/iOS/C11/IMSDKLoginTwitter.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("IMSDKVK",   "../lib/iOS/C11/IMSDKVK.embeddedframework.zip"));

			//FB
			PublicAdditionalFrameworks.Add(new UEBuildFramework("Bolts", "../lib/iOS/Third/Bolts.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FBSDKCoreKit", "../lib/iOS/Third/FBSDKCoreKit.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FBSDKLoginKit", "../lib/iOS/Third/FBSDKLoginKit.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FBSDKMessengerShareKit", "../lib/iOS/Third/FBSDKMessengerShareKit.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FBSDKShareKit", "../lib/iOS/Third/FBSDKShareKit.embeddedframework.zip"));

			PublicAdditionalFrameworks.Add(new UEBuildFramework("AdjustSdk", "../lib/iOS/Third/AdjustSdk.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("Bugly", "../lib/iOS/Third/Bugly.embeddedframework.zip"));

			PublicAdditionalFrameworks.Add(new UEBuildFramework("BeaconAPI_Base", "../lib/iOS/Third/Beacon_2.4.2/BeaconAPI_Base.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("BeaconAPI_Log", "../lib/iOS/Third/Beacon_2.4.2/BeaconAPI_Log.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("BeaconAPI_Speed", "../lib/iOS/Third/Beacon_2.4.2/BeaconAPI_Speed.embeddedframework.zip"));

			PublicAdditionalFrameworks.Add(new UEBuildFramework("TwitterCore", "../lib/iOS/Third/TwitterKit_3.1.0/TwitterCore.embeddedframework.zip", "TwitterShareExtensionUIResources.bundle"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("TwitterKit", "../lib/iOS/Third/TwitterKit_3.1.0/TwitterKit.embeddedframework.zip", "TwitterKitResources.bundle"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("VKSdkFramework", "../lib/iOS/Third/VK_1.4.6/VKSdkFramework.embeddedframework.zip", "VKSdkResources.bundle"));

			//Firebase
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FirebaseAnalytics", "../lib/iOS/Third/Firebase/FirebaseAnalytics.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FirebaseCore", "../lib/iOS/Third/Firebase/FirebaseCore.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FirebaseCoreDiagnostics", "../lib/iOS/Third/Firebase/FirebaseCoreDiagnostics.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FirebaseInstanceID", "../lib/iOS/Third/Firebase/FirebaseInstanceID.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("FirebaseNanoPB", "../lib/iOS/Third/Firebase/FirebaseNanoPB.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("GoogleToolboxForMac", "../lib/iOS/Third/Firebase/GoogleToolboxForMac.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new UEBuildFramework("nanopb", "../lib/iOS/Third/Firebase/nanopb.embeddedframework.zip"));

			var libPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../lib/iOS" ));
			PublicAdditionalLibraries.Add(Path.Combine(libPath, "Third/XG_2.5.0/libXG-SDK.a"));

			PublicAdditionalLibraries.Add(Path.Combine(libPath, "Third/Bugly_2.4.8/BuglyBridge/libBuglyBridge.a"));
			PublicAdditionalLibraries.Add(Path.Combine(libPath, "Third/WeChat_1.8.2/libWeChatSDK.a"));
			//system
			PublicFrameworks.AddRange( 
					new string[] 
					{
						"Security",
						"AdSupport",
						"CoreGraphics",
						"CoreLocation",
						"CoreTelephony",
						"EventKit",
						"EventKitUI",
						"Foundation",
						"MediaPlayer",
						"QuartzCore",
						"StoreKit",
						"SystemConfiguration",
						"UIKit",
						"AudioToolbox",
						"AVFoundation",
						"iAd",
						"MessageUI",
						"MobileCoreServices",
						"Social",
						"GameKit",
						"MobileCoreServices",
						"Metal",
						"CoreText",
						"CFNetwork",
						"CoreMedia",
						"CoreMotion",
						"CoreVideo",
						"OpenAL",
						"OpenGLES",
						"UserNotifications",
						"WebKit",
						"SafariServices"
					}
				);
			PublicAdditionalLibraries.AddRange(
				new string[] { "stdc++.6.0.9","z","c++","z.1.1.3","sqlite3","xml2"}
				);
		}
	}
}
