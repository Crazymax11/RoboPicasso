#include "animatorapplication.h"

AnimatorApplication::AnimatorApplication(int &argc, char** argv): QApplication(argc, argv){
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    rootQML = engine.rootObjects()[0];

}
