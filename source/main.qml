import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
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
    property int untouchablesNum: untouchablesSlider.value

    property int mitosNum: mitosSlider.value
    property double minimalOpacity: minimalOpacitySlider.value/100
    property int populationNum: Math.round(populationNumSlider.value)
    property int populationCrossoverKoef: populationCrossoverSlider.value
    property double populationSelectionKoef: populationSelectionSlider.value

    property int figuresNum: Math.round(figuresNumSlider.value)
    property url tarImage: openFile.fileUrl
    property int generationIndex: 0
    property int bestValueIndex: 0
    property bool saveAll: saveEveryNewBest.checked
    property url savePath: saveResultsPathDialog
    property bool saveAsJsonBool: false

    onSaveAsJsonBoolChanged: setSaveAsJson(saveAsJsonBool)
    signal setSaveAsJson(bool newval)



    onPopulationCrossoverKoefChanged: setPopulationCrossoverKoef(populationCrossoverKoef)
    signal setPopulationCrossoverKoef(int num)

    onPopulationSelectionKoefChanged: setPopulationSelectionKoef(populationSelectionKoef)
    signal setPopulationSelectionKoef(double num)

    onSavePathChanged: setSavePath(savePath)
    signal setSavePath(url newpath)

    signal setSaveAll(bool newval)
    onSaveAllChanged: setSaveAll(saveAll)

    signal saveCurrentBest();

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
    signal setUntouchablesNum(int val)
    onUntouchablesNumChanged: setUntouchablesNum(untouchablesNum)
    signal setMitosNum(int num)
    onMitosNumChanged: setMitosNum(mitosNum)

    signal shake(bool isBig)

    property double smallShakeRange: smallShakeRangeSlider.value
    property int bigShakeRange: bigShakeRangeSlider.value
    property int smallShakeInterval: smallShakeIntervalSlider.value
    property int bigShakeInterval: bigShakeIntervalSlider.value

    signal setSmallShakeRange(double newrange)
    signal setBigShakeRange(int newrange)
    signal setSmallShakeInterval(int newinterval)
    signal setBigShakeInterval(int newinterval)

    onSmallShakeRangeChanged: setSmallShakeRange(smallShakeRange)
    onSmallShakeIntervalChanged: setSmallShakeInterval(smallShakeInterval)
    onBigShakeIntervalChanged: setBigShakeInterval(bigShakeInterval)
    onBigShakeRangeChanged: setBigShakeRange(bigShakeRange)

    property int bestResValue: 0
    onBestResValueChanged: bestValueIndex=generationIndex
    property string bestResultSource: "image://imageProvider/image.png"
    signal start()
    signal resume()
    signal pause()
    onStart: {isRunning = true; isStarted = true;imRect.isImageShowing = true;}
    onPause: {isRunning = false}
    onResume: (isRunning = true)
    function updateImage(){
        bestResultSource = "";
        bestResultSource = "image://imageProvider/image.png";
    }


    signal visualize()

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
        Rectangle{
            id: settingsRect
            height: parent.height - 2
            width: parent.width*0.3 - 10
            border.width: 2
            border.color: "black"
            color: "silver"
            state: "популяция"
            radius: 10
            states: [
                State{
                    name: "настройки"
                    PropertyChanges {
                        target: settingsTab
                        visible: true
                    }

                },
                State{
                    name: "мутация"
                    PropertyChanges {
                        target: mutationTab
                        visible: true
                    }
                },
                State{
                    name: "популяция"
                    PropertyChanges {
                        target: populationTab
                        visible: true
                    }
                }
            ]
            RowLayout{
                id: tabs
                anchors.top: parent.top
                height: parent.height*0.15
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 5
                spacing: 5
                Rectangle{
                    color: mutationTab.visible? "#C0392B" :"#E74C3C"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    radius: 10
                    Image{
                        anchors.fill: parent
                        source: "qrc:/images/mutation-icon.png"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: settingsRect.state = "мутация"
                    }
                }
                Rectangle{
                    color: populationTab.visible? "#27AE60" :"#2ECC71"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    radius: 10
                    Image{
                        anchors.fill: parent
                        source: "qrc:/images/population-icon.png"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: settingsRect.state = "популяция"
                    }
                }
                Rectangle{
                    color: settingsTab.visible? "#2980B9" :"#3498DB"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    radius: 10
                    Image{
                        anchors.fill: parent
                        source: "qrc:/images/settings-icon.png"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: settingsRect.state = "настройки"
                    }
                }
            }
            //3 columnLayouts
            ColumnLayout{
                id: mutationTab
                anchors.top: tabs.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 5
                visible: false
                Text{
                    fontSizeMode: Text.Fit
                    text: "шанс мутировать у особи: " + mutationChanceSlider.value +"%"
                }
                Slider{
                    id: mutationChanceSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    value: 100
                    maximumValue: 100
                    stepSize: 0.25
                }
                Text{
                    fontSizeMode: Text.Fit
                    text: "предел мутации параметра фигуры: " +mutationAmountSlider.value +"%"
                }
                Slider{
                    id: mutationAmountSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    value: 12.5
                    maximumValue: 100
                    stepSize: 0.25
                }
                Text{
                    fontSizeMode: Text.Fit
                    text: "мутирующие фигуры: " +mutationFiguresSlider.value +"%"
                }
                Slider{
                    id: mutationFiguresSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    value: 5
                    maximumValue: 100
                    stepSize: 0.25
                }
                Text{
                    fontSizeMode: Text.Fit
                    text: "количество мутирующих параметров : " + mutationParametrsSlider.value
                }
                Slider{
                    id: mutationParametrsSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 6
                    minimumValue: 1
                    value: 1
                    stepSize: 1
                }
                Text{
                    fontSizeMode: Text.Fit
                    text: "неприкосновенные для мутаций: " + untouchablesSlider.value
                }
                Slider{
                    id: untouchablesSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 10
                    minimumValue: 0
                    value: 1
                    stepSize: 1
                }
                Text{
                    fontSizeMode: Text.Fit
                    text: "митоз сильнейшего: " + mitosSlider.value
                }
                Slider{
                    id: mitosSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 100
                    minimumValue: 0
                    value: 0
                    stepSize: 1
                }
            }
            //популяция
            ColumnLayout{
                id: populationTab

                anchors.top: tabs.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 5
                visible: false
                Text{
                    fontSizeMode: Text.Fit
                    text: "минимальная видимость: " + minimalOpacitySlider.value +"%"
                }
                Slider{
                    id: minimalOpacitySlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumValue: 100
                    value: 90
                    stepSize: 0.25
                }

                Text{
                    fontSizeMode: Text.Fit
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
                    fontSizeMode: Text.Fit
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Предел расширения популяции: " + populationCrossoverSlider.value
                }
                Slider{
                    id: populationCrossoverSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    minimumValue: 1
                    maximumValue: 10
                    value: 4
                    stepSize: 0.25
                }
                Text{
                    fontSizeMode: Text.Fit
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Остаток популяции после селекции: " + Math.round(populationSelectionSlider.value*100)/100
                }
                Slider{
                    id: populationSelectionSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    minimumValue: 0
                    maximumValue: 1
                    value: 0.7
                    stepSize: 0.01
                }
                Text{
                    fontSizeMode: Text.Fit
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
            }
            //настройки
            ColumnLayout{
                id: settingsTab
                anchors.top: tabs.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 5
                visible: false
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
                CheckBox{
                    id: unchangedBestInsteadGenNumCheckBox
                    text: "Показывать количество поколений стагнации"
                }
                Text{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    fontSizeMode: Text.Fit
                    text: "выжившие после встряски: " + (smallShakeRangeSlider.value*100)/100
                }
                Slider{
                    id: smallShakeRangeSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    minimumValue: 0
                    maximumValue: 1
                    value: 0.2
                    stepSize: 0.05
                }
                Text{
                    fontSizeMode: Text.Fit
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "интервал встряски: " + smallShakeIntervalSlider.value
                }
                Slider{
                    id: smallShakeIntervalSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    minimumValue: 0
                    maximumValue: 500
                    value: 5
                    stepSize: 1
                }
                Text{
                    fontSizeMode: Text.Fit
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "выжившие после катаклизма: " + bigShakeRangeSlider.value
                }
                Slider{
                    id: bigShakeRangeSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    minimumValue: 0
                    maximumValue: populationNumSlider.value
                    value: 1
                    stepSize: 1
                }
                Text{
                    fontSizeMode: Text.Fit
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "интервал катаклизма: " + bigShakeIntervalSlider.value
                }
                Slider{
                    id: bigShakeIntervalSlider
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    minimumValue: 0
                    maximumValue: 500
                    value: 100
                    stepSize: 1
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
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    id: saveResultPathBtn
                    onClicked: saveResultsPathDialog.open()
                    text: "директория для сохранения"
                    FileDialog{
                        id: saveResultsPathDialog
                        selectFolder: true
                    }
                }
                CheckBox{
                    id: saveEveryNewBest
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "сохранять каждый найденный лучший"
                }
                CheckBox{
                    id: saveAsJSON
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "сохранять в JSON"
                    onCheckedChanged: root.saveAsJsonBool = checked
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
                    text: "save"
                    onClicked: root.saveCurrentBest()
                }
                Button{
                    id: visualizeBtn
                    text: "визуализировать"
                    onClicked: root.visualize();
                }
            }
        }
    }
}


