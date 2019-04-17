import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("TCPServer")
    Row {
        Button {
            text: "监听"
            onClicked: {
                tcpMgr.start();
            }
        }
        Button {
            text: "不监听"
            onClicked: {
                tcpMgr.stop();
            }
        }
    }
    ScrollView {
        TextArea {
            id: textArea
            y: 50
            width: parent.width
            height: parent.height - y
        }
    }
    Connections {
        target: tcpMgr
        ignoreUnknownSignals: true
        onInfoReady: {
            console.log(info)
            textArea.append(info);
            if (textArea.text.length > 1024 )
            {
                textArea.clear()
            }
        }
    }
}
