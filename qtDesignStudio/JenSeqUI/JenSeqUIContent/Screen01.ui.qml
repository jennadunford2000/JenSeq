

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import JenSeqUI

Rectangle {
    width: Constants.width
    height: Constants.height
    color: "#000000"

    Image {
        id: jenseqlogo
        x: 0
        y: 8
        width: 453
        height: 201
        source: "images/jenseqlogo.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: text1
        x: 108
        y: 154
        color: "#ffffff"
        text: "Jenna's Sequencer"
        font.pointSize: 20
        font.family: "Jersey 10"
    }

    TextArea {
        id: textArea
        x: 80
        y: 413
        width: 770
        height: 425
        color: "#000000"
        text: "Hello this is the text"
        font.pointSize: 22
        layer.format: ShaderEffectSource.Alpha
        placeholderTextColor: "#d6ffffff"
        placeholderText: qsTr("Text Area")

        Rectangle {
            id: rectangle
            x: 149
            y: -19
            width: 770
            height: 425
            color: "#63c74d"
        }
    }
}
