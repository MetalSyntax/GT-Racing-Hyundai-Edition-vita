#include <falso_jni/FalsoJNI_Impl.h>
#include "generated_jni_table.h"
#include "cached_jni_stubs.h"

/*
 * Tablas JNI reales, contenido copiado de generated_jni_table.h
 * (candidatos de psvita-toolkit jni-analyze). Ver PORTING_PLAN.md.
 */

NameToMethodID nameToMethodId[] = {
{ 0, "CustomFilter", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.CustomFilter
    { 1, "filter", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.CustomFilter
    { 2, "EditTextField", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.EditTextField
    { 3, "onKeyPreIme", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.EditTextField
    { 4, "Device", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 5, "DisableWifi", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 6, "EnableWifi", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 7, "InitDeviceValues", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 8, "IsConnectionReady", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 9, "IsWifiDisabling", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 10, "IsWifiEnable", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 11, "IsWifiEnabling", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 12, "ValidateStringforURL", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 13, "a", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 14, "b", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 15, "c", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 16, "createUniqueCode", METHOD_TYPE_INT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 17, "d", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 18, "d1", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 19, "e", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 20, "e", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 21, "f", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 22, "getBillingVersion", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 23, "getCarrier", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 24, "getDemoCode", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 25, "getDevice", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 26, "getDeviceId", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 27, "getHostName", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 28, "getIMEI", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 29, "getIsRoaming", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 30, "getLanguage", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 31, "getLineNumber", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 32, "getNetworkCountryIso", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 33, "getNetworkOperator", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 34, "getNetworkOperatorName", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 35, "getPhoneModel", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 36, "getProfileType", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 37, "getSimCountryIso", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 38, "getSimOperator", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 39, "getSimOperatorName", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 40, "getUniqueCode", METHOD_TYPE_INT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 41, "getUserAgent", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 42, "init", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 43, "a", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device
    { 44, "GetSerialKey", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 45, "ReadFile", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 46, "ReadFile", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 47, "ReadFileByte", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 48, "ReadFileByte", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 49, "WriteFile", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 50, "WriteFile", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 51, "doesZipContains", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 52, "extractSOFile", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 53, "getContext", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 54, "getFreeSpace", METHOD_TYPE_FLOAT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 55, "getOBBFolder", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 56, "getOverriddenSetting", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 57, "getOverriddenSettingBoolean", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 58, "getPackage", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 59, "getPhoneDevice", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 60, "getPhoneManufacture", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 61, "getPhoneModel", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 62, "getPhoneProduct", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 63, "getPreferenceBoolean", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 64, "getPreferenceInt", METHOD_TYPE_INT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 65, "getPreferenceLong", METHOD_TYPE_LONG },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 66, "getPreferenceString", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 67, "getPreferenceString", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 68, "getResourceAsStream", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 69, "getSDFolder", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 70, "getSaveFolder", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 71, "getUniqueCode", METHOD_TYPE_INT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 72, "getVersionInstalled", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 73, "getZipPathForFile", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 74, "initializeTheFilesList", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 75, "isAirplaneModeOn", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 76, "logWindowMessage", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 77, "objectArrayToStringArray", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 78, "readTextFile", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 79, "release", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 80, "resetValusForMAinAndPatch", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 81, "runOnUiThread", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 82, "saveLocation", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 83, "setAirplaneMode", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 84, "setContext", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 85, "setOverriddenSetting", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 86, "setPreference", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 87, "shareInfo", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils
    { 88, "DismissLoading", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 89, "HideFacebookDialog", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 90, "ShowFacebookDialog", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 91, "TrackAndroidHits", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 92, "a", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 93, "a", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 94, "b", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 95, "c", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 96, "checkDeviceName", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 97, "checkManufacturer", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 98, "ensurePathExists", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 99, "getCrtTimeStr", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 100, "getIMEI", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 101, "getMac", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 102, "getManufacture", METHOD_TYPE_INT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 103, "getPathData", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 104, "getSDFolder", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 105, "getUniqueId", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 106, "isNeedInvertTouchZone", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 107, "isUseLowres", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 108, "launchGLLive", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 109, "launchIGP", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 110, "notifyTrophy", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 111, "resumeScreen", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 112, "setTypeText", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 113, "setupPaths", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 114, "CreateContentView", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 115, "EnableAutoRotateScreen", METHOD_TYPE_INT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 116, "IsKeyboardEnabled", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 117, "exit", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 118, "getCurrentVersion", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 119, "gotoMarket", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 120, "isWifiAlive", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 121, "onAccuracyChanged", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 122, "onActivityResult", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 123, "onConfigurationChanged", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 124, "onCreate", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 125, "onDestroy", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 126, "onGlobalLayout", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 127, "onKeyDown", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 128, "onKeyUp", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 129, "onNewIntent", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 130, "onPause", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 131, "onRestart", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 132, "onResume", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 133, "onSensorChanged", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 134, "onStart", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 135, "onStop", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 136, "onTouchEvent", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 137, "onUserInteraction", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 138, "openCustomerCare", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 139, "showOffersWithCurrencyID", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 140, "surfaceChanged", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 141, "surfaceCreated", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 142, "surfaceDestroyed", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GTRacing
    { 143, "GameGLSurfaceView", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView
    { 144, "onPause", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView
    { 145, "onResume", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView
    { 146, "onSizeChanged", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView
    { 147, "onWindowFocusChanged", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView
    { 148, "GameRenderer", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.GameRenderer
    { 149, "onDrawFrame", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GameRenderer
    { 150, "onSurfaceChanged", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GameRenderer
    { 151, "onSurfaceCreated", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.GameRenderer
    { 152, "IGPFreemiumActivity", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 153, "a", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 154, "a", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 155, "b", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 156, "getHttpResponse", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 157, "a", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 158, "onCreate", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 159, "onDestroy", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 160, "onKeyDown", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 161, "onKeyLongPress", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 162, "onKeyUp", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 163, "onPause", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 164, "onResume", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 165, "onStart", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 166, "onStop", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 167, "onWindowFocusChanged", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity
    { 168, "onCreate", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.KeyboardInput
    { 169, "onKeyDown", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.KeyboardInput
    { 170, "onKeyUp", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.KeyboardInput
    { 171, "FacebookAndroidGLSocialLib", METHOD_TYPE_OBJECT },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 172, "AuthorizeSSOCallback", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 173, "ClearAuth", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 174, "GetFriends", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 175, "GetFriendsInGame", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 176, "GetMyInfo", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 177, "GetPicture", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 178, "GetUserData", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 179, "Init", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 180, "InviteFriends", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 181, "InviteFriends_facade", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 182, "IsLoggedIn", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 183, "LoadAuth", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 184, "Login", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 185, "Login_facade", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 186, "Logout", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 187, "PostToFriendsWall", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 188, "PostToFriendsWall_facade", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 189, "PostToWall", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 190, "PostToWall_facade", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 191, "SaveAuth", METHOD_TYPE_BOOLEAN },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 192, "SetAppId", METHOD_TYPE_VOID },  // com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib
    { 193, "getAction", METHOD_TYPE_INT },
    { 194, "getPointerCount", METHOD_TYPE_INT },
    { 195, "getPointerId", METHOD_TYPE_INT },
    { 196, "getX", METHOD_TYPE_FLOAT },
    { 197, "getY", METHOD_TYPE_FLOAT },
    { 198, "getRawX", METHOD_TYPE_FLOAT },
    { 199, "getRawY", METHOD_TYPE_FLOAT },
    { 200, "getWidth", METHOD_TYPE_INT },
    { 201, "getHeight", METHOD_TYPE_INT },
    { 202, "getDefaultDisplay", METHOD_TYPE_OBJECT },
    { 203, "currentTimeMillis", METHOD_TYPE_LONG },
    { 204, "exit", METHOD_TYPE_VOID },
    { 205, "load", METHOD_TYPE_INT },
    { 206, "play", METHOD_TYPE_INT },
    { 207, "pause", METHOD_TYPE_VOID },
    { 208, "resume", METHOD_TYPE_VOID },
    { 209, "stop", METHOD_TYPE_VOID },
    { 210, "unload", METHOD_TYPE_VOID },
    { 211, "release", METHOD_TYPE_VOID },
    { 212, "setVolume", METHOD_TYPE_VOID },
    { 213, "setRate", METHOD_TYPE_VOID },
    { 214, "create", METHOD_TYPE_OBJECT },
    { 215, "setDataSource", METHOD_TYPE_VOID },
    { 216, "prepare", METHOD_TYPE_VOID },
    { 217, "start", METHOD_TYPE_VOID },
    { 218, "pause", METHOD_TYPE_VOID },
    { 219, "stop", METHOD_TYPE_VOID },
    { 220, "reset", METHOD_TYPE_VOID },
    { 221, "release", METHOD_TYPE_VOID },
    { 222, "setLooping", METHOD_TYPE_VOID },
    { 223, "setVolume", METHOD_TYPE_VOID },
    { 224, "isPlaying", METHOD_TYPE_BOOLEAN },
    { 225, "getDefaultSensor", METHOD_TYPE_OBJECT },
    { 226, "registerListener", METHOD_TYPE_BOOLEAN },
    { 227, "unregisterListener", METHOD_TYPE_VOID },
    { 228, "getType", METHOD_TYPE_INT },
    { 229, "getRingerMode", METHOD_TYPE_INT },
    { 230, "getStreamVolume", METHOD_TYPE_INT },
    { 231, "setStreamMute", METHOD_TYPE_VOID },
    { 232, "getActiveNetworkInfo", METHOD_TYPE_OBJECT },
    { 233, "getType", METHOD_TYPE_INT },
    { 234, "isConnected", METHOD_TYPE_BOOLEAN },
    { 235, "getSystemService", METHOD_TYPE_OBJECT },
    { 236, "finish", METHOD_TYPE_VOID },
    { 237, "getIntent", METHOD_TYPE_OBJECT },
    { 238, "getWindow", METHOD_TYPE_OBJECT },
    { 239, "getWindowManager", METHOD_TYPE_OBJECT },
    { 240, "hasWindowFocus", METHOD_TYPE_BOOLEAN },
    { 241, "moveTaskToBack", METHOD_TYPE_VOID },
    { 242, "requestWindowFeature", METHOD_TYPE_BOOLEAN },
    { 243, "setContentView", METHOD_TYPE_VOID },
    { 244, "setVolumeControlStream", METHOD_TYPE_VOID },
    { 245, "startActivity", METHOD_TYPE_VOID },
    { 246, "setFlags", METHOD_TYPE_VOID },
    { 247, "getVisibility", METHOD_TYPE_INT },
    { 248, "setVisibility", METHOD_TYPE_VOID },
    { 249, "setBackgroundColor", METHOD_TYPE_VOID },
    { 250, "setLayoutParams", METHOD_TYPE_VOID },
    { 251, "addView", METHOD_TYPE_VOID },
    { 252, "removeView", METHOD_TYPE_VOID },
    { 253, "getText", METHOD_TYPE_OBJECT },
    { 254, "setText", METHOD_TYPE_VOID },
    { 255, "setGravity", METHOD_TYPE_VOID },
    { 256, "setImeOptions", METHOD_TYPE_VOID },
    { 257, "setInputType", METHOD_TYPE_VOID },
    { 258, "setTextSize", METHOD_TYPE_VOID },
    { 259, "setTypeface", METHOD_TYPE_VOID },
    { 260, "getWindowToken", METHOD_TYPE_OBJECT },
    { 261, "requestFocus", METHOD_TYPE_BOOLEAN },
    { 262, "setFilters", METHOD_TYPE_VOID },
    { 263, "showSoftInput", METHOD_TYPE_BOOLEAN },
    { 264, "hideSoftInputFromWindow", METHOD_TYPE_BOOLEAN },
    { 265, "obtainMessage", METHOD_TYPE_OBJECT },
    { 266, "sendEmptyMessage", METHOD_TYPE_BOOLEAN },
    { 267, "sendMessage", METHOD_TYPE_BOOLEAN },
    { 268, "obtain", METHOD_TYPE_OBJECT },
    { 269, "sendToTarget", METHOD_TYPE_VOID },
    { 270, "setData", METHOD_TYPE_VOID },
    { 271, "setTarget", METHOD_TYPE_VOID },
    { 272, "glClear", METHOD_TYPE_VOID },
    { 273, "glGetString", METHOD_TYPE_OBJECT },
    { 274, "create", METHOD_TYPE_OBJECT },
    { 275, "parse", METHOD_TYPE_OBJECT },
    { 276, "init", METHOD_TYPE_OBJECT },
    { 277, "openConnection", METHOD_TYPE_OBJECT },
    { 278, "connect", METHOD_TYPE_VOID },
    { 279, "toString", METHOD_TYPE_OBJECT },
    { 280, "getFD", METHOD_TYPE_OBJECT },
    { 281, "addCategory", METHOD_TYPE_OBJECT },
    { 282, "getIntExtra", METHOD_TYPE_INT },
    { 283, "removeExtra", METHOD_TYPE_VOID },
    { 284, "setFlags", METHOD_TYPE_VOID },
    { 285, "getDisplayAd", METHOD_TYPE_OBJECT },
    { 286, "getFeaturedApp", METHOD_TYPE_OBJECT },
    { 287, "isAllowToReload", METHOD_TYPE_BOOLEAN },
    { 288, "resetDisplayTimeStamp", METHOD_TYPE_VOID },
    { 289, "testInAppBilling", METHOD_TYPE_VOID },
    { 290, "getCrtTimeStr", METHOD_TYPE_OBJECT },
    { 291, "isVideoCompleted", METHOD_TYPE_BOOLEAN },
    { 292, "getDefault", METHOD_TYPE_OBJECT },
    { 293, "getLanguage", METHOD_TYPE_OBJECT },
    { 294, "toLowerCase", METHOD_TYPE_OBJECT },
    { 300, "android/content/Intent/<init>", METHOD_TYPE_OBJECT },
    { 301, "putExtra", METHOD_TYPE_OBJECT },
    { 302, "setEGLConfigChooser", METHOD_TYPE_VOID },
    { 303, "setRenderer", METHOD_TYPE_VOID },
    { 304, "android/media/SoundPool/<init>", METHOD_TYPE_OBJECT },
    { 305, "android/media/MediaPlayer/<init>", METHOD_TYPE_OBJECT },
    { 306, "java/io/File/<init>", METHOD_TYPE_OBJECT },
    { 307, "java/io/FileInputStream/<init>", METHOD_TYPE_OBJECT },
    { 308, "android/widget/EditText/<init>", METHOD_TYPE_OBJECT },
    { 309, "android/text/InputFilter$LengthFilter/<init>", METHOD_TYPE_OBJECT },
    { 310, "android/widget/AbsoluteLayout/<init>", METHOD_TYPE_OBJECT },
    { 311, "android/widget/AbsoluteLayout$LayoutParams/<init>", METHOD_TYPE_OBJECT },
    { 312, "android/os/Message/<init>", METHOD_TYPE_OBJECT },
    { 313, "java/net/URL/<init>", METHOD_TYPE_OBJECT },
    { 314, "android/media/AudioTrack/<init>", METHOD_TYPE_OBJECT },
    { 315, "getMinBufferSize", METHOD_TYPE_INT },
    { 316, "write", METHOD_TYPE_INT },
};

MethodsObject methodsObject[] = {
{ 0, stub_CustomFilter_CustomFilter_0 },
    { 1, stub_CustomFilter_filter_1 },
    { 2, stub_EditTextField_EditTextField_2 },
    { 4, stub_Device_Device_4 },
    { 12, stub_Device_ValidateStringforURL_12 },
    { 13, stub_Device_a_13 },
    { 14, stub_Device_b_14 },
    { 15, stub_Device_c_15 },
    { 17, stub_Device_d_17 },
    { 18, stub_Device_d1_18 },
    { 19, stub_Device_e_19 },
    { 21, stub_Device_f_21 },
    { 22, stub_Device_getBillingVersion_22 },
    { 23, stub_Device_getCarrier_23 },
    { 24, stub_Device_getDemoCode_24 },
    { 25, stub_Device_getDevice_25 },
    { 26, stub_Device_getDeviceId_26 },
    { 27, stub_Device_getHostName_27 },
    { 28, stub_Device_getIMEI_28 },
    { 30, stub_Device_getLanguage_30 },
    { 31, stub_Device_getLineNumber_31 },
    { 32, stub_Device_getNetworkCountryIso_32 },
    { 33, stub_Device_getNetworkOperator_33 },
    { 34, stub_Device_getNetworkOperatorName_34 },
    { 35, stub_Device_getPhoneModel_35 },
    { 36, stub_Device_getProfileType_36 },
    { 37, stub_Device_getSimCountryIso_37 },
    { 38, stub_Device_getSimOperator_38 },
    { 39, stub_Device_getSimOperatorName_39 },
    { 41, stub_Device_getUserAgent_41 },
    { 44, stub_SUtils_GetSerialKey_44 },
    { 45, stub_SUtils_ReadFile_45 },
    { 46, stub_SUtils_ReadFile_46 },
    { 47, stub_SUtils_ReadFileByte_47 },
    { 48, stub_SUtils_ReadFileByte_48 },
    { 52, stub_SUtils_extractSOFile_52 },
    { 53, stub_SUtils_getContext_53 },
    { 55, stub_SUtils_getOBBFolder_55 },
    { 56, stub_SUtils_getOverriddenSetting_56 },
    { 58, stub_SUtils_getPackage_58 },
    { 59, stub_SUtils_getPhoneDevice_59 },
    { 60, stub_SUtils_getPhoneManufacture_60 },
    { 61, stub_SUtils_getPhoneModel_61 },
    { 62, stub_SUtils_getPhoneProduct_62 },
    { 66, stub_SUtils_getPreferenceString_66 },
    { 67, stub_SUtils_getPreferenceString_67 },
    { 68, stub_SUtils_getResourceAsStream_68 },
    { 69, stub_SUtils_getSDFolder_69 },
    { 70, stub_SUtils_getSaveFolder_70 },
    { 72, stub_SUtils_getVersionInstalled_72 },
    { 73, stub_SUtils_getZipPathForFile_73 },
    { 77, stub_SUtils_objectArrayToStringArray_77 },
    { 78, stub_SUtils_readTextFile_78 },
    { 96, stub_GTRacing_checkDeviceName_96 },
    { 97, stub_GTRacing_checkManufacturer_97 },
    { 99, stub_GTRacing_getCrtTimeStr_99 },
    { 100, stub_GTRacing_getIMEI_100 },
    { 101, stub_GTRacing_getMac_101 },
    { 103, stub_GTRacing_getPathData_103 },
    { 104, stub_GTRacing_getSDFolder_104 },
    { 105, stub_GTRacing_getUniqueId_105 },
    { 118, stub_GTRacing_getCurrentVersion_118 },
    { 143, stub_GameGLSurfaceView_GameGLSurfaceView_143 },
    { 148, stub_GameRenderer_GameRenderer_148 },
    { 152, stub_IGPFreemiumActivity_IGPFreemiumActivity_152 },
    { 156, stub_IGPFreemiumActivity_getHttpResponse_156 },
    { 171, stub_FacebookAndroidGLSocialLib_FacebookAndroidGLSocialLib_171 },
    { 202, stubx_WindowManager_getDefaultDisplay },
    { 214, stubx_MediaPlayer_create },
    { 225, stubx_SensorManager_getDefaultSensor },
    { 232, stubx_ConnectivityManager_getActiveNetworkInfo },
    { 235, stubx_Context_getSystemService },
    { 237, stubx_Activity_getIntent },
    { 238, stubx_Activity_getWindow },
    { 239, stubx_Activity_getWindowManager },
    { 253, stubx_TextView_getText },
    { 260, stubx_EditText_getWindowToken },
    { 265, stubx_Handler_obtainMessage },
    { 268, stubx_Message_obtain },
    { 273, stubx_GL10_glGetString },
    { 274, stubx_Typeface_create },
    { 275, stubx_Uri_parse },
    { 276, stubx_URL_init },
    { 277, stubx_URL_openConnection },
    { 279, stubx_CharSequence_toString },
    { 280, stubx_FileInputStream_getFD },
    { 281, stubx_Intent_addCategory },
    { 285, stubx_GTRacing_getDisplayAd },
    { 286, stubx_GTRacing_getFeaturedApp },
    { 290, stubx_GTRacing_getCrtTimeStr },
    { 292, stubx_Locale_getDefault },
    { 293, stubx_Locale_getLanguage },
    { 294, stubx_String_toLowerCase },
    { 300, stubx_dummy_NewObject },
    { 301, stubx_dummy_NewObject },
    { 304, stubx_dummy_NewObject },
    { 305, stubx_dummy_NewObject },
    { 306, stubx_dummy_NewObject },
    { 307, stubx_dummy_NewObject },
    { 308, stubx_dummy_NewObject },
    { 309, stubx_dummy_NewObject },
    { 310, stubx_dummy_NewObject },
    { 311, stubx_dummy_NewObject },
    { 312, stubx_dummy_NewObject },
    { 313, stubx_dummy_NewObject },
    { 314, stubx_AudioTrack_new },
};

MethodsBoolean methodsBoolean[] = {
{ 3, stub_EditTextField_onKeyPreIme_3 },
    { 8, stub_Device_IsConnectionReady_8 },
    { 9, stub_Device_IsWifiDisabling_9 },
    { 10, stub_Device_IsWifiEnable_10 },
    { 11, stub_Device_IsWifiEnabling_11 },
    { 29, stub_Device_getIsRoaming_29 },
    { 49, stub_SUtils_WriteFile_49 },
    { 50, stub_SUtils_WriteFile_50 },
    { 51, stub_SUtils_doesZipContains_51 },
    { 57, stub_SUtils_getOverriddenSettingBoolean_57 },
    { 63, stub_SUtils_getPreferenceBoolean_63 },
    { 75, stub_SUtils_isAirplaneModeOn_75 },
    { 94, stub_GTRacing_b_94 },
    { 106, stub_GTRacing_isNeedInvertTouchZone_106 },
    { 107, stub_GTRacing_isUseLowres_107 },
    { 116, stub_GTRacing_IsKeyboardEnabled_116 },
    { 120, stub_GTRacing_isWifiAlive_120 },
    { 127, stub_GTRacing_onKeyDown_127 },
    { 128, stub_GTRacing_onKeyUp_128 },
    { 136, stub_GTRacing_onTouchEvent_136 },
    { 160, stub_IGPFreemiumActivity_onKeyDown_160 },
    { 161, stub_IGPFreemiumActivity_onKeyLongPress_161 },
    { 162, stub_IGPFreemiumActivity_onKeyUp_162 },
    { 169, stub_KeyboardInput_onKeyDown_169 },
    { 170, stub_KeyboardInput_onKeyUp_170 },
    { 182, stub_FacebookAndroidGLSocialLib_IsLoggedIn_182 },
    { 183, stub_FacebookAndroidGLSocialLib_LoadAuth_183 },
    { 191, stub_FacebookAndroidGLSocialLib_SaveAuth_191 },
    { 224, stubx_MediaPlayer_isPlaying },
    { 226, stubx_SensorManager_registerListener },
    { 234, stubx_NetworkInfo_isConnected },
    { 240, stubx_Activity_hasWindowFocus },
    { 242, stubx_Activity_requestWindowFeature },
    { 261, stubx_EditText_requestFocus },
    { 263, stubx_InputMethodManager_showSoftInput },
    { 264, stubx_InputMethodManager_hideSoftInputFromWindow },
    { 266, stubx_Handler_sendEmptyMessage },
    { 267, stubx_Handler_sendMessage },
    { 287, stubx_GTRacing_isAllowToReload },
    { 291, stubx_MyVideoView_isVideoCompleted },
};

MethodsVoid methodsVoid[] = {
{ 5, stub_Device_DisableWifi_5 },
    { 6, stub_Device_EnableWifi_6 },
    { 7, stub_Device_InitDeviceValues_7 },
    { 20, stub_Device_e_20 },
    { 42, stub_Device_init_42 },
    { 43, stub_Device_a_43 },
    { 74, stub_SUtils_initializeTheFilesList_74 },
    { 76, stub_SUtils_logWindowMessage_76 },
    { 79, stub_SUtils_release_79 },
    { 80, stub_SUtils_resetValusForMAinAndPatch_80 },
    { 81, stub_SUtils_runOnUiThread_81 },
    { 82, stub_SUtils_saveLocation_82 },
    { 83, stub_SUtils_setAirplaneMode_83 },
    { 84, stub_SUtils_setContext_84 },
    { 85, stub_SUtils_setOverriddenSetting_85 },
    { 86, stub_SUtils_setPreference_86 },
    { 87, stub_SUtils_shareInfo_87 },
    { 88, stub_GTRacing_DismissLoading_88 },
    { 89, stub_GTRacing_HideFacebookDialog_89 },
    { 90, stub_GTRacing_ShowFacebookDialog_90 },
    { 91, stub_GTRacing_TrackAndroidHits_91 },
    { 92, stub_GTRacing_a_92 },
    { 93, stub_GTRacing_a_93 },
    { 95, stub_GTRacing_c_95 },
    { 98, stub_GTRacing_ensurePathExists_98 },
    { 108, stub_GTRacing_launchGLLive_108 },
    { 109, stub_GTRacing_launchIGP_109 },
    { 110, stub_GTRacing_notifyTrophy_110 },
    { 111, stub_GTRacing_resumeScreen_111 },
    { 112, stub_GTRacing_setTypeText_112 },
    { 113, stub_GTRacing_setupPaths_113 },
    { 114, stub_GTRacing_CreateContentView_114 },
    { 117, stub_GTRacing_exit_117 },
    { 119, stub_GTRacing_gotoMarket_119 },
    { 121, stub_GTRacing_onAccuracyChanged_121 },
    { 122, stub_GTRacing_onActivityResult_122 },
    { 123, stub_GTRacing_onConfigurationChanged_123 },
    { 124, stub_GTRacing_onCreate_124 },
    { 125, stub_GTRacing_onDestroy_125 },
    { 126, stub_GTRacing_onGlobalLayout_126 },
    { 129, stub_GTRacing_onNewIntent_129 },
    { 130, stub_GTRacing_onPause_130 },
    { 131, stub_GTRacing_onRestart_131 },
    { 132, stub_GTRacing_onResume_132 },
    { 133, stub_GTRacing_onSensorChanged_133 },
    { 134, stub_GTRacing_onStart_134 },
    { 135, stub_GTRacing_onStop_135 },
    { 137, stub_GTRacing_onUserInteraction_137 },
    { 138, stub_GTRacing_openCustomerCare_138 },
    { 139, stub_GTRacing_showOffersWithCurrencyID_139 },
    { 140, stub_GTRacing_surfaceChanged_140 },
    { 141, stub_GTRacing_surfaceCreated_141 },
    { 142, stub_GTRacing_surfaceDestroyed_142 },
    { 144, stub_GameGLSurfaceView_onPause_144 },
    { 145, stub_GameGLSurfaceView_onResume_145 },
    { 146, stub_GameGLSurfaceView_onSizeChanged_146 },
    { 147, stub_GameGLSurfaceView_onWindowFocusChanged_147 },
    { 149, stub_GameRenderer_onDrawFrame_149 },
    { 150, stub_GameRenderer_onSurfaceChanged_150 },
    { 151, stub_GameRenderer_onSurfaceCreated_151 },
    { 153, stub_IGPFreemiumActivity_a_153 },
    { 154, stub_IGPFreemiumActivity_a_154 },
    { 155, stub_IGPFreemiumActivity_b_155 },
    { 157, stub_IGPFreemiumActivity_a_157 },
    { 158, stub_IGPFreemiumActivity_onCreate_158 },
    { 159, stub_IGPFreemiumActivity_onDestroy_159 },
    { 163, stub_IGPFreemiumActivity_onPause_163 },
    { 164, stub_IGPFreemiumActivity_onResume_164 },
    { 165, stub_IGPFreemiumActivity_onStart_165 },
    { 166, stub_IGPFreemiumActivity_onStop_166 },
    { 167, stub_IGPFreemiumActivity_onWindowFocusChanged_167 },
    { 168, stub_KeyboardInput_onCreate_168 },
    { 172, stub_FacebookAndroidGLSocialLib_AuthorizeSSOCallback_172 },
    { 173, stub_FacebookAndroidGLSocialLib_ClearAuth_173 },
    { 174, stub_FacebookAndroidGLSocialLib_GetFriends_174 },
    { 175, stub_FacebookAndroidGLSocialLib_GetFriendsInGame_175 },
    { 176, stub_FacebookAndroidGLSocialLib_GetMyInfo_176 },
    { 177, stub_FacebookAndroidGLSocialLib_GetPicture_177 },
    { 178, stub_FacebookAndroidGLSocialLib_GetUserData_178 },
    { 179, stub_FacebookAndroidGLSocialLib_Init_179 },
    { 180, stub_FacebookAndroidGLSocialLib_InviteFriends_180 },
    { 181, stub_FacebookAndroidGLSocialLib_InviteFriends_facade_181 },
    { 184, stub_FacebookAndroidGLSocialLib_Login_184 },
    { 185, stub_FacebookAndroidGLSocialLib_Login_facade_185 },
    { 186, stub_FacebookAndroidGLSocialLib_Logout_186 },
    { 187, stub_FacebookAndroidGLSocialLib_PostToFriendsWall_187 },
    { 188, stub_FacebookAndroidGLSocialLib_PostToFriendsWall_facade_188 },
    { 189, stub_FacebookAndroidGLSocialLib_PostToWall_189 },
    { 190, stub_FacebookAndroidGLSocialLib_PostToWall_facade_190 },
    { 192, stub_FacebookAndroidGLSocialLib_SetAppId_192 },
    { 204, stubx_System_exit },
    { 206, stubx_AudioTrack_play },   // AudioTrack.play()V (mismo nombre que SoundPool.play)
    { 207, stubx_AudioTrack_pause },  // AudioTrack.pause()V
    { 208, stubx_SoundPool_resume },
    { 209, stubx_AudioTrack_stop },   // AudioTrack.stop()V
    { 210, stubx_SoundPool_unload },
    { 211, stubx_SoundPool_release },
    { 212, stubx_SoundPool_setVolume },
    { 213, stubx_SoundPool_setRate },
    { 215, stubx_MediaPlayer_setDataSource },
    { 216, stubx_MediaPlayer_prepare },
    { 217, stubx_MediaPlayer_start },
    { 218, stubx_MediaPlayer_pause },
    { 219, stubx_MediaPlayer_stop },
    { 220, stubx_MediaPlayer_reset },
    { 221, stubx_MediaPlayer_release },
    { 222, stubx_MediaPlayer_setLooping },
    { 223, stubx_MediaPlayer_setVolume },
    { 227, stubx_SensorManager_unregisterListener },
    { 231, stubx_AudioManager_setStreamMute },
    { 236, stubx_Activity_finish },
    { 241, stubx_Activity_moveTaskToBack },
    { 243, stubx_Activity_setContentView },
    { 244, stubx_Activity_setVolumeControlStream },
    { 245, stubx_Activity_startActivity },
    { 246, stubx_Window_setFlags },
    { 248, stubx_View_setVisibility },
    { 249, stubx_View_setBackgroundColor },
    { 250, stubx_View_setLayoutParams },
    { 251, stubx_ViewGroup_addView },
    { 252, stubx_ViewGroup_removeView },
    { 254, stubx_TextView_setText },
    { 255, stubx_TextView_setGravity },
    { 256, stubx_TextView_setImeOptions },
    { 257, stubx_TextView_setInputType },
    { 258, stubx_TextView_setTextSize },
    { 259, stubx_TextView_setTypeface },
    { 262, stubx_EditText_setFilters },
    { 269, stubx_Message_sendToTarget },
    { 270, stubx_Message_setData },
    { 271, stubx_Message_setTarget },
    { 272, stubx_GL10_glClear },
    { 278, stubx_URLConnection_connect },
    { 283, stubx_Intent_removeExtra },
    { 284, stubx_Intent_setFlags },
    { 288, stubx_GTRacing_resetDisplayTimeStamp },
    { 289, stubx_GTRacing_testInAppBilling },
    { 302, stubx_dummy_void },
    { 303, stubx_dummy_void },
};

MethodsInt methodsInt[] = {
{ 16, stub_Device_createUniqueCode_16 },
    { 40, stub_Device_getUniqueCode_40 },
    { 64, stub_SUtils_getPreferenceInt_64 },
    { 71, stub_SUtils_getUniqueCode_71 },
    { 102, stub_GTRacing_getManufacture_102 },
    { 115, stub_GTRacing_EnableAutoRotateScreen_115 },
    { 193, stubx_MotionEvent_getAction },
    { 194, stubx_MotionEvent_getPointerCount },
    { 195, stubx_MotionEvent_getPointerId },
    { 200, stubx_Display_getWidth },
    { 201, stubx_Display_getHeight },
    { 205, stubx_SoundPool_load },
    { 206, stubx_SoundPool_play },
    { 228, stubx_Sensor_getType },
    { 229, stubx_AudioManager_getRingerMode },
    { 230, stubx_AudioManager_getStreamVolume },
    { 233, stubx_NetworkInfo_getType },
    { 247, stubx_View_getVisibility },
    { 282, stubx_Intent_getIntExtra },
    { 315, stubx_AudioTrack_getMinBufferSize },
    { 316, stubx_AudioTrack_write },
};

MethodsFloat methodsFloat[] = {
{ 54, stub_SUtils_getFreeSpace_54 },
    { 196, stubx_MotionEvent_getX },
    { 197, stubx_MotionEvent_getY },
    { 198, stubx_MotionEvent_getRawX },
    { 199, stubx_MotionEvent_getRawY },
};

MethodsLong methodsLong[] = {
    { 65, stub_SUtils_getPreferenceLong_65 },
    { 203, stubx_System_currentTimeMillis },
};

/* Sin candidatos del analizador: tablas vacías pero deben existir (FalsoJNI). */
MethodsByte methodsByte[] = {};
MethodsChar methodsChar[] = {};
MethodsShort methodsShort[] = {};
MethodsDouble methodsDouble[] = {};

/*
 * JNI Fields
*/

NameToFieldID nameToFieldId[] = {
    { FID_WINDOW_SERVICE, "WINDOW_SERVICE", FIELD_TYPE_OBJECT },
    { FID_SDK_INT, "SDK_INT", FIELD_TYPE_INT },
    { FID_mDeviceInfo, "mDeviceInfo", FIELD_TYPE_OBJECT },
    { FID_SERIAL, "SERIAL", FIELD_TYPE_OBJECT },
    { FID_m_sInstance, "m_sInstance", FIELD_TYPE_OBJECT },
    { FID_sbIsFocus, "sbIsFocus", FIELD_TYPE_BOOLEAN },
    { FID_mGame, "mGame", FIELD_TYPE_OBJECT },
    { FID_gIsRunning, "gIsRunning", FIELD_TYPE_BOOLEAN },
    { FID_sStartedFromPopup, "sStartedFromPopup", FIELD_TYPE_INT },
    { FID_GAMELOFT_TYPE, "GAMELOFT_TYPE", FIELD_TYPE_BOOLEAN },
    { FID_m_sDeviceID, "m_sDeviceID", FIELD_TYPE_OBJECT },
    { FID_m_sPhoneName, "m_sPhoneName", FIELD_TYPE_OBJECT },
    { FID_m_sFirmware, "m_sFirmware", FIELD_TYPE_OBJECT },
    { FID_m_sDeviceName, "m_sDeviceName", FIELD_TYPE_OBJECT },
    { FID_MANUFACTURER, "MANUFACTURER", FIELD_TYPE_OBJECT },
    { FID_viewHandler, "viewHandler", FIELD_TYPE_OBJECT },
    { FID_mainGameLayout, "mainGameLayout", FIELD_TYPE_OBJECT },
    { FID_mGLView, "mGLView", FIELD_TYPE_OBJECT },
    { FID_m_sKeyboardContext, "m_sKeyboardContext", FIELD_TYPE_OBJECT },
    { FID_sensor, "sensor", FIELD_TYPE_OBJECT },
    { FID_values, "values", FIELD_TYPE_OBJECT },
    { FID_isAllowToReload, "isAllowToReload", FIELD_TYPE_INT },

    // Aliases
    { FID_ALIAS_viewHandler, "iGTRacing_viewHandler", FIELD_TYPE_OBJECT },
    { FID_ALIAS_mainGameLayout, "iGTRacing_mainGameLayout", FIELD_TYPE_OBJECT },
    { FID_ALIAS_mGLView, "iGTRacing_mGLView", FIELD_TYPE_OBJECT },
    { FID_ALIAS_m_sKeyboardContext, "iGTRacing_m_sKeyboardContext", FIELD_TYPE_OBJECT },
    { FID_ALIAS_cGTRacing, "cGTRacing", FIELD_TYPE_OBJECT },
    { FID_ALIAS_cTypeface, "cTypeface", FIELD_TYPE_OBJECT },
};

FieldsBoolean fieldsBoolean[] = {
    { FID_sbIsFocus, JNI_TRUE },
    { FID_gIsRunning, JNI_TRUE },
    { FID_GAMELOFT_TYPE, JNI_FALSE },
};
FieldsByte fieldsByte[] = {};
FieldsChar fieldsChar[] = {};
FieldsDouble fieldsDouble[] = {};
FieldsFloat fieldsFloat[] = {};
FieldsInt fieldsInt[] = {
    { FID_SDK_INT, 19 },
    { FID_sStartedFromPopup, 0 },
    { FID_isAllowToReload, 1 },
};
FieldsObject fieldsObject[] = {
    { FID_WINDOW_SERVICE, NULL },
    { FID_mDeviceInfo, (jobject)0x1 },
    { FID_SERIAL, NULL },
    { FID_m_sInstance, (jobject)0x1 },
    { FID_mGame, (jobject)0x1 },
    { FID_m_sDeviceID, NULL },
    { FID_m_sPhoneName, NULL },
    { FID_m_sFirmware, NULL },
    { FID_m_sDeviceName, NULL },
    { FID_MANUFACTURER, NULL },
    { FID_viewHandler, (jobject)0x1 },
    { FID_mainGameLayout, (jobject)0x1 },
    { FID_mGLView, (jobject)0x1 },
    { FID_m_sKeyboardContext, (jobject)0x1 },
    { FID_sensor, (jobject)0x1 },
    { FID_values, NULL },
    { FID_ALIAS_viewHandler, (jobject)0x1 },
    { FID_ALIAS_mainGameLayout, (jobject)0x1 },
    { FID_ALIAS_mGLView, (jobject)0x1 },
    { FID_ALIAS_m_sKeyboardContext, (jobject)0x1 },
    { FID_ALIAS_cGTRacing, (jobject)0x1 },
    { FID_ALIAS_cTypeface, (jobject)0x1 },
};
FieldsLong fieldsLong[] = {};
FieldsShort fieldsShort[] = {};

__FALSOJNI_IMPL_CONTAINER_SIZES

