
git rm -r UIKit
git rm -r Cocos
git rm -r Quartz
cp -R /c/Users/dura/Documents/cocos2d-1.0.1-x-0.10.0/HelloWorld/Classes/UIKit \
   UIKit
cp -R /c/Users/dura/Documents/cocos2d-1.0.1-x-0.10.0/HelloWorld/Classes/Cocos \
   Cocos
cp -R /c/Users/dura/Documents/cocos2d-1.0.1-x-0.10.0/HelloWorld/Classes/Quartz \
   Quartz
sh water_mark.sh
sh commit_push.sh
