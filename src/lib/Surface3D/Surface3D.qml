import QtQuick 2.10
import QtDataVisualization 1.0

Item {
    id: surfaceView
    property alias model: surfaceDataProxy.itemModel
    anchors.fill: parent

    ColorGradient {
        id: surfaceGradient
        ColorGradientStop { position: 0.0; color: "darkslategray" }
        ColorGradientStop { id: middleGradient; position: 0.25; color: "peru" }
        ColorGradientStop { position: 1.0; color: "red" }
    }

    Surface3D {
        id: surfacePlot
        width: surfaceView.width
        height: surfaceView.height
        theme: Theme3D {
            type: Theme3D.ThemeStoneMoss
            font.family: "STCaiyun"
            font.pointSize: 35
            colorStyle: Theme3D.ColorStyleRangeGradient
            baseGradients: [surfaceGradient]
        }
        shadowQuality: AbstractGraph3D.ShadowQualityNone
        scene.activeCamera.cameraPreset: Camera3D.CameraPresetIsometricLeft

        Surface3DSeries {
            id: surface3DSeries
            drawMode: Surface3DSeries.DrawSurface

            flatShadingEnabled: false

            ItemModelSurfaceDataProxy {
                id: surfaceDataProxy
                rowRole: "x"
                columnRole: "y"
                yPosRole: "z"
            }
        }
    }
}
