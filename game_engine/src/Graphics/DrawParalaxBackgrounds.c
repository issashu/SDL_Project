//
// Created by Iordan Tonchev on 12.11.21.
//

#include "Graphics/DrawParalaxBackgrounds.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Managers/TextureManager.h"

/*
 * 1. RESEARCH: Create vectors for each screen layer and push what needs to be drawn inside in order of appearance
 * 1. Load background textures in order of layers
 * 2. Call storage BackgroundsLayers
 * 3. Get total size of the storage vector
 * 4. In a loop draw each layer
 * 5. Set speed of layer to  5-10% speed of players (needs double checking of speed)
 * 6. Present to renderer
 * 7. Make sure there is a flag to avoid drawing multiple times (just one delivery on level load).
 * */

/*
 * Loading of textures done quick and dirty, until a better way to load consecutive files from a directory is researched
 * */

static STRING Layer[4][4];

void loadLayerPaths() {
    Layer[0][0] = ASSETS_PATH "images/Background/Layer_0_0.png";
    Layer[0][1] = ASSETS_PATH "images/Background/Layer_0_1.png";
    Layer[0][2] = ASSETS_PATH "images/Background/Layer_0_2.png";
    Layer[1][0] = ASSETS_PATH "images/Background/Layer_1_0.png";
    Layer[1][1] = ASSETS_PATH "images/Background/Layer_1_1.png";
    Layer[1][2] = ASSETS_PATH "images/Background/Layer_1_2.png";
    Layer[2][0] = ASSETS_PATH "images/Background/Layer_2_0.png";
    Layer[2][1] = ASSETS_PATH "images/Background/Layer_2_1.png";
    Layer[2][2] = ASSETS_PATH "images/Background/Layer_2_1.png";
    Layer[3][0] = ASSETS_PATH "images/Background/Layer_3_0.png";
    Layer[3][1] = ASSETS_PATH "images/Background/Layer_3_1.png";
    Layer[3][2] = ASSETS_PATH "images/Background/Layer_3_2.png";
    Layer[3][3] = ASSETS_PATH "images/Background/Layer_3_3.png";
}

void LoadImageLayer(ImageLayer **BackgroundSet, int32_t LayerIndex, int32_t ImageCount, int32_t Width, int32_t Height,
                    int32_t ScrollSpeed, BOOL isLooped, BOOL isFlipped, UNUSED STRING *ImageMap) {
    //FIXME Refactor the method, once above is solved...quick and ugly below
    // ...avoid the pointer arithmetic for 2D array ImageMap
    loadLayerPaths();
    initLayeredImage(BackgroundSet, ImageCount, Width, Height, LayerIndex, ScrollSpeed, isLooped, isFlipped);

    for(int32_t ImageIndex = 0; ImageIndex < (ImageCount); ImageIndex++) {
        loadImageSurfaces(getTexturesContainer(*BackgroundSet), Layer[LayerIndex][ImageIndex]);
    }
}

void UnloadImageLayer(ImageLayer **BackgroundSet) {
        unloadTextures(getTexturesContainer(*BackgroundSet));
        free(*BackgroundSet);
        *BackgroundSet = NONE;
}