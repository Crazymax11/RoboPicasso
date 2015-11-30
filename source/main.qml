import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 1000
    height: 480
    property bool isRunning: false
    property bool isStarted: false
    property double mutationChance: mutationChanceSlider.value/100
    property double mutationAmount: mutationAmountSlider.value/100
    property double mutationFigures: mutationFiguresSlider.value/100
    property double minimalOpacity: minimalOpacitySlider.value/100
    property int populationNum: Math.round(populationNumSlider.value)
    property int figuresNum: Math.round(figuresNumSlider.value)
    property url tarImage: openFile.fileUrl

    property int bestResValue: 0

    property string bestResultSource: "image://imageProvider/image.png"
    signal start()
    signal resume()
    signal pause()
    onStart: {isRunning = true; isStarted = true;}
    onPause: {isRunning = false}
    onResume: (isRunning = true)
    function updateImage(){
        bestResultSource = "";
        bestResultSource = "image://imageProvider/image.png";
    }

    id:root
    title: qsTr("Подборка фигур генетических алгоритмом")
    Row{
        width: parent.width
        height: parent.height
        spacing: 10
        Rectangle{
            id: imRect
            height: parent.height - 2
            width: parent.width*0.7
            color: "black"
            Image{
                id: bestResult
                anchors.fill: parent
                source: root.isStarted ? root.bestResultSource : openFile.fileUrl
                cache: false
            }
        }
        Rectangle
        {
            height: parent.height - 2
            width: parent.width*0.25 - 10
            color: "transparent"
            border.width: 2
            border.color: "black"
            ColumnLayout{
                anchors.fill: parent
                anchors.margins: 3
                Button{
                    id: loadBtn
                    text: "load image"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onClicked: openFile.open()
                    FileDialog{
                        id: openFile
                        onAccepted: loadBtn.text = openFile.fileUrl
                    }
                }
                Text{
                    text: "шанс мутировать у особи: " + mutationChanceSlider.value +"%"
                }

                Slider{
                    id: mutationChanceSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 100
                    stepSize: 0.25
                }
                Text{
                    text: "предел мутации параметра фигуры: " +mutationAmountSlider.value +"%"
                }
                Slider{
                    id: mutationAmountSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 100
                    stepSize: 0.25
                }
                Text{
                    text: "мутирующие фигуры: " +mutationFiguresSlider.value +"%"
                }
                Slider{
                    id: mutationFiguresSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 100
                    stepSize: 0.25
                }
                Text{
                    text: "минимальная видимость: " + minimalOpacitySlider.value +"%"
                }
                Slider{
                    id: minimalOpacitySlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 100
                    stepSize: 0.25
                }

                Text{
                    id: populationNum
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "размер популяции: " + populationNumSlider.value
                }
                Slider{
                    id: populationNumSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    minimumValue: 2
                    maximumValue: 200
                    value: 40
                    stepSize: 1
                }
                Text{
                    id: figuresNum
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "количество фигур: " + figuresNumSlider.value
                }
                Slider{
                    id: figuresNumSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    minimumValue: 10
                    maximumValue: 200
                    value: 40
                    stepSize: 1
                }

                Text{
                    id: bestResultText
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: root.bestResValue
                }
                CheckBox{
                    id: saveEveryNewBest
                    text: "сохранять каждый найденный лучший"
                    onCheckedChanged: if (!checked) saveEveryNewBestAsImage.checked = false
                }
                CheckBox{
                    id: saveEveryNewBestAsImage
                    enabled: saveEveryNewBest.checked
                    text: "сохранять как изображение"
                }

                Button{
                    id: startBtn
                    text: root.isStarted? root.isRunning? "pause": "resume" : "start"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onClicked: root.isStarted? root.isRunning? root.pause(): root.resume() : root.start()
                }
                Button{
                    id: saveBtn
                    enabled: !root.isRunning
                    text: "save"
                }
            }
        }


    }
}
