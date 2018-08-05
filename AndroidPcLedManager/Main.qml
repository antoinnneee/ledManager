import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2

import QtQuick.Window 2.0
Item {
    property real milimetter: Screen.pixelDensity * Screen.devicePixelRatio
    property real redColorSel: 0
    property real greenColorSel: 0
    property real blueColorSel: 0
    width: 256
    height: 256
    signal colorUpdated(real red, real green, real blue)
    signal lightIntensityUpdated(real light)

        function updateSelectedColor()
        {

            var selected_red =
                    (1 - (cursor.y / globalColorSelector.height)) *
                    (1 + (cursor.x / globalColorSelector.width) * (redColorSel - 1))
            var selected_green =
                    (1 - (cursor.y / globalColorSelector.height)) *
                    (1 + (cursor.x / globalColorSelector.width) * (greenColorSel - 1))
            var selected_blue =
                    (1 - (cursor.y / globalColorSelector.height)) *
                    (1 + (cursor.x / globalColorSelector.width) * (blueColorSel - 1))
            console.log("FINAL RGB",selected_red, selected_green, selected_blue)
            colorUpdated(selected_red, selected_green, selected_blue)
        }
    Item {
        id: globalColorSelector
        anchors.right: generalColorSelector.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 0


        Rectangle
        {
            width: parent.height
            height: parent.width
            transform: Rotation { angle: 90}
            x: parent.width
            y: 0
            gradient: Gradient
            {
                GradientStop { position: 0.0; color: Qt.rgba(redColorSel, greenColorSel, blueColorSel, 1)}
                GradientStop { position: 1.0; color: "white" }
            }
        }

        Rectangle
        {
            anchors.fill: parent
            gradient: Gradient
            {
                GradientStop { position: 0.0; color: Qt.rgba(0, 0, 0, 0) }
                GradientStop { position: 1.0; color: Qt.rgba(0, 0, 0, 1) }
            }
        }

        Image
        {
            id: cursor
            x: width/2
            y: height/2
            source: "qrc:/cursor.png"
        }

        MouseArea
        {
            acceptedButtons: Qt.LeftButton
            anchors.fill: parent
            onPressed:
            {
                cursor.x = mouseX - 4
                cursor.y = mouseY - 4
                updateSelectedColor()
            }
            onPositionChanged:
            {
                cursor.x = mouseX - 4
                cursor.y = mouseY - 4
                updateSelectedColor()
            }
        }

    }
    Rectangle {
        id: generalColorSelector
        x: 190
        width: 10*milimetter
        radius: 4
        border.width: 1
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ff0000"
            }

            GradientStop {
                position: 0.166
                color: "#ffff00"
            }

            GradientStop {
                position: 0.333
                color: "#00ff00"
            }

            GradientStop {
                position: 0.499
                color: "#00ffff"
            }

            GradientStop {
                position: 0.666
                color: "#0000ff"
            }
            GradientStop {
                position: 0.833
                color: "#ff00ff"
            }

            GradientStop {
                position: 1.00
                color: "#ff0000"
            }
        }//*milimetter
        anchors.right: lightIntensity.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onMouseYChanged: {
                var realPos = mouseY / generalColorSelector.height
                var percentColor = 0
                if (realPos <= 0.166)
                {
                    percentColor = realPos * 6
                    redColorSel = 1
                    greenColorSel = 1 * percentColor
                    blueColorSel = 0
                }
                else if (realPos <= 0.333)
                {
                    percentColor = 1 - ((realPos - 0.166) * 6)
                    redColorSel = 1 * percentColor
                    greenColorSel = 1
                    blueColorSel = 0
                }
                else if (realPos <= 0.499)
                {
                    percentColor = (realPos - 0.333) * 6
                    redColorSel = 0
                    greenColorSel = 1
                    blueColorSel = 1 * percentColor
                }
                else if (realPos <= 0.666)
                {
                    percentColor = 1 - ((realPos - 0.499) * 6)
                    redColorSel = 0
                    greenColorSel = 1 * percentColor
                    blueColorSel = 1
                }
                else if (realPos <= 0.833)
                {
                    percentColor = (realPos - 0.666) * 6
                    redColorSel = 1 * percentColor
                    greenColorSel = 0
                    blueColorSel = 1
                }
                else if (realPos <= 1)
                {
                    percentColor = 1 - (realPos - 0.833) * 6
                    redColorSel = 1
                    greenColorSel = 0
                    blueColorSel = 1 * percentColor
                }
                colorUpdated(redColorSel, greenColorSel, blueColorSel)
                console.log("RGB", redColorSel, greenColorSel, blueColorSel)
            }
        }
    }

    Rectangle {
        id: lightIntensity
        x: 184
        y: -4
        width: 9*milimetter
        radius: 4
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ffffff"
            }
            GradientStop {
                position: 1
                color: "#000000"
            }
        }
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onMouseYChanged: {
                var realPos = mouseY / generalColorSelector.height
                lightIntensityUpdated(realPos);
            }
        }
        border.width: 1
        anchors.right: parent.right
    }
}
