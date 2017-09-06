#include "TextureManger.h"


cTextureManger::cTextureManger(){
	#ifdef __APPLE__  
    
    if (!LoadTexture(resourcePath()+"isometric/astronaut_N.png", OBJ_ASTRONAUT_N))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/astronaut_E.png", OBJ_ASTRONAUT_E))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/astronaut_W.png", OBJ_ASTRONAUT_W))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/astronaut_S.png", OBJ_ASTRONAUT_S))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/astronaut_NE.png", OBJ_ASTRONAUT_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/astronaut_NW.png", OBJ_ASTRONAUT_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/astronaut_SE.png", OBJ_ASTRONAUT_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/astronaut_SW.png", OBJ_ASTRONAUT_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/alien_N.png", OBJ_ALIEN_N))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alien_E.png", OBJ_ALIEN_E))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alien_W.png", OBJ_ALIEN_W))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alien_S.png", OBJ_ALIEN_S))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alien_NE.png", OBJ_ALIEN_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alien_NW.png", OBJ_ALIEN_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alien_SE.png", OBJ_ALIEN_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alien_SW.png", OBJ_ALIEN_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/groundTile_NW.png", OBJ_GROUND_TILE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/groundTileRough_NE.png", OBJ_GROUND_TILE_ROUGH1))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/groundTileRough_NW.png", OBJ_GROUND_TILE_ROUGH2))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/buildingCorridorOpen_NE.png", OBJ_BUILDING_CORRIDOR_OPEN_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/buildingCorridorOpen_NW.png", OBJ_BUILDING_CORRIDOR_OPEN_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/buildingCorridorOpen_SE.png", OBJ_BUILDING_CORRIDOR_OPEN_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/buildingCorridorOpen_SW.png", OBJ_BUILDING_CORRIDOR_OPEN_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/buildingOpen_NE.png", OBJ_BUILDING_OPEN_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/buildingOpen_NW.png", OBJ_BUILDING_OPEN_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/buildingOpen_SE.png", OBJ_BUILDING_OPEN_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/buildingOpen_SW.png", OBJ_BUILDING_OPEN_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/frameLowTile_NE.png", OBJ_FRAME_LOW_TILE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/frameLowTile_NW.png", OBJ_FRAME_LOW_TILE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/frameLowTile_SE.png", OBJ_FRAME_LOW_TILE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/frameLowTile_SW.png", OBJ_FRAME_LOW_TILE_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/frameHighTile_NE.png", OBJ_FRAME_HIGH_TILE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/frameHighTile_NW.png", OBJ_FRAME_HIGH_TILE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/frameHighTile_SE.png", OBJ_FRAME_HIGH_TILE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/frameHighTile_SW.png", OBJ_FRAME_HIGH_TILE_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/consoleScreen_NE.png", OBJ_CONSOLE_SCREEN_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/consoleScreen_NW.png", OBJ_CONSOLE_SCREEN_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/consoleScreen_SE.png", OBJ_CONSOLE_SCREEN_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/consoleScreen_SW.png", OBJ_CONSOLE_SCREEN_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/satelliteDishAntenna_NE.png", OBJ_SATELLITE_DISH_ANTENNA_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/satelliteDishAntenna_NW.png", OBJ_SATELLITE_DISH_ANTENNA_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/satelliteDishAntenna_SE.png", OBJ_SATELLITE_DISH_ANTENNA_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/satelliteDishAntenna_SW.png", OBJ_SATELLITE_DISH_ANTENNA_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/satelliteDishLarge_NE.png", OBJ_SATELLITE_DISH_ANTENNA_LARGE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/satelliteDishLarge_NW.png", OBJ_SATELLITE_DISH_ANTENNA_LARGE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/satelliteDishLarge_SE.png", OBJ_SATELLITE_DISH_ANTENNA_LARGE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/satelliteDishLarge_SW.png", OBJ_SATELLITE_DISH_ANTENNA_LARGE_SW))
        exit(0);
    
    
    if (!LoadTexture(resourcePath()+"isometric/itemWeapon_NE.png", OBJ_ITEM_WEAPON_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/itemWeapon_NW.png", OBJ_ITEM_WEAPON_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/itemWeapon_SE.png", OBJ_ITEM_WEAPON_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/itemWeapon_SW.png", OBJ_ITEM_WEAPON_SW))
        exit(0);
    
    
    if (!LoadTexture(resourcePath()+"isometric/rocksTallOre_NE.png", OBJ_URANIUM_TALL_ORE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksTallOre_NW.png", OBJ_URANIUM_TALL_ORE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksTallOre_SE.png", OBJ_URANIUM_TALL_ORE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksTallOre_SW.png", OBJ_URANIUM_TALL_ORE_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/rocksTall_NE.png", OBJ_STONE_TALL_ORE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksTall_NW.png", OBJ_STONE_TALL_ORE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksTall_SE.png", OBJ_STONE_TALL_ORE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksTall_SW.png", OBJ_STONE_TALL_ORE_SW))
        exit(0);
    
    
    
    
    if (!LoadTexture(resourcePath()+"isometric/rocksSmallOre_NE.png", OBJ_URANIUM_SMALL_ORE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksSmallOre_NW.png", OBJ_URANIUM_SMALL_ORE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksSmallOre_SE.png", OBJ_URANIUM_SMALL_ORE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksSmallOre_SW.png", OBJ_URANIUM_SMALL_ORE_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/rocksSmall_NE.png", OBJ_STONE_SMALL_ORE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksSmall_NW.png", OBJ_STONE_SMALL_ORE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksSmall_SE.png", OBJ_STONE_SMALL_ORE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/rocksSmall_SW.png", OBJ_STONE_SMALL_ORE_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/pipeCorner_NE.png", OBJ_PIPE_CORNER_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeCorner_NW.png", OBJ_PIPE_CORNER_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeCorner_SE.png", OBJ_PIPE_CORNER_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeCorner_SW.png", OBJ_PIPE_CORNER_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/pipeStraight_NE.png", OBJ_PIPE_STRAIGHT_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeStraight_NW.png", OBJ_PIPE_STRAIGHT_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeStraight_SE.png", OBJ_PIPE_STRAIGHT_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeStraight_SW.png", OBJ_PIPE_STRAIGHT_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/pipeSplit_NE.png", OBJ_PIPE_SPLIT_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeSplit_NW.png", OBJ_PIPE_SPLIT_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeSplit_SE.png", OBJ_PIPE_SPLIT_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/pipeSplit_SW.png", OBJ_PIPE_SPLIT_SW))
        exit(0);
    
    
    if (!LoadTexture(resourcePath()+"isometric/barrelLarge_NE.png", OBJ_BARREL_LARGE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/barrelLarge_NW.png", OBJ_BARREL_LARGE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/barrelLarge_SE.png", OBJ_BARREL_LARGE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/barrelLarge_SW.png", OBJ_BARREL_LARGE_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/alienBones_NE.png", OBJ_ALIEN_BONES_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alienBones_NW.png", OBJ_ALIEN_BONES_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alienBones_SE.png", OBJ_ALIEN_BONES_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/alienBones_SW.png", OBJ_ALIEN_BONES_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/craterLarge_NE.png", OBJ_CRATER_LARGE_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/craterLarge_NW.png", OBJ_CRATER_LARGE_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/craterLarge_SE.png", OBJ_CRATER_LARGE_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/craterLarge_SW.png", OBJ_CRATER_LARGE_SW))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/meteorHalf_NE.png", OBJ_METEOR_HALF_NE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/meteorHalf_NW.png", OBJ_METEOR_HALF_NW))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/meteorHalf_SE.png", OBJ_METEOR_HALF_SE))
        exit(0);
    if (!LoadTexture(resourcePath()+"isometric/meteorHalf_SW.png", OBJ_METEOR_HALF_SW))
        exit(0);
    
    
    
    if (!LoadTexture(resourcePath()+"isometric/spaceCraft4_W.png", OBJ_SPACECRAT4_W))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"isometric/spaceCraft5_SW.png", OBJ_SPACESHIP_DESTROYED))
        exit(0);
    
    
    
    
    
    
    
    if (!LoadTexture(resourcePath()+"ui/metal_ico.png", OBJ_ICON_METAL))
        exit(0);
    if (!LoadTexture(resourcePath()+"ui/stone_ico.png", OBJ_ICON_STONE))
        exit(0);
    if (!LoadTexture(resourcePath()+"ui/URANIUM_ico.png", OBJ_ICON_URANIUM))
        exit(0);
    
    
     
    
    if (!LoadTexture(resourcePath()+"ui/X1.png", OBJ_BUTTON_X1))
        exit(0);
    if (!LoadTexture(resourcePath()+"ui/X2.png", OBJ_BUTTON_X2))
        exit(0);
    if (!LoadTexture(resourcePath()+"ui/X3.png", OBJ_BUTTON_X3))
        exit(0);
    
    
    if (!LoadTexture(resourcePath()+"ui/X1.png", OBJ_BUTTON_X1))
        exit(0);
    if (!LoadTexture(resourcePath()+"ui/X2.png", OBJ_BUTTON_X2))
        exit(0);
    if (!LoadTexture(resourcePath()+"ui/X3.png", OBJ_BUTTON_X3))
        exit(0);
    
    if (!LoadTexture(resourcePath()+"ui/BUILD_ICO1.png", OBJ_BUILD_ICO1))
        exit(0);
    if (!LoadTexture(resourcePath()+"ui/BUILD_ICO2.png", OBJ_BUILD_ICO2))
        exit(0);
    if (!LoadTexture(resourcePath()+"ui/BUILD_ICO3.png", OBJ_BUILD_ICO3))
        exit(0);

    
    
	#else
	if (!LoadTexture("gfx/isometric/astronaut_N.png", OBJ_ASTRONAUT_N))
	exit(0);
	if (!LoadTexture("gfx/isometric/astronaut_E.png", OBJ_ASTRONAUT_E))
	exit(0);
	if (!LoadTexture("gfx/isometric/astronaut_W.png", OBJ_ASTRONAUT_W))
	exit(0);
	if (!LoadTexture("gfx/isometric/astronaut_S.png", OBJ_ASTRONAUT_S))
	exit(0);
	if (!LoadTexture("gfx/isometric/astronaut_NE.png", OBJ_ASTRONAUT_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/astronaut_NW.png", OBJ_ASTRONAUT_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/astronaut_SE.png", OBJ_ASTRONAUT_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/astronaut_SW.png", OBJ_ASTRONAUT_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/alien_N.png", OBJ_ALIEN_N))
	exit(0);
	if (!LoadTexture("gfx/isometric/alien_E.png", OBJ_ALIEN_E))
	exit(0);
	if (!LoadTexture("gfx/isometric/alien_W.png", OBJ_ALIEN_W))
	exit(0);
	if (!LoadTexture("gfx/isometric/alien_S.png", OBJ_ALIEN_S))
	exit(0);
	if (!LoadTexture("gfx/isometric/alien_NE.png", OBJ_ALIEN_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/alien_NW.png", OBJ_ALIEN_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/alien_SE.png", OBJ_ALIEN_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/alien_SW.png", OBJ_ALIEN_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/groundTile_NW.png", OBJ_GROUND_TILE))
	exit(0);
	if (!LoadTexture("gfx/isometric/groundTileRough_NE.png", OBJ_GROUND_TILE_ROUGH1))
	exit(0);
	if (!LoadTexture("gfx/isometric/groundTileRough_NW.png", OBJ_GROUND_TILE_ROUGH2))
	exit(0);

	if (!LoadTexture("gfx/isometric/buildingCorridorOpen_NE.png", OBJ_BUILDING_CORRIDOR_OPEN_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/buildingCorridorOpen_NW.png", OBJ_BUILDING_CORRIDOR_OPEN_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/buildingCorridorOpen_SE.png", OBJ_BUILDING_CORRIDOR_OPEN_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/buildingCorridorOpen_SW.png", OBJ_BUILDING_CORRIDOR_OPEN_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/buildingOpen_NE.png", OBJ_BUILDING_OPEN_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/buildingOpen_NW.png", OBJ_BUILDING_OPEN_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/buildingOpen_SE.png", OBJ_BUILDING_OPEN_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/buildingOpen_SW.png", OBJ_BUILDING_OPEN_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/frameLowTile_NE.png", OBJ_FRAME_LOW_TILE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/frameLowTile_NW.png", OBJ_FRAME_LOW_TILE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/frameLowTile_SE.png", OBJ_FRAME_LOW_TILE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/frameLowTile_SW.png", OBJ_FRAME_LOW_TILE_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/frameHighTile_NE.png", OBJ_FRAME_HIGH_TILE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/frameHighTile_NW.png", OBJ_FRAME_HIGH_TILE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/frameHighTile_SE.png", OBJ_FRAME_HIGH_TILE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/frameHighTile_SW.png", OBJ_FRAME_HIGH_TILE_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/consoleScreen_NE.png", OBJ_CONSOLE_SCREEN_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/consoleScreen_NW.png", OBJ_CONSOLE_SCREEN_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/consoleScreen_SE.png", OBJ_CONSOLE_SCREEN_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/consoleScreen_SW.png", OBJ_CONSOLE_SCREEN_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/satelliteDishAntenna_NE.png", OBJ_SATELLITE_DISH_ANTENNA_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/satelliteDishAntenna_NW.png", OBJ_SATELLITE_DISH_ANTENNA_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/satelliteDishAntenna_SE.png", OBJ_SATELLITE_DISH_ANTENNA_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/satelliteDishAntenna_SW.png", OBJ_SATELLITE_DISH_ANTENNA_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/satelliteDishLarge_NE.png", OBJ_SATELLITE_DISH_ANTENNA_LARGE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/satelliteDishLarge_NW.png", OBJ_SATELLITE_DISH_ANTENNA_LARGE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/satelliteDishLarge_SE.png", OBJ_SATELLITE_DISH_ANTENNA_LARGE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/satelliteDishLarge_SW.png", OBJ_SATELLITE_DISH_ANTENNA_LARGE_SW))
	exit(0);


	if (!LoadTexture("gfx/isometric/itemWeapon_NE.png", OBJ_ITEM_WEAPON_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/itemWeapon_NW.png", OBJ_ITEM_WEAPON_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/itemWeapon_SE.png", OBJ_ITEM_WEAPON_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/itemWeapon_SW.png", OBJ_ITEM_WEAPON_SW))
	exit(0);


	if (!LoadTexture("gfx/isometric/rocksTallOre_NE.png", OBJ_URANIUM_TALL_ORE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksTallOre_NW.png", OBJ_URANIUM_TALL_ORE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksTallOre_SE.png", OBJ_URANIUM_TALL_ORE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksTallOre_SW.png", OBJ_URANIUM_TALL_ORE_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/rocksTall_NE.png", OBJ_STONE_TALL_ORE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksTall_NW.png", OBJ_STONE_TALL_ORE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksTall_SE.png", OBJ_STONE_TALL_ORE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksTall_SW.png", OBJ_STONE_TALL_ORE_SW))
	exit(0);




	if (!LoadTexture("gfx/isometric/rocksSmallOre_NE.png", OBJ_URANIUM_SMALL_ORE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksSmallOre_NW.png", OBJ_URANIUM_SMALL_ORE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksSmallOre_SE.png", OBJ_URANIUM_SMALL_ORE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksSmallOre_SW.png", OBJ_URANIUM_SMALL_ORE_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/rocksSmall_NE.png", OBJ_STONE_SMALL_ORE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksSmall_NW.png", OBJ_STONE_SMALL_ORE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksSmall_SE.png", OBJ_STONE_SMALL_ORE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/rocksSmall_SW.png", OBJ_STONE_SMALL_ORE_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/pipeCorner_NE.png", OBJ_PIPE_CORNER_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeCorner_NW.png", OBJ_PIPE_CORNER_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeCorner_SE.png", OBJ_PIPE_CORNER_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeCorner_SW.png", OBJ_PIPE_CORNER_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/pipeStraight_NE.png", OBJ_PIPE_STRAIGHT_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeStraight_NW.png", OBJ_PIPE_STRAIGHT_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeStraight_SE.png", OBJ_PIPE_STRAIGHT_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeStraight_SW.png", OBJ_PIPE_STRAIGHT_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/pipeSplit_NE.png", OBJ_PIPE_SPLIT_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeSplit_NW.png", OBJ_PIPE_SPLIT_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeSplit_SE.png", OBJ_PIPE_SPLIT_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/pipeSplit_SW.png", OBJ_PIPE_SPLIT_SW))
	exit(0);


	if (!LoadTexture("gfx/isometric/barrelLarge_NE.png", OBJ_BARREL_LARGE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/barrelLarge_NW.png", OBJ_BARREL_LARGE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/barrelLarge_SE.png", OBJ_BARREL_LARGE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/barrelLarge_SW.png", OBJ_BARREL_LARGE_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/alienBones_NE.png", OBJ_ALIEN_BONES_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/alienBones_NW.png", OBJ_ALIEN_BONES_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/alienBones_SE.png", OBJ_ALIEN_BONES_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/alienBones_SW.png", OBJ_ALIEN_BONES_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/craterLarge_NE.png", OBJ_CRATER_LARGE_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/craterLarge_NW.png", OBJ_CRATER_LARGE_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/craterLarge_SE.png", OBJ_CRATER_LARGE_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/craterLarge_SW.png", OBJ_CRATER_LARGE_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/meteorHalf_NE.png", OBJ_METEOR_HALF_NE))
	exit(0);
	if (!LoadTexture("gfx/isometric/meteorHalf_NW.png", OBJ_METEOR_HALF_NW))
	exit(0);
	if (!LoadTexture("gfx/isometric/meteorHalf_SE.png", OBJ_METEOR_HALF_SE))
	exit(0);
	if (!LoadTexture("gfx/isometric/meteorHalf_SW.png", OBJ_METEOR_HALF_SW))
	exit(0);

	if (!LoadTexture("gfx/isometric/spaceCraft4_W.png", OBJ_SPACECRAT4_W))
	exit(0);

	if (!LoadTexture("gfx/isometric/spaceCraft5_SW.png", OBJ_SPACESHIP_DESTROYED))
	exit(0);



	if (!LoadTexture("gfx/ui/metal_ico.png", OBJ_ICON_METAL))
	exit(0);
	if (!LoadTexture("gfx/ui/stone_ico.png", OBJ_ICON_STONE))
	exit(0);
	if (!LoadTexture("gfx/ui/URANIUM_ico.png", OBJ_ICON_URANIUM))
	exit(0);

 

	if (!LoadTexture("gfx/ui/X1.png", OBJ_BUTTON_X1))
		exit(0);
	if (!LoadTexture("gfx/ui/X2.png", OBJ_BUTTON_X2))
		exit(0);
	if (!LoadTexture("gfx/ui/X3.png", OBJ_BUTTON_X3))
		exit(0);

	if (!LoadTexture("gfx/ui/BUILD_ICO1.png", OBJ_BUILD_ICO1))
		exit(0);
	if (!LoadTexture("gfx/ui/BUILD_ICO2.png", OBJ_BUILD_ICO2))
		exit(0);
	if (!LoadTexture("gfx/ui/BUILD_ICO3.png", OBJ_BUILD_ICO3))
		exit(0);


	#endif  
}

cTextureManger::~cTextureManger(){
    
}


bool cTextureManger::LoadTexture(std::string fname, int ID){
    if (!tex[ID].loadFromFile(fname)){
        std::cout<<"[ERROR] cannot load "<<fname<<"\n";
        return false;
    }
    
    std::cout<<"[INFO] "<<fname<<" loaded\n";
    return true;
}

sf::Texture *cTextureManger::GetTexture(int ID){
    return &tex[ID];
}
