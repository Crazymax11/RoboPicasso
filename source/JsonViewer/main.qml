import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Json Viewer")

    id: root
    signal jsonLoaded(url path)

    function updateImage(){
        image.source = "";
        image.source= "image://imageProvider/image.png";
    }

    Button{
        id: btn
        width: parent.width
        height: 30
        text: "load json"
        onClicked: fd.open()
        FileDialog{
            id: fd
            onAccepted: root.jsonLoaded(fileUrl)
        }
    }
    Image{
        id: image
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: btn.bottom
        source: "image://imageProvider/image.png"
    }
}
