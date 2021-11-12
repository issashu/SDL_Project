//
// Created by Iordan Tonchev on 12.11.21.
//

#include "Graphics/DrawParalaxBackgrounds.h"

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