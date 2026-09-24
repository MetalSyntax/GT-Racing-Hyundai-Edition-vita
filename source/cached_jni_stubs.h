/* Externs de cached_jni_stubs.c para java.c */
#pragma once
#include <stdarg.h>
#include <falso_jni/FalsoJNI_Impl.h>

extern jint stubx_MotionEvent_getAction(jmethodID id, va_list args);
extern jint stubx_MotionEvent_getPointerCount(jmethodID id, va_list args);
extern jint stubx_MotionEvent_getPointerId(jmethodID id, va_list args);
extern jfloat stubx_MotionEvent_getX(jmethodID id, va_list args);
extern jfloat stubx_MotionEvent_getY(jmethodID id, va_list args);
extern jfloat stubx_MotionEvent_getRawX(jmethodID id, va_list args);
extern jfloat stubx_MotionEvent_getRawY(jmethodID id, va_list args);
extern jint stubx_Display_getWidth(jmethodID id, va_list args);
extern jint stubx_Display_getHeight(jmethodID id, va_list args);
extern jobject stubx_WindowManager_getDefaultDisplay(jmethodID id, va_list args);
extern jlong stubx_System_currentTimeMillis(jmethodID id, va_list args);
extern void stubx_System_exit(jmethodID id, va_list args);
extern jint stubx_SoundPool_load(jmethodID id, va_list args);
extern jint stubx_SoundPool_play(jmethodID id, va_list args);
extern void stubx_SoundPool_play_void(jmethodID id, va_list args);
extern void stubx_SoundPool_pause(jmethodID id, va_list args);
extern void stubx_SoundPool_resume(jmethodID id, va_list args);
extern void stubx_SoundPool_stop(jmethodID id, va_list args);
extern void stubx_SoundPool_unload(jmethodID id, va_list args);
extern void stubx_SoundPool_release(jmethodID id, va_list args);
extern void stubx_SoundPool_setVolume(jmethodID id, va_list args);
extern void stubx_SoundPool_setRate(jmethodID id, va_list args);
extern jobject stubx_MediaPlayer_create(jmethodID id, va_list args);
extern void stubx_MediaPlayer_setDataSource(jmethodID id, va_list args);
extern void stubx_MediaPlayer_prepare(jmethodID id, va_list args);
extern void stubx_MediaPlayer_start(jmethodID id, va_list args);
extern void stubx_MediaPlayer_pause(jmethodID id, va_list args);
extern void stubx_MediaPlayer_stop(jmethodID id, va_list args);
extern void stubx_MediaPlayer_reset(jmethodID id, va_list args);
extern void stubx_MediaPlayer_release(jmethodID id, va_list args);
extern void stubx_MediaPlayer_setLooping(jmethodID id, va_list args);
extern void stubx_MediaPlayer_setVolume(jmethodID id, va_list args);
extern jboolean stubx_MediaPlayer_isPlaying(jmethodID id, va_list args);
extern jobject stubx_SensorManager_getDefaultSensor(jmethodID id, va_list args);
extern jboolean stubx_SensorManager_registerListener(jmethodID id, va_list args);
extern void stubx_SensorManager_unregisterListener(jmethodID id, va_list args);
extern jint stubx_Sensor_getType(jmethodID id, va_list args);
extern jint stubx_AudioManager_getRingerMode(jmethodID id, va_list args);
extern jint stubx_AudioManager_getStreamVolume(jmethodID id, va_list args);
extern void stubx_AudioManager_setStreamMute(jmethodID id, va_list args);
extern jobject stubx_ConnectivityManager_getActiveNetworkInfo(jmethodID id, va_list args);
extern jint stubx_NetworkInfo_getType(jmethodID id, va_list args);
extern jboolean stubx_NetworkInfo_isConnected(jmethodID id, va_list args);
extern jobject stubx_Context_getSystemService(jmethodID id, va_list args);
extern void stubx_Activity_finish(jmethodID id, va_list args);
extern jobject stubx_Activity_getIntent(jmethodID id, va_list args);
extern jobject stubx_Activity_getWindow(jmethodID id, va_list args);
extern jobject stubx_Activity_getWindowManager(jmethodID id, va_list args);
extern jboolean stubx_Activity_hasWindowFocus(jmethodID id, va_list args);
extern void stubx_Activity_moveTaskToBack(jmethodID id, va_list args);
extern jboolean stubx_Activity_requestWindowFeature(jmethodID id, va_list args);
extern void stubx_Activity_setContentView(jmethodID id, va_list args);
extern void stubx_Activity_setVolumeControlStream(jmethodID id, va_list args);
extern void stubx_Activity_startActivity(jmethodID id, va_list args);
extern void stubx_Window_setFlags(jmethodID id, va_list args);
extern jint stubx_View_getVisibility(jmethodID id, va_list args);
extern void stubx_View_setVisibility(jmethodID id, va_list args);
extern void stubx_View_setBackgroundColor(jmethodID id, va_list args);
extern void stubx_View_setLayoutParams(jmethodID id, va_list args);
extern void stubx_ViewGroup_addView(jmethodID id, va_list args);
extern void stubx_ViewGroup_removeView(jmethodID id, va_list args);
extern jobject stubx_TextView_getText(jmethodID id, va_list args);
extern void stubx_TextView_setText(jmethodID id, va_list args);
extern void stubx_TextView_setGravity(jmethodID id, va_list args);
extern void stubx_TextView_setImeOptions(jmethodID id, va_list args);
extern void stubx_TextView_setInputType(jmethodID id, va_list args);
extern void stubx_TextView_setTextSize(jmethodID id, va_list args);
extern void stubx_TextView_setTypeface(jmethodID id, va_list args);
extern jobject stubx_EditText_getWindowToken(jmethodID id, va_list args);
extern jboolean stubx_EditText_requestFocus(jmethodID id, va_list args);
extern void stubx_EditText_setFilters(jmethodID id, va_list args);
extern jboolean stubx_InputMethodManager_showSoftInput(jmethodID id, va_list args);
extern jboolean stubx_InputMethodManager_hideSoftInputFromWindow(jmethodID id, va_list args);
extern jobject stubx_Handler_obtainMessage(jmethodID id, va_list args);
extern jboolean stubx_Handler_sendEmptyMessage(jmethodID id, va_list args);
extern jboolean stubx_Handler_sendMessage(jmethodID id, va_list args);
extern jobject stubx_Message_obtain(jmethodID id, va_list args);
extern void stubx_Message_sendToTarget(jmethodID id, va_list args);
extern void stubx_Message_setData(jmethodID id, va_list args);
extern void stubx_Message_setTarget(jmethodID id, va_list args);
extern void stubx_GL10_glClear(jmethodID id, va_list args);
extern jobject stubx_GL10_glGetString(jmethodID id, va_list args);
extern jobject stubx_Typeface_create(jmethodID id, va_list args);
extern jobject stubx_Uri_parse(jmethodID id, va_list args);
extern jobject stubx_URL_init(jmethodID id, va_list args);
extern jobject stubx_URL_openConnection(jmethodID id, va_list args);
extern void stubx_URLConnection_connect(jmethodID id, va_list args);
extern jobject stubx_CharSequence_toString(jmethodID id, va_list args);
extern jobject stubx_FileInputStream_getFD(jmethodID id, va_list args);
extern jobject stubx_Intent_addCategory(jmethodID id, va_list args);
extern jint stubx_Intent_getIntExtra(jmethodID id, va_list args);
extern void stubx_Intent_removeExtra(jmethodID id, va_list args);
extern void stubx_Intent_setFlags(jmethodID id, va_list args);
extern jobject stubx_GTRacing_getDisplayAd(jmethodID id, va_list args);
extern jobject stubx_GTRacing_getFeaturedApp(jmethodID id, va_list args);
extern jboolean stubx_GTRacing_isAllowToReload(jmethodID id, va_list args);
extern void stubx_GTRacing_resetDisplayTimeStamp(jmethodID id, va_list args);
extern void stubx_GTRacing_testInAppBilling(jmethodID id, va_list args);
extern jobject stubx_GTRacing_getCrtTimeStr(jmethodID id, va_list args);
extern jboolean stubx_MyVideoView_isVideoCompleted(jmethodID id, va_list args);
extern jobject stubx_Locale_getDefault(jmethodID id, va_list args);
extern jobject stubx_Locale_getLanguage(jmethodID id, va_list args);
extern jobject stubx_String_toLowerCase(jmethodID id, va_list args);
extern jobject stubx_dummy_NewObject(jmethodID id, va_list args);
extern void stubx_dummy_void(jmethodID id, va_list args);
extern jint stubx_AudioTrack_getMinBufferSize(jmethodID id, va_list args);
extern jint stubx_AudioTrack_write(jmethodID id, va_list args);
extern jobject stubx_AudioTrack_new(jmethodID id, va_list args);
extern void stubx_AudioTrack_play(jmethodID id, va_list args);
extern void stubx_AudioTrack_pause(jmethodID id, va_list args);
extern void stubx_AudioTrack_stop(jmethodID id, va_list args);
extern void hy_fields_init(void);

enum {
    FID_WINDOW_SERVICE = 1,
    FID_SDK_INT = 2,
    FID_mDeviceInfo = 3,
    FID_SERIAL = 4,
    FID_m_sInstance = 5,
    FID_sbIsFocus = 6,
    FID_mGame = 7,
    FID_gIsRunning = 8,
    FID_sStartedFromPopup = 9,
    FID_GAMELOFT_TYPE = 10,
    FID_m_sDeviceID = 11,
    FID_m_sPhoneName = 12,
    FID_m_sFirmware = 13,
    FID_m_sDeviceName = 14,
    FID_MANUFACTURER = 15,
    FID_viewHandler = 16,
    FID_mainGameLayout = 17,
    FID_mGLView = 18,
    FID_m_sKeyboardContext = 19,
    FID_sensor = 20,
    FID_values = 21,
    FID_isAllowToReload = 22,

    // Aliases (Ghidra variable names)
    FID_ALIAS_viewHandler = 23,
    FID_ALIAS_mainGameLayout = 24,
    FID_ALIAS_mGLView = 25,
    FID_ALIAS_m_sKeyboardContext = 26,
    FID_ALIAS_cGTRacing = 27,
    FID_ALIAS_cTypeface = 28,
};
