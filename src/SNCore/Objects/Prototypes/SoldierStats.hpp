#ifndef SOLDIERSTATS_HPP
#define SOLDIERSTATS_HPP

/* 
 * Infantry
 */

#define INFANTRY_AP 2
#define INFANTRY_COST 0
#define INFANTRY_NAME "Infantry"
#define INFANTRY_HEALTH 20
#define INFANTRY_ATKRANGE 2
#define INFANTRY_DMG 8
#define INFANTRY_ATKCOST 1
#define INF_VS_INF_MULTI 1.0
#define INF_VS_HEA_MULTI 1.0
#define INF_VS_ART_MULTI 1.5

/* 
 * Heavy
 */

#define HEAVY_AP 3
#define HEAVY_COST 0
#define HEAVY_NAME "Tank"
#define HEAVY_HEALTH 35
#define HEAVY_ATKRANGE 3
#define HEAVY_DMG 13
#define HEAVY_ATKCOST 2
#define HEA_VS_INF_MULTI 1.5
#define HEA_VS_HEA_MULTI 1.0
#define HEA_VS_ART_MULTI 1.0

/*
 * Artillery
 */

#define ARTILLERY_AP 2
#define ARTILLERY_COST 0
#define ARTILLERY_NAME "Artillery"
#define ARTILLERY_HEALTH 35
#define ARTILLERY_ATKRANGE 4
#define ARTILLERY_DMG 21
#define ARTILLERY_ATKCOST 2
#define ART_VS_INF_MULTI 1.0
#define ART_VS_HEA_MULTI 1.5
#define ART_VS_ART_MULTI 1.0

#endif