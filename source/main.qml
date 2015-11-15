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
    property double mutationChance: mutationChanceSlider/100
    property double mutationAmount: mutationAmountSlider/100
    property double mutationFigures: mutationFiguresSlider/100
    property double minimalOpacity: minimalOpacitySlider/100
    property int populationNum: Math.round(populationNumSlider)
    property int figuresNum: Math.round(figuresNumSlider)
    property url tarImage: openFile.fileUrl
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
                    id: bestResult
                    Layout.fillHeight: true
                    Layout.fillWidth: true
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
                    text: root.isRunning? "pause": "start"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
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
