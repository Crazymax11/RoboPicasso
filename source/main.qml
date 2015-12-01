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
    property int mutationParametrsNum: mutationParametrsSlider.value
    property double minimalOpacity: minimalOpacitySlider.value/100
    property int populationNum: Math.round(populationNumSlider.value)
    property int figuresNum: Math.round(figuresNumSlider.value)
    property url tarImage: openFile.fileUrl
    property int generationIndex: 0
    property int bestValueIndex: 0


    signal setGenerationIndex(int num)
    onSetGenerationIndex: generationIndex=num


    //не знаю как соединит нативный qml сигнал
    signal newMutationChance(double val)
    onMutationChanceChanged: newMutationChance(mutationChance)
    signal newMutationAmount(double val)
    onMutationAmountChanged: newMutationAmount(mutationAmount)
    signal newMutationFigures(double val)
    onMutationFiguresChanged: newMutationFigures(mutationFigures)
    signal newMutationParametrsNum(int val)
    onMutationParametrsNumChanged: newMutationParametrsNum(mutationParametrsNum)
    signal newMinimalOpacity(double val)
    onMinimalOpacityChanged: newMinimalOpacity(minimalOpacity)

    signal shake(bool isBig)


    property int bestResValue: 0
    onBestResValueChanged: bestValueIndex=generationIndex
    property string bestResultSource: "image://imageProvider/image.png"
    signal start()
    signal resume()
    signal pause()
    onStart: {isRunning = true; isStarted = true;isImageShowing = true;}
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
            property bool isImageShowing: false

            Image{
                id: bestResult
                anchors.fill: parent
                source: imRect.isImageShowing ? root.bestResultSource : openFile.fileUrl
                cache: false
                RowLayout{
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height: parent.height* 0.15
                    Text{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        id: generationindexText
                        fontSizeMode: Text.Fit
                        text: unchangedBestInsteadGenNumCheckBox.checked? "поколений без улучшений " + (root.generationIndex - root.bestValueIndex) : "текущее поколение " + root.generationIndex
                        font.pointSize: 50
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        style: Text.Outline;
                        styleColor: "white"
                    }

                    Text{
                        id: bestResultText
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        fontSizeMode: Text.Fit
                        text: "лучший результат " + root.bestResValue
                        font.pointSize: 50
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        style: Text.Outline;
                        styleColor: "white"
                    }
                }
            }
            Button{
                id: tarImageBtn
                onClicked: imRect.isImageShowing=!imRect.isImageShowing
                anchors.top: parent.top
                anchors.right: parent.right
                height: 20
                width: 60
                text: imRect.isImageShowing? "картинка" : "фигуры"
            }

            Button{
                //пока уберем
                visible: false
                id: graphicBtn
                anchors.top: parent.top
                anchors.right: parent.right
                height: 20
                width: 60
                text: imRect.isImageShowing? "график" : "изображение"
                onClicked: imRect.isImageShowing=!imRect.isImageShowing
            }
        }

        Rectangle
        {
            height: parent.height - 2
            width: parent.width*0.3 - 10
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
                    text: "количество мутирующих параметров : " + mutationParametrsSlider.value
                }
                Slider{
                    id: mutationParametrsSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 6
                    minimumValue: 1
                    stepSize: 1
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
                CheckBox{
                    id: unchangedBestInsteadGenNumCheckBox
                    text: "Показывать количество поколений стагнации"
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

                RowLayout{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Button{
                        id: smallShake
                        text: "встряска"
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        onClicked: root.shake(false)
                    }
                    Button{
                        id: bigShake
                        text: "катаклизм"
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        onClicked: root.shake(true)
                    }
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
