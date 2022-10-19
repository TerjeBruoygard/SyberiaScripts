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
		textSize=0.015;
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
		textSize=0.015;
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
		textSize=0.015;
	};
	class Marine: Name
	{
		color[]={0.050000001,0.40000001,0.80000001,0.80000001};
		textSize=0.015;
	};
	class Ruin: NameIcon
	{
		texture="\DZ\gear\navigation\data\map_ruin_ca.paa";
		textSize=0.035;
		importance=3;
		size=8;
	};
	class Camp: NameIcon
	{
		color[]={0.69800001,0.98000002,0.61900002,1};
		texture="\DZ\gear\navigation\data\map_camp_ca.paa";
		textSize=0.041999999;
		importance=3;
		size=9;
	};
	class Hill: NameIcon
	{
		color[]={0.69800001,0.98000002,0.61900002,1};
		texture="\DZ\gear\navigation\data\map_hill_ca.paa";
		textSize=0.041999999;
		importance=6;
		size=8;
	};
	class ViewPoint: NameIcon
	{
		color[]={0.69800001,0.98000002,0.61900002,1};
		texture="\DZ\gear\navigation\data\map_viewpoint_ca.paa";
		textSize=0.041999999;
		importance=6;
		size=8;
	};
	class RockArea: NameIcon
	{
		color[]={0.54100001,0.921,0.98400003,0.89999998};
		texture="\DZ\gear\navigation\data\map_rock_ca.paa";
		size=8;
	};
	class RailroadStation: NameIcon
	{
		color[]={0.54100001,0.921,0.98400003,0.89999998};
		texture="\DZ\gear\navigation\data\map_station_ca.paa";
		size=7;
	};
	class IndustrialSite: NameIcon
	{
		color[]={0.54100001,0.921,0.98400003,0.89999998};
		texture="\DZ\gear\navigation\data\map_factory_ca.paa";
		size=7;
	};
	class LocalOffice: NameIcon
	{
		color[]={0.54100001,0.921,0.98400003,0.89999998};
		texture="\DZ\gear\navigation\data\map_govoffice_ca.paa";
		size=7;
	};
	class BorderCrossing: NameIcon
	{
		color[]={0.54100001,0.921,0.98400003,0.89999998};
		texture="\DZ\gear\navigation\data\map_border_cross_ca.paa";
		size=7;
	};
	class MilitaryBase: Name
	{
		color[]={0.97000003,0.23899999,0.31400001,1};
		textSize=0.054000001;
		importance=5;
	};
	class MilitaryBaseShadow: MilitaryBase
	{
		color[]={0.87,0.87,0.87,0.69999999};
		textSize=0.056000002;
		importance=5;
	};
	class MilitaryOutpost: Name
	{
		color[]={0.97000003,0.23899999,0.31400001,1};
		textSize=0.048;
		importance=4;
	};
	class MilitaryOutpostShadow: MilitaryOutpost
	{
		color[]={0.87,0.87,0.87,0.69999999};
		textSize=0.050999999;
		importance=4;
	};
};
class RscMapControl
{
	scaleMin=0.0099999998;
	scaleMax=0.94999999;
	ptsPerSquareSea=8;
	ptsPerSquareTxt=10;
	ptsPerSquareCLn=10;
	ptsPerSquareExp=10;
	ptsPerSquareCost=10;
	ptsPerSquareFor=9;
	ptsPerSquareForEdge=12;
	ptsPerSquareRoad=4;
	ptsPerSquareObj=12;
	scaleDefault=0.41999999;
	maxSatelliteAlpha=1;
	alphaFadeStartScale=2;
	alphaFadeEndScale=2;
	userMapPath="";
	maxUserMapAlpha=0;
	alphaUserMapFadeStartScale=1;
	alphaUserMapFadeEndScale=1;
	showCountourInterval=1;
	colorBackground[]={0,0,0,0};
	colorSea[]={0.46599999,0.53299999,0.77600002,0.33000001};
	colorForest[]={0.30199999,0.64700001,0.208,0.050000001};
	colorForestBorder[]={0,0,0,0};
	colorRocks[]={0.54100001,0.54100001,0.54100001,0.40000001};
	colorRocksBorder[]={0,0,0,0};
	colorLevels[]={0.28600001,0.177,0.093999997,0.5};
	colorMainCountlines[]={0.57200003,0.354,0.18799999,0.5};
	colorCountlines[]={0.57200003,0.354,0.18799999,0};
	colorMainCountlinesWater[]={0.491,0.57700002,0.70200002,0.60000002};
	colorCountlinesWater[]={0.491,0.57700002,0.70200002,0.30000001};
	colorPowerLines[]={0.050000001,0.050000001,0.050000001,0.80000001};
	colorRailWay[]={0.60000002,0.15000001,0,0.94999999};
	colorNames[]={0.1,0.1,0.1,0.89999998};
	colorInactive[]={1,1,1,0};
	colorOutside[]={0,0,0,1};
	colorTracks[]={0.83999997,0.75999999,0.64999998,0.80000001};
	colorTracksFill[]={0.83999997,0.75999999,0.64999998,0.5};
	colorRoads[]={0.60000002,0.60000002,0.60000002,0.94999999};
	colorRoadsFill[]={1,1,1,0.85000002};
	colorMainRoads[]={0.89999998,0.5,0.30000001,0.94999999};
	colorMainRoadsFill[]={1,0.60000002,0.40000001,0.89999998};
	colorGrid[]={0.1,0.1,0.1,0.5};
	colorGridMap[]={0.1,0.1,0.1,0.5};
	colorTrails[]={0.83999997,0.75999999,0.64999998,0.2};
	colorTrailsFill[]={0.83999997,0.75999999,0.64999998,0.60000002};
	colorMountPoint[]={0.44,0.38,0.23,0.99000001};
	fontLabel="gui/fonts/sdf_MetronBook24";
	fontGrid="gui/fonts/sdf_MetronBook24";
	sizeExGrid=0.015;
	fontUnits="gui/fonts/sdf_MetronBook24";
	fontNames="gui/fonts/sdf_MetronBook24";
	sizeExNames=0.02;
	fontInfo="gui/fonts/sdf_MetronBook24";
	fontLevel="gui/fonts/sdf_MetronBook24";
	text="#(argb,8,8,3)color(0.95,0.95,0.95,0.95)";
	class Legend
	{
		x=0;
		y=0;
		w=0;
		h=0;
		font="gui/fonts/sdf_MetronBook24";
		sizeEx=0.02;
		colorBackground[]={1,1,1,0};
		color[]={0.1,0.1,0.1,0};
	};
	class Bush
	{
		icon="\dz\gear\navigation\data\map_bush_ca.paa";
		color[]={0.30199999,0.64700001,0.208,0.25};
		size=14;
		importance="0.2 * 10 * 0.05";
		coefMin=0.2;
		coefMax=2;
	};
	class SmallTree
	{
		icon="\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[]={0.30199999,0.64700001,0.208,0.25};
		size=12;
		importance="0.6 * 8 * 0.05";
		coefMin=0.2;
		coefMax=2;
	};
	class Tree
	{
		icon="\dz\gear\navigation\data\map_tree_ca.paa";
		color[]={0.30199999,0.64700001,0.208,0.25};
		size=12;
		importance="0.6 * 8 * 0.05";
		coefMin=0.2;
		coefMax=2;
	};
	class Store
	{
		icon="\dz\gear\navigation\data\map_store_ca.paa";
		color[]={1,1,1,0.60000002};
		size=18;
		importance="2 * 20 * 0.05";
		coefMin=0.1;
		coefMax=4;
	};
	class FireDep
	{
		icon="\dz\gear\navigation\data\map_firedep_ca.paa";
		color[]={0.764,0,0,0.60000002};
		size=18;
		importance="2 * 20 * 0.05";
		coefMin=0.2;
		coefMax=2;
	};
	class Rocks
	{
		icon="\dz\gear\navigation\data\map_rock_ca.paa";
		color[]={0.1,0.1,0.1,0.60000002};
		size=12;
		importance="0.5 * 12 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
};
class MapDefaults
{
	scaleMin=0.0099999998;
	scaleMax=0.94999999;
	ptsPerSquareSea=8;
	ptsPerSquareTxt=10;
	ptsPerSquareCLn=10;
	ptsPerSquareExp=10;
	ptsPerSquareCost=10;
	ptsPerSquareFor=9;
	ptsPerSquareForEdge=12;
	ptsPerSquareRoad=4;
	ptsPerSquareObj=12;
	scaleDefault=0.41999999;
	maxSatelliteAlpha=1;
	alphaFadeStartScale=2;
	alphaFadeEndScale=2;
	userMapPath="";
	maxUserMapAlpha=0;
	alphaUserMapFadeStartScale=1;
	alphaUserMapFadeEndScale=1;
	showCountourInterval=1;
	colorBackground[]={0,0,0,0};
	colorSea[]={0.46599999,0.53299999,0.77600002,0.33000001};
	colorForest[]={0.30199999,0.64700001,0.208,0.050000001};
	colorForestBorder[]={0,0,0,0};
	colorRocks[]={0.54100001,0.54100001,0.54100001,0.40000001};
	colorRocksBorder[]={0,0,0,0};
	colorLevels[]={0.28600001,0.177,0.093999997,0.5};
	colorMainCountlines[]={0.57200003,0.354,0.18799999,0.5};
	colorCountlines[]={0.57200003,0.354,0.18799999,0};
	colorMainCountlinesWater[]={0.491,0.57700002,0.70200002,0.60000002};
	colorCountlinesWater[]={0.491,0.57700002,0.70200002,0.30000001};
	colorPowerLines[]={0.050000001,0.050000001,0.050000001,0.80000001};
	colorRailWay[]={0.60000002,0.15000001,0,0.94999999};
	colorNames[]={0.1,0.1,0.1,0.89999998};
	colorInactive[]={1,1,1,0};
	colorOutside[]={0,0,0,1};
	colorTracks[]={0.83999997,0.75999999,0.64999998,0.80000001};
	colorTracksFill[]={0.83999997,0.75999999,0.64999998,0.5};
	colorRoads[]={0.60000002,0.60000002,0.60000002,0.94999999};
	colorRoadsFill[]={1,1,1,0.85000002};
	colorMainRoads[]={0.89999998,0.5,0.30000001,0.94999999};
	colorMainRoadsFill[]={1,0.60000002,0.40000001,0.89999998};
	colorGrid[]={0.1,0.1,0.1,0.5};
	colorGridMap[]={0.1,0.1,0.1,0.5};
	colorTrails[]={0.83999997,0.75999999,0.64999998,0.2};
	colorTrailsFill[]={0.83999997,0.75999999,0.64999998,0.60000002};
	colorMountPoint[]={0.44,0.38,0.23,0.99000001};
	fontLabel="gui/fonts/sdf_MetronBook24";
	fontGrid="gui/fonts/sdf_MetronBook24";
	sizeExGrid=0.015;
	fontUnits="gui/fonts/sdf_MetronBook24";
	fontNames="gui/fonts/sdf_MetronBook24";
	sizeExNames=0.02;
	fontInfo="gui/fonts/sdf_MetronBook24";
	fontLevel="gui/fonts/sdf_MetronBook24";
	text="#(argb,8,8,3)color(0.95,0.95,0.95,0.95)";
	class Legend
	{
		x=0;
		y=0;
		w=0;
		h=0;
		font="gui/fonts/sdf_MetronBook24";
		sizeEx=0.02;
		colorBackground[]={1,1,1,0};
		color[]={0.1,0.1,0.1,0};
	};
	class Bush
	{
		icon="\dz\gear\navigation\data\map_bush_ca.paa";
		color[]={0.30199999,0.64700001,0.208,0.25};
		size=14;
		importance="0.2 * 10 * 0.05";
		coefMin=0.2;
		coefMax=2;
	};
	class SmallTree
	{
		icon="\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[]={0.30199999,0.64700001,0.208,0.25};
		size=12;
		importance="0.6 * 8 * 0.05";
		coefMin=0.2;
		coefMax=2;
	};
	class Tree
	{
		icon="\dz\gear\navigation\data\map_tree_ca.paa";
		color[]={0.30199999,0.64700001,0.208,0.25};
		size=12;
		importance="0.6 * 8 * 0.05";
		coefMin=0.2;
		coefMax=2;
	};
	class Store
	{
		icon="\dz\gear\navigation\data\map_store_ca.paa";
		color[]={1,1,1,0.60000002};
		size=18;
		importance="2 * 20 * 0.05";
		coefMin=0.1;
		coefMax=4;
	};
	class FireDep
	{
		icon="\dz\gear\navigation\data\map_firedep_ca.paa";
		color[]={0.764,0,0,0.60000002};
		size=18;
		importance="2 * 20 * 0.05";
		coefMin=0.2;
		coefMax=2;
	};
	class Rocks
	{
		icon="\dz\gear\navigation\data\map_rock_ca.paa";
		color[]={0.1,0.1,0.1,0.60000002};
		size=12;
		importance="0.5 * 12 * 0.05";
		coefMin=0.25;
		coefMax=4;
	};
};