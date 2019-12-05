#pragma once

namespace Settings
{

    const int c_margin = 10;

    const int c_documentSizeX = 650;
    const int c_documentSizeY = 580;

    const int c_inspectorPosX = c_documentSizeX + 2 * c_margin;
    const int c_inspectorPosY = c_margin;

    const int c_inspectorSizeX = 250;
    const int c_inspectorSizeY = 580;

    const int c_windowSizeX = c_documentSizeX + c_inspectorSizeX + c_margin * 3;
    const int c_windowSizeY = c_documentSizeY + c_margin * 2;

    const int c_windowCenterX = c_windowSizeX / 2;
    const int c_windowCenterY = c_windowSizeY / 2;
}
