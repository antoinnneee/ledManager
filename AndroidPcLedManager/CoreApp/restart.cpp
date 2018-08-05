#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QtAndroid>

void	androidrestart()
{
#ifdef Q_OS_ANDROID
        auto activity = QtAndroid::androidActivity();
        auto packageManager = activity.callObjectMethod("getPackageManager",
                                                        "()Landroid/content/pm/PackageManager;");

        auto activityIntent = packageManager.callObjectMethod("getLaunchIntentForPackage",
                                                              "(Ljava/lang/String;)Landroid/content/Intent;",
                                                              activity.callObjectMethod("getPackageName",
                                                              "()Ljava/lang/String;").object());

        auto pendingIntent = QAndroidJniObject::callStaticObjectMethod("android/app/PendingIntent", "getActivity",
                                                                       "(Landroid/content/Context;ILandroid/content/Intent;I)Landroid/app/PendingIntent;",
                                                                       activity.object(), jint(0), activityIntent.object(),
                                                                       QAndroidJniObject::getStaticField<jint>("android/content/Intent",
                                                                                                               "FLAG_ACTIVITY_CLEAR_TOP"));

        auto alarmManager = activity.callObjectMethod("getSystemService",
                                                      "(Ljava/lang/String;)Ljava/lang/Object;",
                                                      QAndroidJniObject::getStaticObjectField("android/content/Context",
                                                                                              "ALARM_SERVICE",
                                                                                              "Ljava/lang/String;").object());

        alarmManager.callMethod<void>("set",
                                      "(IJLandroid/app/PendingIntent;)V",
                                      QAndroidJniObject::getStaticField<jint>("android/app/AlarmManager", "RTC"),
                                      jlong(QDateTime::currentMSecsSinceEpoch() + 200), pendingIntent.object());

        qApp->quit();
//        auto service = QAndroidIntent(QtAndroid::androidActivity().object(), "com.example.MyService");
#endif
}
