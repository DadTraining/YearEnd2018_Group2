LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
				   $(LOCAL_PATH)/../../../Classes/Constants.cpp \
				   $(LOCAL_PATH)/../../../Classes/MyBodyParser.cpp \
				   $(LOCAL_PATH)/../../../Classes/sqlite3.c \
				   $(LOCAL_PATH)/../../../Classes/DbContext.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/Model.cpp \
				   $(LOCAL_PATH)/../../../Classes/SkinGame.cpp \
				   $(LOCAL_PATH)/../../../Classes/InfoMap.cpp \
				   $(LOCAL_PATH)/../../../Classes/Popup.cpp \
				   $(LOCAL_PATH)/../../../Classes/PopUpShop.cpp \
				   $(LOCAL_PATH)/../../../Classes/PopUpEndGame.cpp \
				   $(LOCAL_PATH)/../../../Classes/PopUpLoseGame.cpp \
				   $(LOCAL_PATH)/../../../Classes/PopupPause.cpp \
				   $(LOCAL_PATH)/../../../Classes/PopUpPlay.cpp \
				   $(LOCAL_PATH)/../../../Classes/PopUpSetting.cpp \
				   $(LOCAL_PATH)/../../../Classes/MapLevel.cpp \
				   $(LOCAL_PATH)/../../../Classes/Ship.cpp \
				   $(LOCAL_PATH)/../../../Classes/Meat.cpp \
				   $(LOCAL_PATH)/../../../Classes/Cable.cpp \
				   $(LOCAL_PATH)/../../../Classes/Bullet.cpp \
				   $(LOCAL_PATH)/../../../Classes/Shark.cpp \
				   $(LOCAL_PATH)/../../../Classes/Item.cpp \
				   $(LOCAL_PATH)/../../../Classes/IntroScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/ShopScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/MapScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamePlayScene.cpp
				   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
