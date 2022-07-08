class CfgWorlds
{
	class DefaultWorld
	{
        winterWorld=0;
        airDayTemperatureMin=10;
        airDayTemperatureMax=15;
        airNightTemperatureMin=8;
        airNightTemperatureMax=12;
        clothingHeatIsolationGlobal=0.8;
        
        temperatureHighConsumeItemsMod = 0.02;
        temperatureLowConsumeItemsMod = -0.01;
        temperatureDrinkPondPenalty = -0.005;
        temperatureDrinkWellPenalty = -0.01;
        temperatureFillWaterBottleTotal = 15;
        temperatureFillWaterBottleMod = 0.1;
        temperatureIceDrain = 0;
        temperatureSnowDrain = 0;
        temperatureHeightReduction = 0.002;
        
        clothingDrenchedHeatDrain = -5;
        clothingWetHeatDrain = -2;
        additionalTemperatureResistForSurvivalSkill = 15;
	};
	class CAWorld;
	class namalsk: CAWorld
	{
        winterWorld=1;
        airDayTemperatureMin=-15;
        airDayTemperatureMax=-10;
        airNightTemperatureMin=-20;
        airNightTemperatureMax=-15;
        clothingHeatIsolationGlobal=1.3;
        
        temperatureHighConsumeItemsMod = 0.03;
        temperatureLowConsumeItemsMod = -0.05;
        temperatureDrinkPondPenalty = -0.05;
        temperatureDrinkWellPenalty = -0.01;
        temperatureFillWaterBottleTotal = 6;
        temperatureIceDrain = -40;
        temperatureSnowDrain = -20;
        temperatureHeightReduction = 0.01;
        
        clothingDrenchedHeatDrain = -50;
        clothingWetHeatDrain = -20;
        additionalTemperatureResistForSurvivalSkill = 30;
    };
};

