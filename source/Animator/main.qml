import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

ApplicationWindow {
    id: root
    visible: true
    width: 400
    height: 500
    title: "Robopicasso Animator"
    property url sourceDirectory
    property url destinationDirectory
    property url ffmpegPath

    property double originalSecondsVal: originalSeconds.value
    property double transitionSecondsVal: transitionSeconds.value
    property double generationSecondsVal: generationSeconds.value

    signal start()
    ColumnLayout{
        anchors.fill: parent
        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: sourceBtn
            text: "каталог - источник"
            onClicked: fdsrc.open()
            FileDialog{
                id: fdsrc
                selectFolder: true
                onAccepted: root.sourceDirectory = fileUrl
            }
        }
        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: destinationBtn
            text: "каталог вывода"
            onClicked: fddst.open()
            FileDialog{
                id: fddst
                selectFolder: true
                onAccepted: root.destinationDirectory = fileUrl
            }
        }

        Text{
            fontSizeMode: Text.Fit
            font.pointSize: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "оригинал: " + (originalSeconds.value*100)/100 + "с"
        }

        Slider{
            id: originalSeconds
            stepSize: 0.1
            value: 2
            minimumValue: 0
            maximumValue: 4
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text{
            fontSizeMode: Text.Fit
            font.pointSize: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "поколение: " + (generationSeconds.value*100)/100 + "с"
        }

        Slider{
            id: generationSeconds
            stepSize: 0.1
            value: 2
            minimumValue: 0
            maximumValue: 4
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text{
            fontSizeMode: Text.Fit
            font.pointSize: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "переход: " + (transitionSeconds.value*100)/100 + "с"
        }

        Slider{
            id: transitionSeconds
            stepSize: 0.1
            value: 2
            minimumValue: 0
            maximumValue: 4
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: ffmpegBtn
            text: "ffmpeg путь"
            onClicked: fdffmpeg.open()
            FileDialog{
                id: fdffmpeg
                onAccepted: root.ffmpegPath= fileUrl
            }
        }
        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: startBtn
            text: "start"
            onClicked: root.start()
        }
    }
}