class RscMapControl
{
	scaleMin=4.9999999e-005;
	scaleMax=0.85000002;
	scaleDefault=0.85000002;
	ptsPerSquareSea=8;
	ptsPerSquareTxt=10;
	ptsPerSquareCLn=10;
	ptsPerSquareExp=10;
	ptsPerSquareCost=10;
	ptsPerSquareFor=99;
	ptsPerSquareForEdge=99;
	ptsPerSquareRoad=4;
	ptsPerSquareObj=15;
	maxSatelliteAlpha=1;
	alphaFadeStartScale=1;
	alphaFadeEndScale=1;
	userMapPath="dz\gear\navigation\data\usermap";
	maxUserMapAlpha=0.2;
	alphaUserMapFadeStartScale=0.5;
	alphaUserMapFadeEndScale=0.80000001;
	showCountourInterval=1;
	colorLevels[]={0.64999998,0.60000002,0.44999999,0.30000001};
	colorSea[]={0.2,0.5,0.69999999,1};
	colorForest[]={0.36000001,0.77999997,0.079999998,0};
	colorRocks[]={0.5,0.5,0.5,0.2};
	colorCountlines[]={0.85000002,0.80000001,0.64999998,0.1};
	colorMainCountlines[]={0.44999999,0.40000001,0.25,0};
	colorCountlinesWater[]={0.25,0.40000001,0.5,0.30000001};
	colorMainCountlinesWater[]={0.25,0.40000001,0.5,0.89999998};
	colorPowerLines[]={0.1,0.1,0.1,1};
	colorRailWay[]={0.80000001,0.2,0,1};
	colorForestBorder[]={0.40000001,0.80000001,0,0};
	colorRocksBorder[]={0.5,0.5,0.5,0};
	colorOutside[]={1,1,1,1};
	colorTracks[]={0.77999997,0.66000003,0.34,1};
	colorRoads[]={0.69,0.43000001,0.23,1};
	colorMainRoads[]={0.52999997,0.34999999,0,1};
	colorTracksFill[]={0.95999998,0.91000003,0.60000002,1};
	colorRoadsFill[]={0.92000002,0.73000002,0.41,1};
	colorMainRoadsFill[]={0.83999997,0.61000001,0.20999999,1};
	colorGrid[]={0.89999998,0.89999998,0.89999998,0.80000001};
	colorGridMap[]={0.89999998,0.89999998,0.89999998,0.2};
	fontNames="gui/fonts/sdf_MetronBook24";
	sizeExNames=0.029999999;
	colorNames[]={1,1,1,1};
	fontGrid="gui/fonts/sdf_MetronBook24";
	sizeExGrid=0.02;
	fontLevel="gui/fonts/sdf_MetronBook24";
	sizeExLevel=0.0099999998;
	colorMountPoint[]={0.44999999,0.40000001,0.25,0};
	mapPointDensity=0.12;
	text="";
	fontLabel="gui/fonts/sdf_MetronBook24";
	fontInfo="gui/fonts/sdf_MetronBook24";
	class Legend
	{
		x=0.050000001;
		y=0.85000002;
		w=0.40000001;
		h=0.1;
		font="gui/fonts/sdf_MetronBook24";
		sizeEx=0.02;
		colorBackground[]={1,1,1,0};
		color[]={0,0,0,0};
	};
	class Bush
	{
		icon="\dz\gear\navigation\data\map_bush_ca.paa";
		color[]={0.40000001,0.80000001,0,0};
		size=14;
		importance="0.2 * 14 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class SmallTree
	{
		icon="\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[]={0.40000001,0.80000001,0,0};
		size=12;
		importance="0.6 * 12 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Tree
	{
		icon="\dz\gear\navigation\data\map_tree_ca.paa";
		color[]={0.40000001,0.80000001,0,0};
		size=12;
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Rock
	{
		icon="\dz\gear\navigation\data\map_rock_ca.paa";
		color[]={0.1,0.1,0.1,0.80000001};
		size=12;
		importance="0.5 * 12 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Fuelstation
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\fuelstation.paa";
		size=16;
		color[]={1,1,1,1};
		importance="0.9 * 16 * 0.05";
		coefMin=0.75;
		coefMax=2;
	};
	class Lighthouse
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\lighthouse.paa";
		size=30;
		color[]={1,1,1,1};
		importance="0.9 * 16 * 0.05";
		coefMin=1;
		coefMax=4;
	};
	class Stack
	{
		icon="\dz\gear\navigation\data\map_stack_ca.paa";
		size=16;
		color[]={1,1,1,0};
		importance="0.9 * 16 * 0.05";
		coefMin=0.89999998;
		coefMax=4;
	};
	class Transmitter
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\radiotower.paa";
		color[]={1,1,1,1};
		size=30;
		importance="0.9 * 16 * 0.05";
		coefMin=0.69999999;
		coefMax=4;
	};
	class Watertower
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\watertower.paa";
		color[]={1,1,1,1};
		size=30;
		importance="0.9 * 16 * 0.05";
		coefMin=0.69999999;
		coefMax=4;
	};
	class Shipwreck
	{
		icon="\dz\gear\navigation\data\map_shipwreck_ca.paa";
		color[]={1,1,1,1};
		size=16;
		importance="0.9 * 16 * 0.05";
		coefMin=0.89999998;
		coefMax=4;
	};
	class Monument
	{
		icon="\dz\gear\navigation\data\map_monument_ca.paa";
		color[]={1,1,1,0};
		size=20;
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class BusStop
	{
		icon="\dz\gear\navigation\data\map_busstop_ca.paa";
		color[]={1,1,1,0};
		size=16;
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Fountain
	{
		icon="\dz\gear\navigation\data\map_fountain_ca.paa";
		color[]={1,1,1,0};
		size=20;
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Waterpump
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\waterpump.paa";
		color[]={1,1,1,1};
		size=20;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=2;
	};
	class Hospital
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\hospital.paa";
		color[]={1,1,1,1};
		size=25;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=2;
	};
	class Store
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\shopping.paa";
		color[]={1,1,1,1};
		size=20;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=2;
	};
	class Police
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\police.paa";
		color[]={1,1,1,1};
		size=25;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=2;
	};
	class FireDep
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\firestation.paa";
		color[]={1,1,1,1};
		size=25;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=2;
	};
	class TouristSign
	{
		icon="\dz\gear\navigation\data\map_tsign_ca.paa";
		color[]={1,1,1,0};
		size=15;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=4;
	};
	class Tourism
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\bar.paa";
		color[]={1,1,1,1};
		size=20;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=2;
	};
	class Cross
	{
		icon="\dz\gear\navigation\data\map_cross_ca.paa";
		size=20;
		color[]={1,1,0,0};
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Chapel
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\church.paa";
		color[]={1,1,1,1};
		size=25;
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=2;
	};
	class Church
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\church.paa";
		color[]={1,1,1,1};
		size=35;
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=2;
	};
	class ViewTower
	{
		icon="\VanillaPPMap\GUI\Textures\CustomMapIcons\watchtower.paa";
		color[]={1,1,1,1};
		size=22;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=2;
	};
	class TouristShelter
	{
		icon="\dz\gear\navigation\data\map_tshelter_ca.paa";
		color[]={1,1,1,1};
		size=18;
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=4;
	};
	class Quay
	{
		icon="\dz\gear\navigation\data\map_quay_ca.paa";
		size=16;
		color[]={1,1,1,1};
		importance="0.9 * 16 * 0.05";
		coefMin=0.5;
		coefMax=4;
	};
	class Bunker
	{
		icon="\dz\gear\navigation\data\map_bunker_ca.paa";
		color[]={0.60000002,0.60000002,0.60000002,1};
		size=20;
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Fortress
	{
		icon="\dz\gear\navigation\data\map_fortress_ca.paa";
		size=20;
		color[]={0.60000002,0.60000002,0.60000002,1};
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Rocks
	{
		icon="\dz\gear\navigation\data\map_rock_ca.paa";
		color[]={0.60000002,0.60000002,0.60000002,1};
		size=12;
		importance="0.9 * 16 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
	class Ruin
	{
		icon="\dz\gear\navigation\data\map_ruin_ca.paa";
		size=16;
		color[]={0.60000002,0.60000002,0.60000002,1};
		importance="1.2 * 16 * 0.05";
		coefMin=1;
		coefMax=4;
	};
};
class CfgLocationTypes
{
	class Name
	{
		name="keypoint";
		drawStyle="name";
		texture="#(argb,1,1,1)color(1,1,1,1)";
		color[]={1,1,1,1};
		size=0;
		font="gui/fonts/sdf_MetronBook24";
		textSize=0.029999999;
		shadow=0.1;
		importance=1;
	};
	class NameIcon
	{
		name="keypoint";
		drawStyle="icon";
		texture="#(argb,1,1,1)color(1,1,1,1)";
		color[]={1,1,1,1};
		size=0;
		font="gui/fonts/sdf_MetronBook24";
		textSize=0.029999999;
		shadow=0;
		importance=1;
	};
	class Capital: Name
	{
		color[]={1,1,1,1};
		textSize=0.059999999;
		importance=7;
	};
	class BigMilitary: Name
	{
		color[]={1,0.1,0.1,1};
		textSize=0.050000001;
		importance=6;
	};
	class City: Name
	{
		textSize=0.050000001;
		importance=6;
	};
	class MediumMilitary: Name
	{
		color[]={1,0.1,0.1,1};
		textSize=0.039999999;
		importance=5;
	};
	class SmallMilitary: Name
	{
		color[]={1,0.1,0.1,1};
		textSize=0.035;
		importance=5;
	};
	class Village: Name
	{
		textSize=0.039999999;
		importance=3;
	};
	class Local: Name
	{
		color[]={0.44,0.38,0.30000001,1};
		textSize=0.029999999;
	};
	class Marine: Name
	{
		color[]={0.050000001,0.40000001,0.80000001,0.80000001};
		textSize=0.029999999;
	};
	class FeedShack: NameIcon
	{
		texture="\VanillaPPMap\GUI\Textures\CustomMapIcons\feedshack.paa";
		importance=1;
		size=10;
	};
	class Deerstand: NameIcon
	{
		texture="\VanillaPPMap\GUI\Textures\CustomMapIcons\deerstand.paa";
		importance=1;
		size=10;
	};
	class Ruin: NameIcon
	{
		texture="\DZ\gear\navigation\data\map_ruin_ca.paa";
		textSize=0.029999999;
		importance=2;
		size=7;
	};
	class Camp: NameIcon
	{
		color[]={0.44,0.38,0.30000001,1};
		texture="\DZ\gear\navigation\data\map_camp_ca.paa";
		textSize=0.02;
		size=5;
	};
	class Hill: NameIcon
	{
		color[]={0.69999999,0.69999999,0.69999999,1};
		texture="\DZ\gear\navigation\data\map_hill_ca.paa";
		textSize=0.02;
		size=3;
	};
	class ViewPoint: NameIcon
	{
		color[]={0.77999997,0,0.050000001,0};
		texture="\DZ\gear\navigation\data\map_viewpoint_ca.paa";
		size=9;
	};
	class RockArea: NameIcon
	{
		color[]={0,0,0,1};
		texture="\DZ\gear\navigation\data\map_rock_ca.paa";
		size=9;
	};
	class RailroadStation: NameIcon
	{
		color[]={0,0,0,0};
		texture="\DZ\gear\navigation\data\map_station_ca.paa";
		size=9;
	};
	class IndustrialSite: NameIcon
	{
		color[]={0,0,0,1};
		texture="\DZ\gear\navigation\data\map_factory_ca.paa";
		size=9;
	};
	class LocalOffice: NameIcon
	{
		color[]={0.22,0.20999999,0.50999999,0};
		texture="\DZ\gear\navigation\data\map_govoffice_ca.paa";
		size=10;
	};
	class BorderCrossing: NameIcon
	{
		color[]={0.77999997,0,0.050000001,1};
		texture="\DZ\gear\navigation\data\map_border_cross_ca.paa";
		size=9;
	};
	class VegetationBroadleaf: NameIcon
	{
		color[]={0.25,0.40000001,0.2,1};
		texture="\DZ\gear\navigation\data\map_broadleaf_ca.paa";
		size=9;
	};
	class VegetationFir: NameIcon
	{
		color[]={0.25,0.40000001,0.2,1};
		texture="\DZ\gear\navigation\data\map_fir_ca.paa";
		size=9;
	};
	class VegetationPalm: NameIcon
	{
		color[]={0.25,0.40000001,0.2,1};
		texture="\DZ\gear\navigation\data\map_palm_ca.paa";
		size=9;
	};
	class VegetationVineyard: NameIcon
	{
		color[]={0.25,0.40000001,0.2,1};
		texture="\DZ\gear\navigation\data\map_vineyard_ca.paa";
		size=9;
	};
};